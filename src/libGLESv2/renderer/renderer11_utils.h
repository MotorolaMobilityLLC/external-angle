//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// renderer11_utils.h: Conversion functions and other utility routines
// specific to the D3D11 renderer.

#define GL_APICALL
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <d3d11.h>

#include "libGLESv2/angletypes.h"

namespace gl_d3d11
{

D3D11_BLEND ConvertBlendFunc(GLenum glBlend, bool isAlpha);
D3D11_BLEND_OP ConvertBlendOp(GLenum glBlendOp);
UINT8 ConvertColorMask(bool maskRed, bool maskGreen, bool maskBlue, bool maskAlpha);

D3D11_CULL_MODE ConvertCullMode(bool cullEnabled, GLenum cullMode);

D3D11_COMPARISON_FUNC ConvertComparison(GLenum comparison);
D3D11_DEPTH_WRITE_MASK ConvertDepthMask(bool depthWriteEnabled);
UINT8 ConvertStencilMask(GLuint stencilmask);
D3D11_STENCIL_OP ConvertStencilOp(GLenum stencilOp);

D3D11_FILTER ConvertFilter(GLenum minFilter, GLenum magFilter, float maxAnisotropy);
D3D11_TEXTURE_ADDRESS_MODE ConvertTextureWrap(GLenum wrap);
FLOAT ConvertMinLOD(GLenum minFilter);
FLOAT ConvertMaxLOD(GLenum minFilter);

DXGI_FORMAT ConvertRenderbufferFormat(GLenum format);
DXGI_FORMAT ConvertTextureFormat(GLenum format);
}

namespace d3d11_gl
{

GLenum ConvertBackBufferFormat(DXGI_FORMAT format);
GLenum ConvertDepthStencilFormat(DXGI_FORMAT format);
GLenum ConvertRenderbufferFormat(DXGI_FORMAT format);
GLenum ConvertTextureInternalFormat(DXGI_FORMAT format);

}

namespace d3d11
{
size_t ComputePixelSizeBits(DXGI_FORMAT format);
size_t ComputeBlockSizeBits(DXGI_FORMAT format);

HRESULT SetDebugName(ID3D11DeviceChild *resource, const char *name);
}

inline bool isDeviceLostError(HRESULT errorCode)
{
    switch (errorCode)
    {
      case DXGI_ERROR_DEVICE_HUNG:
      case DXGI_ERROR_DEVICE_REMOVED:
      case DXGI_ERROR_DEVICE_RESET:
      case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
      case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
        return true;
      default:
        return false;
    }
}
