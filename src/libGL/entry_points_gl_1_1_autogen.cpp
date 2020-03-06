// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_1_1_autogen.cpp:
//   Defines the GL 1.1 entry points.

#include "libGL/entry_points_gl_1_1_autogen.h"

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
#include "libANGLE/validationGL11_autogen.h"
#include "libGLESv2/global_state.h"

namespace gl
{
GLboolean GL_APIENTRY AreTexturesResident(GLsizei n, const GLuint *textures, GLboolean *residences)
{
    Context *context = GetValidGlobalContext();
    EVENT("glAreTexturesResident",
          "context = %d, GLsizei n = %d, const GLuint *textures = 0x%016" PRIxPTR
          ", GLboolean *residences = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)textures, (uintptr_t)residences);

    GLboolean returnValue;
    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateAreTexturesResident(context, n, textures, residences));
        if (isCallValid)
        {
            returnValue = context->areTexturesResident(n, textures, residences);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::AreTexturesResident, GLboolean>();
        }
        ANGLE_CAPTURE(AreTexturesResident, isCallValid, context, n, textures, residences,
                      returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::AreTexturesResident, GLboolean>();
    }
    return returnValue;
}

void GL_APIENTRY ArrayElement(GLint i)
{
    Context *context = GetValidGlobalContext();
    EVENT("glArrayElement", "context = %d, GLint i = %d", CID(context), i);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateArrayElement(context, i));
        if (isCallValid)
        {
            context->arrayElement(i);
        }
        ANGLE_CAPTURE(ArrayElement, isCallValid, context, i);
    }
}

void GL_APIENTRY BindTexture(GLenum target, GLuint texture)
{
    Context *context = GetValidGlobalContext();
    EVENT("glBindTexture", "context = %d, GLenum target = %s, GLuint texture = %u", CID(context),
          GLenumToString(GLenumGroup::TextureTarget, target), texture);

    if (context)
    {
        TextureType targetPacked                              = FromGL<TextureType>(target);
        TextureID texturePacked                               = FromGL<TextureID>(texture);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateBindTexture(context, targetPacked, texturePacked));
        if (isCallValid)
        {
            context->bindTexture(targetPacked, texturePacked);
        }
        ANGLE_CAPTURE(BindTexture, isCallValid, context, targetPacked, texturePacked);
    }
}

void GL_APIENTRY ColorPointer(GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glColorPointer",
          "context = %d, GLint size = %d, GLenum type = %s, GLsizei stride = %d, const void "
          "*pointer = 0x%016" PRIxPTR "",
          CID(context), size, GLenumToString(GLenumGroup::ColorPointerType, type), stride,
          (uintptr_t)pointer);

    if (context)
    {
        VertexAttribType typePacked                           = FromGL<VertexAttribType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateColorPointer(context, size, typePacked, stride, pointer));
        if (isCallValid)
        {
            context->colorPointer(size, typePacked, stride, pointer);
        }
        ANGLE_CAPTURE(ColorPointer, isCallValid, context, size, typePacked, stride, pointer);
    }
}

void GL_APIENTRY CopyTexImage1D(GLenum target,
                                GLint level,
                                GLenum internalformat,
                                GLint x,
                                GLint y,
                                GLsizei width,
                                GLint border)
{
    Context *context = GetValidGlobalContext();
    EVENT("glCopyTexImage1D",
          "context = %d, GLenum target = %s, GLint level = %d, GLenum internalformat = %s, GLint x "
          "= %d, GLint y = %d, GLsizei width = %d, GLint border = %d",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level,
          GLenumToString(GLenumGroup::InternalFormat, internalformat), x, y, width, border);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() ||
             ValidateCopyTexImage1D(context, target, level, internalformat, x, y, width, border));
        if (isCallValid)
        {
            context->copyTexImage1D(target, level, internalformat, x, y, width, border);
        }
        ANGLE_CAPTURE(CopyTexImage1D, isCallValid, context, target, level, internalformat, x, y,
                      width, border);
    }
}

