//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// FlipRotationSpecConst.h: Add code to generate AST node for flip and rotation matrices and
// vectors.
//

#ifndef COMPILER_TRANSLATOR_TREEUTIL_FLIPROTATESPECCONST_H_
#define COMPILER_TRANSLATOR_TREEUTIL_FLIPROTATESPECCONST_H_

#include "common/angleutils.h"
#include "compiler/translator/SymbolTable.h"

class TIntermTyped;
class TIntermSymbol;
class TVariable;

namespace sh
{

class FlipRotateSpecConst
{
  public:
    FlipRotateSpecConst();
    virtual ~FlipRotateSpecConst();

    TIntermTyped *getMultiplierXForDFdx();
    TIntermTyped *getMultiplierYForDFdx();
    TIntermTyped *getMultiplierXForDFdy();
    TIntermTyped *getMultiplierYForDFdy();
    TIntermTyped *getPreRotationMatrix();
    TIntermTyped *getFragRotationMatrix();
    TIntermTyped *getFragRotationMultiplyFlipXY();

    // Let Metal override until they provide specialized constant support
    virtual TIntermTyped *getFlipXY();
    virtual TIntermTyped *getNegFlipXY();
    virtual TIntermTyped *getFlipY();
    virtual TIntermTyped *getNegFlipY();

    virtual void generateSymbol(TSymbolTable *symbolTable);
    virtual void outputLayoutString(TInfoSinkBase &sink) const;

  private:
    TIntermSymbol *mSpecConstSymbol;
    // True if mSpecConstSymbol has been used
    bool mReferenced;
};
}  // namespace sh

#endif  // COMPILER_TRANSLATOR_TREEUTIL_FLIPROTATESPECCONST_H_
