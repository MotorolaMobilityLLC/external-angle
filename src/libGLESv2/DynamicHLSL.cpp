//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DynamicHLSL.cpp: Implementation for link and run-time HLSL generation
//

#include "precompiled.h"

#include "libGLESv2/DynamicHLSL.h"
#include "libGLESv2/Shader.h"
#include "libGLESv2/Program.h"
#include "libGLESv2/renderer/Renderer.h"
#include "common/utilities.h"
#include "libGLESv2/ProgramBinary.h"

#include "compiler/translator/HLSLLayoutEncoder.h"

namespace gl_d3d
{

std::string TypeString(GLenum type)
{
    switch (type)
    {
        case GL_FLOAT:        return "float";
        case GL_FLOAT_VEC2:   return "float2";
        case GL_FLOAT_VEC3:   return "float3";
        case GL_FLOAT_VEC4:   return "float4";
        case GL_INT:          return "int";
        case GL_INT_VEC2:     return "int2";
        case GL_INT_VEC3:     return "int3";
        case GL_INT_VEC4:     return "int4";
        case GL_UNSIGNED_INT: return "uint";
        case GL_UNSIGNED_INT_VEC2: return "uint2";
        case GL_UNSIGNED_INT_VEC3: return "uint3";
        case GL_UNSIGNED_INT_VEC4: return "uint4";
        case GL_FLOAT_MAT2:   return "float2x2";
        case GL_FLOAT_MAT3:   return "float3x3";
        case GL_FLOAT_MAT4:   return "float4x4";
        case GL_FLOAT_MAT2x3: return "float2x3";
        case GL_FLOAT_MAT3x2: return "float3x2";
        case GL_FLOAT_MAT2x4: return "float2x4";
        case GL_FLOAT_MAT4x2: return "float4x2";
        case GL_FLOAT_MAT3x4: return "float3x4";
        case GL_FLOAT_MAT4x3: return "float4x3";
        default:  UNREACHABLE(); return "invalid-gl-type";
    }
}

}

namespace gl
{

static std::string Str(int i)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", i);
    return buffer;
}

static std::string ArrayString(int i)
{
    return "[" + Str(i) + "]";
}

std::string ArrayString(unsigned int i)
{
    return (i == GL_INVALID_INDEX ? "" : "[" + Str(i) + "]");
}

DynamicHLSL::DynamicHLSL(rx::Renderer *const renderer)
    : mRenderer(renderer)
{
}