void GL_APIENTRY CopyTexImage2D(GLenum target,
                                GLint level,
                                GLenum internalformat,
                                GLint x,
                                GLint y,
                                GLsizei width,
                                GLsizei height,
                                GLint border)
{
    Context *context = GetValidGlobalContext();
    EVENT("glCopyTexImage2D",
          "context = %d, GLenum target = %s, GLint level = %d, GLenum internalformat = %s, GLint x "
          "= %d, GLint y = %d, GLsizei width = %d, GLsizei height = %d, GLint border = %d",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level,
          GLenumToString(GLenumGroup::InternalFormat, internalformat), x, y, width, height, border);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateCopyTexImage2D(context, targetPacked, level, internalformat, x,
                                                   y, width, height, border));
        if (isCallValid)
        {
            context->copyTexImage2D(targetPacked, level, internalformat, x, y, width, height,
                                    border);
        }
        ANGLE_CAPTURE(CopyTexImage2D, isCallValid, context, targetPacked, level, internalformat, x,
                      y, width, height, border);
    }
}

void GL_APIENTRY
CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    Context *context = GetValidGlobalContext();
    EVENT("glCopyTexSubImage1D",
          "context = %d, GLenum target = %s, GLint level = %d, GLint xoffset = %d, GLint x = %d, "
          "GLint y = %d, GLsizei width = %d",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, x, y,
          width);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() ||
             ValidateCopyTexSubImage1D(context, target, level, xoffset, x, y, width));
        if (isCallValid)
        {
            context->copyTexSubImage1D(target, level, xoffset, x, y, width);
        }
        ANGLE_CAPTURE(CopyTexSubImage1D, isCallValid, context, target, level, xoffset, x, y, width);
    }
}

void GL_APIENTRY CopyTexSubImage2D(GLenum target,
                                   GLint level,
                                   GLint xoffset,
                                   GLint yoffset,
                                   GLint x,
                                   GLint y,
                                   GLsizei width,
                                   GLsizei height)
{
    Context *context = GetValidGlobalContext();
    EVENT("glCopyTexSubImage2D",
          "context = %d, GLenum target = %s, GLint level = %d, GLint xoffset = %d, GLint yoffset = "
          "%d, GLint x = %d, GLint y = %d, GLsizei width = %d, GLsizei height = %d",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, yoffset,
          x, y, width, height);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateCopyTexSubImage2D(context, targetPacked, level, xoffset,
                                                      yoffset, x, y, width, height));
        if (isCallValid)
        {
            context->copyTexSubImage2D(targetPacked, level, xoffset, yoffset, x, y, width, height);
        }
        ANGLE_CAPTURE(CopyTexSubImage2D, isCallValid, context, targetPacked, level, xoffset,
                      yoffset, x, y, width, height);
    }
}

void GL_APIENTRY DeleteTextures(GLsizei n, const GLuint *textures)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDeleteTextures",
          "context = %d, GLsizei n = %d, const GLuint *textures = 0x%016" PRIxPTR "", CID(context),
          n, (uintptr_t)textures);

    if (context)
    {
        const TextureID *texturesPacked                       = FromGL<const TextureID *>(textures);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateDeleteTextures(context, n, texturesPacked));
        if (isCallValid)
        {
            context->deleteTextures(n, texturesPacked);
        }
        ANGLE_CAPTURE(DeleteTextures, isCallValid, context, n, texturesPacked);
    }
}

void GL_APIENTRY DisableClientState(GLenum array)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDisableClientState", "context = %d, GLenum array = %s", CID(context),
          GLenumToString(GLenumGroup::EnableCap, array));

    if (context)
    {
        ClientVertexArrayType arrayPacked = FromGL<ClientVertexArrayType>(array);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateDisableClientState(context, arrayPacked));
        if (isCallValid)
        {
            context->disableClientState(arrayPacked);
        }
        ANGLE_CAPTURE(DisableClientState, isCallValid, context, arrayPacked);
    }
}

void GL_APIENTRY DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDrawArrays", "context = %d, GLenum mode = %s, GLint first = %d, GLsizei count = %d",
          CID(context), GLenumToString(GLenumGroup::PrimitiveType, mode), first, count);

    if (context)
    {
        PrimitiveMode modePacked                              = FromGL<PrimitiveMode>(mode);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateDrawArrays(context, modePacked, first, count));
        if (isCallValid)
        {
            context->drawArrays(modePacked, first, count);
        }
        ANGLE_CAPTURE(DrawArrays, isCallValid, context, modePacked, first, count);
    }
}

