//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include "compiler/OutputHLSL.h"

#include "common/angleutils.h"
#include "common/utilities.h"
#include "compiler/debug.h"
#include "compiler/DetectDiscontinuity.h"
#include "compiler/InfoSink.h"
#include "compiler/SearchSymbol.h"
#include "compiler/UnfoldShortCircuit.h"
#include "compiler/HLSLLayoutEncoder.h"

#include <algorithm>
#include <cfloat>
#include <stdio.h>

namespace sh
{
// Integer to TString conversion
TString str(int i)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", i);
    return buffer;
}

TString OutputHLSL::TextureFunction::name() const
{
    TString name = "gl_texture";

    if (sampler == EbtSampler2D ||
        sampler == EbtISampler2D ||
        sampler == EbtUSampler2D)
    {
        name += "2D";
    }
    else if (sampler == EbtSampler3D ||
             sampler == EbtISampler3D ||
             sampler == EbtUSampler3D)
    {
        name += "3D";
    }
    else if (sampler == EbtSamplerCube ||
             sampler == EbtISamplerCube ||
             sampler == EbtUSamplerCube)
    {
        name += "Cube";
    }
    else UNREACHABLE();

    if (proj)
    {
        name += "Proj";
    }

    switch(mipmap)
    {
      case IMPLICIT:                 break;
      case BIAS:                     break;
      case LOD:      name += "Lod";  break;
      case LOD0:     name += "Lod0"; break;
      default: UNREACHABLE();
    }

    return name + "(";
}

bool OutputHLSL::TextureFunction::operator<(const TextureFunction &rhs) const
{
    if (sampler < rhs.sampler) return true;
    if (coords < rhs.coords)   return true;
    if (!proj && rhs.proj)     return true;
    if (mipmap < rhs.mipmap)   return true;

    return false;
}

OutputHLSL::OutputHLSL(TParseContext &context, const ShBuiltInResources& resources, ShShaderOutput outputType)
    : TIntermTraverser(true, true, true), mContext(context), mOutputType(outputType)
{
    mUnfoldShortCircuit = new UnfoldShortCircuit(context, this);
    mInsideFunction = false;

    mUsesFragColor = false;
    mUsesFragData = false;
    mUsesDepthRange = false;
    mUsesFragCoord = false;
    mUsesPointCoord = false;
    mUsesFrontFacing = false;
    mUsesPointSize = false;
    mUsesXor = false;
    mUsesMod1 = false;
    mUsesMod2v = false;
    mUsesMod2f = false;
    mUsesMod3v = false;
    mUsesMod3f = false;
    mUsesMod4v = false;
    mUsesMod4f = false;
    mUsesFaceforward1 = false;
    mUsesFaceforward2 = false;
    mUsesFaceforward3 = false;
    mUsesFaceforward4 = false;

    for (unsigned int col = 0; col <= 4; col++)
    {
        for (unsigned int row = 0; row <= 4; row++)
        {
            mUsesEqualMat[col][row] = false;
        }
    }
    mUsesEqualVec2 = false;
    mUsesEqualVec3 = false;
    mUsesEqualVec4 = false;
    mUsesEqualIVec2 = false;
    mUsesEqualIVec3 = false;
    mUsesEqualIVec4 = false;
    mUsesEqualUVec2 = false;
    mUsesEqualUVec3 = false;
    mUsesEqualUVec4 = false;
    mUsesEqualBVec2 = false;
    mUsesEqualBVec3 = false;
    mUsesEqualBVec4 = false;
    mUsesAtan2_1 = false;
    mUsesAtan2_2 = false;
    mUsesAtan2_3 = false;
    mUsesAtan2_4 = false;

    mNumRenderTargets = resources.EXT_draw_buffers ? resources.MaxDrawBuffers : 1;

    mScopeDepth = 0;

    mUniqueIndex = 0;

    mContainsLoopDiscontinuity = false;
    mOutputLod0Function = false;
    mInsideDiscontinuousLoop = false;

    mExcessiveLoopIndex = NULL;

    if (mOutputType == SH_HLSL9_OUTPUT)
    {
        if (mContext.shaderType == SH_FRAGMENT_SHADER)
        {
            mUniformRegister = 3;   // Reserve registers for dx_DepthRange, dx_ViewCoords and dx_DepthFront
        }
        else
        {
            mUniformRegister = 2;   // Reserve registers for dx_DepthRange and dx_ViewAdjust
        }
    }
    else
    {
        mUniformRegister = 0;
    }

    mSamplerRegister = 0;
    mInterfaceBlockRegister = 2; // Reserve registers for the default uniform block and driver constants
    mPaddingCounter = 0;
}

OutputHLSL::~OutputHLSL()
{
    delete mUnfoldShortCircuit;
}

void OutputHLSL::output()
{
    mContainsLoopDiscontinuity = mContext.shaderType == SH_FRAGMENT_SHADER && containsLoopDiscontinuity(mContext.treeRoot);

    mContext.treeRoot->traverse(this);   // Output the body first to determine what has to go in the header
    header();

    mContext.infoSink().obj << mHeader.c_str();
    mContext.infoSink().obj << mBody.c_str();
}

TInfoSinkBase &OutputHLSL::getBodyStream()
{
    return mBody;
}

const ActiveUniforms &OutputHLSL::getUniforms()
{
    return mActiveUniforms;
}

const ActiveInterfaceBlocks &OutputHLSL::getInterfaceBlocks() const
{
    return mActiveInterfaceBlocks;
}

const ActiveShaderVariables &OutputHLSL::getOutputVariables() const
{
    return mActiveOutputVariables;
}

const ActiveShaderVariables &OutputHLSL::getAttributes() const
{
    return mActiveAttributes;
}

int OutputHLSL::vectorSize(const TType &type) const
{
    int elementSize = type.isMatrix() ? type.getCols() : 1;
    int arraySize = type.isArray() ? type.getArraySize() : 1;

    return elementSize * arraySize;
}

TString OutputHLSL::interfaceBlockUniformName(const TType &interfaceBlockType, const TType &uniformType)
{
    if (interfaceBlockType.hasInstanceName())
    {
        return interfaceBlockType.getTypeName() + "." + uniformType.getFieldName();
    }
    else
    {
        return uniformType.getFieldName();
    }
}

TString OutputHLSL::decoratePrivate(const TString &privateText)
{
    return "dx_" + privateText;
}

TString OutputHLSL::interfaceBlockStructName(const TType &interfaceBlockType)
{
    return decoratePrivate(interfaceBlockType.getTypeName()) + "_type";
}

TString OutputHLSL::interfaceBlockInstanceString(const TType& interfaceBlockType, unsigned int arrayIndex)
{
    if (!interfaceBlockType.hasInstanceName())
    {
        return "";
    }
    else if (interfaceBlockType.isArray())
    {
        return decoratePrivate(interfaceBlockType.getInstanceName()) + "_" + str(arrayIndex);
    }
    else
    {
        return decorate(interfaceBlockType.getInstanceName());
    }
}

TString OutputHLSL::interfaceBlockMemberTypeString(const TType &memberType)
{
    const TLayoutMatrixPacking matrixPacking = memberType.getLayoutQualifier().matrixPacking;
    ASSERT(matrixPacking != EmpUnspecified);

    if (memberType.isMatrix())
    {
        // Use HLSL row-major packing for GLSL column-major matrices
        const TString &matrixPackString = (matrixPacking == EmpRowMajor ? "column_major" : "row_major");
        return matrixPackString + " " + typeString(memberType);
    }
    else if (memberType.getBasicType() == EbtStruct)
    {
        // Use HLSL row-major packing for GLSL column-major matrices
        return structureTypeName(memberType, matrixPacking == EmpColumnMajor);
    }
    else
    {
        return typeString(memberType);
    }
}

TString OutputHLSL::std140PrePaddingString(const TType &type, int *elementIndex)
{
    if (type.getBasicType() == EbtStruct || type.isMatrix() || type.isArray())
    {
        // no padding needed, HLSL will align the field to a new register
        *elementIndex = 0;
        return "";
    }

    const GLenum glType = glVariableType(type);
    const int numComponents = gl::UniformComponentCount(glType);

    if (numComponents >= 4)
    {
        // no padding needed, HLSL will align the field to a new register
        *elementIndex = 0;
        return "";
    }

    if (*elementIndex + numComponents > 4)
    {
        // no padding needed, HLSL will align the field to a new register
        *elementIndex = numComponents;
        return "";
    }

    TString padding;

    const int alignment = numComponents == 3 ? 4 : numComponents;
    const int paddingOffset = (*elementIndex % alignment);

    if (paddingOffset != 0)
    {
        // padding is neccessary
        for (int paddingIndex = paddingOffset; paddingIndex < alignment; paddingIndex++)
        {
            padding += "    float pad_" + str(mPaddingCounter++) + ";\n";
        }

        *elementIndex += (alignment - paddingOffset);
    }

    *elementIndex += numComponents;
    *elementIndex %= 4;

    return padding;
}

TString OutputHLSL::std140PostPaddingString(const TType &type)
{
    if (!type.isMatrix() && !type.isArray())
    {
        return "";
    }

    const GLenum glType = glVariableType(type);
    int numComponents = 0;

    if (type.isMatrix())
    {
        const bool isRowMajorMatrix = (type.getLayoutQualifier().matrixPacking == EmpRowMajor);
        numComponents = gl::MatrixComponentCount(glType, isRowMajorMatrix);
    }
    else
    {
        numComponents = gl::UniformComponentCount(glType);
    }

    TString padding;
    for (int paddingOffset = numComponents; paddingOffset < 4; paddingOffset++)
    {
        padding += "    float pad_" + str(mPaddingCounter++) + ";\n";
    }
    return padding;
}

TString OutputHLSL::interfaceBlockMemberString(const TTypeList &typeList, TLayoutBlockStorage blockStorage)
{
    TString hlsl;

    int elementIndex = 0;

    for (unsigned int typeIndex = 0; typeIndex < typeList.size(); typeIndex++)
    {
        const TType &memberType = *typeList[typeIndex].type;

        if (blockStorage == EbsStd140)
        {
            if (memberType.getBasicType() == EbtStruct)
            {
                UNIMPLEMENTED();
            }
            else
            {
                // 2 and 3 component vector types in some cases need pre-padding
                hlsl += std140PrePaddingString(memberType, &elementIndex);
            }
        }

        hlsl += "    " + interfaceBlockMemberTypeString(memberType) +
                " " + decorate(memberType.getFieldName()) + arrayString(memberType) + ";\n";

        // must pad out after matrices and arrays, where HLSL usually allows itself room to pack stuff
        if (blockStorage == EbsStd140)
        {
            hlsl += std140PostPaddingString(memberType);
        }
    }

    return hlsl;
}

TString OutputHLSL::interfaceBlockStructString(const TType &interfaceBlockType)
{
    const TTypeList &typeList = *interfaceBlockType.getStruct();
    const TLayoutBlockStorage blockStorage = interfaceBlockType.getLayoutQualifier().blockStorage;

    return "struct " + interfaceBlockStructName(interfaceBlockType) + "\n"
           "{\n" +
           interfaceBlockMemberString(typeList, blockStorage) +
           "};\n\n";
}

TString OutputHLSL::interfaceBlockString(const TType &interfaceBlockType, unsigned int registerIndex, unsigned int arrayIndex)
{
    const TString &arrayIndexString =  (arrayIndex != GL_INVALID_INDEX ? decorate(str(arrayIndex)) : "");
    const TString &blockName = interfaceBlockType.getTypeName() + arrayIndexString;
    TString hlsl;

    hlsl += "cbuffer " + blockName + " : register(b" + str(registerIndex) + ")\n"
            "{\n";

    if (interfaceBlockType.hasInstanceName())
    {
        hlsl += "    " + interfaceBlockStructName(interfaceBlockType) + " " + interfaceBlockInstanceString(interfaceBlockType, arrayIndex) + ";\n";
    }
    else
    {
        const TTypeList &typeList = *interfaceBlockType.getStruct();
        const TLayoutBlockStorage blockStorage = interfaceBlockType.getLayoutQualifier().blockStorage;
        hlsl += interfaceBlockMemberString(typeList, blockStorage);
    }

    hlsl += "};\n\n";

    return hlsl;
}

