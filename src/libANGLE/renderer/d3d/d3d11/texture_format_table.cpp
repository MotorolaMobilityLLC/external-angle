//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Helper routines for the D3D11 texture format table.

#include "libANGLE/renderer/d3d/d3d11/texture_format_table.h"

#include "libANGLE/renderer/d3d/d3d11/load_functions_table.h"

namespace rx
{

namespace d3d11
{

ANGLEFormatSet::ANGLEFormatSet()
    : format(angle::Format::Get(angle::Format::ID::NONE)),
      texFormat(DXGI_FORMAT_UNKNOWN),
      srvFormat(DXGI_FORMAT_UNKNOWN),
      rtvFormat(DXGI_FORMAT_UNKNOWN),
      dsvFormat(DXGI_FORMAT_UNKNOWN),
      blitSRVFormat(DXGI_FORMAT_UNKNOWN),
      swizzle(*this)
{
}

ANGLEFormatSet::ANGLEFormatSet(angle::Format::ID formatID,
                               DXGI_FORMAT texFormat,
                               DXGI_FORMAT srvFormat,
                               DXGI_FORMAT rtvFormat,
                               DXGI_FORMAT dsvFormat,
                               DXGI_FORMAT blitSRVFormat,
                               angle::Format::ID swizzleID,
                               const Renderer11DeviceCaps &deviceCaps)
    : format(angle::Format::Get(formatID)),
      texFormat(texFormat),
      srvFormat(srvFormat),
      rtvFormat(rtvFormat),
      dsvFormat(dsvFormat),
      blitSRVFormat(blitSRVFormat),
      swizzle(swizzleID == formatID ? *this : GetANGLEFormatSet(swizzleID, deviceCaps))
{
}

// For sized GL internal formats, there are several possible corresponding D3D11 formats depending
// on device capabilities.
// This function allows querying for the DXGI texture formats to use for textures, SRVs, RTVs and
// DSVs given a GL internal format.
TextureFormat::TextureFormat(GLenum internalFormat,
                             const angle::Format::ID angleFormatID,
                             InitializeTextureDataFunction internalFormatInitializer,
                             const Renderer11DeviceCaps &deviceCaps)
    : internalFormat(internalFormat),
      formatSet(GetANGLEFormatSet(angleFormatID, deviceCaps)),
      dataInitializerFunction(internalFormatInitializer),
      loadFunctions(GetLoadFunctionsMap(internalFormat, formatSet.texFormat))
{
    ASSERT(!loadFunctions.empty() || angleFormatID == angle::Format::ID::NONE);
}

}  // namespace d3d11

}  // namespace rx