// Packs varyings into generic varying registers, using the algorithm from [OpenGL ES Shading Language 1.00 rev. 17] appendix A section 7 page 111
// Returns the number of used varying registers, or -1 if unsuccesful
int DynamicHLSL::packVaryings(InfoLog &infoLog, const sh::ShaderVariable *packing[][4], FragmentShader *fragmentShader)
{
    const int maxVaryingVectors = mRenderer->getMaxVaryingVectors();

    fragmentShader->resetVaryingsRegisterAssignment();

    for (unsigned int varyingIndex = 0; varyingIndex < fragmentShader->mVaryings.size(); varyingIndex++)
    {
        sh::Varying *varying = &fragmentShader->mVaryings[varyingIndex];
        GLenum transposedType = TransposeMatrixType(varying->type);

        // matrices within varying structs are not transposed
        int registers = (varying->isStruct() ? sh::HLSLVariableRegisterCount(*varying) : gl::VariableRowCount(transposedType)) * varying->elementCount();
        int elements = (varying->isStruct() ? 4 : VariableColumnCount(transposedType));
        bool success = false;

        if (elements == 2 || elements == 3 || elements == 4)
        {
            for (int r = 0; r <= maxVaryingVectors - registers && !success; r++)
            {
                bool available = true;

                for (int y = 0; y < registers && available; y++)
                {
                    for (int x = 0; x < elements && available; x++)
                    {
                        if (packing[r + y][x])
                        {
                            available = false;
                        }
                    }
                }

                if (available)
                {
                    varying->registerIndex = r;
                    varying->elementIndex = 0;

                    for (int y = 0; y < registers; y++)
                    {
                        for (int x = 0; x < elements; x++)
                        {
                            packing[r + y][x] = &*varying;
                        }
                    }

                    success = true;
                }
            }

            if (!success && elements == 2)
            {
                for (int r = maxVaryingVectors - registers; r >= 0 && !success; r--)
                {
                    bool available = true;

                    for (int y = 0; y < registers && available; y++)
                    {
                        for (int x = 2; x < 4 && available; x++)
                        {
                            if (packing[r + y][x])
                            {
                                available = false;
                            }
                        }
                    }

                    if (available)
                    {
                        varying->registerIndex = r;
                        varying->elementIndex = 2;

                        for (int y = 0; y < registers; y++)
                        {
                            for (int x = 2; x < 4; x++)
                            {
                                packing[r + y][x] = &*varying;
                            }
                        }

                        success = true;
                    }
                }
            }
        }
        else if (elements == 1)
        {
            int space[4] = {0};

            for (int y = 0; y < maxVaryingVectors; y++)
            {
                for (int x = 0; x < 4; x++)
                {
                    space[x] += packing[y][x] ? 0 : 1;
                }
            }

            int column = 0;

            for (int x = 0; x < 4; x++)
            {
                if (space[x] >= registers && space[x] < space[column])
                {
                    column = x;
                }
            }

            if (space[column] >= registers)
            {
                for (int r = 0; r < maxVaryingVectors; r++)
                {
                    if (!packing[r][column])
                    {
                        varying->registerIndex = r;

                        for (int y = r; y < r + registers; y++)
                        {
                            packing[y][column] = &*varying;
                        }

                        break;
                    }
                }

                varying->elementIndex = column;

                success = true;
            }
        }
        else UNREACHABLE();

        if (!success)
        {
            infoLog.append("Could not pack varying %s", varying->name.c_str());

            return -1;
        }
    }

    // Return the number of used registers
    int registers = 0;

    for (int r = 0; r < maxVaryingVectors; r++)
    {
        if (packing[r][0] || packing[r][1] || packing[r][2] || packing[r][3])
        {
            registers++;
        }
    }

    return registers;
}

std::string DynamicHLSL::generateVaryingHLSL(FragmentShader *fragmentShader, const std::string &varyingSemantic) const
{
    std::string varyingHLSL;

    for (unsigned int varyingIndex = 0; varyingIndex < fragmentShader->mVaryings.size(); varyingIndex++)
    {
        sh::Varying *varying = &fragmentShader->mVaryings[varyingIndex];
        if (varying->registerAssigned())
        {
            for (unsigned int elementIndex = 0; elementIndex < varying->elementCount(); elementIndex++)
            {
                GLenum transposedType = TransposeMatrixType(varying->type);
                int variableRows = (varying->isStruct() ? 1 : VariableRowCount(transposedType));
                for (int row = 0; row < variableRows; row++)
                {
                    switch (varying->interpolation)
                    {
                      case sh::INTERPOLATION_SMOOTH:   varyingHLSL += "    ";                 break;
                      case sh::INTERPOLATION_FLAT:     varyingHLSL += "    nointerpolation "; break;
                      case sh::INTERPOLATION_CENTROID: varyingHLSL += "    centroid ";        break;
                      default:  UNREACHABLE();
                    }

                    std::string n = Str(varying->registerIndex + elementIndex * variableRows + row);

                    // matrices within structs are not transposed, hence we do not use the special struct prefix "rm"
                    std::string typeString = varying->isStruct() ? "_" + varying->structName :
                                             gl_d3d::TypeString(UniformComponentType(transposedType)) + Str(VariableColumnCount(transposedType));

                    varyingHLSL += typeString + " v" + n + " : " + varyingSemantic + n + ";\n";
                }
            }
        }
        else UNREACHABLE();
    }

    return varyingHLSL;
}

