//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// formatutils.h: Queries for GL image formats.

#ifndef LIBANGLE_FORMATUTILS_H_
#define LIBANGLE_FORMATUTILS_H_

#include "libANGLE/Caps.h"
#include "libANGLE/angletypes.h"

#include "angle_gl.h"

#include <cstddef>
#include <stdint.h>

namespace gl
{

struct Type
{
    Type();

    GLuint bytes;
    bool specialInterpretation;
};
const Type &GetTypeInfo(GLenum type);

struct InternalFormat
{
    InternalFormat();

    GLuint redBits;
    GLuint greenBits;
    GLuint blueBits;

    GLuint luminanceBits;

    GLuint alphaBits;
    GLuint sharedBits;

    GLuint depthBits;
    GLuint stencilBits;

    GLuint pixelBytes;

    GLuint componentCount;

    bool compressed;
    GLuint compressedBlockWidth;
    GLuint compressedBlockHeight;

    GLenum format;
    GLenum type;

    GLenum componentType;
    GLenum colorEncoding;

    typedef bool (*SupportCheckFunction)(GLuint, const Extensions &);
    SupportCheckFunction textureSupport;
    SupportCheckFunction renderSupport;
    SupportCheckFunction filterSupport;

    GLuint computeRowPitch(GLenum type, GLsizei width, GLint alignment) const;
    GLuint computeDepthPitch(GLenum type, GLsizei width, GLsizei height, GLint alignment) const;
    GLuint computeBlockSize(GLenum type, GLsizei width, GLsizei height) const;
};
const InternalFormat &GetInternalFormatInfo(GLenum internalFormat);

GLenum GetSizedInternalFormat(GLenum internalFormat, GLenum type);

typedef std::set<GLenum> FormatSet;
const FormatSet &GetAllSizedInternalFormats();

}

#endif // LIBANGLE_FORMATUTILS_H_
