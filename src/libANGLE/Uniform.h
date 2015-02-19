//
// Copyright (c) 2010-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef LIBANGLE_UNIFORM_H_
#define LIBANGLE_UNIFORM_H_

#include <string>
#include <vector>

#include "angle_gl.h"
#include "common/debug.h"
#include "compiler/translator/blocklayout.h"
#include "libANGLE/angletypes.h"

namespace gl
{

// Helper struct representing a single shader uniform
struct LinkedUniform
{
    LinkedUniform(GLenum type, GLenum precision, const std::string &name, unsigned int arraySize, const int blockIndex, const sh::BlockMemberInfo &blockInfo);

    ~LinkedUniform();

    bool isArray() const;
    unsigned int elementCount() const;
    bool isReferencedByVertexShader() const;
    bool isReferencedByFragmentShader() const;
    bool isInDefaultBlock() const;
    size_t dataSize() const;
    bool isSampler() const;

    const GLenum type;
    const GLenum precision;
    const std::string name;
    const unsigned int arraySize;
    const int blockIndex;
    const sh::BlockMemberInfo blockInfo;

    unsigned char *data;
    bool dirty;

    unsigned int psRegisterIndex;
    unsigned int vsRegisterIndex;
    unsigned int registerCount;

    // Register "elements" are used for uniform structs in ES3, to appropriately identify single uniforms
    // inside aggregate types, which are packed according C-like structure rules.
    unsigned int registerElement;

  private:
    DISALLOW_COPY_AND_ASSIGN(LinkedUniform);
};

// Helper struct representing a single shader uniform block
struct UniformBlock
{
    // use GL_INVALID_INDEX for non-array elements
    UniformBlock(const std::string &name, unsigned int elementIndex, unsigned int dataSize);

    bool isArrayElement() const;
    bool isReferencedByVertexShader() const;
    bool isReferencedByFragmentShader() const;

    const std::string name;
    const unsigned int elementIndex;
    const unsigned int dataSize;

    std::vector<unsigned int> memberUniformIndexes;

    unsigned int psRegisterIndex;
    unsigned int vsRegisterIndex;

  private:
    DISALLOW_COPY_AND_ASSIGN(UniformBlock);
};

}

#endif   // LIBANGLE_UNIFORM_H_