bool DynamicHLSL::generateShaderLinkHLSL(InfoLog &infoLog, int registers, const sh::ShaderVariable *packing[][4],
                                         std::string& pixelHLSL, std::string& vertexHLSL,
                                         FragmentShader *fragmentShader, VertexShader *vertexShader,
                                         std::map<int, VariableLocation> *programOutputVars) const
{
    if (pixelHLSL.empty() || vertexHLSL.empty())
    {
        return false;
    }

    bool usesMRT = fragmentShader->mUsesMultipleRenderTargets;
    bool usesFragColor = fragmentShader->mUsesFragColor;
    bool usesFragData = fragmentShader->mUsesFragData;
    if (usesFragColor && usesFragData)
    {
        infoLog.append("Cannot use both gl_FragColor and gl_FragData in the same fragment shader.");
        return false;
    }

    // Write the HLSL input/output declarations
    const int shaderModel = mRenderer->getMajorShaderModel();
    const int maxVaryingVectors = mRenderer->getMaxVaryingVectors();

    const int registersNeeded = registers + (fragmentShader->mUsesFragCoord ? 1 : 0) + (fragmentShader->mUsesPointCoord ? 1 : 0);

    // Two cases when writing to gl_FragColor and using ESSL 1.0:
    // - with a 3.0 context, the output color is copied to channel 0
    // - with a 2.0 context, the output color is broadcast to all channels
    const bool broadcast = (fragmentShader->mUsesFragColor && mRenderer->getCurrentClientVersion() < 3);
    const unsigned int numRenderTargets = (broadcast || usesMRT ? mRenderer->getMaxRenderTargets() : 1);

    int shaderVersion = vertexShader->getShaderVersion();

    if (registersNeeded > maxVaryingVectors)
    {
        infoLog.append("No varying registers left to support gl_FragCoord/gl_PointCoord");

        return false;
    }

    std::string varyingSemantic = (vertexShader->mUsesPointSize && shaderModel == 3) ? "COLOR" : "TEXCOORD";
    std::string targetSemantic = (shaderModel >= 4) ? "SV_Target" : "COLOR";
    std::string positionSemantic = (shaderModel >= 4) ? "SV_Position" : "POSITION";
    std::string depthSemantic = (shaderModel >= 4) ? "SV_Depth" : "DEPTH";

    std::string varyingHLSL = generateVaryingHLSL(fragmentShader, varyingSemantic);

    // special varyings that use reserved registers
    int reservedRegisterIndex = registers;
    std::string fragCoordSemantic;
    std::string pointCoordSemantic;

    if (fragmentShader->mUsesFragCoord)
    {
        fragCoordSemantic = varyingSemantic + Str(reservedRegisterIndex++);
    }

    if (fragmentShader->mUsesPointCoord)
    {
        // Shader model 3 uses a special TEXCOORD semantic for point sprite texcoords.
        // In DX11 we compute this in the GS.
        if (shaderModel == 3)
        {
            pointCoordSemantic = "TEXCOORD0";
        }
        else if (shaderModel >= 4)
        {
            pointCoordSemantic = varyingSemantic + Str(reservedRegisterIndex++);
        }
    }

    vertexHLSL += "struct VS_INPUT\n"
                  "{\n";

    int semanticIndex = 0;
    const std::vector<sh::Attribute> &activeAttributes = vertexShader->mActiveAttributes;
    for (unsigned int attributeIndex = 0; attributeIndex < activeAttributes.size(); attributeIndex++)
    {
        const sh::Attribute &attribute = activeAttributes[attributeIndex];
        vertexHLSL += "    " + gl_d3d::TypeString(TransposeMatrixType(attribute.type)) + " ";
        vertexHLSL += decorateAttribute(attribute.name) + " : TEXCOORD" + Str(semanticIndex) + ";\n";

        semanticIndex += AttributeRegisterCount(attribute.type);
    }

    vertexHLSL += "};\n"
                  "\n"
                  "struct VS_OUTPUT\n"
                  "{\n";

    if (shaderModel < 4)
    {
        vertexHLSL += "    float4 gl_Position : " + positionSemantic + ";\n";
    }

    vertexHLSL += varyingHLSL;

    if (fragmentShader->mUsesFragCoord)
    {
        vertexHLSL += "    float4 gl_FragCoord : " + fragCoordSemantic + ";\n";
    }

    if (vertexShader->mUsesPointSize && shaderModel >= 3)
    {
        vertexHLSL += "    float gl_PointSize : PSIZE;\n";
    }

    if (shaderModel >= 4)
    {
        vertexHLSL += "    float4 gl_Position : " + positionSemantic + ";\n";
    }

    vertexHLSL += "};\n"
                  "\n"
                  "VS_OUTPUT main(VS_INPUT input)\n"
                  "{\n";

    for (unsigned int attributeIndex = 0; attributeIndex < activeAttributes.size(); attributeIndex++)
    {
        const sh::ShaderVariable &attribute = activeAttributes[attributeIndex];
        vertexHLSL += "    " + decorateAttribute(attribute.name) + " = ";

        if (IsMatrixType(attribute.type))   // Matrix
        {
            vertexHLSL += "transpose";
        }

        vertexHLSL += "(input." + decorateAttribute(attribute.name) + ");\n";
    }

    if (shaderModel >= 4)
    {
        vertexHLSL += "\n"
                      "    gl_main();\n"
                      "\n"
                      "    VS_OUTPUT output;\n"
                      "    output.gl_Position.x = gl_Position.x;\n"
                      "    output.gl_Position.y = -gl_Position.y;\n"
                      "    output.gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;\n"
                      "    output.gl_Position.w = gl_Position.w;\n";
    }
    else
    {
        vertexHLSL += "\n"
                      "    gl_main();\n"
                      "\n"
                      "    VS_OUTPUT output;\n"
                      "    output.gl_Position.x = gl_Position.x * dx_ViewAdjust.z + dx_ViewAdjust.x * gl_Position.w;\n"
                      "    output.gl_Position.y = -(gl_Position.y * dx_ViewAdjust.w + dx_ViewAdjust.y * gl_Position.w);\n"
                      "    output.gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;\n"
                      "    output.gl_Position.w = gl_Position.w;\n";
    }

    if (vertexShader->mUsesPointSize && shaderModel >= 3)
    {
        vertexHLSL += "    output.gl_PointSize = gl_PointSize;\n";
    }

    if (fragmentShader->mUsesFragCoord)
    {
        vertexHLSL += "    output.gl_FragCoord = gl_Position;\n";
    }

    for (unsigned int vertVaryingIndex = 0; vertVaryingIndex < vertexShader->mVaryings.size(); vertVaryingIndex++)
    {
        sh::Varying *varying = &vertexShader->mVaryings[vertVaryingIndex];
        if (varying->registerAssigned())
        {
            for (unsigned int elementIndex = 0; elementIndex < varying->elementCount(); elementIndex++)
            {
                int variableRows = (varying->isStruct() ? 1 : VariableRowCount(TransposeMatrixType(varying->type)));

                for (int row = 0; row < variableRows; row++)
                {
                    int r = varying->registerIndex + elementIndex * variableRows + row;
                    vertexHLSL += "    output.v" + Str(r);

                    bool sharedRegister = false;   // Register used by multiple varyings

                    for (int x = 0; x < 4; x++)
                    {
                        if (packing[r][x] && packing[r][x] != packing[r][0])
                        {
                            sharedRegister = true;
                            break;
                        }
                    }

                    if(sharedRegister)
                    {
                        vertexHLSL += ".";

                        for (int x = 0; x < 4; x++)
                        {
                            if (packing[r][x] == &*varying)
                            {
                                switch(x)
                                {
                                  case 0: vertexHLSL += "x"; break;
                                  case 1: vertexHLSL += "y"; break;
                                  case 2: vertexHLSL += "z"; break;
                                  case 3: vertexHLSL += "w"; break;
                                }
                            }
                        }
                    }

                    vertexHLSL += " = _" + varying->name;

                    if (varying->isArray())
                    {
                        vertexHLSL += ArrayString(elementIndex);
                    }

                    if (variableRows > 1)
                    {
                        vertexHLSL += ArrayString(row);
                    }

                    vertexHLSL += ";\n";
                }
            }
        }
    }

    vertexHLSL += "\n"
                  "    return output;\n"
                  "}\n";

    pixelHLSL += "struct PS_INPUT\n"
                 "{\n";

    pixelHLSL += varyingHLSL;

    if (fragmentShader->mUsesFragCoord)
    {
        pixelHLSL += "    float4 gl_FragCoord : " + fragCoordSemantic + ";\n";
    }

    if (fragmentShader->mUsesPointCoord && shaderModel >= 3)
    {
        pixelHLSL += "    float2 gl_PointCoord : " + pointCoordSemantic + ";\n";
    }

    // Must consume the PSIZE element if the geometry shader is not active
    // We won't know if we use a GS until we draw
    if (vertexShader->mUsesPointSize && shaderModel >= 4)
    {
        pixelHLSL += "    float gl_PointSize : PSIZE;\n";
    }

    if (fragmentShader->mUsesFragCoord)
    {
        if (shaderModel >= 4)
        {
            pixelHLSL += "    float4 dx_VPos : SV_Position;\n";
        }
        else if (shaderModel >= 3)
        {
            pixelHLSL += "    float2 dx_VPos : VPOS;\n";
        }
    }

    pixelHLSL += "};\n"
                 "\n"
                 "struct PS_OUTPUT\n"
                 "{\n";

    if (shaderVersion < 300)
    {
        for (unsigned int renderTargetIndex = 0; renderTargetIndex < numRenderTargets; renderTargetIndex++)
        {
            pixelHLSL += "    float4 gl_Color" + Str(renderTargetIndex) + " : " + targetSemantic + Str(renderTargetIndex) + ";\n";
        }

        if (fragmentShader->mUsesFragDepth)
        {
            pixelHLSL += "    float gl_Depth : " + depthSemantic + ";\n";
        }
    }
    else
    {
        defineOutputVariables(fragmentShader, programOutputVars);

        const std::vector<sh::Attribute> &shaderOutputVars = fragmentShader->getOutputVariables();
        for (auto locationIt = programOutputVars->begin(); locationIt != programOutputVars->end(); locationIt++)
        {
            const VariableLocation &outputLocation = locationIt->second;
            const sh::ShaderVariable &outputVariable = shaderOutputVars[outputLocation.index];
            const std::string &elementString = (outputLocation.element == GL_INVALID_INDEX ? "" : Str(outputLocation.element));

            pixelHLSL += "    " + gl_d3d::TypeString(outputVariable.type) +
                         " out_" + outputLocation.name + elementString +
                         " : " + targetSemantic + Str(locationIt->first) + ";\n";
        }
    }

    pixelHLSL += "};\n"
                 "\n";

    if (fragmentShader->mUsesFrontFacing)
    {
        if (shaderModel >= 4)
        {
            pixelHLSL += "PS_OUTPUT main(PS_INPUT input, bool isFrontFace : SV_IsFrontFace)\n"
                         "{\n";
        }
        else
        {
            pixelHLSL += "PS_OUTPUT main(PS_INPUT input, float vFace : VFACE)\n"
                         "{\n";
        }
    }
    else
    {
        pixelHLSL += "PS_OUTPUT main(PS_INPUT input)\n"
                     "{\n";
    }

    if (fragmentShader->mUsesFragCoord)
    {
        pixelHLSL += "    float rhw = 1.0 / input.gl_FragCoord.w;\n";

        if (shaderModel >= 4)
        {
            pixelHLSL += "    gl_FragCoord.x = input.dx_VPos.x;\n"
                         "    gl_FragCoord.y = input.dx_VPos.y;\n";
        }
        else if (shaderModel >= 3)
        {
            pixelHLSL += "    gl_FragCoord.x = input.dx_VPos.x + 0.5;\n"
                         "    gl_FragCoord.y = input.dx_VPos.y + 0.5;\n";
        }
        else
        {
            // dx_ViewCoords contains the viewport width/2, height/2, center.x and center.y. See Renderer::setViewport()
            pixelHLSL += "    gl_FragCoord.x = (input.gl_FragCoord.x * rhw) * dx_ViewCoords.x + dx_ViewCoords.z;\n"
                         "    gl_FragCoord.y = (input.gl_FragCoord.y * rhw) * dx_ViewCoords.y + dx_ViewCoords.w;\n";
        }

        pixelHLSL += "    gl_FragCoord.z = (input.gl_FragCoord.z * rhw) * dx_DepthFront.x + dx_DepthFront.y;\n"
                     "    gl_FragCoord.w = rhw;\n";
    }

    if (fragmentShader->mUsesPointCoord && shaderModel >= 3)
    {
        pixelHLSL += "    gl_PointCoord.x = input.gl_PointCoord.x;\n";
        pixelHLSL += "    gl_PointCoord.y = 1.0 - input.gl_PointCoord.y;\n";
    }

    if (fragmentShader->mUsesFrontFacing)
    {
        if (shaderModel <= 3)
        {
            pixelHLSL += "    gl_FrontFacing = (vFace * dx_DepthFront.z >= 0.0);\n";
        }
        else
        {
            pixelHLSL += "    gl_FrontFacing = isFrontFace;\n";
        }
    }

    for (unsigned int varyingIndex = 0; varyingIndex < fragmentShader->mVaryings.size(); varyingIndex++)
    {
        sh::Varying *varying = &fragmentShader->mVaryings[varyingIndex];
        if (varying->registerAssigned())
        {
            for (unsigned int elementIndex = 0; elementIndex < varying->elementCount(); elementIndex++)
            {
                GLenum transposedType = TransposeMatrixType(varying->type);
                int variableRows = (varying->isStruct() ? 1 : VariableRowCount(transposedType));
                for (int row = 0; row < variableRows; row++)
                {
                    std::string n = Str(varying->registerIndex + elementIndex * variableRows + row);
                    pixelHLSL += "    _" + varying->name;

                    if (varying->isArray())
                    {
                        pixelHLSL += ArrayString(elementIndex);
                    }

                    if (variableRows > 1)
                    {
                        pixelHLSL += ArrayString(row);
                    }

                    if (varying->isStruct())
                    {
                        pixelHLSL += " = input.v" + n + ";\n";   break;
                    }
                    else
                    {
                        switch (VariableColumnCount(transposedType))
                        {
                          case 1: pixelHLSL += " = input.v" + n + ".x;\n";   break;
                          case 2: pixelHLSL += " = input.v" + n + ".xy;\n";  break;
                          case 3: pixelHLSL += " = input.v" + n + ".xyz;\n"; break;
                          case 4: pixelHLSL += " = input.v" + n + ";\n";     break;
                          default: UNREACHABLE();
                        }
                    }
                }
            }
        }
        else UNREACHABLE();
    }

    pixelHLSL += "\n"
                 "    gl_main();\n"
                 "\n"
                 "    PS_OUTPUT output;\n";

    if (shaderVersion < 300)
    {
        for (unsigned int renderTargetIndex = 0; renderTargetIndex < numRenderTargets; renderTargetIndex++)
        {
            unsigned int sourceColorIndex = broadcast ? 0 : renderTargetIndex;

            pixelHLSL += "    output.gl_Color" + Str(renderTargetIndex) + " = gl_Color[" + Str(sourceColorIndex) + "];\n";
        }

        if (fragmentShader->mUsesFragDepth)
        {
            pixelHLSL += "    output.gl_Depth = gl_Depth;\n";
        }
    }
    else
    {
        for (auto locationIt = programOutputVars->begin(); locationIt != programOutputVars->end(); locationIt++)
        {
            const VariableLocation &outputLocation = locationIt->second;
            const std::string &variableName = "out_" + outputLocation.name;
            const std::string &outVariableName = variableName + (outputLocation.element == GL_INVALID_INDEX ? "" : Str(outputLocation.element));
            const std::string &staticVariableName = variableName + ArrayString(outputLocation.element);

            pixelHLSL += "    output." + outVariableName + " = " + staticVariableName + ";\n";
        }
    }

    pixelHLSL += "\n"
                 "    return output;\n"
                 "}\n";

    return true;
}