void GL_APIENTRY DrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDrawElements",
          "context = %d, GLenum mode = %s, GLsizei count = %d, GLenum type = %s, const void "
          "*indices = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::PrimitiveType, mode), count,
          GLenumToString(GLenumGroup::DrawElementsType, type), (uintptr_t)indices);

    if (context)
    {
        PrimitiveMode modePacked                              = FromGL<PrimitiveMode>(mode);
        DrawElementsType typePacked                           = FromGL<DrawElementsType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateDrawElements(context, modePacked, count, typePacked, indices));
        if (isCallValid)
        {
            context->drawElements(modePacked, count, typePacked, indices);
        }
        ANGLE_CAPTURE(DrawElements, isCallValid, context, modePacked, count, typePacked, indices);
    }
}

void GL_APIENTRY EdgeFlagPointer(GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glEdgeFlagPointer",
          "context = %d, GLsizei stride = %d, const void *pointer = 0x%016" PRIxPTR "",
          CID(context), stride, (uintptr_t)pointer);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateEdgeFlagPointer(context, stride, pointer));
        if (isCallValid)
        {
            context->edgeFlagPointer(stride, pointer);
        }
        ANGLE_CAPTURE(EdgeFlagPointer, isCallValid, context, stride, pointer);
    }
}

void GL_APIENTRY EnableClientState(GLenum array)
{
    Context *context = GetValidGlobalContext();
    EVENT("glEnableClientState", "context = %d, GLenum array = %s", CID(context),
          GLenumToString(GLenumGroup::EnableCap, array));

    if (context)
    {
        ClientVertexArrayType arrayPacked = FromGL<ClientVertexArrayType>(array);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateEnableClientState(context, arrayPacked));
        if (isCallValid)
        {
            context->enableClientState(arrayPacked);
        }
        ANGLE_CAPTURE(EnableClientState, isCallValid, context, arrayPacked);
    }
}

void GL_APIENTRY GenTextures(GLsizei n, GLuint *textures)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGenTextures", "context = %d, GLsizei n = %d, GLuint *textures = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)textures);

    if (context)
    {
        TextureID *texturesPacked                             = FromGL<TextureID *>(textures);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGenTextures(context, n, texturesPacked));
        if (isCallValid)
        {
            context->genTextures(n, texturesPacked);
        }
        ANGLE_CAPTURE(GenTextures, isCallValid, context, n, texturesPacked);
    }
}

void GL_APIENTRY GetPointerv(GLenum pname, void **params)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetPointerv", "context = %d, GLenum pname = %s, void **params = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::GetPointervPName, pname), (uintptr_t)params);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGetPointerv(context, pname, params));
        if (isCallValid)
        {
            context->getPointerv(pname, params);
        }
        ANGLE_CAPTURE(GetPointerv, isCallValid, context, pname, params);
    }
}

void GL_APIENTRY IndexPointer(GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT(
        "glIndexPointer",
        "context = %d, GLenum type = %s, GLsizei stride = %d, const void *pointer = 0x%016" PRIxPTR
        "",
        CID(context), GLenumToString(GLenumGroup::IndexPointerType, type), stride,
        (uintptr_t)pointer);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateIndexPointer(context, type, stride, pointer));
        if (isCallValid)
        {
            context->indexPointer(type, stride, pointer);
        }
        ANGLE_CAPTURE(IndexPointer, isCallValid, context, type, stride, pointer);
    }
}

void GL_APIENTRY Indexub(GLubyte c)
{
    Context *context = GetValidGlobalContext();
    EVENT("glIndexub", "context = %d, GLubyte c = %d", CID(context), c);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateIndexub(context, c));
        if (isCallValid)
        {
            context->indexub(c);
        }
        ANGLE_CAPTURE(Indexub, isCallValid, context, c);
    }
}

