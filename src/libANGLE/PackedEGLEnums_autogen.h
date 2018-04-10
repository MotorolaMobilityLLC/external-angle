// GENERATED FILE - DO NOT EDIT.
// Generated by gen_packed_gl_enums.py using data from packed_egl_enums.json.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// PackedEGLEnums_autogen.h:
//   Declares ANGLE-specific enums classes for EGLenums and functions operating
//   on them.

#ifndef LIBANGLE_PACKEDEGLENUMS_AUTOGEN_H_
#define LIBANGLE_PACKEDEGLENUMS_AUTOGEN_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <angle_gl.h>

#include <cstdint>

namespace egl
{

template <typename Enum>
Enum FromEGLenum(EGLenum from);

enum class TextureFormat : uint8_t
{
    NoTexture = 0,
    RGB       = 1,
    RGBA      = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
TextureFormat FromEGLenum<TextureFormat>(EGLenum from);
EGLenum ToEGLenum(TextureFormat from);

}  // namespace egl

#endif  // LIBANGLE_PACKEDEGLENUMS_AUTOGEN_H_
