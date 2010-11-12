//
// Copyright (c) 2002-2010 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include "compiler/Initialize.h"
#include "compiler/ParseHelper.h"
#include "compiler/ShHandle.h"

static bool InitializeSymbolTable(
        const TBuiltInStrings& builtInStrings,
        ShShaderType type, ShShaderSpec spec, const ShBuiltInResources& resources,
        TInfoSink& infoSink, TSymbolTable& symbolTable)
{
    TIntermediate intermediate(infoSink);
    TExtensionBehavior extBehavior;
    TParseContext parseContext(symbolTable, extBehavior, intermediate, type, spec, infoSink);

    GlobalParseContext = &parseContext;

    assert(symbolTable.isEmpty());       
    //
    // Parse the built-ins.  This should only happen once per
    // language symbol table.
    //
    // Push the symbol table to give it an initial scope.  This
    // push should not have a corresponding pop, so that built-ins
    // are preserved, and the test for an empty table fails.
    //
    symbolTable.push();

    for (TBuiltInStrings::const_iterator i = builtInStrings.begin(); i != builtInStrings.end(); ++i)
    {
        const char* builtInShaders = i->c_str();
        int builtInLengths = static_cast<int>(i->size());
        if (builtInLengths <= 0)
          continue;

        if (PaParseStrings(1, &builtInShaders, &builtInLengths, &parseContext) != 0)
        {
            infoSink.info.message(EPrefixInternalError, "Unable to parse built-ins");
            return false;
        }
    }

    IdentifyBuiltIns(type, spec, resources, symbolTable);

    return true;
}

TCompiler::TCompiler(ShShaderType type, ShShaderSpec spec)
    : shaderType(type),
      shaderSpec(spec) 
{
}

TCompiler::~TCompiler()
{
}

bool TCompiler::Init(const ShBuiltInResources& resources)
{
    // Generate built-in symbol table.
    if (!InitBuiltInSymbolTable(resources))
        return false;

    InitExtensionBehavior(resources, extensionBehavior);
    return true;
}

bool TCompiler::compile(const char* const shaderStrings[],
                        const int numStrings,
                        int compileOptions)
{
    clearResults();

    if (numStrings == 0)
        return true;

    // If compiling for WebGL, validate control-flow and indexing as well.
    if (shaderSpec == SH_WEBGL_SPEC) {
        compileOptions |= SH_VALIDATE_CONTROL_FLOW | SH_VALIDATE_INDEXING;
    }

    TIntermediate intermediate(infoSink);
    TParseContext parseContext(symbolTable, extensionBehavior, intermediate,
                               shaderType, shaderSpec, infoSink);
    GlobalParseContext = &parseContext;

    // We preserve symbols at the built-in level from compile-to-compile.
    // Start pushing the user-defined symbols at global level.
    symbolTable.push();
    if (!symbolTable.atGlobalLevel())
        infoSink.info.message(EPrefixInternalError, "Wrong symbol table level");

    // Parse shader.
    bool success =
        (PaParseStrings(numStrings, shaderStrings, NULL, &parseContext) == 0) &&
        (parseContext.treeRoot != NULL);
    if (success) {
        success = intermediate.postProcess(parseContext.treeRoot);

        if (success && (compileOptions & SH_INTERMEDIATE_TREE))
            intermediate.outputTree(parseContext.treeRoot);

        if (success && (compileOptions & SH_OBJECT_CODE))
            translate(parseContext.treeRoot);

        if (success && (compileOptions & SH_ATTRIBUTES_UNIFORMS))
            collectAttribsUniforms(parseContext.treeRoot);
    }

    // Cleanup memory.
    intermediate.remove(parseContext.treeRoot);
    // Ensure symbol table is returned to the built-in level,
    // throwing away all but the built-ins.
    while (!symbolTable.atBuiltInLevel())
        symbolTable.pop();

    return success;
}

bool TCompiler::InitBuiltInSymbolTable(const ShBuiltInResources& resources)
{
    TBuiltIns builtIns;

    builtIns.initialize(shaderType, shaderSpec, resources);
    return InitializeSymbolTable(builtIns.getBuiltInStrings(),
        shaderType, shaderSpec, resources, infoSink, symbolTable);
}

void TCompiler::clearResults()
{
    infoSink.info.erase();
    infoSink.obj.erase();
    infoSink.debug.erase();

    attribs.clear();
    uniforms.clear();
}

void TCompiler::collectAttribsUniforms(TIntermNode* root)
{
    CollectAttribsUniforms collect(attribs, uniforms);
    root->traverse(&collect);
}

