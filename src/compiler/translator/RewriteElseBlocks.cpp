//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// RewriteElseBlocks.cpp: Implementation for tree transform to change
//   all if-else blocks to if-if blocks.
//

#include "compiler/translator/RewriteElseBlocks.h"
#include "compiler/translator/NodeSearch.h"
#include "compiler/translator/SymbolTable.h"

namespace sh
{

namespace
{

class ElseBlockRewriter : public TIntermTraverser
{
  public:
    ElseBlockRewriter();

  protected:
    bool visitAggregate(Visit visit, TIntermAggregate *aggregate) override;

  private:
    const TType *mFunctionType;

    TIntermNode *rewriteIfElse(TIntermIfElse *ifElse);
};

ElseBlockRewriter::ElseBlockRewriter()
    : TIntermTraverser(true, false, true),
      mFunctionType(NULL)
{}

bool ElseBlockRewriter::visitAggregate(Visit visit, TIntermAggregate *node)
{
    switch (node->getOp())
    {
      case EOpSequence:
        if (visit == PostVisit)
        {
            for (size_t statementIndex = 0; statementIndex != node->getSequence()->size(); statementIndex++)
            {
                TIntermNode *statement = (*node->getSequence())[statementIndex];
                TIntermIfElse *ifElse  = statement->getAsIfElseNode();
                if (ifElse && ifElse->getFalseBlock() != nullptr)
                {
                    // Check for if / else if
                    TIntermIfElse *elseIfBranch = ifElse->getFalseBlock()->getAsIfElseNode();
                    if (elseIfBranch)
                    {
                        ifElse->replaceChildNode(elseIfBranch, rewriteIfElse(elseIfBranch));
                        delete elseIfBranch;
                    }

                    (*node->getSequence())[statementIndex] = rewriteIfElse(ifElse);
                    delete ifElse;
                }
            }
        }
        break;

      case EOpFunction:
        // Store the current function context (see comment below)
        mFunctionType = ((visit == PreVisit) ? &node->getType() : NULL);
        break;

      default: break;
    }

    return true;
}

TIntermNode *ElseBlockRewriter::rewriteIfElse(TIntermIfElse *ifElse)
{
    ASSERT(ifElse != nullptr);

    nextTemporaryIndex();

    TIntermTyped *typedCondition     = ifElse->getCondition()->getAsTyped();
    TIntermAggregate *storeCondition = createTempInitDeclaration(typedCondition);

    TIntermIfElse *falseBlock = nullptr;

    TType boolType(EbtBool, EbpUndefined, EvqTemporary);

    if (ifElse->getFalseBlock())
    {
        TIntermAggregate *negatedElse = nullptr;
        // crbug.com/346463
        // D3D generates error messages claiming a function has no return value, when rewriting
        // an if-else clause that returns something non-void in a function. By appending dummy
        // returns (that are unreachable) we can silence this compile error.
        if (mFunctionType && mFunctionType->getBasicType() != EbtVoid)
        {
            TString typeString = mFunctionType->getStruct() ? mFunctionType->getStruct()->name() :
                mFunctionType->getBasicString();
            TString rawText = "return (" + typeString + ")0";
            TIntermRaw *returnNode = new TIntermRaw(*mFunctionType, rawText);
            negatedElse = new TIntermAggregate(EOpSequence);
            negatedElse->getSequence()->push_back(returnNode);
        }

        TIntermSymbol *conditionSymbolElse = createTempSymbol(boolType);
        TIntermUnary *negatedCondition     = new TIntermUnary(EOpLogicalNot, conditionSymbolElse);
        falseBlock = new TIntermIfElse(negatedCondition, ifElse->getFalseBlock(), negatedElse);
    }

    TIntermSymbol *conditionSymbolSel = createTempSymbol(boolType);
    TIntermIfElse *newIfElse =
        new TIntermIfElse(conditionSymbolSel, ifElse->getTrueBlock(), falseBlock);

    TIntermAggregate *block = new TIntermAggregate(EOpSequence);
    block->getSequence()->push_back(storeCondition);
    block->getSequence()->push_back(newIfElse);

    return block;
}

}

void RewriteElseBlocks(TIntermNode *node, unsigned int *temporaryIndex)
{
    ElseBlockRewriter rewriter;
    rewriter.useTemporaryIndex(temporaryIndex);
    node->traverse(&rewriter);
}

}