// Use the same layout for packed and shared
void setBlockLayout(InterfaceBlock *interfaceBlock, BlockLayoutType newLayout)
{
    interfaceBlock->layout = newLayout;
    interfaceBlock->blockInfo.clear();

    switch (newLayout)
    {
      case BLOCKLAYOUT_SHARED:
      case BLOCKLAYOUT_PACKED:
        {
            HLSLBlockEncoder hlslEncoder(&interfaceBlock->blockInfo);
            hlslEncoder.encodeFields(interfaceBlock->activeUniforms);
            interfaceBlock->dataSize = hlslEncoder.getBlockSize();
        }
        break;

      case BLOCKLAYOUT_STANDARD:
        {
            Std140BlockEncoder stdEncoder(&interfaceBlock->blockInfo);
            stdEncoder.encodeFields(interfaceBlock->activeUniforms);
            interfaceBlock->dataSize = stdEncoder.getBlockSize();
        }
        break;

      default:
        UNREACHABLE();
        break;
    }
}

BlockLayoutType convertBlockLayoutType(TLayoutBlockStorage blockStorage)
{
    switch (blockStorage)
    {
      case EbsPacked: return BLOCKLAYOUT_PACKED;
      case EbsShared: return BLOCKLAYOUT_SHARED;
      case EbsStd140: return BLOCKLAYOUT_STANDARD;
      default: UNREACHABLE(); return BLOCKLAYOUT_SHARED;
    }
}