void DynamicHLSL::defineOutputVariables(FragmentShader *fragmentShader, std::map<int, VariableLocation> *programOutputVars) const
{
    const std::vector<sh::Attribute> &shaderOutputVars = fragmentShader->getOutputVariables();

    for (unsigned int outputVariableIndex = 0; outputVariableIndex < shaderOutputVars.size(); outputVariableIndex++)
    {
        const sh::Attribute &outputVariable = shaderOutputVars[outputVariableIndex];
        const int baseLocation = outputVariable.location == -1 ? 0 : outputVariable.location;

        if (outputVariable.arraySize > 0)
        {
            for (unsigned int elementIndex = 0; elementIndex < outputVariable.arraySize; elementIndex++)
            {
                const int location = baseLocation + elementIndex;
                ASSERT(programOutputVars->count(location) == 0);
                (*programOutputVars)[location] = VariableLocation(outputVariable.name, elementIndex, outputVariableIndex);
            }
        }
        else
        {
            ASSERT(programOutputVars->count(baseLocation) == 0);
            (*programOutputVars)[baseLocation] = VariableLocation(outputVariable.name, GL_INVALID_INDEX, outputVariableIndex);
        }
    }
}

std::string DynamicHLSL::generateGeometryShaderHLSL(int registers, const sh::ShaderVariable *packing[][4], FragmentShader *fragmentShader, VertexShader *vertexShader) const
{
    // for now we only handle point sprite emulation
    ASSERT(vertexShader->mUsesPointSize && mRenderer->getMajorShaderModel() >= 4);
    return generatePointSpriteHLSL(registers, packing, fragmentShader, vertexShader);
}

