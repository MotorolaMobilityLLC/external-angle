//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
#ifndef _PARSER_HELPER_INCLUDED_
#define _PARSER_HELPER_INCLUDED_

#include "compiler/Diagnostics.h"
#include "compiler/DirectiveHandler.h"
#include "compiler/localintermediate.h"
#include "compiler/preprocessor/Preprocessor.h"
#include "compiler/ShHandle.h"
#include "compiler/SymbolTable.h"

struct TMatrixFields {
    bool wholeRow;
    bool wholeCol;
    int row;
    int col;
};

//
// The following are extra variables needed during parsing, grouped together so
// they can be passed to the parser without needing a global.
//
struct TParseContext {
    TParseContext(TSymbolTable& symt, TExtensionBehavior& ext, TIntermediate& interm, ShShaderType type, ShShaderSpec spec, int options, bool checksPrecErrors, const char* sourcePath, TInfoSink& is) :
            intermediate(interm),
            symbolTable(symt),
            shaderType(type),
            shaderSpec(spec),
            compileOptions(options),
            sourcePath(sourcePath),
            treeRoot(0),
            loopNestingLevel(0),
            structNestingLevel(0),
            currentFunctionType(NULL),
            functionReturnsValue(false),
            checksPrecisionErrors(checksPrecErrors),
            diagnostics(is),
            shaderVersion(100),
            directiveHandler(ext, diagnostics, shaderVersion),
            preprocessor(&diagnostics, &directiveHandler),
            scanner(NULL) {  }
    TIntermediate& intermediate; // to hold and build a parse tree
    TSymbolTable& symbolTable;   // symbol table that goes with the language currently being parsed
    ShShaderType shaderType;              // vertex or fragment language (future: pack or unpack)
    ShShaderSpec shaderSpec;              // The language specification compiler conforms to - GLES2 or WebGL.
    int shaderVersion;
    int compileOptions;
    const char* sourcePath;      // Path of source file or NULL.
    TIntermNode* treeRoot;       // root of parse tree being created
    int loopNestingLevel;        // 0 if outside all loops
    int structNestingLevel;      // incremented while parsing a struct declaration
    const TType* currentFunctionType;  // the return type of the function that's currently being parsed
    bool functionReturnsValue;   // true if a non-void function has a return
    bool checksPrecisionErrors;  // true if an error will be generated when a variable is declared without precision, explicit or implicit.
    bool fragmentPrecisionHigh;  // true if highp precision is supported in the fragment language.
    TString HashErrMsg;
    TDiagnostics diagnostics;
    TDirectiveHandler directiveHandler;
    pp::Preprocessor preprocessor;
    void* scanner;

    int getShaderVersion() const { return shaderVersion; }
    int numErrors() const { return diagnostics.numErrors(); }
    TInfoSink& infoSink() { return diagnostics.infoSink(); }
    void error(TSourceLoc loc, const char *reason, const char* token,
               const char* extraInfo="");
    void warning(TSourceLoc loc, const char* reason, const char* token,
                 const char* extraInfo="");
    void trace(const char* str);
    void recover();

    bool parseVectorFields(const TString&, int vecSize, TVectorFields&, int line);
    bool parseMatrixFields(const TString&, int matCols, int matRows, TMatrixFields&, int line);

    bool reservedErrorCheck(int line, const TString& identifier);
    void assignError(int line, const char* op, TString left, TString right);
    void unaryOpError(int line, const char* op, TString operand);
    void binaryOpError(int line, const char* op, TString left, TString right);
    bool precisionErrorCheck(int line, TPrecision precision, TBasicType type);
    bool lValueErrorCheck(int line, const char* op, TIntermTyped*);
    bool constErrorCheck(TIntermTyped* node);
    bool integerErrorCheck(TIntermTyped* node, const char* token);
    bool globalErrorCheck(int line, bool global, const char* token);
    bool constructorErrorCheck(int line, TIntermNode*, TFunction&, TOperator, TType*);
    bool arraySizeErrorCheck(int line, TIntermTyped* expr, int& size);
    bool arrayQualifierErrorCheck(int line, TPublicType type);
    bool arrayTypeErrorCheck(int line, TPublicType type);
    bool arrayErrorCheck(int line, const TString& identifier, const TPublicType &type, TVariable*& variable);
    bool voidErrorCheck(int, const TString&, const TPublicType&);
    bool boolErrorCheck(int, const TIntermTyped*);
    bool boolErrorCheck(int, const TPublicType&);
    bool samplerErrorCheck(int line, const TPublicType& pType, const char* reason);
    bool structQualifierErrorCheck(int line, const TPublicType& pType);
    bool parameterSamplerErrorCheck(int line, TQualifier qualifier, const TType& type);
    bool nonInitConstErrorCheck(int line, const TString& identifier, TPublicType& type, bool array);
    bool nonInitErrorCheck(int line, const TString& identifier, const TPublicType& type, TVariable*& variable);
    bool paramErrorCheck(int line, TQualifier qualifier, TQualifier paramQualifier, TType* type);
    bool extensionErrorCheck(int line, const TString&);
    bool singleDeclarationErrorCheck(TPublicType &publicType, TSourceLoc identifierLocation, const TString &identifier);
    bool layoutLocationErrorCheck(TSourceLoc location, const TLayoutQualifier &layoutQualifier);

