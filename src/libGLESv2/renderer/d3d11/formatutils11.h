//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// formatutils11.h: Queries for GL image formats and their translations to D3D11
// formats.

#ifndef LIBGLESV2_RENDERER_FORMATUTILS11_H_
#define LIBGLESV2_RENDERER_FORMATUTILS11_H_

#include "libGLESv2/formatutils.h"

namespace rx
{

class Renderer;

namespace d3d11
{

typedef std::set<DXGI_FORMAT> DXGIFormatSet;

MipGenerationFunction GetMipGenerationFunction(DXGI_FORMAT format, GLuint clientVersion);
LoadImageFunction GetImageLoadFunction(GLenum internalFormat, GLenum type, GLuint clientVersion);

GLuint GetFormatPixelBytes(DXGI_FORMAT format, GLuint clientVersion);
GLuint GetBlockWidth(DXGI_FORMAT format, GLuint clientVersion);
GLuint GetBlockHeight(DXGI_FORMAT format, GLuint clientVersion);

GLuint GetDepthBits(DXGI_FORMAT format);
GLuint GetDepthOffset(DXGI_FORMAT format);
GLuint GetStencilBits(DXGI_FORMAT format);
GLuint GetStencilOffset(DXGI_FORMAT format);

void MakeValidSize(bool isImage, DXGI_FORMAT format, GLuint clientVersion, GLsizei *requestWidth, GLsizei *requestHeight, int *levelOffset);

const DXGIFormatSet &GetAllUsedDXGIFormats();

ColorReadFunction GetColorReadFunction(DXGI_FORMAT format, GLuint clientVersion);
ColorCopyFunction GetFastCopyFunction(DXGI_FORMAT sourceFormat, GLenum destFormat, GLenum destType, GLuint clientVersion);

}

namespace gl_d3d11
{

DXGI_FORMAT GetTexFormat(GLenum internalFormat, GLuint clientVersion);
DXGI_FORMAT GetSRVFormat(GLenum internalFormat, GLuint clientVersion);
DXGI_FORMAT GetRTVFormat(GLenum internalFormat, GLuint clientVersion);
DXGI_FORMAT GetDSVFormat(GLenum internalFormat, GLuint clientVersion);
DXGI_FORMAT GetRenderableFormat(GLenum internalFormat, GLuint clientVersion);

DXGI_FORMAT GetSwizzleTexFormat(GLint internalFormat, const Renderer *renderer);
DXGI_FORMAT GetSwizzleSRVFormat(GLint internalFormat, const Renderer *renderer);
DXGI_FORMAT GetSwizzleRTVFormat(GLint internalFormat, const Renderer *renderer);

}

namespace d3d11_gl
{

GLenum GetInternalFormat(DXGI_FORMAT format, GLuint clientVersion);

}

}

#endif // LIBGLESV2_RENDERER_FORMATUTILS11_H_