void GL_APIENTRY Indexubv(const GLubyte *c)
{
    Context *context = GetValidGlobalContext();
    EVENT("glIndexubv", "context = %d, const GLubyte *c = 0x%016" PRIxPTR "", CID(context),
          (uintptr_t)c);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateIndexubv(context, c));
        if (isCallValid)
        {
            context->indexubv(c);
        }
        ANGLE_CAPTURE(Indexubv, isCallValid, context, c);
    }
}

void GL_APIENTRY InterleavedArrays(GLenum format, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glInterleavedArrays",
          "context = %d, GLenum format = %s, GLsizei stride = %d, const void *pointer = "
          "0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::InterleavedArrayFormat, format), stride,
          (uintptr_t)pointer);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateInterleavedArrays(context, format, stride, pointer));
        if (isCallValid)
        {
            context->interleavedArrays(format, stride, pointer);
        }
        ANGLE_CAPTURE(InterleavedArrays, isCallValid, context, format, stride, pointer);
    }
}

GLboolean GL_APIENTRY IsTexture(GLuint texture)
{
    Context *context = GetValidGlobalContext();
    EVENT("glIsTexture", "context = %d, GLuint texture = %u", CID(context), texture);

    GLboolean returnValue;
    if (context)
    {
        TextureID texturePacked                               = FromGL<TextureID>(texture);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateIsTexture(context, texturePacked));
        if (isCallValid)
        {
            returnValue = context->isTexture(texturePacked);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::IsTexture, GLboolean>();
        }
        ANGLE_CAPTURE(IsTexture, isCallValid, context, texturePacked, returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::IsTexture, GLboolean>();
    }
    return returnValue;
}

void GL_APIENTRY NormalPointer(GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT(
        "glNormalPointer",
        "context = %d, GLenum type = %s, GLsizei stride = %d, const void *pointer = 0x%016" PRIxPTR
        "",
        CID(context), GLenumToString(GLenumGroup::NormalPointerType, type), stride,
        (uintptr_t)pointer);

    if (context)
    {
        VertexAttribType typePacked                           = FromGL<VertexAttribType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateNormalPointer(context, typePacked, stride, pointer));
        if (isCallValid)
        {
            context->normalPointer(typePacked, stride, pointer);
        }
        ANGLE_CAPTURE(NormalPointer, isCallValid, context, typePacked, stride, pointer);
    }
}

void GL_APIENTRY PolygonOffset(GLfloat factor, GLfloat units)
{
    Context *context = GetValidGlobalContext();
    EVENT("glPolygonOffset", "context = %d, GLfloat factor = %f, GLfloat units = %f", CID(context),
          factor, units);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidatePolygonOffset(context, factor, units));
        if (isCallValid)
        {
            context->polygonOffset(factor, units);
        }
        ANGLE_CAPTURE(PolygonOffset, isCallValid, context, factor, units);
    }
}

void GL_APIENTRY PopClientAttrib()
{
    Context *context = GetValidGlobalContext();
    EVENT("glPopClientAttrib", "context = %d", CID(context));

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidatePopClientAttrib(context));
        if (isCallValid)
        {
            context->popClientAttrib();
        }
        ANGLE_CAPTURE(PopClientAttrib, isCallValid, context);
    }
}

void GL_APIENTRY PrioritizeTextures(GLsizei n, const GLuint *textures, const GLfloat *priorities)
{
    Context *context = GetValidGlobalContext();
    EVENT("glPrioritizeTextures",
          "context = %d, GLsizei n = %d, const GLuint *textures = 0x%016" PRIxPTR
          ", const GLfloat *priorities = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)textures, (uintptr_t)priorities);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidatePrioritizeTextures(context, n, textures, priorities));
        if (isCallValid)
        {
            context->prioritizeTextures(n, textures, priorities);
        }
        ANGLE_CAPTURE(PrioritizeTextures, isCallValid, context, n, textures, priorities);
    }
}

void GL_APIENTRY PushClientAttrib(GLbitfield mask)
{
    Context *context = GetValidGlobalContext();
    EVENT("glPushClientAttrib", "context = %d, GLbitfield mask = %s", CID(context),
          GLbitfieldToString(GLenumGroup::ClientAttribMask, mask).c_str());

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidatePushClientAttrib(context, mask));
        if (isCallValid)
        {
            context->pushClientAttrib(mask);
        }
        ANGLE_CAPTURE(PushClientAttrib, isCallValid, context, mask);
    }
}

