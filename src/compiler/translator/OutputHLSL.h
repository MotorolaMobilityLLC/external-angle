//
// Copyright (c) 2002-2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef COMPILER_OUTPUTHLSL_H_
#define COMPILER_OUTPUTHLSL_H_

#include <list>
#include <set>
#include <map>

#include <GLES3/gl3.h>
#include <GLES2/gl2.h>

#include "compiler/translator/intermediate.h"
#include "compiler/translator/ParseContext.h"
#include "common/shadervars.h"

namespace sh
{
class UnfoldShortCircuit;
class StructureHLSL;

class OutputHLSL : public TIntermTraverser
{
  public:
    OutputHLSL(TParseContext &context, const ShBuiltInResources& resources, ShShaderOutput outputType);
    ~OutputHLSL();

    void output();

    TInfoSinkBase &getBodyStream();
    const std::vector<gl::Uniform> &getUniforms();
    const std::vector<gl::InterfaceBlock> &getInterfaceBlocks() const;
    const std::vector<gl::Attribute> &getOutputVariables() const;
    const std::vector<gl::Attribute> &getAttributes() const;
    const std::vector<gl::Varying> &getVaryings() const;

    static TString initializer(const TType &type);

  protected:
    void header();

    // Visit AST nodes and output their code to the body stream
    void visitSymbol(TIntermSymbol*);
    void visitConstantUnion(TIntermConstantUnion*);
    bool visitBinary(Visit visit, TIntermBinary*);
    bool visitUnary(Visit visit, TIntermUnary*);
    bool visitSelection(Visit visit, TIntermSelection*);
    bool visitAggregate(Visit visit, TIntermAggregate*);
    bool visitLoop(Visit visit, TIntermLoop*);
    bool visitBranch(Visit visit, TIntermBranch*);

    void traverseStatements(TIntermNode *node);
    bool isSingleStatement(TIntermNode *node);
    bool handleExcessiveLoop(TIntermLoop *node);
    void outputTriplet(Visit visit, const TString &preString, const TString &inString, const TString &postString);
    void outputLineDirective(int line);
    TString argumentString(const TIntermSymbol *symbol);
    int vectorSize(const TType &type) const;

    void outputConstructor(Visit visit, const TType &type, const TString &name, const TIntermSequence *parameters);
    const ConstantUnion *writeConstantUnion(const TType &type, const ConstantUnion *constUnion);

    TParseContext &mContext;
    const ShShaderOutput mOutputType;
    UnfoldShortCircuit *mUnfoldShortCircuit;
    bool mInsideFunction;

    // Output streams
    TInfoSinkBase mHeader;
    TInfoSinkBase mBody;
    TInfoSinkBase mFooter;

    typedef std::map<TString, TIntermSymbol*> ReferencedSymbols;
    ReferencedSymbols mReferencedUniforms;
    ReferencedSymbols mReferencedInterfaceBlocks;
    ReferencedSymbols mReferencedAttributes;
    ReferencedSymbols mReferencedVaryings;
    ReferencedSymbols mReferencedOutputVariables;

    StructureHLSL *mStructureHLSL;

    struct TextureFunction
    {
        enum Method
        {
            IMPLICIT,   // Mipmap LOD determined implicitly (standard lookup)
            BIAS,
            LOD,
            LOD0,
            LOD0BIAS,
            SIZE,   // textureSize()
            FETCH,
            GRAD
        };

        TBasicType sampler;
        int coords;
        bool proj;
        bool offset;
        Method method;

        TString name() const;

        bool operator<(const TextureFunction &rhs) const;
    };

    typedef std::set<TextureFunction> TextureFunctionSet;

    // Parameters determining what goes in the header output
    TextureFunctionSet mUsesTexture;
    bool mUsesFragColor;
    bool mUsesFragData;
    bool mUsesDepthRange;
    bool mUsesFragCoord;
    bool mUsesPointCoord;
    bool mUsesFrontFacing;
    bool mUsesPointSize;
    bool mUsesFragDepth;
    bool mUsesXor;
    bool mUsesMod1;
    bool mUsesMod2v;
    bool mUsesMod2f;
    bool mUsesMod3v;
    bool mUsesMod3f;
    bool mUsesMod4v;
    bool mUsesMod4f;
    bool mUsesFaceforward1;
    bool mUsesFaceforward2;
    bool mUsesFaceforward3;
    bool mUsesFaceforward4;
    bool mUsesAtan2_1;
    bool mUsesAtan2_2;
    bool mUsesAtan2_3;
    bool mUsesAtan2_4;
    bool mUsesDiscardRewriting;
    bool mUsesNestedBreak;

    int mNumRenderTargets;

    int mUniqueIndex;   // For creating unique names

    bool mContainsLoopDiscontinuity;
    bool mOutputLod0Function;
    bool mInsideDiscontinuousLoop;
    int mNestedLoopDepth;

    TIntermSymbol *mExcessiveLoopIndex;

    int mUniformRegister;
    int mInterfaceBlockRegister;
    int mSamplerRegister;

    TString registerString(TIntermSymbol *operand);
    int samplerRegister(TIntermSymbol *sampler);
    int uniformRegister(TIntermSymbol *uniform);
    void declareInterfaceBlockField(const TType &type, const TString &name, std::vector<gl::InterfaceBlockField>& output);
    gl::Uniform declareUniformToList(const TType &type, const TString &name, int registerIndex, std::vector<gl::Uniform>& output);
    void declareUniform(const TType &type, const TString &name, int index);
    void declareVaryingToList(const TType &type, TQualifier baseTypeQualifier, const TString &name, std::vector<gl::Varying>& fieldsOut);

    // Returns the uniform's register index
    int declareUniformAndAssignRegister(const TType &type, const TString &name);

    TString interfaceBlockFieldString(const TInterfaceBlock &interfaceBlock, const TField &field);
    TString interfaceBlockStructNameString(const TInterfaceBlock &interfaceBlockType);
    TString interfaceBlockInstanceString(const TInterfaceBlock& interfaceBlock, unsigned int arrayIndex);
    TString interfaceBlockFieldTypeString(const TField &field, TLayoutBlockStorage blockStorage);
    TString interfaceBlockFieldString(const TInterfaceBlock &interfaceBlock, TLayoutBlockStorage blockStorage);
    TString interfaceBlockStructString(const TInterfaceBlock &interfaceBlock);
    TString interfaceBlockString(const TInterfaceBlock &interfaceBlock, unsigned int registerIndex, unsigned int arrayIndex);
    TString structInitializerString(int indent, const TStructure &structure, const TString &rhsStructName);

    std::vector<gl::Uniform> mActiveUniforms;
    std::vector<gl::InterfaceBlock> mActiveInterfaceBlocks;
    std::vector<gl::Attribute> mActiveOutputVariables;
    std::vector<gl::Attribute> mActiveAttributes;
    std::vector<gl::Varying> mActiveVaryings;
    std::map<TIntermTyped*, TString> mFlaggedStructMappedNames;
    std::map<TIntermTyped*, TString> mFlaggedStructOriginalNames;

    void makeFlaggedStructMaps(const std::vector<TIntermTyped *> &flaggedStructs);
};

}

#endif   // COMPILER_OUTPUTHLSL_H_