void OutputHLSL::header()
{
    TInfoSinkBase &out = mHeader;

    TString uniforms;
    TString interfaceBlocks;
    TString varyings;
    TString attributes;

    for (ReferencedSymbols::const_iterator uniform = mReferencedUniforms.begin(); uniform != mReferencedUniforms.end(); uniform++)
    {
        const TType &type = uniform->second->getType();
        const TString &name = uniform->second->getSymbol();

        if (mOutputType == SH_HLSL11_OUTPUT && IsSampler(type.getBasicType()))   // Also declare the texture
        {
            int index = samplerRegister(mReferencedUniforms[name]);

            uniforms += "uniform SamplerState sampler_" + decorateUniform(name, type) + arrayString(type) + 
                        " : register(s" + str(index) + ");\n";

            uniforms += "uniform " + textureString(type) + " texture_" + decorateUniform(name, type) + arrayString(type) +
                        " : register(t" + str(index) + ");\n";
        }
        else
        {
            uniforms += "uniform " + typeString(type) + " " + decorateUniform(name, type) + arrayString(type) + 
                        " : register(" + registerString(mReferencedUniforms[name]) + ");\n";
        }
    }

    for (ReferencedSymbols::const_iterator interfaceBlockIt = mReferencedInterfaceBlocks.begin(); interfaceBlockIt != mReferencedInterfaceBlocks.end(); interfaceBlockIt++)
    {
        const TType &nodeType = interfaceBlockIt->second->getType();
        const TType &interfaceBlockType = nodeType.isInterfaceBlockMember() ? *nodeType.getInterfaceBlockType() : nodeType;
        const TString &blockName = interfaceBlockType.getTypeName();
        const TTypeList &typeList = *interfaceBlockType.getStruct();

        const unsigned int arraySize = interfaceBlockType.isArray() ? interfaceBlockType.getArraySize() : 0;
        sh::InterfaceBlock interfaceBlock(blockName.c_str(), arraySize, mInterfaceBlockRegister);
        for (unsigned int typeIndex = 0; typeIndex < typeList.size(); typeIndex++)
        {
            const TType &memberType = *typeList[typeIndex].type;
            const TString &fullUniformName = interfaceBlockUniformName(interfaceBlockType, memberType);
            declareUniformToList(memberType, fullUniformName, typeIndex, interfaceBlock.activeUniforms);
        }

        mInterfaceBlockRegister += std::max(1u, interfaceBlock.arraySize);

        BlockLayoutType blockLayoutType = convertBlockLayoutType(interfaceBlockType.getLayoutQualifier().blockStorage);
        setBlockLayout(&interfaceBlock, blockLayoutType);
        mActiveInterfaceBlocks.push_back(interfaceBlock);

        if (interfaceBlockType.hasInstanceName())
        {
            interfaceBlocks += interfaceBlockStructString(interfaceBlockType);
        }

        if (arraySize > 0)
        {
            for (unsigned int arrayIndex = 0; arrayIndex < arraySize; arrayIndex++)
            {
                interfaceBlocks += interfaceBlockString(interfaceBlockType, interfaceBlock.registerIndex + arrayIndex, arrayIndex);
            }
        }
        else
        {
            interfaceBlocks += interfaceBlockString(interfaceBlockType, interfaceBlock.registerIndex, GL_INVALID_INDEX);
        }
    }

    for (ReferencedSymbols::const_iterator varying = mReferencedVaryings.begin(); varying != mReferencedVaryings.end(); varying++)
    {
        const TType &type = varying->second->getType();
        const TString &name = varying->second->getSymbol();

        // Program linking depends on this exact format
        varyings += "static " + interpolationString(type.getQualifier()) + " " + typeString(type) + " " +
                    decorate(name) + arrayString(type) + " = " + initializer(type) + ";\n";
    }

    for (ReferencedSymbols::const_iterator attribute = mReferencedAttributes.begin(); attribute != mReferencedAttributes.end(); attribute++)
    {
        const TType &type = attribute->second->getType();
        const TString &name = attribute->second->getSymbol();

        attributes += "static " + typeString(type) + " " + decorate(name) + arrayString(type) + " = " + initializer(type) + ";\n";

        ShaderVariable shaderVar(glVariableType(type), glVariablePrecision(type), name.c_str(),
                                 (unsigned int)type.getArraySize(), type.getLayoutQualifier().location);
        mActiveAttributes.push_back(shaderVar);
    }

    for (StructDeclarations::iterator structDeclaration = mStructDeclarations.begin(); structDeclaration != mStructDeclarations.end(); structDeclaration++)
    {
        out << *structDeclaration;
    }

    for (Constructors::iterator constructor = mConstructors.begin(); constructor != mConstructors.end(); constructor++)
    {
        out << *constructor;
    }

    if (mContext.shaderType == SH_FRAGMENT_SHADER)
    {
        TExtensionBehavior::const_iterator iter = mContext.extensionBehavior().find("GL_EXT_draw_buffers");
        const bool usingMRTExtension = (iter != mContext.extensionBehavior().end() && (iter->second == EBhEnable || iter->second == EBhRequire));

        out << "// Varyings\n";
        out <<  varyings;
        out << "\n";

        if (mContext.getShaderVersion() >= 300)
        {
            for (auto outputVariableIt = mReferencedOutputVariables.begin(); outputVariableIt != mReferencedOutputVariables.end(); outputVariableIt++)
            {
                const TString &variableName = outputVariableIt->first;
                const TType &variableType = outputVariableIt->second->getType();
                const TLayoutQualifier &layoutQualifier = variableType.getLayoutQualifier();

                out << "static " + typeString(variableType) + " out_" + variableName + arrayString(variableType) +
                       " = " + initializer(variableType) + ";\n";

                ShaderVariable outputVar(glVariableType(variableType), glVariablePrecision(variableType), variableName.c_str(),
                                         (unsigned int)variableType.getArraySize(), layoutQualifier.location);
                mActiveOutputVariables.push_back(outputVar);
            }
        }
        else
        {
            const unsigned int numColorValues = usingMRTExtension ? mNumRenderTargets : 1;

            out << "static float4 gl_Color[" << numColorValues << "] =\n"
                   "{\n";
            for (unsigned int i = 0; i < numColorValues; i++)
            {
                out << "    float4(0, 0, 0, 0)";
                if (i + 1 != numColorValues)
                {
                    out << ",";
                }
                out << "\n";
            }

            out << "};\n";
        }

        if (mUsesFragCoord)
        {
            out << "static float4 gl_FragCoord = float4(0, 0, 0, 0);\n";
        }

        if (mUsesPointCoord)
        {
            out << "static float2 gl_PointCoord = float2(0.5, 0.5);\n";
        }

        if (mUsesFrontFacing)
        {
            out << "static bool gl_FrontFacing = false;\n";
        }

        out << "\n";

        if (mUsesDepthRange)
        {
            out << "struct gl_DepthRangeParameters\n"
                   "{\n"
                   "    float near;\n"
                   "    float far;\n"
                   "    float diff;\n"
                   "};\n"
                   "\n";
        }

        if (mOutputType == SH_HLSL11_OUTPUT)
        {
            out << "cbuffer DriverConstants : register(b1)\n"
                   "{\n";

            if (mUsesDepthRange)
            {
                out << "    float3 dx_DepthRange : packoffset(c0);\n";
            }

            if (mUsesFragCoord)
            {
                out << "    float4 dx_ViewCoords : packoffset(c1);\n";
            }

            if (mUsesFragCoord || mUsesFrontFacing)
            {
                out << "    float3 dx_DepthFront : packoffset(c2);\n";
            }

            out << "};\n";
        }
        else
        {
            if (mUsesDepthRange)
            {
                out << "uniform float3 dx_DepthRange : register(c0);";
            }

            if (mUsesFragCoord)
            {
                out << "uniform float4 dx_ViewCoords : register(c1);\n";
            }

            if (mUsesFragCoord || mUsesFrontFacing)
            {
                out << "uniform float3 dx_DepthFront : register(c2);\n";
            }
        }

        out << "\n";

        if (mUsesDepthRange)
        {
            out << "static gl_DepthRangeParameters gl_DepthRange = {dx_DepthRange.x, dx_DepthRange.y, dx_DepthRange.z};\n"
                   "\n";
        }
        
        out <<  uniforms;
        out << "\n";

        if (!interfaceBlocks.empty())
        {
            out << interfaceBlocks;
            out << "\n";
        }

        if (usingMRTExtension && mNumRenderTargets > 1)
        {
            out << "#define GL_USES_MRT\n";
        }

        if (mUsesFragColor)
        {
            out << "#define GL_USES_FRAG_COLOR\n";
        }

        if (mUsesFragData)
        {
            out << "#define GL_USES_FRAG_DATA\n";
        }
    }
    else   // Vertex shader
    {
        out << "// Attributes\n";
        out <<  attributes;
        out << "\n"
               "static float4 gl_Position = float4(0, 0, 0, 0);\n";
        
        if (mUsesPointSize)
        {
            out << "static float gl_PointSize = float(1);\n";
        }

        out << "\n"
               "// Varyings\n";
        out <<  varyings;
        out << "\n";

        if (mUsesDepthRange)
        {
            out << "struct gl_DepthRangeParameters\n"
                   "{\n"
                   "    float near;\n"
                   "    float far;\n"
                   "    float diff;\n"
                   "};\n"
                   "\n";
        }

        if (mOutputType == SH_HLSL11_OUTPUT)
        {
            if (mUsesDepthRange)
            {
                out << "cbuffer DriverConstants : register(b1)\n"
                       "{\n"
                       "    float3 dx_DepthRange : packoffset(c0);\n"
                       "};\n"
                       "\n";
            }
        }
        else
        {
            if (mUsesDepthRange)
            {
                out << "uniform float3 dx_DepthRange : register(c0);\n";
            }

            out << "uniform float4 dx_ViewAdjust : register(c1);\n"
                   "\n";
        }

        if (mUsesDepthRange)
        {
            out << "static gl_DepthRangeParameters gl_DepthRange = {dx_DepthRange.x, dx_DepthRange.y, dx_DepthRange.z};\n"
                   "\n";
        }

        out << uniforms;
        out << "\n";
        
        if (!interfaceBlocks.empty())
        {
            out << interfaceBlocks;
            out << "\n";
        }
    }

    for (TextureFunctionSet::const_iterator textureFunction = mUsesTexture.begin(); textureFunction != mUsesTexture.end(); textureFunction++)
    {
        // Return type
        switch(textureFunction->sampler)
        {
          case EbtSampler2D:    out << "float4 "; break;
          case EbtSampler3D:    out << "float4 "; break;
          case EbtSamplerCube:  out << "float4 "; break;
          case EbtISampler2D:   out << "int4 ";   break;
          case EbtISampler3D:   out << "int4 ";   break;
          case EbtISamplerCube: out << "int4 ";   break;
          case EbtUSampler2D:   out << "uint4 ";  break;
          case EbtUSampler3D:   out << "uint4 ";  break;
          case EbtUSamplerCube: out << "uint4 ";  break;
          default: UNREACHABLE();
        }

        // Function name
        out << textureFunction->name();

        // Argument list
        int hlslCoords = 4;

        if (mOutputType == SH_HLSL9_OUTPUT)
        {
            switch(textureFunction->sampler)
            {
              case EbtSampler2D:   out << "sampler2D s";   hlslCoords = 2; break;
              case EbtSamplerCube: out << "samplerCUBE s"; hlslCoords = 3; break;
              default: UNREACHABLE();
            }

            switch(textureFunction->mipmap)
            {
              case TextureFunction::IMPLICIT:                 break;
              case TextureFunction::BIAS:     hlslCoords = 4; break;
              case TextureFunction::LOD:      hlslCoords = 4; break;
              case TextureFunction::LOD0:     hlslCoords = 4; break;
              default: UNREACHABLE();
            }
        }
        else if (mOutputType == SH_HLSL11_OUTPUT)
        {
            switch(textureFunction->sampler)
            {
              case EbtSampler2D:    out << "Texture2D x, SamplerState s";          hlslCoords = 2; break;
              case EbtSampler3D:    out << "Texture3D x, SamplerState s";          hlslCoords = 3; break;
              case EbtSamplerCube:  out << "TextureCube x, SamplerState s";        hlslCoords = 3; break;
              case EbtISampler2D:   out << "Texture2D<int4> x, SamplerState s";    hlslCoords = 2; break;
              case EbtISampler3D:   out << "Texture3D<int4> x, SamplerState s";    hlslCoords = 3; break;
              case EbtISamplerCube: out << "TextureCube<int4> x, SamplerState s";  hlslCoords = 3; break;
              case EbtUSampler2D:   out << "Texture2D<uint4> x, SamplerState s";   hlslCoords = 2; break;
              case EbtUSampler3D:   out << "Texture3D<uint4> x, SamplerState s";   hlslCoords = 3; break;
              case EbtUSamplerCube: out << "TextureCube<uint4> x, SamplerState s"; hlslCoords = 3; break;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();

        switch(textureFunction->coords)
        {
          case 2: out << ", float2 t"; break;
          case 3: out << ", float3 t"; break;
          case 4: out << ", float4 t"; break;
          default: UNREACHABLE();
        }

        switch(textureFunction->mipmap)
        {
          case TextureFunction::IMPLICIT:                        break;
          case TextureFunction::BIAS:     out << ", float bias"; break;
          case TextureFunction::LOD:      out << ", float lod";  break;
          case TextureFunction::LOD0:                            break;
          default: UNREACHABLE();
        }

        out << ")\n"
               "{\n"
               "    return ";

        // HLSL intrinsic
        if (mOutputType == SH_HLSL9_OUTPUT)
        {
            switch(textureFunction->sampler)
            {
              case EbtSampler2D:   out << "tex2D";   break;
              case EbtSamplerCube: out << "texCUBE"; break;
              default: UNREACHABLE();
            }
        }
        else if (mOutputType == SH_HLSL11_OUTPUT)
        {
            out << "x.Sample";
        }
        else UNREACHABLE();

        if (mOutputType == SH_HLSL9_OUTPUT)
        {
            switch(textureFunction->mipmap)
            {
              case TextureFunction::IMPLICIT: out << "(s, ";     break;
              case TextureFunction::BIAS:     out << "bias(s, "; break;
              case TextureFunction::LOD:      out << "lod(s, ";  break;
              case TextureFunction::LOD0:     out << "lod(s, ";  break;
              default: UNREACHABLE();
            }
        }
        else if (mOutputType == SH_HLSL11_OUTPUT)
        {
            switch(textureFunction->mipmap)
            {
              case TextureFunction::IMPLICIT: out << "(s, ";      break;
              case TextureFunction::BIAS:     out << "Bias(s, ";  break;
              case TextureFunction::LOD:      out << "Level(s, "; break;
              case TextureFunction::LOD0:     out << "Level(s, "; break;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();

        switch(hlslCoords)
        {
          case 2: out << "float2("; break;
          case 3: out << "float3("; break;
          case 4: out << "float4("; break;
          default: UNREACHABLE();
        }

        TString proj = "";
        
        if (textureFunction->proj)
        {
            switch(textureFunction->coords)
            {
              case 3: proj = " / t.z"; break;
              case 4: proj = " / t.w"; break;
              default: UNREACHABLE();
            }
        }

        out << "t.x" + proj + ", t.y" + proj;

        if (mOutputType == SH_HLSL9_OUTPUT)
        {
            if (hlslCoords >= 3)
            {
                if (textureFunction->coords < 3)
                {
                    out << ", 0";
                }
                else
                {
                    out << ", t.z" + proj;
                }
            }

            if (hlslCoords == 4)
            {
                switch(textureFunction->mipmap)
                {
                  case TextureFunction::BIAS: out << ", bias"; break;
                  case TextureFunction::LOD:  out << ", lod";  break;
                  case TextureFunction::LOD0: out << ", 0";    break;
                  default: UNREACHABLE();
                }
            }

            out << "));\n";
        }
        else if (mOutputType == SH_HLSL11_OUTPUT)
        {
            if (hlslCoords >= 3)
            {
                out << ", t.z" + proj;
            }

            switch(textureFunction->mipmap)
            {
              case TextureFunction::IMPLICIT: out << "));";       break;
              case TextureFunction::BIAS:     out << "), bias);"; break;
              case TextureFunction::LOD:      out << "), lod);";  break;
              case TextureFunction::LOD0:     out << "), 0);";    break;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();

        out << "}\n"
               "\n";
    }

    if (mUsesFragCoord)
    {
        out << "#define GL_USES_FRAG_COORD\n";
    }

    if (mUsesPointCoord)
    {
        out << "#define GL_USES_POINT_COORD\n";
    }

    if (mUsesFrontFacing)
    {
        out << "#define GL_USES_FRONT_FACING\n";
    }

    if (mUsesPointSize)
    {
        out << "#define GL_USES_POINT_SIZE\n";
    }

    if (mUsesDepthRange)
    {
        out << "#define GL_USES_DEPTH_RANGE\n";
    }

    if (mUsesXor)
    {
        out << "bool xor(bool p, bool q)\n"
               "{\n"
               "    return (p || q) && !(p && q);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod1)
    {
        out << "float mod(float x, float y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod2v)
    {
        out << "float2 mod(float2 x, float2 y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod2f)
    {
        out << "float2 mod(float2 x, float y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }
    
    if (mUsesMod3v)
    {
        out << "float3 mod(float3 x, float3 y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod3f)
    {
        out << "float3 mod(float3 x, float y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod4v)
    {
        out << "float4 mod(float4 x, float4 y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesMod4f)
    {
        out << "float4 mod(float4 x, float y)\n"
               "{\n"
               "    return x - y * floor(x / y);\n"
               "}\n"
               "\n";
    }

    if (mUsesFaceforward1)
    {
        out << "float faceforward(float N, float I, float Nref)\n"
               "{\n"
               "    if(dot(Nref, I) >= 0)\n"
               "    {\n"
               "        return -N;\n"
               "    }\n"
               "    else\n"
               "    {\n"
               "        return N;\n"
               "    }\n"
               "}\n"
               "\n";
    }

    if (mUsesFaceforward2)
    {
        out << "float2 faceforward(float2 N, float2 I, float2 Nref)\n"
               "{\n"
               "    if(dot(Nref, I) >= 0)\n"
               "    {\n"
               "        return -N;\n"
               "    }\n"
               "    else\n"
               "    {\n"
               "        return N;\n"
               "    }\n"
               "}\n"
               "\n";
    }

    if (mUsesFaceforward3)
    {
        out << "float3 faceforward(float3 N, float3 I, float3 Nref)\n"
               "{\n"
               "    if(dot(Nref, I) >= 0)\n"
               "    {\n"
               "        return -N;\n"
               "    }\n"
               "    else\n"
               "    {\n"
               "        return N;\n"
               "    }\n"
               "}\n"
               "\n";
    }

    if (mUsesFaceforward4)
    {
        out << "float4 faceforward(float4 N, float4 I, float4 Nref)\n"
               "{\n"
               "    if(dot(Nref, I) >= 0)\n"
               "    {\n"
               "        return -N;\n"
               "    }\n"
               "    else\n"
               "    {\n"
               "        return N;\n"
               "    }\n"
               "}\n"
               "\n";
    }

    for (unsigned int cols = 2; cols <= 4; cols++)
    {
        for (unsigned int rows = 2; rows <= 4; rows++)
        {
            if (mUsesEqualMat[cols][rows])
            {
                TString matrixType = "float" + str(cols) + "x" + str(rows);

                out << "bool equal(" + matrixType + " m, " + matrixType + " n)\n"
                       "{\n";

                for (unsigned int row = 0; row < rows; row++)
                {
                    if (row == 0)
                    {
                        out << "    return ";
                    }
                    else
                    {
                        out << "           ";
                    }

                    for (unsigned int col = 0; col < cols; col++)
                    {
                        TString index = "[" + str(col) + "][" + str(row) + "]";
                        out << "m" + index + " == n" + index;

                        if (col == cols-1 && row == rows-1)
                        {
                            out << ";\n";
                        }
                        else if (col == cols-1)
                        {
                            out << " &&\n";
                        }
                        else
                        {
                            out << " && ";
                        }
                    }
                }

                out << "}\n";
            }
        }
    }

    if (mUsesEqualVec2)
    {
        out << "bool equal(float2 v, float2 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y;\n"
               "}\n";
    }

    if (mUsesEqualVec3)
    {
        out << "bool equal(float3 v, float3 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z;\n"
               "}\n";
    }

    if (mUsesEqualVec4)
    {
        out << "bool equal(float4 v, float4 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z && v.w == u.w;\n"
               "}\n";
    }

    if (mUsesEqualIVec2)
    {
        out << "bool equal(int2 v, int2 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y;\n"
               "}\n";
    }

    if (mUsesEqualIVec3)
    {
        out << "bool equal(int3 v, int3 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z;\n"
               "}\n";
    }

    if (mUsesEqualIVec4)
    {
        out << "bool equal(int4 v, int4 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z && v.w == u.w;\n"
               "}\n";
    }

    if (mUsesEqualUVec2)
    {
        out << "bool equal(uint2 v, uint2 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y;\n"
               "}\n";
    }

    if (mUsesEqualUVec3)
    {
        out << "bool equal(uint3 v, uint3 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z;\n"
               "}\n";
    }

    if (mUsesEqualUVec4)
    {
        out << "bool equal(uint4 v, uint4 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z && v.w == u.w;\n"
               "}\n";
    }

    if (mUsesEqualBVec2)
    {
        out << "bool equal(bool2 v, bool2 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y;\n"
               "}\n";
    }

    if (mUsesEqualBVec3)
    {
        out << "bool equal(bool3 v, bool3 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z;\n"
               "}\n";
    }

    if (mUsesEqualBVec4)
    {
        out << "bool equal(bool4 v, bool4 u)\n"
               "{\n"
               "    return v.x == u.x && v.y == u.y && v.z == u.z && v.w == u.w;\n"
               "}\n";
    }

    if (mUsesAtan2_1)
    {
        out << "float atanyx(float y, float x)\n"
               "{\n"
               "    if(x == 0 && y == 0) x = 1;\n"   // Avoid producing a NaN
               "    return atan2(y, x);\n"
               "}\n";
    }

    if (mUsesAtan2_2)
    {
        out << "float2 atanyx(float2 y, float2 x)\n"
               "{\n"
               "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
               "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
               "    return float2(atan2(y[0], x[0]), atan2(y[1], x[1]));\n"
               "}\n";
    }

    if (mUsesAtan2_3)
    {
        out << "float3 atanyx(float3 y, float3 x)\n"
               "{\n"
               "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
               "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
               "    if(x[2] == 0 && y[2] == 0) x[2] = 1;\n"
               "    return float3(atan2(y[0], x[0]), atan2(y[1], x[1]), atan2(y[2], x[2]));\n"
               "}\n";
    }

    if (mUsesAtan2_4)
    {
        out << "float4 atanyx(float4 y, float4 x)\n"
               "{\n"
               "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
               "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
               "    if(x[2] == 0 && y[2] == 0) x[2] = 1;\n"
               "    if(x[3] == 0 && y[3] == 0) x[3] = 1;\n"
               "    return float4(atan2(y[0], x[0]), atan2(y[1], x[1]), atan2(y[2], x[2]), atan2(y[3], x[3]));\n"
               "}\n";
    }
}

void OutputHLSL::visitSymbol(TIntermSymbol *node)
{
    TInfoSinkBase &out = mBody;

    TString name = node->getSymbol();

    if (name == "gl_DepthRange")
    {
        mUsesDepthRange = true;
        out << name;
    }
    else
    {
        TQualifier qualifier = node->getQualifier();

        if (qualifier == EvqUniform)
        {
            if (node->getType().isInterfaceBlockMember())
            {
                const TString& interfaceBlockTypeName = node->getType().getInterfaceBlockType()->getTypeName();
                mReferencedInterfaceBlocks[interfaceBlockTypeName] = node;
                out << decorateUniform(name, node->getType());
            }
            else if (node->getBasicType() == EbtInterfaceBlock)
            {
                const TString& interfaceBlockTypeName = node->getType().getTypeName();
                mReferencedInterfaceBlocks[interfaceBlockTypeName] = node;
                out << decorateUniform(name, node->getType());
            }
            else
            {
                mReferencedUniforms[name] = node;
                out << decorateUniform(name, node->getType());
            }
        }
        else if (qualifier == EvqAttribute || qualifier == EvqVertexInput)
        {
            mReferencedAttributes[name] = node;
            out << decorate(name);
        }
        else if (isVarying(qualifier))
        {
            mReferencedVaryings[name] = node;
            out << decorate(name);
        }
        else if (qualifier == EvqFragmentOutput)
        {
            mReferencedOutputVariables[name] = node;
            out << "out_" << name;
        }
        else if (qualifier == EvqFragColor)
        {
            out << "gl_Color[0]";
            mUsesFragColor = true;
        }
        else if (qualifier == EvqFragData)
        {
            out << "gl_Color";
            mUsesFragData = true;
        }
        else if (qualifier == EvqFragCoord)
        {
            mUsesFragCoord = true;
            out << name;
        }
        else if (qualifier == EvqPointCoord)
        {
            mUsesPointCoord = true;
            out << name;
        }
        else if (qualifier == EvqFrontFacing)
        {
            mUsesFrontFacing = true;
            out << name;
        }
        else if (qualifier == EvqPointSize)
        {
            mUsesPointSize = true;
            out << name;
        }
        else
        {
            out << decorate(name);
        }
    }
}

bool OutputHLSL::visitBinary(Visit visit, TIntermBinary *node)
{
    TInfoSinkBase &out = mBody;

    switch (node->getOp())
    {
      case EOpAssign:                  outputTriplet(visit, "(", " = ", ")");           break;
      case EOpInitialize:
        if (visit == PreVisit)
        {
            // GLSL allows to write things like "float x = x;" where a new variable x is defined
            // and the value of an existing variable x is assigned. HLSL uses C semantics (the
            // new variable is created before the assignment is evaluated), so we need to convert
            // this to "float t = x, x = t;".

            TIntermSymbol *symbolNode = node->getLeft()->getAsSymbolNode();
            TIntermTyped *expression = node->getRight();

            sh::SearchSymbol searchSymbol(symbolNode->getSymbol());
            expression->traverse(&searchSymbol);
            bool sameSymbol = searchSymbol.foundMatch();

            if (sameSymbol)
            {
                // Type already printed
                out << "t" + str(mUniqueIndex) + " = ";
                expression->traverse(this);
                out << ", ";
                symbolNode->traverse(this);
                out << " = t" + str(mUniqueIndex);

                mUniqueIndex++;
                return false;
            }
        }
        else if (visit == InVisit)
        {
            out << " = ";
        }
        break;
      case EOpAddAssign:               outputTriplet(visit, "(", " += ", ")");          break;
      case EOpSubAssign:               outputTriplet(visit, "(", " -= ", ")");          break;
      case EOpMulAssign:               outputTriplet(visit, "(", " *= ", ")");          break;
      case EOpVectorTimesScalarAssign: outputTriplet(visit, "(", " *= ", ")");          break;
      case EOpMatrixTimesScalarAssign: outputTriplet(visit, "(", " *= ", ")");          break;
      case EOpVectorTimesMatrixAssign:
        if (visit == PreVisit)
        {
            out << "(";
        }
        else if (visit == InVisit)
        {
            out << " = mul(";
            node->getLeft()->traverse(this);
            out << ", transpose(";   
        }
        else
        {
            out << ")))";
        }
        break;
      case EOpMatrixTimesMatrixAssign:
        if (visit == PreVisit)
        {
            out << "(";
        }
        else if (visit == InVisit)
        {
            out << " = mul(";
            node->getLeft()->traverse(this);
            out << ", ";   
        }
        else
        {
            out << "))";
        }
        break;
      case EOpDivAssign:               outputTriplet(visit, "(", " /= ", ")");          break;
      case EOpIndexDirect:
        if (node->getLeft()->getBasicType() == EbtInterfaceBlock)
        {
            if (visit == PreVisit)
            {
                const TType &interfaceBlockType = node->getLeft()->getType();
                mReferencedInterfaceBlocks[interfaceBlockType.getInstanceName()] = node->getLeft()->getAsSymbolNode();
                out << interfaceBlockInstanceString(interfaceBlockType, node->getRight()->getAsConstantUnion()->getIConst(0));
                return false;
            }
        }
        else
        {
            outputTriplet(visit, "", "[", "]");
        }
        break;
      case EOpIndexIndirect:
        // We do not currently support indirect references to interface blocks
        ASSERT(node->getLeft()->getBasicType() != EbtInterfaceBlock);
        outputTriplet(visit, "", "[", "]");
        break;
      case EOpIndexDirectStruct:
      case EOpIndexDirectInterfaceBlock:
        if (visit == InVisit)
        {
            out << "." + decorateField(node->getType().getFieldName(), node->getLeft()->getType());

            return false;
        }
        break;
      case EOpVectorSwizzle:
        if (visit == InVisit)
        {
            out << ".";

            TIntermAggregate *swizzle = node->getRight()->getAsAggregate();

            if (swizzle)
            {
                TIntermSequence &sequence = swizzle->getSequence();

                for (TIntermSequence::iterator sit = sequence.begin(); sit != sequence.end(); sit++)
                {
                    TIntermConstantUnion *element = (*sit)->getAsConstantUnion();

                    if (element)
                    {
                        int i = element->getIConst(0);

                        switch (i)
                        {
                        case 0: out << "x"; break;
                        case 1: out << "y"; break;
                        case 2: out << "z"; break;
                        case 3: out << "w"; break;
                        default: UNREACHABLE();
                        }
                    }
                    else UNREACHABLE();
                }
            }
            else UNREACHABLE();

            return false;   // Fully processed
        }
        break;
      case EOpAdd:               outputTriplet(visit, "(", " + ", ")"); break;
      case EOpSub:               outputTriplet(visit, "(", " - ", ")"); break;
      case EOpMul:               outputTriplet(visit, "(", " * ", ")"); break;
      case EOpDiv:               outputTriplet(visit, "(", " / ", ")"); break;
      case EOpEqual:
      case EOpNotEqual:
        if (node->getLeft()->isScalar())
        {
            if (node->getOp() == EOpEqual)
            {
                outputTriplet(visit, "(", " == ", ")");
            }
            else
            {
                outputTriplet(visit, "(", " != ", ")");
            }
        }
        else if (node->getLeft()->getBasicType() == EbtStruct)
        {
            if (node->getOp() == EOpEqual)
            {
                out << "(";
            }
            else
            {
                out << "!(";
            }

            const TTypeList *fields = node->getLeft()->getType().getStruct();

            for (size_t i = 0; i < fields->size(); i++)
            {
                const TType *fieldType = (*fields)[i].type;

                node->getLeft()->traverse(this);
                out << "." + decorateField(fieldType->getFieldName(), node->getLeft()->getType()) + " == ";
                node->getRight()->traverse(this);
                out << "." + decorateField(fieldType->getFieldName(), node->getLeft()->getType());

                if (i < fields->size() - 1)
                {
                    out << " && ";
                }
            }

            out << ")";

            return false;
        }
        else
        {
            if (node->getLeft()->isMatrix())
            {
                mUsesEqualMat[node->getLeft()->getCols()][node->getLeft()->getRows()] = true;
            }
            else if (node->getLeft()->isVector())
            {
                switch (node->getLeft()->getBasicType())
                {
                  case EbtFloat:
                    switch (node->getLeft()->getNominalSize())
                    {
                      case 2: mUsesEqualVec2 = true; break;
                      case 3: mUsesEqualVec3 = true; break;
                      case 4: mUsesEqualVec4 = true; break;
                      default: UNREACHABLE();
                    }
                    break;
                  case EbtInt:
                    switch (node->getLeft()->getNominalSize())
                    {
                      case 2: mUsesEqualIVec2 = true; break;
                      case 3: mUsesEqualIVec3 = true; break;
                      case 4: mUsesEqualIVec4 = true; break;
                      default: UNREACHABLE();
                    }
                    break;
                  case EbtUInt:
                    switch (node->getLeft()->getNominalSize())
                    {
                      case 2: mUsesEqualUVec2 = true; break;
                      case 3: mUsesEqualUVec3 = true; break;
                      case 4: mUsesEqualUVec4 = true; break;
                      default: UNREACHABLE();
                    }
                    break;
                  case EbtBool:
                    switch (node->getLeft()->getNominalSize())
                    {
                      case 2: mUsesEqualBVec2 = true; break;
                      case 3: mUsesEqualBVec3 = true; break;
                      case 4: mUsesEqualBVec4 = true; break;
                      default: UNREACHABLE();
                    }
                    break;
                  default: UNREACHABLE();
                }
            }
            else UNREACHABLE();

            if (node->getOp() == EOpEqual)
            {
                outputTriplet(visit, "equal(", ", ", ")");
            }
            else
            {
                outputTriplet(visit, "!equal(", ", ", ")");
            }
        }
        break;
      case EOpLessThan:          outputTriplet(visit, "(", " < ", ")");   break;
      case EOpGreaterThan:       outputTriplet(visit, "(", " > ", ")");   break;
      case EOpLessThanEqual:     outputTriplet(visit, "(", " <= ", ")");  break;
      case EOpGreaterThanEqual:  outputTriplet(visit, "(", " >= ", ")");  break;
      case EOpVectorTimesScalar: outputTriplet(visit, "(", " * ", ")");   break;
      case EOpMatrixTimesScalar: outputTriplet(visit, "(", " * ", ")");   break;
      case EOpVectorTimesMatrix: outputTriplet(visit, "mul(", ", transpose(", "))"); break;
      case EOpMatrixTimesVector: outputTriplet(visit, "mul(transpose(", "), ", ")"); break;
      case EOpMatrixTimesMatrix: outputTriplet(visit, "transpose(mul(transpose(", "), transpose(", ")))"); break;
      case EOpLogicalOr:
        out << "s" << mUnfoldShortCircuit->getNextTemporaryIndex();
        return false;
      case EOpLogicalXor:
        mUsesXor = true;
        outputTriplet(visit, "xor(", ", ", ")");
        break;
      case EOpLogicalAnd:
        out << "s" << mUnfoldShortCircuit->getNextTemporaryIndex();
        return false;
      default: UNREACHABLE();
    }

    return true;
}

bool OutputHLSL::visitUnary(Visit visit, TIntermUnary *node)
{
    switch (node->getOp())
    {
      case EOpNegative:         outputTriplet(visit, "(-", "", ")");  break;
      case EOpVectorLogicalNot: outputTriplet(visit, "(!", "", ")");  break;
      case EOpLogicalNot:       outputTriplet(visit, "(!", "", ")");  break;
      case EOpPostIncrement:    outputTriplet(visit, "(", "", "++)"); break;
      case EOpPostDecrement:    outputTriplet(visit, "(", "", "--)"); break;
      case EOpPreIncrement:     outputTriplet(visit, "(++", "", ")"); break;
      case EOpPreDecrement:     outputTriplet(visit, "(--", "", ")"); break;
      case EOpConvIntToBool:
      case EOpConvUIntToBool:
      case EOpConvFloatToBool:
        switch (node->getOperand()->getType().getNominalSize())
        {
          case 1:    outputTriplet(visit, "bool(", "", ")");  break;
          case 2:    outputTriplet(visit, "bool2(", "", ")"); break;
          case 3:    outputTriplet(visit, "bool3(", "", ")"); break;
          case 4:    outputTriplet(visit, "bool4(", "", ")"); break;
          default: UNREACHABLE();
        }
        break;
      case EOpConvBoolToFloat:
      case EOpConvIntToFloat:
      case EOpConvUIntToFloat:
        switch (node->getOperand()->getType().getNominalSize())
        {
          case 1:    outputTriplet(visit, "float(", "", ")");  break;
          case 2:    outputTriplet(visit, "float2(", "", ")"); break;
          case 3:    outputTriplet(visit, "float3(", "", ")"); break;
          case 4:    outputTriplet(visit, "float4(", "", ")"); break;
          default: UNREACHABLE();
        }
        break;
      case EOpConvFloatToInt:
      case EOpConvBoolToInt:
      case EOpConvUIntToInt:
        switch (node->getOperand()->getType().getNominalSize())
        {
          case 1:    outputTriplet(visit, "int(", "", ")");  break;
          case 2:    outputTriplet(visit, "int2(", "", ")"); break;
          case 3:    outputTriplet(visit, "int3(", "", ")"); break;
          case 4:    outputTriplet(visit, "int4(", "", ")"); break;
          default: UNREACHABLE();
        }
        break;
      case EOpConvFloatToUInt:
      case EOpConvBoolToUInt:
      case EOpConvIntToUInt:
        switch (node->getOperand()->getType().getCols())
        {
          case 1:    outputTriplet(visit, "uint(", "", ")");  break;
          case 2:    outputTriplet(visit, "uint2(", "", ")");  break;
          case 3:    outputTriplet(visit, "uint3(", "", ")");  break;
          case 4:    outputTriplet(visit, "uint4(", "", ")");  break;
          default: UNREACHABLE();
        }
        break;
      case EOpRadians:          outputTriplet(visit, "radians(", "", ")");   break;
      case EOpDegrees:          outputTriplet(visit, "degrees(", "", ")");   break;
      case EOpSin:              outputTriplet(visit, "sin(", "", ")");       break;
      case EOpCos:              outputTriplet(visit, "cos(", "", ")");       break;
      case EOpTan:              outputTriplet(visit, "tan(", "", ")");       break;
      case EOpAsin:             outputTriplet(visit, "asin(", "", ")");      break;
      case EOpAcos:             outputTriplet(visit, "acos(", "", ")");      break;
      case EOpAtan:             outputTriplet(visit, "atan(", "", ")");      break;
      case EOpExp:              outputTriplet(visit, "exp(", "", ")");       break;
      case EOpLog:              outputTriplet(visit, "log(", "", ")");       break;
      case EOpExp2:             outputTriplet(visit, "exp2(", "", ")");      break;
      case EOpLog2:             outputTriplet(visit, "log2(", "", ")");      break;
      case EOpSqrt:             outputTriplet(visit, "sqrt(", "", ")");      break;
      case EOpInverseSqrt:      outputTriplet(visit, "rsqrt(", "", ")");     break;
      case EOpAbs:              outputTriplet(visit, "abs(", "", ")");       break;
      case EOpSign:             outputTriplet(visit, "sign(", "", ")");      break;
      case EOpFloor:            outputTriplet(visit, "floor(", "", ")");     break;
      case EOpCeil:             outputTriplet(visit, "ceil(", "", ")");      break;
      case EOpFract:            outputTriplet(visit, "frac(", "", ")");      break;
      case EOpLength:           outputTriplet(visit, "length(", "", ")");    break;
      case EOpNormalize:        outputTriplet(visit, "normalize(", "", ")"); break;
      case EOpDFdx:
        if(mInsideDiscontinuousLoop || mOutputLod0Function)
        {
            outputTriplet(visit, "(", "", ", 0.0)");
        }
        else
        {
            outputTriplet(visit, "ddx(", "", ")");
        }
        break;
      case EOpDFdy:
        if(mInsideDiscontinuousLoop || mOutputLod0Function)
        {
            outputTriplet(visit, "(", "", ", 0.0)");
        }
        else
        {
           outputTriplet(visit, "ddy(", "", ")");
        }
        break;
      case EOpFwidth:
        if(mInsideDiscontinuousLoop || mOutputLod0Function)
        {
            outputTriplet(visit, "(", "", ", 0.0)");
        }
        else
        {
            outputTriplet(visit, "fwidth(", "", ")");
        }
        break;
      case EOpAny:              outputTriplet(visit, "any(", "", ")");       break;
      case EOpAll:              outputTriplet(visit, "all(", "", ")");       break;
      default: UNREACHABLE();
    }

    return true;
}

bool OutputHLSL::visitAggregate(Visit visit, TIntermAggregate *node)
{
    TInfoSinkBase &out = mBody;

    switch (node->getOp())
    {
      case EOpSequence:
        {
            if (mInsideFunction)
            {
                outputLineDirective(node->getLine());
                out << "{\n";

                mScopeDepth++;

                if (mScopeBracket.size() < mScopeDepth)
                {
                    mScopeBracket.push_back(0);   // New scope level
                }
                else
                {
                    mScopeBracket[mScopeDepth - 1]++;   // New scope at existing level
                }
            }

            for (TIntermSequence::iterator sit = node->getSequence().begin(); sit != node->getSequence().end(); sit++)
            {
                outputLineDirective((*sit)->getLine());

                traverseStatements(*sit);

                out << ";\n";
            }

            if (mInsideFunction)
            {
                outputLineDirective(node->getEndLine());
                out << "}\n";

                mScopeDepth--;
            }

            return false;
        }
      case EOpDeclaration:
        if (visit == PreVisit)
        {
            TIntermSequence &sequence = node->getSequence();
            TIntermTyped *variable = sequence[0]->getAsTyped();

            if (variable && (variable->getQualifier() == EvqTemporary || variable->getQualifier() == EvqGlobal))
            {
                if (variable->getType().getStruct())
                {
                    addConstructor(variable->getType(), scopedStruct(variable->getType().getTypeName()), NULL);
                }

                if (!variable->getAsSymbolNode() || variable->getAsSymbolNode()->getSymbol() != "")   // Variable declaration
                {
                    if (!mInsideFunction)
                    {
                        out << "static ";
                    }

                    out << typeString(variable->getType()) + " ";

                    for (TIntermSequence::iterator sit = sequence.begin(); sit != sequence.end(); sit++)
                    {
                        TIntermSymbol *symbol = (*sit)->getAsSymbolNode();

                        if (symbol)
                        {
                            symbol->traverse(this);
                            out << arrayString(symbol->getType());
                            out << " = " + initializer(variable->getType());
                        }
                        else
                        {
                            (*sit)->traverse(this);
                        }

                        if (*sit != sequence.back())
                        {
                            out << ", ";
                        }
                    }
                }
                else if (variable->getAsSymbolNode() && variable->getAsSymbolNode()->getSymbol() == "")   // Type (struct) declaration
                {
                    // Already added to constructor map
                }
                else UNREACHABLE();
            }
            else if (variable && isVaryingOut(variable->getQualifier()))
            {
                for (TIntermSequence::iterator sit = sequence.begin(); sit != sequence.end(); sit++)
                {
                    TIntermSymbol *symbol = (*sit)->getAsSymbolNode();

                    if (symbol)
                    {
                        // Vertex (output) varyings which are declared but not written to should still be declared to allow successful linking
                        mReferencedVaryings[symbol->getSymbol()] = symbol;
                    }
                    else
                    {
                        (*sit)->traverse(this);
                    }
                }
            }

            return false;
        }
        else if (visit == InVisit)
        {
            out << ", ";
        }
        break;
      case EOpPrototype:
        if (visit == PreVisit)
        {
            out << typeString(node->getType()) << " " << decorate(node->getName()) << (mOutputLod0Function ? "Lod0(" : "(");

            TIntermSequence &arguments = node->getSequence();

            for (unsigned int i = 0; i < arguments.size(); i++)
            {
                TIntermSymbol *symbol = arguments[i]->getAsSymbolNode();

                if (symbol)
                {
                    out << argumentString(symbol);

                    if (i < arguments.size() - 1)
                    {
                        out << ", ";
                    }
                }
                else UNREACHABLE();
            }

            out << ");\n";

            // Also prototype the Lod0 variant if needed
            if (mContainsLoopDiscontinuity && !mOutputLod0Function)
            {
                mOutputLod0Function = true;
                node->traverse(this);
                mOutputLod0Function = false;
            }

            return false;
        }
        break;
      case EOpComma:            outputTriplet(visit, "(", ", ", ")");                break;
      case EOpFunction:
        {
            TString name = TFunction::unmangleName(node->getName());

            out << typeString(node->getType()) << " ";

            if (name == "main")
            {
                out << "gl_main(";
            }
            else
            {
                out << decorate(name) << (mOutputLod0Function ? "Lod0(" : "(");
            }

            TIntermSequence &sequence = node->getSequence();
            TIntermSequence &arguments = sequence[0]->getAsAggregate()->getSequence();

            for (unsigned int i = 0; i < arguments.size(); i++)
            {
                TIntermSymbol *symbol = arguments[i]->getAsSymbolNode();

                if (symbol)
                {
                    if (symbol->getType().getStruct())
                    {
                        addConstructor(symbol->getType(), scopedStruct(symbol->getType().getTypeName()), NULL);
                    }

                    out << argumentString(symbol);

                    if (i < arguments.size() - 1)
                    {
                        out << ", ";
                    }
                }
                else UNREACHABLE();
            }

            out << ")\n"
                "{\n";
            
            if (sequence.size() > 1)
            {
                mInsideFunction = true;
                sequence[1]->traverse(this);
                mInsideFunction = false;
            }
            
            out << "}\n";

            if (mContainsLoopDiscontinuity && !mOutputLod0Function)
            {
                if (name != "main")
                {
                    mOutputLod0Function = true;
                    node->traverse(this);
                    mOutputLod0Function = false;
                }
            }

            return false;
        }
        break;
      case EOpFunctionCall:
        {
            TString name = TFunction::unmangleName(node->getName());
            bool lod0 = mInsideDiscontinuousLoop || mOutputLod0Function;
            TIntermSequence &arguments = node->getSequence();

            if (node->isUserDefined())
            {
                out << decorate(name) << (lod0 ? "Lod0(" : "(");
            }
            else
            {
                TBasicType samplerType = arguments[0]->getAsTyped()->getType().getBasicType();

                TextureFunction textureFunction;
                textureFunction.sampler = samplerType;
                textureFunction.coords = arguments[1]->getAsTyped()->getNominalSize();
                textureFunction.mipmap = TextureFunction::IMPLICIT;

                if (name == "texture2D" || name == "textureCube" || name == "texture")
                {
                    textureFunction.mipmap = TextureFunction::IMPLICIT;
                    textureFunction.proj = false;
                }
                else if (name == "texture2DProj" || name == "textureProj")
                {
                    textureFunction.mipmap = TextureFunction::IMPLICIT;
                    textureFunction.proj = true;
                }
                else if (name == "texture2DLod" || name == "textureCubeLod" || name == "textureLod")
                {
                    textureFunction.mipmap = TextureFunction::LOD;
                    textureFunction.proj = false;
                }
                else if (name == "texture2DProjLod" || name == "textureProjLod")
                {
                    textureFunction.mipmap = TextureFunction::LOD;
                    textureFunction.proj = true;
                }
                else UNREACHABLE();

                if (textureFunction.mipmap != TextureFunction::LOD)
                {
                    if (lod0 || mContext.shaderType == SH_VERTEX_SHADER)
                    {
                        textureFunction.mipmap = TextureFunction::LOD0;
                    }
                    else if (arguments.size() == 3)
                    {
                        textureFunction.mipmap = TextureFunction::BIAS;
                    }
                }

                mUsesTexture.insert(textureFunction);
                
                out << textureFunction.name();
            }
            
            for (TIntermSequence::iterator arg = arguments.begin(); arg != arguments.end(); arg++)
            {
                if (mOutputType == SH_HLSL11_OUTPUT && IsSampler((*arg)->getAsTyped()->getBasicType()))
                {
                    out << "texture_";
                    (*arg)->traverse(this);
                    out << ", sampler_";
                }

                (*arg)->traverse(this);

                if (arg < arguments.end() - 1)
                {
                    out << ", ";
                }
            }

            out << ")";

            return false;
        }
        break;
      case EOpParameters:       outputTriplet(visit, "(", ", ", ")\n{\n");             break;
      case EOpConstructFloat:
        addConstructor(node->getType(), "vec1", &node->getSequence());
        outputTriplet(visit, "vec1(", "", ")");
        break;
      case EOpConstructVec2:
        addConstructor(node->getType(), "vec2", &node->getSequence());
        outputTriplet(visit, "vec2(", ", ", ")");
        break;
      case EOpConstructVec3:
        addConstructor(node->getType(), "vec3", &node->getSequence());
        outputTriplet(visit, "vec3(", ", ", ")");
        break;
      case EOpConstructVec4:
        addConstructor(node->getType(), "vec4", &node->getSequence());
        outputTriplet(visit, "vec4(", ", ", ")");
        break;
      case EOpConstructBool:
        addConstructor(node->getType(), "bvec1", &node->getSequence());
        outputTriplet(visit, "bvec1(", "", ")");
        break;
      case EOpConstructBVec2:
        addConstructor(node->getType(), "bvec2", &node->getSequence());
        outputTriplet(visit, "bvec2(", ", ", ")");
        break;
      case EOpConstructBVec3:
        addConstructor(node->getType(), "bvec3", &node->getSequence());
        outputTriplet(visit, "bvec3(", ", ", ")");
        break;
      case EOpConstructBVec4:
        addConstructor(node->getType(), "bvec4", &node->getSequence());
        outputTriplet(visit, "bvec4(", ", ", ")");
        break;
      case EOpConstructInt:
        addConstructor(node->getType(), "ivec1", &node->getSequence());
        outputTriplet(visit, "ivec1(", "", ")");
        break;
      case EOpConstructIVec2:
        addConstructor(node->getType(), "ivec2", &node->getSequence());
        outputTriplet(visit, "ivec2(", ", ", ")");
        break;
      case EOpConstructIVec3:
        addConstructor(node->getType(), "ivec3", &node->getSequence());
        outputTriplet(visit, "ivec3(", ", ", ")");
        break;
      case EOpConstructIVec4:
        addConstructor(node->getType(), "ivec4", &node->getSequence());
        outputTriplet(visit, "ivec4(", ", ", ")");
        break;
      case EOpConstructUInt:
        addConstructor(node->getType(), "uvec1", &node->getSequence());
        outputTriplet(visit, "uvec1(", "", ")");
        break;
      case EOpConstructUVec2:
        addConstructor(node->getType(), "uvec2", &node->getSequence());
        outputTriplet(visit, "uvec2(", ", ", ")");
        break;
      case EOpConstructUVec3:
        addConstructor(node->getType(), "uvec3", &node->getSequence());
        outputTriplet(visit, "uvec3(", ", ", ")");
        break;
      case EOpConstructUVec4:
        addConstructor(node->getType(), "uvec4", &node->getSequence());
        outputTriplet(visit, "uvec4(", ", ", ")");
        break;
      case EOpConstructMat2:
        addConstructor(node->getType(), "mat2", &node->getSequence());
        outputTriplet(visit, "mat2(", ", ", ")");
        break;
      case EOpConstructMat3:
        addConstructor(node->getType(), "mat3", &node->getSequence());
        outputTriplet(visit, "mat3(", ", ", ")");
        break;
      case EOpConstructMat4: 
        addConstructor(node->getType(), "mat4", &node->getSequence());
        outputTriplet(visit, "mat4(", ", ", ")");
        break;
      case EOpConstructStruct:
        addConstructor(node->getType(), scopedStruct(node->getType().getTypeName()), &node->getSequence());
        outputTriplet(visit, structLookup(node->getType().getTypeName()) + "_ctor(", ", ", ")");
        break;
      case EOpLessThan:         outputTriplet(visit, "(", " < ", ")");                 break;
      case EOpGreaterThan:      outputTriplet(visit, "(", " > ", ")");                 break;
      case EOpLessThanEqual:    outputTriplet(visit, "(", " <= ", ")");                break;
      case EOpGreaterThanEqual: outputTriplet(visit, "(", " >= ", ")");                break;
      case EOpVectorEqual:      outputTriplet(visit, "(", " == ", ")");                break;
      case EOpVectorNotEqual:   outputTriplet(visit, "(", " != ", ")");                break;
      case EOpMod:
        {
            // We need to look at the number of components in both arguments
            const int modValue = node->getSequence()[0]->getAsTyped()->getNominalSize() * 10
                               + node->getSequence()[1]->getAsTyped()->getNominalSize();
            switch (modValue)
            {
              case 11: mUsesMod1 = true; break;
              case 22: mUsesMod2v = true; break;
              case 21: mUsesMod2f = true; break;
              case 33: mUsesMod3v = true; break;
              case 31: mUsesMod3f = true; break;
              case 44: mUsesMod4v = true; break;
              case 41: mUsesMod4f = true; break;
              default: UNREACHABLE();
            }

            outputTriplet(visit, "mod(", ", ", ")");
        }
        break;
      case EOpPow:              outputTriplet(visit, "pow(", ", ", ")");               break;
      case EOpAtan:
        ASSERT(node->getSequence().size() == 2);   // atan(x) is a unary operator
        switch (node->getSequence()[0]->getAsTyped()->getNominalSize())
        {
          case 1: mUsesAtan2_1 = true; break;
          case 2: mUsesAtan2_2 = true; break;
          case 3: mUsesAtan2_3 = true; break;
          case 4: mUsesAtan2_4 = true; break;
          default: UNREACHABLE();
        }
        outputTriplet(visit, "atanyx(", ", ", ")");
        break;
      case EOpMin:           outputTriplet(visit, "min(", ", ", ")");           break;
      case EOpMax:           outputTriplet(visit, "max(", ", ", ")");           break;
      case EOpClamp:         outputTriplet(visit, "clamp(", ", ", ")");         break;
      case EOpMix:           outputTriplet(visit, "lerp(", ", ", ")");          break;
      case EOpStep:          outputTriplet(visit, "step(", ", ", ")");          break;
      case EOpSmoothStep:    outputTriplet(visit, "smoothstep(", ", ", ")");    break;
      case EOpDistance:      outputTriplet(visit, "distance(", ", ", ")");      break;
      case EOpDot:           outputTriplet(visit, "dot(", ", ", ")");           break;
      case EOpCross:         outputTriplet(visit, "cross(", ", ", ")");         break;
      case EOpFaceForward:
        {
            switch (node->getSequence()[0]->getAsTyped()->getNominalSize())   // Number of components in the first argument
            {
            case 1: mUsesFaceforward1 = true; break;
            case 2: mUsesFaceforward2 = true; break;
            case 3: mUsesFaceforward3 = true; break;
            case 4: mUsesFaceforward4 = true; break;
            default: UNREACHABLE();
            }
            
            outputTriplet(visit, "faceforward(", ", ", ")");
        }
        break;
      case EOpReflect:       outputTriplet(visit, "reflect(", ", ", ")");       break;
      case EOpRefract:       outputTriplet(visit, "refract(", ", ", ")");       break;
      case EOpMul:           outputTriplet(visit, "(", " * ", ")");             break;
      default: UNREACHABLE();
    }

    return true;
}

bool OutputHLSL::visitSelection(Visit visit, TIntermSelection *node)
{
    TInfoSinkBase &out = mBody;

    if (node->usesTernaryOperator())
    {
        out << "s" << mUnfoldShortCircuit->getNextTemporaryIndex();
    }
    else  // if/else statement
    {
        mUnfoldShortCircuit->traverse(node->getCondition());

        out << "if(";

        node->getCondition()->traverse(this);

        out << ")\n";
        
        outputLineDirective(node->getLine());
        out << "{\n";

        if (node->getTrueBlock())
        {
            traverseStatements(node->getTrueBlock());
        }

        outputLineDirective(node->getLine());
        out << ";\n}\n";

        if (node->getFalseBlock())
        {
            out << "else\n";

            outputLineDirective(node->getFalseBlock()->getLine());
            out << "{\n";

            outputLineDirective(node->getFalseBlock()->getLine());
            traverseStatements(node->getFalseBlock());

            outputLineDirective(node->getFalseBlock()->getLine());
            out << ";\n}\n";
        }
    }

    return false;
}

void OutputHLSL::visitConstantUnion(TIntermConstantUnion *node)
{
    writeConstantUnion(node->getType(), node->getUnionArrayPointer());
}

bool OutputHLSL::visitLoop(Visit visit, TIntermLoop *node)
{
    bool wasDiscontinuous = mInsideDiscontinuousLoop;

    if (mContainsLoopDiscontinuity && !mInsideDiscontinuousLoop)
    {
        mInsideDiscontinuousLoop = containsLoopDiscontinuity(node);
    }

    if (mOutputType == SH_HLSL9_OUTPUT)
    {
        if (handleExcessiveLoop(node))
        {
            return false;
        }
    }

    TInfoSinkBase &out = mBody;

    if (node->getType() == ELoopDoWhile)
    {
        out << "{do\n";

        outputLineDirective(node->getLine());
        out << "{\n";
    }
    else
    {
        out << "{for(";
        
        if (node->getInit())
        {
            node->getInit()->traverse(this);
        }

        out << "; ";

        if (node->getCondition())
        {
            node->getCondition()->traverse(this);
        }

        out << "; ";

        if (node->getExpression())
        {
            node->getExpression()->traverse(this);
        }

        out << ")\n";
        
        outputLineDirective(node->getLine());
        out << "{\n";
    }

    if (node->getBody())
    {
        traverseStatements(node->getBody());
    }

    outputLineDirective(node->getLine());
    out << ";}\n";

    if (node->getType() == ELoopDoWhile)
    {
        outputLineDirective(node->getCondition()->getLine());
        out << "while(\n";

        node->getCondition()->traverse(this);

        out << ");";
    }

    out << "}\n";

    mInsideDiscontinuousLoop = wasDiscontinuous;

    return false;
}

bool OutputHLSL::visitBranch(Visit visit, TIntermBranch *node)
{
    TInfoSinkBase &out = mBody;

    switch (node->getFlowOp())
    {
      case EOpKill:     outputTriplet(visit, "discard;\n", "", "");  break;
      case EOpBreak:
        if (visit == PreVisit)
        {
            if (mExcessiveLoopIndex)
            {
                out << "{Break";
                mExcessiveLoopIndex->traverse(this);
                out << " = true; break;}\n";
            }
            else
            {
                out << "break;\n";
            }
        }
        break;
      case EOpContinue: outputTriplet(visit, "continue;\n", "", ""); break;
      case EOpReturn:
        if (visit == PreVisit)
        {
            if (node->getExpression())
            {
                out << "return ";
            }
            else
            {
                out << "return;\n";
            }
        }
        else if (visit == PostVisit)
        {
            if (node->getExpression())
            {
                out << ";\n";
            }
        }
        break;
      default: UNREACHABLE();
    }

    return true;
}

void OutputHLSL::traverseStatements(TIntermNode *node)
{
    if (isSingleStatement(node))
    {
        mUnfoldShortCircuit->traverse(node);
    }

    node->traverse(this);
}

bool OutputHLSL::isSingleStatement(TIntermNode *node)
{
    TIntermAggregate *aggregate = node->getAsAggregate();

    if (aggregate)
    {
        if (aggregate->getOp() == EOpSequence)
        {
            return false;
        }
        else
        {
            for (TIntermSequence::iterator sit = aggregate->getSequence().begin(); sit != aggregate->getSequence().end(); sit++)
            {
                if (!isSingleStatement(*sit))
                {
                    return false;
                }
            }

            return true;
        }
    }

    return true;
}

// Handle loops with more than 254 iterations (unsupported by D3D9) by splitting them
// (The D3D documentation says 255 iterations, but the compiler complains at anything more than 254).
bool OutputHLSL::handleExcessiveLoop(TIntermLoop *node)
{
    const int MAX_LOOP_ITERATIONS = 254;
    TInfoSinkBase &out = mBody;

    // Parse loops of the form:
    // for(int index = initial; index [comparator] limit; index += increment)
    TIntermSymbol *index = NULL;
    TOperator comparator = EOpNull;
    int initial = 0;
    int limit = 0;
    int increment = 0;

    // Parse index name and intial value
    if (node->getInit())
    {
        TIntermAggregate *init = node->getInit()->getAsAggregate();

        if (init)
        {
            TIntermSequence &sequence = init->getSequence();
            TIntermTyped *variable = sequence[0]->getAsTyped();

            if (variable && variable->getQualifier() == EvqTemporary)
            {
                TIntermBinary *assign = variable->getAsBinaryNode();

                if (assign->getOp() == EOpInitialize)
                {
                    TIntermSymbol *symbol = assign->getLeft()->getAsSymbolNode();
                    TIntermConstantUnion *constant = assign->getRight()->getAsConstantUnion();

                    if (symbol && constant)
                    {
                        if (constant->getBasicType() == EbtInt && constant->isScalar())
                        {
                            index = symbol;
                            initial = constant->getIConst(0);
                        }
                    }
                }
            }
        }
    }

    // Parse comparator and limit value
    if (index != NULL && node->getCondition())
    {
        TIntermBinary *test = node->getCondition()->getAsBinaryNode();
        
        if (test && test->getLeft()->getAsSymbolNode()->getId() == index->getId())
        {
            TIntermConstantUnion *constant = test->getRight()->getAsConstantUnion();

            if (constant)
            {
                if (constant->getBasicType() == EbtInt && constant->isScalar())
                {
                    comparator = test->getOp();
                    limit = constant->getIConst(0);
                }
            }
        }
    }

    // Parse increment
    if (index != NULL && comparator != EOpNull && node->getExpression())
    {
        TIntermBinary *binaryTerminal = node->getExpression()->getAsBinaryNode();
        TIntermUnary *unaryTerminal = node->getExpression()->getAsUnaryNode();
        
        if (binaryTerminal)
        {
            TOperator op = binaryTerminal->getOp();
            TIntermConstantUnion *constant = binaryTerminal->getRight()->getAsConstantUnion();

            if (constant)
            {
                if (constant->getBasicType() == EbtInt && constant->isScalar())
                {
                    int value = constant->getIConst(0);

                    switch (op)
                    {
                      case EOpAddAssign: increment = value;  break;
                      case EOpSubAssign: increment = -value; break;
                      default: UNIMPLEMENTED();
                    }
                }
            }
        }
        else if (unaryTerminal)
        {
            TOperator op = unaryTerminal->getOp();

            switch (op)
            {
              case EOpPostIncrement: increment = 1;  break;
              case EOpPostDecrement: increment = -1; break;
              case EOpPreIncrement:  increment = 1;  break;
              case EOpPreDecrement:  increment = -1; break;
              default: UNIMPLEMENTED();
            }
        }
    }

    if (index != NULL && comparator != EOpNull && increment != 0)
    {
        if (comparator == EOpLessThanEqual)
        {
            comparator = EOpLessThan;
            limit += 1;
        }

        if (comparator == EOpLessThan)
        {
            int iterations = (limit - initial) / increment;

            if (iterations <= MAX_LOOP_ITERATIONS)
            {
                return false;   // Not an excessive loop
            }

            TIntermSymbol *restoreIndex = mExcessiveLoopIndex;
            mExcessiveLoopIndex = index;

            out << "{int ";
            index->traverse(this);
            out << ";\n"
                   "bool Break";
            index->traverse(this);
            out << " = false;\n";

            bool firstLoopFragment = true;

            while (iterations > 0)
            {
                int clampedLimit = initial + increment * std::min(MAX_LOOP_ITERATIONS, iterations);

                if (!firstLoopFragment)
                {
                    out << "if(!Break";
                    index->traverse(this);
                    out << ") {\n";
                }

                if (iterations <= MAX_LOOP_ITERATIONS)   // Last loop fragment
                {
                    mExcessiveLoopIndex = NULL;   // Stops setting the Break flag
                }
                
                // for(int index = initial; index < clampedLimit; index += increment)

                out << "for(";
                index->traverse(this);
                out << " = ";
                out << initial;

                out << "; ";
                index->traverse(this);
                out << " < ";
                out << clampedLimit;

                out << "; ";
                index->traverse(this);
                out << " += ";
                out << increment;
                out << ")\n";
                
                outputLineDirective(node->getLine());
                out << "{\n";

                if (node->getBody())
                {
                    node->getBody()->traverse(this);
                }

                outputLineDirective(node->getLine());
                out << ";}\n";

                if (!firstLoopFragment)
                {
                    out << "}\n";
                }

                firstLoopFragment = false;

                initial += MAX_LOOP_ITERATIONS * increment;
                iterations -= MAX_LOOP_ITERATIONS;
            }
            
            out << "}";

            mExcessiveLoopIndex = restoreIndex;

            return true;
        }
        else UNIMPLEMENTED();
    }

    return false;   // Not handled as an excessive loop
}

void OutputHLSL::outputTriplet(Visit visit, const TString &preString, const TString &inString, const TString &postString)
{
    TInfoSinkBase &out = mBody;

    if (visit == PreVisit)
    {
        out << preString;
    }
    else if (visit == InVisit)
    {
        out << inString;
    }
    else if (visit == PostVisit)
    {
        out << postString;
    }
}

void OutputHLSL::outputLineDirective(int line)
{
    if ((mContext.compileOptions & SH_LINE_DIRECTIVES) && (line > 0))
    {
        mBody << "\n";
        mBody << "#line " << line;

        if (mContext.sourcePath)
        {
            mBody << " \"" << mContext.sourcePath << "\"";
        }
        
        mBody << "\n";
    }
}

TString OutputHLSL::argumentString(const TIntermSymbol *symbol)
{
    TQualifier qualifier = symbol->getQualifier();
    const TType &type = symbol->getType();
    TString name = symbol->getSymbol();

    if (name.empty())   // HLSL demands named arguments, also for prototypes
    {
        name = "x" + str(mUniqueIndex++);
    }
    else
    {
        name = decorate(name);
    }

    if (mOutputType == SH_HLSL11_OUTPUT && IsSampler(type.getBasicType()))
    {
       return qualifierString(qualifier) + " " + textureString(type) + " texture_" + name + arrayString(type) + ", " +
              qualifierString(qualifier) + " SamplerState sampler_" + name + arrayString(type);
    }

    return qualifierString(qualifier) + " " + typeString(type) + " " + name + arrayString(type);
}

TString OutputHLSL::interpolationString(TQualifier qualifier)
{
    switch(qualifier)
    {
      case EvqVaryingIn:           return "";
      case EvqInvariantVaryingIn:  return "";
      case EvqSmoothIn:            return "linear";
      case EvqFlatIn:              return "nointerpolation";
      case EvqCentroidIn:          return "centroid";
      case EvqVaryingOut:          return "";
      case EvqInvariantVaryingOut: return "";
      case EvqSmoothOut:           return "linear";
      case EvqFlatOut:             return "nointerpolation";
      case EvqCentroidOut:         return "centroid";
      default: UNREACHABLE();
    }

    return "";
}

TString OutputHLSL::qualifierString(TQualifier qualifier)
{
    switch(qualifier)
    {
      case EvqIn:            return "in";
      case EvqOut:           return "out";
      case EvqInOut:         return "inout";
      case EvqConstReadOnly: return "const";
      default: UNREACHABLE();
    }

    return "";
}

TString OutputHLSL::typeString(const TType &type)
{
    if (type.getBasicType() == EbtStruct)
    {
        if (type.getTypeName() != "")
        {
            return structLookup(type.getTypeName());
        }
        else   // Nameless structure, define in place
        {
            return structureString(type, false);
        }
    }
    else if (type.isMatrix())
    {
        int cols = type.getCols();
        int rows = type.getRows();
        return "float" + str(cols) + "x" + str(rows);
    }
    else
    {
        switch (type.getBasicType())
        {
          case EbtFloat:
            switch (type.getNominalSize())
            {
              case 1: return "float";
              case 2: return "float2";
              case 3: return "float3";
              case 4: return "float4";
            }
          case EbtInt:
            switch (type.getNominalSize())
            {
              case 1: return "int";
              case 2: return "int2";
              case 3: return "int3";
              case 4: return "int4";
            }
          case EbtUInt:
            switch (type.getNominalSize())
            {
              case 1: return "uint";
              case 2: return "uint2";
              case 3: return "uint3";
              case 4: return "uint4";
            }
          case EbtBool:
            switch (type.getNominalSize())
            {
              case 1: return "bool";
              case 2: return "bool2";
              case 3: return "bool3";
              case 4: return "bool4";
            }
          case EbtVoid:
            return "void";
          case EbtSampler2D:
          case EbtISampler2D:
          case EbtUSampler2D:
            return "sampler2D";
          case EbtSamplerCube:
          case EbtISamplerCube:
          case EbtUSamplerCube:
            return "samplerCUBE";
          case EbtSamplerExternalOES:
            return "sampler2D";
          default:
            break;
        }
    }

    UNREACHABLE();
    return "<unknown type>";
}

TString OutputHLSL::textureString(const TType &type)
{
    switch (type.getBasicType())
    {
      case EbtSampler2D:
        return "Texture2D";
      case EbtSamplerCube:
        return "TextureCube";
      case EbtSamplerExternalOES:
        return "Texture2D";
      case EbtISampler2D:
        return "Texture2D<int4>";
      case EbtISamplerCube:
        return "TextureCube<int4>";
      case EbtUSampler2D:
        return "Texture2D<uint4>";
      case EbtUSamplerCube:
        return "TextureCube<uint4>";
      default:
        break;
    }

    UNREACHABLE();
    return "<unknown texture type>";
}

TString OutputHLSL::arrayString(const TType &type)
{
    if (!type.isArray())
    {
        return "";
    }

    return "[" + str(type.getArraySize()) + "]";
}

TString OutputHLSL::initializer(const TType &type)
{
    TString string;

    for (int component = 0; component < type.getObjectSize(); component++)
    {
        string += "0";

        if (component < type.getObjectSize() - 1)
        {
            string += ", ";
        }
    }

    return "{" + string + "}";
}

TString OutputHLSL::structureString(const TType &structType, bool useHLSLRowMajorPacking)
{
    ASSERT(structType.getStruct());

    const TTypeList &fields = *structType.getStruct();
    const bool isNameless = (structType.getTypeName() == "");
    const TString &structName = structureTypeName(structType, useHLSLRowMajorPacking);

    const TString declareString = (isNameless ? "struct" : "struct " + structName);

    TString structure;
    structure += declareString + "\n"
                 "{\n";

    for (unsigned int i = 0; i < fields.size(); i++)
    {
        const TType &field = *fields[i].type;

        structure += "    " + structureTypeName(field, useHLSLRowMajorPacking) + " " +
                     decorateField(field.getFieldName(), structType) + arrayString(field) + ";\n";
    }

    // Nameless structs do not finish with a semicolon and newline, to leave room for an instance variable
    structure += (isNameless ? "} " : "};\n");

    return structure;
}

TString OutputHLSL::structureTypeName(const TType &structType, bool useHLSLRowMajorPacking)
{
    if (structType.getBasicType() != EbtStruct)
    {
        return typeString(structType);
    }

    if (structType.getTypeName() == "")
    {
        return "";
    }

    TString prefix = "";

    // Structs packed with row-major matrices in HLSL are prefixed with "rm"
    // GLSL column-major maps to HLSL row-major, and the converse is true
    if (useHLSLRowMajorPacking)
    {
        prefix += "rm";
    }

    return prefix + typeString(structType);
}

void OutputHLSL::addConstructor(const TType &type, const TString &name, const TIntermSequence *parameters)
{
    if (name == "")
    {
        return;   // Nameless structures don't have constructors
    }

    if (type.getStruct() && mStructNames.find(decorate(name)) != mStructNames.end())
    {
        return;   // Already added
    }

    TType ctorType = type;
    ctorType.clearArrayness();
    ctorType.setPrecision(EbpHigh);
    ctorType.setQualifier(EvqTemporary);

    TString ctorName = type.getStruct() ? decorate(name) : name;

    typedef std::vector<TType> ParameterArray;
    ParameterArray ctorParameters;

    if (type.getStruct())
    {
        mStructNames.insert(decorate(name));

        const TString &structure = structureString(type, false);

        if (std::find(mStructDeclarations.begin(), mStructDeclarations.end(), structure) == mStructDeclarations.end())
        {
            // Add row-major packed struct for interface blocks
            TString rowMajorString = "#pragma pack_matrix(row_major)\n" +
                                     structureString(type, true) +
                                     "#pragma pack_matrix(column_major)\n";

            mStructDeclarations.push_back(structure);
            mStructDeclarations.push_back(rowMajorString);
        }

        const TTypeList &fields = *type.getStruct();
        for (unsigned int i = 0; i < fields.size(); i++)
        {
            ctorParameters.push_back(*fields[i].type);
        }
    }
    else if (parameters)
    {
        for (TIntermSequence::const_iterator parameter = parameters->begin(); parameter != parameters->end(); parameter++)
        {
            ctorParameters.push_back((*parameter)->getAsTyped()->getType());
        }
    }
    else UNREACHABLE();

    TString constructor;

    if (ctorType.getStruct())
    {
        constructor += ctorName + " " + ctorName + "_ctor(";
    }
    else   // Built-in type
    {
        constructor += typeString(ctorType) + " " + ctorName + "(";
    }

    for (unsigned int parameter = 0; parameter < ctorParameters.size(); parameter++)
    {
        const TType &type = ctorParameters[parameter];

        constructor += typeString(type) + " x" + str(parameter) + arrayString(type);

        if (parameter < ctorParameters.size() - 1)
        {
            constructor += ", ";
        }
    }

    constructor += ")\n"
                   "{\n";

    if (ctorType.getStruct())
    {
        constructor += "    " + ctorName + " structure = {";
    }
    else
    {
        constructor += "    return " + typeString(ctorType) + "(";
    }

    if (ctorType.isMatrix() && ctorParameters.size() == 1)
    {
        int rows = ctorType.getRows();
        int cols = ctorType.getCols();
        const TType &parameter = ctorParameters[0];

        if (parameter.isScalar())
        {
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                {
                    constructor += TString((row == col) ? "x0" : "0.0");
                    
                    if (row < rows - 1 || col < cols - 1)
                    {
                        constructor += ", ";
                    }
                }
            }
        }
        else if (parameter.isMatrix())
        {
            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < cols; col++)
                {
                    if (row < parameter.getRows() && col < parameter.getCols())
                    {
                        constructor += TString("x0") + "[" + str(row) + "]" + "[" + str(col) + "]";
                    }
                    else
                    {
                        constructor += TString((row == col) ? "1.0" : "0.0");
                    }

                    if (row < rows - 1 || col < cols - 1)
                    {
                        constructor += ", ";
                    }
                }
            }
        }
        else UNREACHABLE();
    }
    else
    {
        int remainingComponents = ctorType.getObjectSize();
        int parameterIndex = 0;

        while (remainingComponents > 0)
        {
            const TType &parameter = ctorParameters[parameterIndex];
            bool moreParameters = parameterIndex < (int)ctorParameters.size() - 1;

            constructor += "x" + str(parameterIndex);

            if (parameter.isScalar())
            {
                remainingComponents -= parameter.getObjectSize();
            }
            else if (parameter.isVector())
            {
                if (remainingComponents == parameter.getObjectSize() || moreParameters)
                {
                    remainingComponents -= parameter.getObjectSize();
                }
                else if (remainingComponents < parameter.getNominalSize())
                {
                    switch (remainingComponents)
                    {
                      case 1: constructor += ".x";    break;
                      case 2: constructor += ".xy";   break;
                      case 3: constructor += ".xyz";  break;
                      case 4: constructor += ".xyzw"; break;
                      default: UNREACHABLE();
                    }

                    remainingComponents = 0;
                }
                else UNREACHABLE();
            }
            else if (parameter.isMatrix() || parameter.getStruct())
            {
                ASSERT(remainingComponents == parameter.getObjectSize() || moreParameters);
                
                remainingComponents -= parameter.getObjectSize();
            }
            else UNREACHABLE();

            if (moreParameters)
            {
                parameterIndex++;
            }

            if (remainingComponents)
            {
                constructor += ", ";
            }
        }
    }

    if (ctorType.getStruct())
    {
        constructor += "};\n"
                       "    return structure;\n"
                       "}\n";
    }
    else
    {
        constructor += ");\n"
                       "}\n";
    }

    mConstructors.insert(constructor);
}

const ConstantUnion *OutputHLSL::writeConstantUnion(const TType &type, const ConstantUnion *constUnion)
{
    TInfoSinkBase &out = mBody;

    if (type.getBasicType() == EbtStruct)
    {
        out << structLookup(type.getTypeName()) + "_ctor(";
        
        const TTypeList *structure = type.getStruct();

        for (size_t i = 0; i < structure->size(); i++)
        {
            const TType *fieldType = (*structure)[i].type;

            constUnion = writeConstantUnion(*fieldType, constUnion);

            if (i != structure->size() - 1)
            {
                out << ", ";
            }
        }

        out << ")";
    }
    else
    {
        int size = type.getObjectSize();
        bool writeType = size > 1;
        
        if (writeType)
        {
            out << typeString(type) << "(";
        }

        for (int i = 0; i < size; i++, constUnion++)
        {
            switch (constUnion->getType())
            {
              case EbtFloat: out << std::min(FLT_MAX, std::max(-FLT_MAX, constUnion->getFConst())); break;
              case EbtInt:   out << constUnion->getIConst(); break;
              case EbtUInt:  out << constUnion->getUConst(); break;
              case EbtBool:  out << constUnion->getBConst(); break;
              default: UNREACHABLE();
            }

            if (i != size - 1)
            {
                out << ", ";
            }
        }

        if (writeType)
        {
            out << ")";
        }
    }

    return constUnion;
}

TString OutputHLSL::scopeString(unsigned int depthLimit)
{
    TString string;

    for (unsigned int i = 0; i < mScopeBracket.size() && i < depthLimit; i++)
    {
        string += "_" + str(i);
    }

    return string;
}

TString OutputHLSL::scopedStruct(const TString &typeName)
{
    if (typeName == "")
    {
        return typeName;
    }

    return typeName + scopeString(mScopeDepth);
}

TString OutputHLSL::structLookup(const TString &typeName)
{
    for (int depth = mScopeDepth; depth >= 0; depth--)
    {
        TString scopedName = decorate(typeName + scopeString(depth));

        for (StructNames::iterator structName = mStructNames.begin(); structName != mStructNames.end(); structName++)
        {
            if (*structName == scopedName)
            {
                return scopedName;
            }
        }
    }

    UNREACHABLE();   // Should have found a matching constructor

    return typeName;
}

TString OutputHLSL::decorate(const TString &string)
{
    if (string.compare(0, 3, "gl_") != 0 && string.compare(0, 3, "dx_") != 0)
    {
        return "_" + string;
    }
    
    return string;
}

TString OutputHLSL::decorateUniform(const TString &string, const TType &type)
{
    if (type.getBasicType() == EbtSamplerExternalOES)
    {
        return "ex_" + string;
    }
    
    return decorate(string);
}

TString OutputHLSL::decorateField(const TString &string, const TType &structure)
{
    if (structure.getTypeName().compare(0, 3, "gl_") != 0)
    {
        return decorate(string);
    }

    return string;
}

TString OutputHLSL::registerString(TIntermSymbol *operand)
{
    ASSERT(operand->getQualifier() == EvqUniform);

    if (IsSampler(operand->getBasicType()))
    {
        return "s" + str(samplerRegister(operand));
    }

    return "c" + str(uniformRegister(operand));
}

int OutputHLSL::samplerRegister(TIntermSymbol *sampler)
{
    const TType &type = sampler->getType();
    ASSERT(IsSampler(type.getBasicType()));

    int index = mSamplerRegister;
    mSamplerRegister += sampler->totalRegisterCount();

    declareUniform(type, sampler->getSymbol(), index);

    return index;
}

int OutputHLSL::uniformRegister(TIntermSymbol *uniform)
{
    const TType &type = uniform->getType();
    ASSERT(!IsSampler(type.getBasicType()));

    int index = mUniformRegister;
    mUniformRegister += uniform->totalRegisterCount();

    declareUniform(type, uniform->getSymbol(), index);

    return index;
}

void OutputHLSL::declareUniformToList(const TType &type, const TString &name, int index, ActiveUniforms& output)
{
    const TTypeList *structure = type.getStruct();

    if (!structure)
    {
        const bool isRowMajorMatrix = (type.isMatrix() && type.getLayoutQualifier().matrixPacking == EmpRowMajor);
        output.push_back(Uniform(glVariableType(type), glVariablePrecision(type), name.c_str(), (unsigned int)type.getArraySize(), (unsigned int)index, isRowMajorMatrix));
    }
    else
    {
        Uniform structUniform(GL_NONE, GL_NONE, name.c_str(), (unsigned int)type.getArraySize(), (unsigned int)index, false);

        int fieldIndex = index;

        for (size_t i = 0; i < structure->size(); i++)
        {
            TType fieldType = *(*structure)[i].type;
            const TString &fieldName = fieldType.getFieldName();

            // make sure to copy matrix packing information
            fieldType.setLayoutQualifier(type.getLayoutQualifier());

            declareUniformToList(fieldType, fieldName, fieldIndex, structUniform.fields);
            fieldIndex += fieldType.totalRegisterCount();
        }

        output.push_back(structUniform);
    }
}

void OutputHLSL::declareUniform(const TType &type, const TString &name, int index)
{
    declareUniformToList(type, name, index, mActiveUniforms);
}

GLenum OutputHLSL::glVariableType(const TType &type)
{
    if (type.getBasicType() == EbtFloat)
    {
        if (type.isScalar())
        {
            return GL_FLOAT;
        }
        else if (type.isVector())
        {
            switch(type.getNominalSize())
            {
              case 2: return GL_FLOAT_VEC2;
              case 3: return GL_FLOAT_VEC3;
              case 4: return GL_FLOAT_VEC4;
              default: UNREACHABLE();
            }
        }
        else if (type.isMatrix())
        {
            switch (type.getCols())
            {
              case 2:
                switch(type.getRows())
                {
                  case 2: return GL_FLOAT_MAT2;
                  case 3: return GL_FLOAT_MAT2x3;
                  case 4: return GL_FLOAT_MAT2x4;
                  default: UNREACHABLE();
                }

              case 3:
                switch(type.getRows())
                {
                  case 2: return GL_FLOAT_MAT3x2;
                  case 3: return GL_FLOAT_MAT3;
                  case 4: return GL_FLOAT_MAT3x4;
                  default: UNREACHABLE();
                }

              case 4:
                switch(type.getRows())
                {
                  case 2: return GL_FLOAT_MAT4x2;
                  case 3: return GL_FLOAT_MAT4x3;
                  case 4: return GL_FLOAT_MAT4;
                  default: UNREACHABLE();
                }

              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();
    }
    else if (type.getBasicType() == EbtInt)
    {
        if (type.isScalar())
        {
            return GL_INT;
        }
        else if (type.isVector())
        {
            switch(type.getNominalSize())
            {
              case 2: return GL_INT_VEC2;
              case 3: return GL_INT_VEC3;
              case 4: return GL_INT_VEC4;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();
    }
    else if (type.getBasicType() == EbtUInt)
    {
        if (type.isScalar())
        {
            return GL_UNSIGNED_INT;
        }
        else if (type.isVector())
        {
            switch(type.getNominalSize())
            {
              case 2: return GL_UNSIGNED_INT_VEC2;
              case 3: return GL_UNSIGNED_INT_VEC3;
              case 4: return GL_UNSIGNED_INT_VEC4;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();
    }
    else if (type.getBasicType() == EbtBool)
    {
        if (type.isScalar())
        {
            return GL_BOOL;
        }
        else if (type.isVector())
        {
            switch(type.getNominalSize())
            {
              case 2: return GL_BOOL_VEC2;
              case 3: return GL_BOOL_VEC3;
              case 4: return GL_BOOL_VEC4;
              default: UNREACHABLE();
            }
        }
        else UNREACHABLE();
    }
    else if (type.getBasicType() == EbtSampler2D)
    {
        return GL_SAMPLER_2D;
    }
    else if (type.getBasicType() == EbtSampler3D)
    {
        return GL_SAMPLER_3D;
    }
    else if (type.getBasicType() == EbtSamplerCube)
    {
        return GL_SAMPLER_CUBE;
    }
    else if (type.getBasicType() == EbtISampler2D)
    {
        return GL_INT_SAMPLER_2D;
    }
    else if (type.getBasicType() == EbtISampler3D)
    {
        return GL_INT_SAMPLER_3D;
    }
    else if (type.getBasicType() == EbtISamplerCube)
    {
        return GL_INT_SAMPLER_CUBE;
    }
    else if (type.getBasicType() == EbtUSampler2D)
    {
        return GL_UNSIGNED_INT_SAMPLER_2D;
    }
    else if (type.getBasicType() == EbtUSampler3D)
    {
        return GL_UNSIGNED_INT_SAMPLER_3D;
    }
    else if (type.getBasicType() == EbtUSamplerCube)
    {
        return GL_UNSIGNED_INT_SAMPLER_CUBE;
    }
    else UNREACHABLE();

    return GL_NONE;
}

GLenum OutputHLSL::glVariablePrecision(const TType &type)
{
    if (type.getBasicType() == EbtFloat)
    {
        switch (type.getPrecision())
        {
          case EbpHigh:   return GL_HIGH_FLOAT;
          case EbpMedium: return GL_MEDIUM_FLOAT;
          case EbpLow:    return GL_LOW_FLOAT;
          case EbpUndefined:
            // Should be defined as the default precision by the parser
          default: UNREACHABLE();
        }
    }
    else if (type.getBasicType() == EbtInt || type.getBasicType() == EbtUInt)
    {
        switch (type.getPrecision())
        {
          case EbpHigh:   return GL_HIGH_INT;
          case EbpMedium: return GL_MEDIUM_INT;
          case EbpLow:    return GL_LOW_INT;
          case EbpUndefined:
            // Should be defined as the default precision by the parser
          default: UNREACHABLE();
        }
    }

    // Other types (boolean, sampler) don't have a precision
    return GL_NONE;
}

bool OutputHLSL::isVaryingOut(TQualifier qualifier)
{
    switch(qualifier)
    {
      case EvqVaryingOut:
      case EvqInvariantVaryingOut:
      case EvqSmoothOut:
      case EvqFlatOut:
      case EvqCentroidOut:
        return true;
    }

    return false;
}

bool OutputHLSL::isVaryingIn(TQualifier qualifier)
{
    switch(qualifier)
    {
      case EvqVaryingIn:
      case EvqInvariantVaryingIn:
      case EvqSmoothIn:
      case EvqFlatIn:
      case EvqCentroidIn:
        return true;
    }

    return false;
}

bool OutputHLSL::isVarying(TQualifier qualifier)
{
    return isVaryingIn(qualifier) || isVaryingOut(qualifier);
}

}
