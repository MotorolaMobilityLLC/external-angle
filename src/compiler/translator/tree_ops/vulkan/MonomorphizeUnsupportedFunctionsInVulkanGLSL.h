//
// Copyright 2021 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// MonomorphizeUnsupportedFunctionsInVulkanGLSL: Monomorphize functions that are called with
// parameters that are not compatible with Vulkan GLSL:
//
// - Samplers in structs
// - Structs that have samplers
// - Partially subscripted array of array of samplers
// - Partially subscripted array of array of images
// - Atomic counters
//
// This transformation basically duplicates such functions, removes the
// sampler/image/atomic_counter parameters and uses the opaque uniforms used by the caller.

#ifndef COMPILER_TRANSLATOR_TREEOPS_VULKAN_MONOMORPHIZEUNSUPPORTEDFUNCTIONSINVULKANGLSL_H_
#define COMPILER_TRANSLATOR_TREEOPS_VULKAN_MONOMORPHIZEUNSUPPORTEDFUNCTIONSINVULKANGLSL_H_

#include "common/angleutils.h"

namespace sh
{
class TCompiler;
class TIntermBlock;
class TSymbolTable;

ANGLE_NO_DISCARD bool MonomorphizeUnsupportedFunctionsInVulkanGLSL(TCompiler *compiler,
                                                                   TIntermBlock *root,
                                                                   TSymbolTable *symbolTable);
}  // namespace sh

#endif  // COMPILER_TRANSLATOR_TREEOPS_VULKAN_MONOMORPHIZEUNSUPPORTEDFUNCTIONSINVULKANGLSL_H_