void GL_APIENTRY TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glTexCoordPointer",
          "context = %d, GLint size = %d, GLenum type = %s, GLsizei stride = %d, const void "
          "*pointer = 0x%016" PRIxPTR "",
          CID(context), size, GLenumToString(GLenumGroup::TexCoordPointerType, type), stride,
          (uintptr_t)pointer);

    if (context)
    {
        VertexAttribType typePacked                           = FromGL<VertexAttribType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateTexCoordPointer(context, size, typePacked, stride, pointer));
        if (isCallValid)
        {
            context->texCoordPointer(size, typePacked, stride, pointer);
        }
        ANGLE_CAPTURE(TexCoordPointer, isCallValid, context, size, typePacked, stride, pointer);
    }
}

void GL_APIENTRY TexSubImage1D(GLenum target,
                               GLint level,
                               GLint xoffset,
                               GLsizei width,
                               GLenum format,
                               GLenum type,
                               const void *pixels)
{
    Context *context = GetValidGlobalContext();
    EVENT("glTexSubImage1D",
          "context = %d, GLenum target = %s, GLint level = %d, GLint xoffset = %d, GLsizei width = "
          "%d, GLenum format = %s, GLenum type = %s, const void *pixels = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, width,
          GLenumToString(GLenumGroup::PixelFormat, format),
          GLenumToString(GLenumGroup::PixelType, type), (uintptr_t)pixels);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() ||
             ValidateTexSubImage1D(context, target, level, xoffset, width, format, type, pixels));
        if (isCallValid)
        {
            context->texSubImage1D(target, level, xoffset, width, format, type, pixels);
        }
        ANGLE_CAPTURE(TexSubImage1D, isCallValid, context, target, level, xoffset, width, format,
                      type, pixels);
    }
}

void GL_APIENTRY TexSubImage2D(GLenum target,
                               GLint level,
                               GLint xoffset,
                               GLint yoffset,
                               GLsizei width,
                               GLsizei height,
                               GLenum format,
                               GLenum type,
                               const void *pixels)
{
    Context *context = GetValidGlobalContext();
    EVENT("glTexSubImage2D",
          "context = %d, GLenum target = %s, GLint level = %d, GLint xoffset = %d, GLint yoffset = "
          "%d, GLsizei width = %d, GLsizei height = %d, GLenum format = %s, GLenum type = %s, "
          "const void *pixels = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::TextureTarget, target), level, xoffset, yoffset,
          width, height, GLenumToString(GLenumGroup::PixelFormat, format),
          GLenumToString(GLenumGroup::PixelType, type), (uintptr_t)pixels);

    if (context)
    {
        TextureTarget targetPacked                            = FromGL<TextureTarget>(target);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateTexSubImage2D(context, targetPacked, level, xoffset, yoffset,
                                                  width, height, format, type, pixels));
        if (isCallValid)
        {
            context->texSubImage2D(targetPacked, level, xoffset, yoffset, width, height, format,
                                   type, pixels);
        }
        ANGLE_CAPTURE(TexSubImage2D, isCallValid, context, targetPacked, level, xoffset, yoffset,
                      width, height, format, type, pixels);
    }
}

void GL_APIENTRY VertexPointer(GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glVertexPointer",
          "context = %d, GLint size = %d, GLenum type = %s, GLsizei stride = %d, const void "
          "*pointer = 0x%016" PRIxPTR "",
          CID(context), size, GLenumToString(GLenumGroup::VertexPointerType, type), stride,
          (uintptr_t)pointer);

    if (context)
    {
        VertexAttribType typePacked                           = FromGL<VertexAttribType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateVertexPointer(context, size, typePacked, stride, pointer));
        if (isCallValid)
        {
            context->vertexPointer(size, typePacked, stride, pointer);
        }
        ANGLE_CAPTURE(VertexPointer, isCallValid, context, size, typePacked, stride, pointer);
    }
}
}  // namespace gl
