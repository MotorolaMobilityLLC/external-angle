// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_1_2_autogen.cpp:
//   Defines the GL 1.2 entry points.

#include "libGL/entry_points_gl_1_2_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/Context.inl.h"
#include "libANGLE/entry_points_utils.h"
#include "libANGLE/gl_enum_utils.h"
#include "libANGLE/validationEGL.h"
#include "libANGLE/validationES.h"
#include "libANGLE/validationES1.h"
#include "libANGLE/validationES2.h"
#include "libANGLE/validationES3.h"
#include "libANGLE/validationES31.h"
#include "libANGLE/validationES32.h"
#include "libANGLE/validationESEXT.h"
#include "libANGLE/validationGL12_autogen.h"
#include "libGLESv2/global_state.h"

namespace gl
{
void GL_APIENTRY CopyTexSubImage3D(GLenum target,
                                   GLint level,
                                   GLint xoffset,
                                   GLint yoffset,
                                   GLint zoffset,
                                   GLint x,
                                   GLint y,
                                   GLsizei width,
                                   GLsizei height)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, GLCopyTexSubImage3D,
          "context = %d, target = %s, level = %d, xoffset = %d, yoffset = %d, zoffset = %d, x = "
          "%d, y = %d, width = %d, height = %d",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, yoffset,
          zoffset, x, y, width, height);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateCopyTexSubImage3D(context, targetPacked, level, xoffset,
                                                      yoffset, zoffset, x, y, width, height));
        if (isCallValid)
        {
            context->copyTexSubImage3D(targetPacked, level, xoffset, yoffset, zoffset, x, y, width,
                                       height);
        }
        ANGLE_CAPTURE(CopyTexSubImage3D, isCallValid, context, targetPacked, level, xoffset,
                      yoffset, zoffset, x, y, width, height);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY DrawRangeElements(GLenum mode,
                                   GLuint start,
                                   GLuint end,
                                   GLsizei count,
                                   GLenum type,
                                   const void *indices)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, GLDrawRangeElements,
          "context = %d, mode = %s, start = %u, end = %u, count = %d, type = %s, indices = "
          "0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::PrimitiveType, mode), start, end, count,
          GLenumToString(GLenumGroup::DrawElementsType, type), (uintptr_t)indices);

    if (context)
    {
        PrimitiveMode modePacked                              = FromGL<PrimitiveMode>(mode);
        DrawElementsType typePacked                           = FromGL<DrawElementsType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateDrawRangeElements(context, modePacked, start, end,
                                                                    count, typePacked, indices));
        if (isCallValid)
        {
            context->drawRangeElements(modePacked, start, end, count, typePacked, indices);
        }
        ANGLE_CAPTURE(DrawRangeElements, isCallValid, context, modePacked, start, end, count,
                      typePacked, indices);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY TexImage3D(GLenum target,
                            GLint level,
                            GLint internalformat,
                            GLsizei width,
                            GLsizei height,
                            GLsizei depth,
                            GLint border,
                            GLenum format,
                            GLenum type,
                            const void *pixels)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, GLTexImage3D,
          "context = %d, target = %s, level = %d, internalformat = %d, width = %d, height = %d, "
          "depth = %d, border = %d, format = %s, type = %s, pixels = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, internalformat,
          width, height, depth, border, GLenumToString(GLenumGroup::PixelFormat, format),
          GLenumToString(GLenumGroup::PixelType, type), (uintptr_t)pixels);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateTexImage3D(context, targetPacked, level, internalformat, width,
                                               height, depth, border, format, type, pixels));
        if (isCallValid)
        {
            context->texImage3D(targetPacked, level, internalformat, width, height, depth, border,
                                format, type, pixels);
        }
        ANGLE_CAPTURE(TexImage3D, isCallValid, context, targetPacked, level, internalformat, width,
                      height, depth, border, format, type, pixels);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY TexSubImage3D(GLenum target,
                               GLint level,
                               GLint xoffset,
                               GLint yoffset,
                               GLint zoffset,
                               GLsizei width,
                               GLsizei height,
                               GLsizei depth,
                               GLenum format,
                               GLenum type,
                               const void *pixels)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, GLTexSubImage3D,
          "context = %d, target = %s, level = %d, xoffset = %d, yoffset = %d, zoffset = %d, width "
          "= %d, height = %d, depth = %d, format = %s, type = %s, pixels = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, yoffset,
          zoffset, width, height, depth, GLenumToString(GLenumGroup::PixelFormat, format),
          GLenumToString(GLenumGroup::PixelType, type), (uintptr_t)pixels);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() ||
             ValidateTexSubImage3D(context, targetPacked, level, xoffset, yoffset, zoffset, width,
                                   height, depth, format, type, pixels));
        if (isCallValid)
        {
            context->texSubImage3D(targetPacked, level, xoffset, yoffset, zoffset, width, height,
                                   depth, format, type, pixels);
        }
        ANGLE_CAPTURE(TexSubImage3D, isCallValid, context, targetPacked, level, xoffset, yoffset,
                      zoffset, width, height, depth, format, type, pixels);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}
}  // namespace gl