    const TExtensionBehavior& extensionBehavior() const { return directiveHandler.extensionBehavior(); }
    bool supportsExtension(const char* extension);
    void handleExtensionDirective(int line, const char* extName, const char* behavior);

    const TPragma& pragma() const { return directiveHandler.pragma(); }
    void handlePragmaDirective(int line, const char* name, const char* value);

    bool containsSampler(TType& type);
    bool areAllChildConst(TIntermAggregate* aggrNode);
    const TFunction* findFunction(int line, TFunction* pfnCall, int shaderVersion, bool *builtIn = 0);
    bool executeInitializer(TSourceLoc line, const TString& identifier, TPublicType& pType,
                            TIntermTyped* initializer, TIntermNode*& intermNode, TVariable* variable = 0);
    bool arraySetMaxSize(TIntermSymbol*, TType*, int, bool, TSourceLoc);

    TPublicType addFullySpecifiedType(TQualifier qualifier, const TPublicType& typeSpecifier);
    TPublicType addFullySpecifiedType(TQualifier qualifier, TLayoutQualifier layoutQualifier, const TPublicType& typeSpecifier);
    TIntermAggregate* parseSingleDeclaration(TPublicType &publicType, TSourceLoc identifierLocation, const TString &identifier);
    TIntermAggregate* parseSingleArrayDeclaration(TPublicType &publicType, TSourceLoc identifierLocation, const TString &identifier, TSourceLoc indexLocation, TIntermTyped *indexExpression);
    TIntermAggregate* parseSingleInitDeclaration(TPublicType &publicType, TSourceLoc identifierLocation, const TString &identifier, TSourceLoc initLocation, TIntermTyped *initializer);
    void parseGlobalLayoutQualifier(const TPublicType &typeQualifier);
    TFunction *addConstructorFunc(TPublicType publicType);
    TIntermTyped* addConstructor(TIntermNode*, const TType*, TOperator, TFunction*, TSourceLoc);
    TIntermTyped* foldConstConstructor(TIntermAggregate* aggrNode, const TType& type);
    TIntermTyped* constructStruct(TIntermNode*, TType*, int, TSourceLoc, bool subset);
    TIntermTyped* constructBuiltIn(const TType*, TOperator, TIntermNode*, TSourceLoc, bool subset);
    TIntermTyped* addConstVectorNode(TVectorFields&, TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstMatrixNode(int , TIntermTyped*, TSourceLoc);
    TIntermTyped* addConstArrayNode(int index, TIntermTyped* node, TSourceLoc line);
    TIntermTyped* addConstStruct(const TString &identifier, TIntermTyped *node, TSourceLoc line);
    TIntermTyped* addIndexExpression(TIntermTyped *baseExpression, TSourceLoc location, TIntermTyped *indexExpression);
    TIntermTyped* addFieldSelectionExpression(TIntermTyped *baseExpression, TSourceLoc dotLocation, const TString &fieldString, TSourceLoc fieldLocation);

    TTypeList *addStructDeclaratorList(const TPublicType& typeSpecifier, TTypeList *typeList);
    TPublicType addStructure(TSourceLoc structLine, TSourceLoc nameLine, const TString &structName, TTypeList* typeList);

    TIntermAggregate* addInterfaceBlock(const TPublicType& typeQualifier, TSourceLoc nameLine, const TString& blockName, TTypeList* typeList, 
                                        const TString& instanceName, TSourceLoc instanceLine, TIntermTyped* arrayIndex, TSourceLoc arrayIndexLine);

    TLayoutQualifier parseLayoutQualifier(const TString &qualifierType, TSourceLoc qualifierTypeLine);
    TLayoutQualifier parseLayoutQualifier(const TString &qualifierType, TSourceLoc qualifierTypeLine, const TString &intValueString, int intValue, TSourceLoc intValueLine);
    TLayoutQualifier joinLayoutQualifiers(TLayoutQualifier leftQualifier, TLayoutQualifier rightQualifier);

    // Performs an error check for embedded struct declarations.
    // Returns true if an error was raised due to the declaration of
    // this struct.
    bool enterStructDeclaration(TSourceLoc line, const TString& identifier);
    void exitStructDeclaration();

    bool structNestingErrorCheck(TSourceLoc line, const TType& fieldType);
};

int PaParseStrings(size_t count, const char* const string[], const int length[],
                   TParseContext* context);

#endif // _PARSER_HELPER_INCLUDED_
