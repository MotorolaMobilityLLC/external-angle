//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// SeparateArrayConstructorStatements splits statements that are array constructors and drops all of
// their constant arguments. For example, a statement like:
//   int[2](0, i++);
// Will be changed to:
//   i++;

#ifndef COMPILER_TRANSLATOR_TREEOPS_SEPARATEARRAYCONSTRUCTORSTATEMENTS_H_
#define COMPILER_TRANSLATOR_TREEOPS_SEPARATEARRAYCONSTRUCTORSTATEMENTS_H_

namespace sh
{
class TIntermBlock;

void SeparateArrayConstructorStatements(TIntermBlock *root);
}  // namespace sh

#endif  // COMPILER_TRANSLATOR_TREEOPS_SEPARATEARRAYCONSTRUCTORSTATEMENTS_H_
