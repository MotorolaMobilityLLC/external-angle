#include "precompiled.h"
//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// formatutils11.cpp: Queries for GL image formats and their translations to D3D11
// formats.

#include "libGLESv2/renderer/formatutils11.h"
#include "libGLESv2/renderer/generatemip.h"
#include "libGLESv2/renderer/loadimage.h"

namespace rx
{

struct D3D11ES3FormatInfo
{
    DXGI_FORMAT mTexFormat;
    DXGI_FORMAT mSRVFormat;
    DXGI_FORMAT mRTVFormat;
    DXGI_FORMAT mDSVFormat;

    D3D11ES3FormatInfo()
        : mTexFormat(DXGI_FORMAT_UNKNOWN), mDSVFormat(DXGI_FORMAT_UNKNOWN), mRTVFormat(DXGI_FORMAT_UNKNOWN), mSRVFormat(DXGI_FORMAT_UNKNOWN)
    { }

    D3D11ES3FormatInfo(DXGI_FORMAT texFormat, DXGI_FORMAT srvFormat, DXGI_FORMAT rtvFormat, DXGI_FORMAT dsvFormat)
        : mTexFormat(texFormat), mDSVFormat(dsvFormat), mRTVFormat(rtvFormat), mSRVFormat(srvFormat)
    { }
};

// For sized GL internal formats, there is only one corresponding D3D11 format. This map type allows
// querying for the DXGI texture formats to use for textures, SRVs, RTVs and DSVs given a GL internal
// format.
typedef std::pair<GLint, D3D11ES3FormatInfo> D3D11ES3FormatPair;
typedef std::map<GLint, D3D11ES3FormatInfo> D3D11ES3FormatMap;

static D3D11ES3FormatMap buildD3D11ES3FormatMap()
{
    D3D11ES3FormatMap map;

    //                           | GL internal format  |                  | D3D11 texture format            | D3D11 SRV format               | D3D11 RTV format               | D3D11 DSV format   |
    map.insert(D3D11ES3FormatPair(GL_NONE,              D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,              DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R8,                D3D11ES3FormatInfo(DXGI_FORMAT_R8_UNORM,             DXGI_FORMAT_R8_UNORM,            DXGI_FORMAT_R8_UNORM,            DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R8_SNORM,          D3D11ES3FormatInfo(DXGI_FORMAT_R8_SNORM,             DXGI_FORMAT_R8_SNORM,            DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG8,               D3D11ES3FormatInfo(DXGI_FORMAT_R8G8_UNORM,           DXGI_FORMAT_R8G8_UNORM,          DXGI_FORMAT_R8G8_UNORM,          DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG8_SNORM,         D3D11ES3FormatInfo(DXGI_FORMAT_R8G8_SNORM,           DXGI_FORMAT_R8G8_SNORM,          DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB8,              D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB8_SNORM,        D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_SNORM,       DXGI_FORMAT_R8G8B8A8_SNORM,      DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB565,            D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA4,             D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB5_A1,           D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA8,             D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA8_SNORM,       D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_SNORM,       DXGI_FORMAT_R8G8B8A8_SNORM,      DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB10_A2,          D3D11ES3FormatInfo(DXGI_FORMAT_R10G10B10A2_UNORM,    DXGI_FORMAT_R10G10B10A2_UNORM,   DXGI_FORMAT_R10G10B10A2_UNORM,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB10_A2UI,        D3D11ES3FormatInfo(DXGI_FORMAT_R10G10B10A2_UINT,     DXGI_FORMAT_R10G10B10A2_UINT,    DXGI_FORMAT_R10G10B10A2_UINT,    DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_SRGB8,             D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,              DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_SRGB8_ALPHA8,      D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,  DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R16F,              D3D11ES3FormatInfo(DXGI_FORMAT_R16_FLOAT,            DXGI_FORMAT_R16_FLOAT,           DXGI_FORMAT_R16_FLOAT,           DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG16F,             D3D11ES3FormatInfo(DXGI_FORMAT_R16G16_FLOAT,         DXGI_FORMAT_R16G16_FLOAT,        DXGI_FORMAT_R16G16_FLOAT,        DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB16F,            D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT,   DXGI_FORMAT_R16G16B16A16_FLOAT,  DXGI_FORMAT_R16G16B16A16_FLOAT,  DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA16F,           D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT,   DXGI_FORMAT_R16G16B16A16_FLOAT,  DXGI_FORMAT_R16G16B16A16_FLOAT,  DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R32F,              D3D11ES3FormatInfo(DXGI_FORMAT_R32_FLOAT,            DXGI_FORMAT_R32_FLOAT,           DXGI_FORMAT_R32_FLOAT,           DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG32F,             D3D11ES3FormatInfo(DXGI_FORMAT_R32G32_FLOAT,         DXGI_FORMAT_R32G32_FLOAT,        DXGI_FORMAT_R32G32_FLOAT,        DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB32F,            D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32_FLOAT,      DXGI_FORMAT_R32G32B32_FLOAT,     DXGI_FORMAT_R32G32B32_FLOAT,     DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA32F,           D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT,   DXGI_FORMAT_R32G32B32A32_FLOAT,  DXGI_FORMAT_R32G32B32A32_FLOAT,  DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R11F_G11F_B10F,    D3D11ES3FormatInfo(DXGI_FORMAT_R11G11B10_FLOAT,      DXGI_FORMAT_R11G11B10_FLOAT,     DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB9_E5,           D3D11ES3FormatInfo(DXGI_FORMAT_R9G9B9E5_SHAREDEXP,   DXGI_FORMAT_R9G9B9E5_SHAREDEXP,  DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R8I,               D3D11ES3FormatInfo(DXGI_FORMAT_R8_SINT,              DXGI_FORMAT_R8_SINT,             DXGI_FORMAT_R8_SINT,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R8UI,              D3D11ES3FormatInfo(DXGI_FORMAT_R8_UINT,              DXGI_FORMAT_R8_UINT,             DXGI_FORMAT_R8_UINT,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R16I,              D3D11ES3FormatInfo(DXGI_FORMAT_R16_SINT,             DXGI_FORMAT_R16_SINT,            DXGI_FORMAT_R16_SINT,            DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R16UI,             D3D11ES3FormatInfo(DXGI_FORMAT_R16_UINT,             DXGI_FORMAT_R16_UINT,            DXGI_FORMAT_R16_UINT,            DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R32I,              D3D11ES3FormatInfo(DXGI_FORMAT_R32_SINT,             DXGI_FORMAT_R32_SINT,            DXGI_FORMAT_R32_SINT,            DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_R32UI,             D3D11ES3FormatInfo(DXGI_FORMAT_R32_UINT,             DXGI_FORMAT_R32_UINT,            DXGI_FORMAT_R32_UINT,            DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG8I,              D3D11ES3FormatInfo(DXGI_FORMAT_R8G8_SINT,            DXGI_FORMAT_R8G8_SINT,           DXGI_FORMAT_R8G8_SINT,           DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG8UI,             D3D11ES3FormatInfo(DXGI_FORMAT_R8G8_UINT,            DXGI_FORMAT_R8G8_UINT,           DXGI_FORMAT_R8G8_UINT,           DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG16I,             D3D11ES3FormatInfo(DXGI_FORMAT_R16G16_SINT,          DXGI_FORMAT_R16G16_SINT,         DXGI_FORMAT_R16G16_SINT,         DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG16UI,            D3D11ES3FormatInfo(DXGI_FORMAT_R16G16_UINT,          DXGI_FORMAT_R16G16_UINT,         DXGI_FORMAT_R16G16_UINT,         DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG32I,             D3D11ES3FormatInfo(DXGI_FORMAT_R32G32_SINT,          DXGI_FORMAT_R32G32_SINT,         DXGI_FORMAT_R32G32_SINT,         DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RG32UI,            D3D11ES3FormatInfo(DXGI_FORMAT_R32G32_UINT,          DXGI_FORMAT_R32G32_UINT,         DXGI_FORMAT_R32G32_UINT,         DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB8I,             D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_SINT,        DXGI_FORMAT_R8G8B8A8_SINT,       DXGI_FORMAT_R8G8B8A8_SINT,       DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB8UI,            D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UINT,        DXGI_FORMAT_R8G8B8A8_UINT,       DXGI_FORMAT_R8G8B8A8_UINT,       DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB16I,            D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_SINT,    DXGI_FORMAT_R16G16B16A16_SINT,   DXGI_FORMAT_R16G16B16A16_SINT,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB16UI,           D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_UINT,    DXGI_FORMAT_R16G16B16A16_UINT,   DXGI_FORMAT_R16G16B16A16_UINT,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB32I,            D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32_SINT,       DXGI_FORMAT_R32G32B32_SINT,      DXGI_FORMAT_R32G32B32_SINT,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB32UI,           D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32_UINT,       DXGI_FORMAT_R32G32B32_UINT,      DXGI_FORMAT_R32G32B32_UINT,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA8I,            D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_SINT,        DXGI_FORMAT_R8G8B8A8_SINT,       DXGI_FORMAT_R8G8B8A8_SINT,       DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA8UI,           D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UINT,        DXGI_FORMAT_R8G8B8A8_UINT,       DXGI_FORMAT_R8G8B8A8_UINT,       DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA16I,           D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_SINT,    DXGI_FORMAT_R16G16B16A16_SINT,   DXGI_FORMAT_R16G16B16A16_SINT,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA16UI,          D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_UINT,    DXGI_FORMAT_R16G16B16A16_UINT,   DXGI_FORMAT_R16G16B16A16_UINT,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA32I,           D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32A32_SINT,    DXGI_FORMAT_R32G32B32A32_SINT,   DXGI_FORMAT_R32G32B32A32_SINT,   DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA32UI,          D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32A32_UINT,    DXGI_FORMAT_R32G32B32A32_UINT,   DXGI_FORMAT_R32G32B32A32_UINT,   DXGI_FORMAT_UNKNOWN)));

    // Unsized formats, TODO: Are types of float and half float allowed for the unsized types? Would it change the DXGI format?
    map.insert(D3D11ES3FormatPair(GL_ALPHA,             D3D11ES3FormatInfo(DXGI_FORMAT_A8_UNORM,             DXGI_FORMAT_A8_UNORM,            DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE,         D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE_ALPHA,   D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN,             DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGB,               D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_RGBA,              D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,       DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_R8G8B8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_BGRA_EXT,          D3D11ES3FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,       DXGI_FORMAT_B8G8R8A8_UNORM,      DXGI_FORMAT_B8G8R8A8_UNORM,      DXGI_FORMAT_UNKNOWN)));

    // From GL_EXT_texture_storage
    //                           | GL internal format       |                  | D3D11 texture format          | D3D11 SRV format                    | D3D11 RTV format          | D3D11 DSV format                 |
    map.insert(D3D11ES3FormatPair(GL_ALPHA8_EXT,             D3D11ES3FormatInfo(DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_A8_UNORM,                 DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE8_EXT,         D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,           DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_ALPHA32F_EXT,           D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,       DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE32F_EXT,       D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT,          DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_ALPHA16F_EXT,           D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,       DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE16F_EXT,       D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,                  DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE8_ALPHA8_EXT,  D3D11ES3FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,           DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE_ALPHA32F_EXT, D3D11ES3FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,       DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_LUMINANCE_ALPHA16F_EXT, D3D11ES3FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,       DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_BGRA8_EXT,              D3D11ES3FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,           DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_BGRA4_ANGLEX,           D3D11ES3FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,           DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN               )));
    map.insert(D3D11ES3FormatPair(GL_BGR5_A1_ANGLEX,         D3D11ES3FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,           DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN               )));

    // Depth stencil formats
    map.insert(D3D11ES3FormatPair(GL_DEPTH_COMPONENT16,     D3D11ES3FormatInfo(DXGI_FORMAT_R16_TYPELESS,        DXGI_FORMAT_R16_UNORM,                DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D16_UNORM             )));
    map.insert(D3D11ES3FormatPair(GL_DEPTH_COMPONENT24,     D3D11ES3FormatInfo(DXGI_FORMAT_R24G8_TYPELESS,      DXGI_FORMAT_R24_UNORM_X8_TYPELESS,    DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D24_UNORM_S8_UINT     )));
    map.insert(D3D11ES3FormatPair(GL_DEPTH_COMPONENT32F,    D3D11ES3FormatInfo(DXGI_FORMAT_R32_TYPELESS,        DXGI_FORMAT_R32_FLOAT,                DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D32_FLOAT             )));
    map.insert(D3D11ES3FormatPair(GL_DEPTH24_STENCIL8,      D3D11ES3FormatInfo(DXGI_FORMAT_R24G8_TYPELESS,      DXGI_FORMAT_R24_UNORM_X8_TYPELESS,    DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D24_UNORM_S8_UINT     )));
    map.insert(D3D11ES3FormatPair(GL_DEPTH32F_STENCIL8,     D3D11ES3FormatInfo(DXGI_FORMAT_R32G8X24_TYPELESS,   DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS, DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D32_FLOAT_S8X24_UINT  )));

    // From GL_ANGLE_depth_texture
    map.insert(D3D11ES3FormatPair(GL_DEPTH_COMPONENT32_OES, D3D11ES3FormatInfo(DXGI_FORMAT_R24G8_TYPELESS,      DXGI_FORMAT_R24_UNORM_X8_TYPELESS,    DXGI_FORMAT_UNKNOWN,        DXGI_FORMAT_D24_UNORM_S8_UINT     )));

    // Compressed formats, From ES 3.0.1 spec, table 3.16
    //                           | GL internal format                          |                  | D3D11 texture format | D3D11 SRV format     | D3D11 RTV format   | D3D11 DSV format  |
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_R11_EAC,                        D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_SIGNED_R11_EAC,                 D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RG11_EAC,                       D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_SIGNED_RG11_EAC,                D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGB8_ETC2,                      D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_SRGB8_ETC2,                     D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,  D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGBA8_ETC2_EAC,                 D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,          D3D11ES3FormatInfo(DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN,   DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));

    // From GL_EXT_texture_compression_dxt1
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGB_S3TC_DXT1_EXT,              D3D11ES3FormatInfo(DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,             D3D11ES3FormatInfo(DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));

    // From GL_ANGLE_texture_compression_dxt3
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE,           D3D11ES3FormatInfo(DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));

    // From GL_ANGLE_texture_compression_dxt5
    map.insert(D3D11ES3FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE,           D3D11ES3FormatInfo(DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_UNKNOWN)));

    return map;
}

static bool getD3D11ES3FormatInfo(GLint internalFormat, GLuint clientVersion, D3D11ES3FormatInfo *outFormatInfo)
{
    static const D3D11ES3FormatMap formatMap = buildD3D11ES3FormatMap();
    D3D11ES3FormatMap::const_iterator iter = formatMap.find(internalFormat);
    if (iter != formatMap.end())
    {
        if (outFormatInfo)
        {
            *outFormatInfo = iter->second;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// ES3 image loading functions vary based on the internal format and data type given,
// this map type determines the loading function from the internal format and type supplied
// to glTex*Image*D and the destination DXGI_FORMAT. Source formats and types are taken from
// Tables 3.2 and 3.3 of the ES 3 spec.
typedef std::pair<GLint, GLenum> InternalFormatTypePair;
typedef std::pair<InternalFormatTypePair, LoadImageFunction> D3D11LoadFunctionPair;
typedef std::map<InternalFormatTypePair, LoadImageFunction> D3D11LoadFunctionMap;

static void UnimplementedLoadFunction(int width, int height, int depth,
                                      const void *input, unsigned int inputRowPitch, unsigned int inputDepthPitch,
                                      void *output, unsigned int outputRowPitch, unsigned int outputDepthPitch)
{
    UNIMPLEMENTED();
}

// A helper function to insert data into the D3D11LoadFunctionMap with fewer characters.
static inline void insertLoadFunction(D3D11LoadFunctionMap *map, GLint internalFormat, GLenum type,
                                      LoadImageFunction loadFunc)
{
    map->insert(D3D11LoadFunctionPair(InternalFormatTypePair(internalFormat, type), loadFunc));
}

D3D11LoadFunctionMap buildD3D11LoadFunctionMap()
{
    D3D11LoadFunctionMap map;

    //                      | Internal format      | Type                             | Load function                       |
    insertLoadFunction(&map, GL_RGBA8,              GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 4>             );
    insertLoadFunction(&map, GL_RGB5_A1,            GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGBA4,              GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_SRGB8_ALPHA8,       GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 4>             );
    insertLoadFunction(&map, GL_RGBA8_SNORM,        GL_BYTE,                           loadToNative<GLbyte, 4>              );
    insertLoadFunction(&map, GL_RGBA4,              GL_UNSIGNED_SHORT_4_4_4_4,         loadRGBA4444DataToRGBA               );
    insertLoadFunction(&map, GL_RGB10_A2,           GL_UNSIGNED_INT_2_10_10_10_REV,    loadToNative<GLuint, 1>              );
    insertLoadFunction(&map, GL_RGB5_A1,            GL_UNSIGNED_SHORT_5_5_5_1,         loadRGBA5551DataToRGBA               );
    insertLoadFunction(&map, GL_RGB5_A1,            GL_UNSIGNED_INT_2_10_10_10_REV,    loadRGBA2101010ToRGBA                );
    insertLoadFunction(&map, GL_RGBA16F,            GL_HALF_FLOAT,                     loadToNative<GLhalf, 4>              );
    insertLoadFunction(&map, GL_RGBA32F,            GL_FLOAT,                          loadToNative<GLfloat, 4>             );
    insertLoadFunction(&map, GL_RGBA16F,            GL_FLOAT,                          UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGBA8UI,            GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 4>             );
    insertLoadFunction(&map, GL_RGBA8I,             GL_BYTE,                           loadToNative<GLbyte, 4>              );
    insertLoadFunction(&map, GL_RGBA16UI,           GL_UNSIGNED_SHORT,                 loadToNative<GLushort, 4>            );
    insertLoadFunction(&map, GL_RGBA16I,            GL_SHORT,                          loadToNative<GLshort, 4>             );
    insertLoadFunction(&map, GL_RGBA32UI,           GL_UNSIGNED_INT,                   loadToNative<GLuint, 4>              );
    insertLoadFunction(&map, GL_RGBA32I,            GL_INT,                            loadToNative<GLint, 4>               );
    insertLoadFunction(&map, GL_RGB10_A2UI,         GL_UNSIGNED_INT_2_10_10_10_REV,    loadToNative<GLuint, 1>              );
    insertLoadFunction(&map, GL_RGB8,               GL_UNSIGNED_BYTE,                  loadRGBUByteDataToRGBA               );
    insertLoadFunction(&map, GL_RGB565,             GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_SRGB8,              GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGB8_SNORM,         GL_BYTE,                           loadRGBSByteDataToRGBA               );
    insertLoadFunction(&map, GL_RGB565,             GL_UNSIGNED_SHORT_5_6_5,           loadRGB565DataToRGBA                 );
    insertLoadFunction(&map, GL_R11F_G11F_B10F,     GL_UNSIGNED_INT_10F_11F_11F_REV,   loadToNative<GLuint, 1>              );
    insertLoadFunction(&map, GL_RGB9_E5,            GL_UNSIGNED_INT_5_9_9_9_REV,       loadToNative<GLuint, 1>              );
    insertLoadFunction(&map, GL_RGB16F,             GL_HALF_FLOAT,                     loadRGBHalfFloatDataToRGBA           );
    insertLoadFunction(&map, GL_R11F_G11F_B10F,     GL_HALF_FLOAT,                     loadRGBHalfFloatDataTo111110Float    );
    insertLoadFunction(&map, GL_RGB9_E5,            GL_HALF_FLOAT,                     loadRGBHalfFloatDataTo999E5          );
    insertLoadFunction(&map, GL_RGB32F,             GL_FLOAT,                          loadToNative<GLfloat, 3>             );
    insertLoadFunction(&map, GL_RGB16F,             GL_FLOAT,                          UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_R11F_G11F_B10F,     GL_FLOAT,                          loadRGBFloatDataTo111110Float        );
    insertLoadFunction(&map, GL_RGB9_E5,            GL_FLOAT,                          loadRGBFloatDataTo999E5              );
    insertLoadFunction(&map, GL_RGB8UI,             GL_UNSIGNED_BYTE,                  loadToNative3To4<GLubyte, 0x0>       );
    insertLoadFunction(&map, GL_RGB8I,              GL_BYTE,                           loadToNative3To4<GLbyte, 0x0>        );
    insertLoadFunction(&map, GL_RGB16UI,            GL_UNSIGNED_SHORT,                 loadToNative3To4<GLushort, 0x0>      );
    insertLoadFunction(&map, GL_RGB16I,             GL_SHORT,                          loadToNative3To4<GLshort, 0x0>       );
    insertLoadFunction(&map, GL_RGB32UI,            GL_UNSIGNED_INT,                   loadToNative<GLuint, 3>              );
    insertLoadFunction(&map, GL_RGB32I,             GL_INT,                            loadToNative<GLint, 3>               );
    insertLoadFunction(&map, GL_RG8,                GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 2>             );
    insertLoadFunction(&map, GL_RG8_SNORM,          GL_BYTE,                           loadToNative<GLbyte, 2>              );
    insertLoadFunction(&map, GL_RG16F,              GL_HALF_FLOAT,                     loadToNative<GLhalf, 2>              );
    insertLoadFunction(&map, GL_RG32F,              GL_FLOAT,                          loadToNative<GLfloat, 2>             );
    insertLoadFunction(&map, GL_RG16F,              GL_FLOAT,                          loadFloatDataToHalfFloat<2>          );
    insertLoadFunction(&map, GL_RG8UI,              GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 2>             );
    insertLoadFunction(&map, GL_RG8I,               GL_BYTE,                           loadToNative<GLbyte, 2>              );
    insertLoadFunction(&map, GL_RG16UI,             GL_UNSIGNED_SHORT,                 loadToNative<GLushort, 2>            );
    insertLoadFunction(&map, GL_RG16I,              GL_SHORT,                          loadToNative<GLshort, 2>             );
    insertLoadFunction(&map, GL_RG32UI,             GL_UNSIGNED_INT,                   loadToNative<GLuint, 2>              );
    insertLoadFunction(&map, GL_RG32I,              GL_INT,                            loadToNative<GLint, 2>               );
    insertLoadFunction(&map, GL_R8,                 GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 1>             );
    insertLoadFunction(&map, GL_R8_SNORM,           GL_BYTE,                           loadToNative<GLbyte, 1>              );
    insertLoadFunction(&map, GL_R16F,               GL_HALF_FLOAT,                     loadToNative<GLhalf, 1>              );
    insertLoadFunction(&map, GL_R32F,               GL_FLOAT,                          loadToNative<GLfloat, 1>             );
    insertLoadFunction(&map, GL_R16F,               GL_FLOAT,                          loadFloatDataToHalfFloat<1>          );
    insertLoadFunction(&map, GL_R8UI,               GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 1>             );
    insertLoadFunction(&map, GL_R8I,                GL_BYTE,                           loadToNative<GLbyte, 1>              );
    insertLoadFunction(&map, GL_R16UI,              GL_UNSIGNED_SHORT,                 loadToNative<GLushort, 1>            );
    insertLoadFunction(&map, GL_R16I,               GL_SHORT,                          loadToNative<GLshort, 1>             );
    insertLoadFunction(&map, GL_R32UI,              GL_UNSIGNED_INT,                   loadToNative<GLuint, 1>              );
    insertLoadFunction(&map, GL_R32I,               GL_INT,                            loadToNative<GLint, 1>               );
    insertLoadFunction(&map, GL_DEPTH_COMPONENT16,  GL_UNSIGNED_SHORT,                 UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_DEPTH_COMPONENT24,  GL_UNSIGNED_INT,                   UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_DEPTH_COMPONENT16,  GL_UNSIGNED_INT,                   UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_DEPTH_COMPONENT32F, GL_FLOAT,                          UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_DEPTH24_STENCIL8,   GL_UNSIGNED_INT_24_8,              UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_DEPTH32F_STENCIL8,  GL_FLOAT_32_UNSIGNED_INT_24_8_REV, UnimplementedLoadFunction            );

    // Unsized formats
    insertLoadFunction(&map, GL_RGBA,               GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGBA,               GL_UNSIGNED_SHORT_4_4_4_4,         UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGBA,               GL_UNSIGNED_SHORT_5_5_5_1,         UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGB,                GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_RGB,                GL_UNSIGNED_SHORT_5_6_5,           UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_LUMINANCE_ALPHA,    GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_LUMINANCE,          GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );
    insertLoadFunction(&map, GL_ALPHA,              GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction            );

    // From GL_OES_texture_float
    insertLoadFunction(&map, GL_LUMINANCE_ALPHA,    GL_FLOAT,                          loadLuminanceAlphaFloatDataToRGBA    );
    insertLoadFunction(&map, GL_LUMINANCE,          GL_FLOAT,                          loadLuminanceFloatDataToRGB          );
    insertLoadFunction(&map, GL_ALPHA,              GL_FLOAT,                          loadAlphaFloatDataToRGBA             );

    // From GL_OES_texture_half_float
    insertLoadFunction(&map, GL_LUMINANCE_ALPHA,    GL_HALF_FLOAT,                     loadLuminanceAlphaHalfFloatDataToRGBA);
    insertLoadFunction(&map, GL_LUMINANCE,          GL_HALF_FLOAT,                     loadLuminanceHalfFloatDataToRGBA     );
    insertLoadFunction(&map, GL_ALPHA,              GL_HALF_FLOAT,                     loadAlphaHalfFloatDataToRGBA         );

    // From GL_EXT_texture_storage
    insertLoadFunction(&map, GL_ALPHA8_EXT,             GL_UNSIGNED_BYTE,              loadToNative<GLubyte, 1>             );
    insertLoadFunction(&map, GL_LUMINANCE8_EXT,         GL_UNSIGNED_BYTE,              loadLuminanceDataToBGRA              );
    insertLoadFunction(&map, GL_LUMINANCE8_ALPHA8_EXT,  GL_UNSIGNED_BYTE,              loadLuminanceAlphaDataToBGRA         );
    insertLoadFunction(&map, GL_ALPHA32F_EXT,           GL_FLOAT,                      loadAlphaFloatDataToRGBA             );
    insertLoadFunction(&map, GL_LUMINANCE32F_EXT,       GL_FLOAT,                      loadLuminanceFloatDataToRGB          );
    insertLoadFunction(&map, GL_LUMINANCE_ALPHA32F_EXT, GL_FLOAT,                      loadLuminanceAlphaFloatDataToRGBA    );
    insertLoadFunction(&map, GL_ALPHA16F_EXT,           GL_HALF_FLOAT,                 loadAlphaHalfFloatDataToRGBA         );
    insertLoadFunction(&map, GL_LUMINANCE16F_EXT,       GL_HALF_FLOAT,                 loadLuminanceHalfFloatDataToRGBA     );
    insertLoadFunction(&map, GL_LUMINANCE_ALPHA16F_EXT, GL_HALF_FLOAT,                 loadLuminanceAlphaHalfFloatDataToRGBA);

    insertLoadFunction(&map, GL_BGRA8_EXT,              GL_UNSIGNED_BYTE,                  loadToNative<GLubyte, 4>         );
    insertLoadFunction(&map, GL_BGRA4_ANGLEX,           GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT, loadRGBA4444DataToRGBA           );
    insertLoadFunction(&map, GL_BGRA4_ANGLEX,           GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction        );
    insertLoadFunction(&map, GL_BGR5_A1_ANGLEX,         GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT, loadRGBA5551DataToRGBA           );
    insertLoadFunction(&map, GL_BGR5_A1_ANGLEX,         GL_UNSIGNED_BYTE,                  UnimplementedLoadFunction        );

    // Compressed formats
    // From ES 3.0.1 spec, table 3.16
    //                      | Internal format                             | Type            | Load function                     |
    insertLoadFunction(&map, GL_COMPRESSED_R11_EAC,                        GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_R11_EAC,                        GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_SIGNED_R11_EAC,                 GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_RG11_EAC,                       GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_SIGNED_RG11_EAC,                GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_RGB8_ETC2,                      GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_SRGB8_ETC2,                     GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,  GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_RGBA8_ETC2_EAC,                 GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );
    insertLoadFunction(&map, GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,          GL_UNSIGNED_BYTE, UnimplementedLoadFunction          );

    // From GL_EXT_texture_compression_dxt1
    insertLoadFunction(&map, GL_COMPRESSED_RGB_S3TC_DXT1_EXT,              GL_UNSIGNED_BYTE, loadCompressedBlockDataToNative<4, 4,  8>);
    insertLoadFunction(&map, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,             GL_UNSIGNED_BYTE, loadCompressedBlockDataToNative<4, 4,  8>);

    // From GL_ANGLE_texture_compression_dxt3
    insertLoadFunction(&map, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE,           GL_UNSIGNED_BYTE, loadCompressedBlockDataToNative<4, 4, 16>);

    // From GL_ANGLE_texture_compression_dxt5
    insertLoadFunction(&map, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE,           GL_UNSIGNED_BYTE, loadCompressedBlockDataToNative<4, 4, 16>);

    return map;
}

struct D3D11ES2FormatInfo
{
    DXGI_FORMAT mTexFormat;
    DXGI_FORMAT mSRVFormat;
    DXGI_FORMAT mRTVFormat;
    DXGI_FORMAT mDSVFormat;

    LoadImageFunction mLoadImageFunction;

    D3D11ES2FormatInfo()
        : mTexFormat(DXGI_FORMAT_UNKNOWN), mDSVFormat(DXGI_FORMAT_UNKNOWN), mRTVFormat(DXGI_FORMAT_UNKNOWN),
        mSRVFormat(DXGI_FORMAT_UNKNOWN), mLoadImageFunction(NULL)
    { }

    D3D11ES2FormatInfo(DXGI_FORMAT texFormat, DXGI_FORMAT srvFormat, DXGI_FORMAT rtvFormat, DXGI_FORMAT dsvFormat,
        LoadImageFunction loadFunc)
        : mTexFormat(texFormat), mDSVFormat(dsvFormat), mRTVFormat(rtvFormat), mSRVFormat(srvFormat),
        mLoadImageFunction(loadFunc)
    { }
};

// ES2 internal formats can map to DXGI formats and loading functions
typedef std::pair<GLint, D3D11ES2FormatInfo> D3D11ES2FormatPair;
typedef std::map<GLint, D3D11ES2FormatInfo> D3D11ES2FormatMap;

static D3D11ES2FormatMap buildD3D11ES2FormatMap()
{
    D3D11ES2FormatMap map;

    //                           | Internal format                   |                  | Texture format                | SRV format                       | RTV format                    | DSV format                   | Load function                           |
    map.insert(D3D11ES2FormatPair(GL_NONE,                            D3D11ES2FormatInfo(DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,           NULL                                     )));
    map.insert(D3D11ES2FormatPair(GL_DEPTH_COMPONENT16,               D3D11ES2FormatInfo(DXGI_FORMAT_R16_TYPELESS,       DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_D16_UNORM,         NULL                                     )));
    map.insert(D3D11ES2FormatPair(GL_DEPTH_COMPONENT32_OES,           D3D11ES2FormatInfo(DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_D32_FLOAT,         NULL                                     )));
    map.insert(D3D11ES2FormatPair(GL_DEPTH24_STENCIL8_OES,            D3D11ES2FormatInfo(DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_D24_UNORM_S8_UINT, NULL                                     )));
    map.insert(D3D11ES2FormatPair(GL_STENCIL_INDEX8,                  D3D11ES2FormatInfo(DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_X24_TYPELESS_G8_UINT,  DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_D24_UNORM_S8_UINT, NULL                                     )));

    map.insert(D3D11ES2FormatPair(GL_RGBA32F_EXT,                     D3D11ES2FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN,           loadRGBAFloatDataToRGBA                  )));
    map.insert(D3D11ES2FormatPair(GL_RGB32F_EXT,                      D3D11ES2FormatInfo(DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT,       DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_UNKNOWN,           loadRGBFloatDataToNative                 )));
    map.insert(D3D11ES2FormatPair(GL_ALPHA32F_EXT,                    D3D11ES2FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN,           loadAlphaFloatDataToRGBA                 )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE32F_EXT,                D3D11ES2FormatInfo(DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT,       DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_UNKNOWN,           loadLuminanceFloatDataToRGB              )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE_ALPHA32F_EXT,          D3D11ES2FormatInfo(DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN,           loadLuminanceAlphaFloatDataToRGBA        )));

    map.insert(D3D11ES2FormatPair(GL_RGBA16F_EXT,                     D3D11ES2FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_UNKNOWN,           loadRGBAHalfFloatDataToRGBA              )));
    map.insert(D3D11ES2FormatPair(GL_RGB16F_EXT,                      D3D11ES2FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_UNKNOWN,           loadRGBHalfFloatDataToRGBA               )));
    map.insert(D3D11ES2FormatPair(GL_ALPHA16F_EXT,                    D3D11ES2FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_UNKNOWN,           loadAlphaHalfFloatDataToRGBA             )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE16F_EXT,                D3D11ES2FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_UNKNOWN,           loadLuminanceHalfFloatDataToRGBA         )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE_ALPHA16F_EXT,          D3D11ES2FormatInfo(DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_UNKNOWN,           loadLuminanceAlphaHalfFloatDataToRGBA    )));

    map.insert(D3D11ES2FormatPair(GL_ALPHA8_EXT,                      D3D11ES2FormatInfo(DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_A8_UNORM,              DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_UNKNOWN,           loadAlphaDataToNative                    )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE8_EXT,                  D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadLuminanceDataToBGRA                  )));
    map.insert(D3D11ES2FormatPair(GL_LUMINANCE8_ALPHA8_EXT,           D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadLuminanceAlphaDataToBGRA             )));

    map.insert(D3D11ES2FormatPair(GL_RGB8_OES,                        D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBUByteDataToRGBA                   )));
    map.insert(D3D11ES2FormatPair(GL_RGB565,                          D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGB565DataToRGBA                     )));
    map.insert(D3D11ES2FormatPair(GL_RGBA8_OES,                       D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBAUByteDataToNative                )));
    map.insert(D3D11ES2FormatPair(GL_RGBA4,                           D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBA4444DataToRGBA                   )));
    map.insert(D3D11ES2FormatPair(GL_RGB5_A1,                         D3D11ES2FormatInfo(DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBA5551DataToRGBA                   )));
    map.insert(D3D11ES2FormatPair(GL_BGRA8_EXT,                       D3D11ES2FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadBGRADataToBGRA                       )));
    map.insert(D3D11ES2FormatPair(GL_BGRA4_ANGLEX,                    D3D11ES2FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBA4444DataToRGBA                   )));
    map.insert(D3D11ES2FormatPair(GL_BGR5_A1_ANGLEX,                  D3D11ES2FormatInfo(DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_UNKNOWN,           loadRGBA5551DataToRGBA                   )));

    map.insert(D3D11ES2FormatPair(GL_COMPRESSED_RGB_S3TC_DXT1_EXT,    D3D11ES2FormatInfo(DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,           loadCompressedBlockDataToNative<4, 4,  8>)));
    map.insert(D3D11ES2FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,   D3D11ES2FormatInfo(DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,           loadCompressedBlockDataToNative<4, 4,  8>)));
    map.insert(D3D11ES2FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, D3D11ES2FormatInfo(DXGI_FORMAT_BC2_UNORM,          DXGI_FORMAT_BC2_UNORM,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,           loadCompressedBlockDataToNative<4, 4, 16>)));
    map.insert(D3D11ES2FormatPair(GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, D3D11ES2FormatInfo(DXGI_FORMAT_BC3_UNORM,          DXGI_FORMAT_BC3_UNORM,             DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,           loadCompressedBlockDataToNative<4, 4, 16>)));

    return map;
}

static bool getD3D11ES2FormatInfo(GLint internalFormat, GLuint clientVersion, D3D11ES2FormatInfo *outFormatInfo)
{
    static const D3D11ES2FormatMap formatMap = buildD3D11ES2FormatMap();
    D3D11ES2FormatMap::const_iterator iter = formatMap.find(internalFormat);
    if (iter != formatMap.end())
    {
        if (outFormatInfo)
        {
            *outFormatInfo = iter->second;
        }
        return true;
    }
    else
    {
        return false;
    }
}

// A map to determine the pixel size and mipmap generation function of a given DXGI format
struct DXGIFormatInfo
{
    GLuint mPixelBits;
    GLuint mBlockWidth;
    GLuint mBlockHeight;
    GLint mInternalFormat;

    MipGenerationFunction mMipGenerationFunction;

    DXGIFormatInfo()
        : mPixelBits(0), mBlockWidth(0), mBlockHeight(0), mInternalFormat(GL_NONE), mMipGenerationFunction(NULL)
    { }

    DXGIFormatInfo(GLuint pixelBits, GLuint blockWidth, GLuint blockHeight, GLint internalFormat,
                   MipGenerationFunction mipFunc)
        : mPixelBits(pixelBits), mBlockWidth(blockWidth), mBlockHeight(blockHeight), mInternalFormat(internalFormat),
          mMipGenerationFunction(mipFunc)
    { }
};

typedef std::pair<DXGI_FORMAT, DXGIFormatInfo> DXGIFormatInfoPair;
typedef std::map<DXGI_FORMAT, DXGIFormatInfo> DXGIFormatInfoMap;

static DXGIFormatInfoMap buildDXGIFormatInfoMap()
{
    DXGIFormatInfoMap map;

    //                           | DXGI format                                   | S  |W |H | Internal format                   | Mip generation function  |
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_UNKNOWN,             DXGIFormatInfo(  0, 0, 0, GL_NONE,                            NULL                      )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_A8_UNORM,            DXGIFormatInfo(  8, 1, 1, GL_ALPHA8_EXT,                      GenerateMip<A8>           )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8_UNORM,            DXGIFormatInfo(  8, 1, 1, GL_R8,                              GenerateMip<R8>           )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8_UNORM,          DXGIFormatInfo( 16, 1, 1, GL_RG8,                             GenerateMip<R8G8>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8B8A8_UNORM,      DXGIFormatInfo( 32, 1, 1, GL_RGBA8,                           GenerateMip<R8G8B8A8>     )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, DXGIFormatInfo( 32, 1, 1, GL_SRGB8_ALPHA8,                    NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_B8G8R8A8_UNORM,      DXGIFormatInfo( 32, 1, 1, GL_BGRA8_EXT,                       GenerateMip<B8G8R8A8>     )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8_SNORM,            DXGIFormatInfo(  8, 1, 1, GL_R8_SNORM,                        GenerateMip<R8S>          )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8_SNORM,          DXGIFormatInfo( 16, 1, 1, GL_RG8_SNORM,                       GenerateMip<R8G8S>        )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8B8A8_SNORM,      DXGIFormatInfo( 32, 1, 1, GL_RGBA8_SNORM,                     GenerateMip<R8G8B8A8S>    )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8_UINT,             DXGIFormatInfo(  8, 1, 1, GL_R8UI,                            GenerateMip<R8>           )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16_UINT,            DXGIFormatInfo( 16, 1, 1, GL_R16UI,                           GenerateMip<R16>          )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32_UINT,            DXGIFormatInfo( 32, 1, 1, GL_R32UI,                           GenerateMip<R32>          )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8_UINT,           DXGIFormatInfo( 16, 1, 1, GL_RG8UI,                           GenerateMip<R8G8>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16_UINT,         DXGIFormatInfo( 32, 1, 1, GL_RG16UI,                          GenerateMip<R16G16>       )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32_UINT,         DXGIFormatInfo( 64, 1, 1, GL_RG32UI,                          GenerateMip<R32G32>       )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32_UINT,      DXGIFormatInfo( 96, 1, 1, GL_RGB32UI,                         GenerateMip<R32G32B32>    )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8B8A8_UINT,       DXGIFormatInfo( 32, 1, 1, GL_RGBA8UI,                         GenerateMip<R8G8B8A8>     )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16B16A16_UINT,   DXGIFormatInfo( 64, 1, 1, GL_RGBA16UI,                        GenerateMip<R16G16B16A16> )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32A32_UINT,   DXGIFormatInfo(128, 1, 1, GL_RGBA32UI,                        GenerateMip<R32G32B32A32> )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8_SINT,             DXGIFormatInfo(  8, 1, 1, GL_R8I,                             GenerateMip<R8S>          )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16_SINT,            DXGIFormatInfo( 16, 1, 1, GL_R16I,                            GenerateMip<R16S>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32_SINT,            DXGIFormatInfo( 32, 1, 1, GL_R32I,                            GenerateMip<R32S>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8_SINT,           DXGIFormatInfo( 16, 1, 1, GL_RG8I,                            GenerateMip<R8G8S>        )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16_SINT,         DXGIFormatInfo( 32, 1, 1, GL_RG16I,                           GenerateMip<R16G16S>      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32_SINT,         DXGIFormatInfo( 64, 1, 1, GL_RG32I,                           GenerateMip<R32G32S>      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32_SINT,      DXGIFormatInfo( 96, 1, 1, GL_RGB32I,                          GenerateMip<R32G32B32S>   )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R8G8B8A8_SINT,       DXGIFormatInfo( 32, 1, 1, GL_RGBA8I,                          GenerateMip<R8G8B8A8S>    )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16B16A16_SINT,   DXGIFormatInfo( 64, 1, 1, GL_RGBA16I,                         GenerateMip<R16G16B16A16S>)));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32A32_SINT,   DXGIFormatInfo(128, 1, 1, GL_RGBA32I,                         GenerateMip<R32G32B32A32S>)));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R10G10B10A2_UNORM,   DXGIFormatInfo( 32, 1, 1, GL_RGB10_A2,                        GenerateMip<R10G10B10A2>  )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R10G10B10A2_UINT,    DXGIFormatInfo( 32, 1, 1, GL_RGB10_A2UI,                      GenerateMip<R10G10B10A2>  )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16_FLOAT,           DXGIFormatInfo( 16, 1, 1, GL_R16F,                            GenerateMip<R16F>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16_FLOAT,        DXGIFormatInfo( 32, 1, 1, GL_RG16F,                           GenerateMip<R16G16F>      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16G16B16A16_FLOAT,  DXGIFormatInfo( 64, 1, 1, GL_RGBA16F,                         GenerateMip<R16G16B16A16F>)));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32_FLOAT,           DXGIFormatInfo( 32, 1, 1, GL_R32F,                            GenerateMip<R32F>         )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32_FLOAT,        DXGIFormatInfo( 64, 1, 1, GL_RG32F,                           GenerateMip<R32G32F>      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32_FLOAT,     DXGIFormatInfo( 96, 1, 1, GL_RGB32F,                          GenerateMip<R32G32B32F>   )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32G32B32A32_FLOAT,  DXGIFormatInfo(128, 1, 1, GL_RGBA32F,                         GenerateMip<R32G32B32A32F>)));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R9G9B9E5_SHAREDEXP,  DXGIFormatInfo( 32, 1, 1, GL_RGB9_E5,                         GenerateMip<R9G9B9E5>     )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R11G11B10_FLOAT,     DXGIFormatInfo( 32, 1, 1, GL_R11F_G11F_B10F,                  GenerateMip<R11G11B10F>   )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R16_TYPELESS,        DXGIFormatInfo( 16, 1, 1, GL_DEPTH_COMPONENT16,               NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_D16_UNORM,           DXGIFormatInfo( 16, 1, 1, GL_DEPTH_COMPONENT16,               NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R32_TYPELESS,        DXGIFormatInfo( 32, 1, 1, GL_DEPTH_COMPONENT32_OES,           NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_D32_FLOAT,           DXGIFormatInfo( 32, 1, 1, GL_DEPTH_COMPONENT32_OES,           NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_R24G8_TYPELESS,      DXGIFormatInfo( 32, 1, 1, GL_DEPTH24_STENCIL8_OES,            NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_D24_UNORM_S8_UINT,   DXGIFormatInfo( 32, 1, 1, GL_DEPTH24_STENCIL8_OES,            NULL                      )));

    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_BC1_UNORM,           DXGIFormatInfo( 64, 4, 4, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,   NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_BC2_UNORM,           DXGIFormatInfo(128, 4, 4, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, NULL                      )));
    map.insert(DXGIFormatInfoPair(DXGI_FORMAT_BC3_UNORM,           DXGIFormatInfo(128, 4, 4, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, NULL                      )));

    return map;
}

static bool getDXGIFormatInfo(DXGI_FORMAT format, DXGIFormatInfo *outFormatInfo)
{
    static const DXGIFormatInfoMap infoMap = buildDXGIFormatInfoMap();
    DXGIFormatInfoMap::const_iterator iter = infoMap.find(format);
    if (iter != infoMap.end())
    {
        if (outFormatInfo)
        {
            *outFormatInfo = iter->second;
        }
        return true;
    }
    else
    {
        return false;
    }
}

namespace d3d11
{

MipGenerationFunction GetMipGenerationFunction(DXGI_FORMAT format)
{
    DXGIFormatInfo formatInfo;
    if (getDXGIFormatInfo(format, &formatInfo))
    {
        return formatInfo.mMipGenerationFunction;
    }
    else
    {
        UNREACHABLE();
        return NULL;
    }
}

LoadImageFunction GetImageLoadFunction(GLint internalFormat, GLenum type, GLuint clientVersion)
{
    if (clientVersion == 2)
    {
        D3D11ES2FormatInfo d3d11FormatInfo;
        if (getD3D11ES2FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mLoadImageFunction;
        }
        else
        {
            UNREACHABLE();
            return NULL;
        }
    }
    else if (clientVersion == 3)
    {
        static const D3D11LoadFunctionMap loadImageMap = buildD3D11LoadFunctionMap();
        D3D11LoadFunctionMap::const_iterator iter = loadImageMap.find(InternalFormatTypePair(internalFormat, type));
        if (iter != loadImageMap.end())
        {
            return iter->second;
        }
        else
        {
            UNREACHABLE();
            return NULL;
        }
    }
    else
    {
        UNREACHABLE();
        return NULL;
    }
}

GLuint GetFormatPixelBytes(DXGI_FORMAT format)
{
    DXGIFormatInfo dxgiFormatInfo;
    if (getDXGIFormatInfo(format, &dxgiFormatInfo))
    {
        return dxgiFormatInfo.mPixelBits / 8;
    }
    else
    {
        UNREACHABLE();
        return 0;
    }
}

GLuint GetBlockWidth(DXGI_FORMAT format)
{
    DXGIFormatInfo dxgiFormatInfo;
    if (getDXGIFormatInfo(format, &dxgiFormatInfo))
    {
        return dxgiFormatInfo.mBlockWidth;
    }
    else
    {
        UNREACHABLE();
        return 0;
    }
}

GLuint GetBlockHeight(DXGI_FORMAT format)
{
    DXGIFormatInfo dxgiFormatInfo;
    if (getDXGIFormatInfo(format, &dxgiFormatInfo))
    {
        return dxgiFormatInfo.mBlockHeight;
    }
    else
    {
        UNREACHABLE();
        return 0;
    }
}

void MakeValidSize(bool isImage, DXGI_FORMAT format, GLsizei *requestWidth, GLsizei *requestHeight, int *levelOffset)
{
    DXGIFormatInfo dxgiFormatInfo;
    if (getDXGIFormatInfo(format, &dxgiFormatInfo))
    {
        int upsampleCount = 0;

        GLsizei blockWidth = dxgiFormatInfo.mBlockWidth;
        GLsizei blockHeight = dxgiFormatInfo.mBlockHeight;

        // Don't expand the size of full textures that are at least (blockWidth x blockHeight) already.
        if (isImage || *requestWidth < blockWidth || *requestHeight < blockHeight)
        {
            while (*requestWidth % blockWidth != 0 || *requestHeight % blockHeight != 0)
            {
                *requestWidth <<= 1;
                *requestHeight <<= 1;
                upsampleCount++;
            }
        }
        *levelOffset = upsampleCount;
    }
    else
    {
        UNREACHABLE();
    }
}

}

namespace gl_d3d11
{

DXGI_FORMAT GetTexFormat(GLint internalFormat, GLuint clientVersion)
{
    if (clientVersion == 2)
    {
        D3D11ES2FormatInfo d3d11FormatInfo;
        if (getD3D11ES2FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mTexFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else if (clientVersion == 3)
    {
        D3D11ES3FormatInfo d3d11FormatInfo;
        if (getD3D11ES3FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mTexFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else
    {
        UNREACHABLE();
        return DXGI_FORMAT_UNKNOWN;
    }
}

DXGI_FORMAT GetSRVFormat(GLint internalFormat, GLuint clientVersion)
{
    if (clientVersion == 2)
    {
        D3D11ES2FormatInfo d3d11FormatInfo;
        if (getD3D11ES2FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mSRVFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else if (clientVersion == 3)
    {
        D3D11ES3FormatInfo d3d11FormatInfo;
        if (getD3D11ES3FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mSRVFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else
    {
        UNREACHABLE();
        return DXGI_FORMAT_UNKNOWN;
    }
}

DXGI_FORMAT GetRTVFormat(GLint internalFormat, GLuint clientVersion)
{
    if (clientVersion == 2)
    {
        D3D11ES2FormatInfo d3d11FormatInfo;
        if (getD3D11ES2FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mRTVFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else if (clientVersion == 3)
    {
        D3D11ES3FormatInfo d3d11FormatInfo;
        if (getD3D11ES3FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mRTVFormat;
        }
        else
        {
            UNREACHABLE();
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else
    {
        UNREACHABLE();
        return DXGI_FORMAT_UNKNOWN;
    }
}

DXGI_FORMAT GetDSVFormat(GLint internalFormat, GLuint clientVersion)
{
    if (clientVersion == 2)
    {
        D3D11ES2FormatInfo d3d11FormatInfo;
        if (getD3D11ES2FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mDSVFormat;
        }
        else
        {
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else if (clientVersion == 3)
    {
        D3D11ES3FormatInfo d3d11FormatInfo;
        if (getD3D11ES3FormatInfo(internalFormat, clientVersion, &d3d11FormatInfo))
        {
            return d3d11FormatInfo.mDSVFormat;
        }
        else
        {
            return DXGI_FORMAT_UNKNOWN;
        }
    }
    else
    {
        UNREACHABLE();
        return DXGI_FORMAT_UNKNOWN;
    }
}

}

namespace d3d11_gl
{

GLint GetInternalFormat(DXGI_FORMAT format)
{
    DXGIFormatInfo formatInfo;
    if (getDXGIFormatInfo(format, &formatInfo))
    {
        return formatInfo.mInternalFormat;
    }
    else
    {
        UNREACHABLE();
        return GL_NONE;
    }
}

}

}