std::string DynamicHLSL::generatePointSpriteHLSL(int registers, const sh::ShaderVariable *packing[][4], FragmentShader *fragmentShader, VertexShader *vertexShader) const
{
    ASSERT(registers >= 0);
    ASSERT(vertexShader->mUsesPointSize);
    ASSERT(mRenderer->getMajorShaderModel() >= 4);

    std::string geomHLSL;

    std::string varyingSemantic = "TEXCOORD";

    std::string fragCoordSemantic;
    std::string pointCoordSemantic;

    int reservedRegisterIndex = registers;

    if (fragmentShader->mUsesFragCoord)
    {
        fragCoordSemantic = varyingSemantic + Str(reservedRegisterIndex++);
    }

    if (fragmentShader->mUsesPointCoord)
    {
        pointCoordSemantic = varyingSemantic + Str(reservedRegisterIndex++);
    }

    geomHLSL += "uniform float4 dx_ViewCoords : register(c1);\n"
                "\n"
                "struct GS_INPUT\n"
                "{\n";

    std::string varyingHLSL = generateVaryingHLSL(fragmentShader, varyingSemantic);

    geomHLSL += varyingHLSL;

    if (fragmentShader->mUsesFragCoord)
    {
        geomHLSL += "    float4 gl_FragCoord : " + fragCoordSemantic + ";\n";
    }

    geomHLSL += "    float gl_PointSize : PSIZE;\n"
                "    float4 gl_Position : SV_Position;\n"
                "};\n"
                "\n"
                "struct GS_OUTPUT\n"
                "{\n";

    geomHLSL += varyingHLSL;

    if (fragmentShader->mUsesFragCoord)
    {
        geomHLSL += "    float4 gl_FragCoord : " + fragCoordSemantic + ";\n";
    }

    if (fragmentShader->mUsesPointCoord)
    {
        geomHLSL += "    float2 gl_PointCoord : " + pointCoordSemantic + ";\n";
    }

    geomHLSL +=   "    float gl_PointSize : PSIZE;\n"
                  "    float4 gl_Position : SV_Position;\n"
                  "};\n"
                  "\n"
                  "static float2 pointSpriteCorners[] = \n"
                  "{\n"
                  "    float2( 0.5f, -0.5f),\n"
                  "    float2( 0.5f,  0.5f),\n"
                  "    float2(-0.5f, -0.5f),\n"
                  "    float2(-0.5f,  0.5f)\n"
                  "};\n"
                  "\n"
                  "static float2 pointSpriteTexcoords[] = \n"
                  "{\n"
                  "    float2(1.0f, 1.0f),\n"
                  "    float2(1.0f, 0.0f),\n"
                  "    float2(0.0f, 1.0f),\n"
                  "    float2(0.0f, 0.0f)\n"
                  "};\n"
                  "\n"
                  "static float minPointSize = " + Str(ALIASED_POINT_SIZE_RANGE_MIN) + ".0f;\n"
                  "static float maxPointSize = " + Str(mRenderer->getMaxPointSize()) + ".0f;\n"
                  "\n"
                  "[maxvertexcount(4)]\n"
                  "void main(point GS_INPUT input[1], inout TriangleStream<GS_OUTPUT> outStream)\n"
                  "{\n"
                  "    GS_OUTPUT output = (GS_OUTPUT)0;\n"
                  "    output.gl_PointSize = input[0].gl_PointSize;\n";

    for (int r = 0; r < registers; r++)
    {
        geomHLSL += "    output.v" + Str(r) + " = input[0].v" + Str(r) + ";\n";
    }

    if (fragmentShader->mUsesFragCoord)
    {
        geomHLSL += "    output.gl_FragCoord = input[0].gl_FragCoord;\n";
    }

    geomHLSL += "    \n"
                "    float gl_PointSize = clamp(input[0].gl_PointSize, minPointSize, maxPointSize);\n"
                "    float4 gl_Position = input[0].gl_Position;\n"
                "    float2 viewportScale = float2(1.0f / dx_ViewCoords.x, 1.0f / dx_ViewCoords.y) * gl_Position.w;\n";

    for (int corner = 0; corner < 4; corner++)
    {
        geomHLSL += "    \n"
                    "    output.gl_Position = gl_Position + float4(pointSpriteCorners[" + Str(corner) + "] * viewportScale * gl_PointSize, 0.0f, 0.0f);\n";

        if (fragmentShader->mUsesPointCoord)
        {
            geomHLSL += "    output.gl_PointCoord = pointSpriteTexcoords[" + Str(corner) + "];\n";
        }

        geomHLSL += "    outStream.Append(output);\n";
    }

    geomHLSL += "    \n"
                "    outStream.RestartStrip();\n"
                "}\n";

    return geomHLSL;
}

// This method needs to match OutputHLSL::decorate
std::string DynamicHLSL::decorateAttribute(const std::string &name)
{
    if (name.compare(0, 3, "gl_") != 0 && name.compare(0, 3, "dx_") != 0)
    {
        return "_" + name;
    }

    return name;
}

}
