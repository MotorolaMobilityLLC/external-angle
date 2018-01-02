// GENERATED FILE - DO NOT EDIT.
// Generated by gen_packed_gl_enums.py using data from packed_gl_enums.json.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// PackedGLEnums_autogen.h:
//   Declares ANGLE-specific enums classes for GLEnum and functions operating
//   on them.

#ifndef LIBANGLE_PACKEDGLENUMS_AUTOGEN_H_
#define LIBANGLE_PACKEDGLENUMS_AUTOGEN_H_

#include <angle_gl.h>

#include <cstdint>

namespace gl
{

template <typename Enum>
Enum FromGLenum(GLenum from);

enum class BufferBinding : uint8_t
{
    Array             = 0,
    AtomicCounter     = 1,
    CopyRead          = 2,
    CopyWrite         = 3,
    DispatchIndirect  = 4,
    DrawIndirect      = 5,
    ElementArray      = 6,
    PixelPack         = 7,
    PixelUnpack       = 8,
    ShaderStorage     = 9,
    TransformFeedback = 10,
    Uniform           = 11,

    InvalidEnum = 12,
    EnumCount   = 12,
};

template <>
BufferBinding FromGLenum<BufferBinding>(GLenum from);
GLenum ToGLenum(BufferBinding from);

enum class BufferUsage : uint8_t
{
    DynamicCopy = 0,
    DynamicDraw = 1,
    DynamicRead = 2,
    StaticCopy  = 3,
    StaticDraw  = 4,
    StaticRead  = 5,
    StreamCopy  = 6,
    StreamDraw  = 7,
    StreamRead  = 8,

    InvalidEnum = 9,
    EnumCount   = 9,
};

template <>
BufferUsage FromGLenum<BufferUsage>(GLenum from);
GLenum ToGLenum(BufferUsage from);

enum class CullFaceMode : uint8_t
{
    Back         = 0,
    Front        = 1,
    FrontAndBack = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
CullFaceMode FromGLenum<CullFaceMode>(GLenum from);
GLenum ToGLenum(CullFaceMode from);

}  // namespace gl

#endif  // LIBANGLE_PACKEDGLENUMS_AUTOGEN_H_
