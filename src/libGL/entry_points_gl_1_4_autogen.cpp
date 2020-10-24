// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_1_4_autogen.cpp:
//   Defines the GL 1.4 entry points.

#include "libGL/entry_points_gl_1_4_autogen.h"

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
#include "libANGLE/validationGL14_autogen.h"
#include "libGLESv2/global_state.h"

namespace gl
{
void GL_APIENTRY BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    Context *context = GetValidGlobalContext();
    EVENT(
        context, gl::EntryPoint::BlendColor, "glBlendColor",
        "context = %d, GLfloat red = %f, GLfloat green = %f, GLfloat blue = %f, GLfloat alpha = %f",
        CID(context), red, green, blue, alpha);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateBlendColor(context, red, green, blue, alpha));
        if (isCallValid)
        {
            context->blendColor(red, green, blue, alpha);
        }
        ANGLE_CAPTURE(BlendColor, isCallValid, context, red, green, blue, alpha);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY BlendEquation(GLenum mode)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::BlendEquation, "glBlendEquation",
          "context = %d, GLenum mode = %s", CID(context),
          GLenumToString(GLenumGroup::BlendEquationModeEXT, mode));

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateBlendEquation(context, mode));
        if (isCallValid)
        {
            context->blendEquation(mode);
        }
        ANGLE_CAPTURE(BlendEquation, isCallValid, context, mode);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY BlendFuncSeparate(GLenum sfactorRGB,
                                   GLenum dfactorRGB,
                                   GLenum sfactorAlpha,
                                   GLenum dfactorAlpha)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::BlendFuncSeparate, "glBlendFuncSeparate",
          "context = %d, GLenum sfactorRGB = %s, GLenum dfactorRGB = %s, GLenum sfactorAlpha = %s, "
          "GLenum dfactorAlpha = %s",
          CID(context), GLenumToString(GLenumGroup::BlendingFactor, sfactorRGB),
          GLenumToString(GLenumGroup::BlendingFactor, dfactorRGB),
          GLenumToString(GLenumGroup::BlendingFactor, sfactorAlpha),
          GLenumToString(GLenumGroup::BlendingFactor, dfactorAlpha));

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateBlendFuncSeparate(context, sfactorRGB, dfactorRGB,
                                                                    sfactorAlpha, dfactorAlpha));
        if (isCallValid)
        {
            context->blendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
        }
        ANGLE_CAPTURE(BlendFuncSeparate, isCallValid, context, sfactorRGB, dfactorRGB, sfactorAlpha,
                      dfactorAlpha);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY FogCoordPointer(GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT(
        context, gl::EntryPoint::FogCoordPointer, "glFogCoordPointer",
        "context = %d, GLenum type = %s, GLsizei stride = %d, const void *pointer = 0x%016" PRIxPTR
        "",
        CID(context), GLenumToString(GLenumGroup::FogPointerTypeEXT, type), stride,
        (uintptr_t)pointer);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateFogCoordPointer(context, type, stride, pointer));
        if (isCallValid)
        {
            context->fogCoordPointer(type, stride, pointer);
        }
        ANGLE_CAPTURE(FogCoordPointer, isCallValid, context, type, stride, pointer);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY FogCoordd(GLdouble coord)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::FogCoordd, "glFogCoordd", "context = %d, GLdouble coord = %f",
          CID(context), coord);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateFogCoordd(context, coord));
        if (isCallValid)
        {
            context->fogCoordd(coord);
        }
        ANGLE_CAPTURE(FogCoordd, isCallValid, context, coord);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY FogCoorddv(const GLdouble *coord)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::FogCoorddv, "glFogCoorddv",
          "context = %d, const GLdouble *coord = 0x%016" PRIxPTR "", CID(context),
          (uintptr_t)coord);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateFogCoorddv(context, coord));
        if (isCallValid)
        {
            context->fogCoorddv(coord);
        }
        ANGLE_CAPTURE(FogCoorddv, isCallValid, context, coord);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY FogCoordf(GLfloat coord)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::FogCoordf, "glFogCoordf", "context = %d, GLfloat coord = %f",
          CID(context), coord);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateFogCoordf(context, coord));
        if (isCallValid)
        {
            context->fogCoordf(coord);
        }
        ANGLE_CAPTURE(FogCoordf, isCallValid, context, coord);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY FogCoordfv(const GLfloat *coord)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::FogCoordfv, "glFogCoordfv",
          "context = %d, const GLfloat *coord = 0x%016" PRIxPTR "", CID(context), (uintptr_t)coord);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateFogCoordfv(context, coord));
        if (isCallValid)
        {
            context->fogCoordfv(coord);
        }
        ANGLE_CAPTURE(FogCoordfv, isCallValid, context, coord);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY MultiDrawArrays(GLenum mode,
                                 const GLint *first,
                                 const GLsizei *count,
                                 GLsizei drawcount)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::MultiDrawArrays, "glMultiDrawArrays",
          "context = %d, GLenum mode = %s, const GLint *first = 0x%016" PRIxPTR
          ", const GLsizei *count = 0x%016" PRIxPTR ", GLsizei drawcount = %d",
          CID(context), GLenumToString(GLenumGroup::PrimitiveType, mode), (uintptr_t)first,
          (uintptr_t)count, drawcount);

    if (context)
    {
        PrimitiveMode modePacked                              = FromGL<PrimitiveMode>(mode);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateMultiDrawArrays(context, modePacked, first, count, drawcount));
        if (isCallValid)
        {
            context->multiDrawArrays(modePacked, first, count, drawcount);
        }
        ANGLE_CAPTURE(MultiDrawArrays, isCallValid, context, modePacked, first, count, drawcount);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY MultiDrawElements(GLenum mode,
                                   const GLsizei *count,
                                   GLenum type,
                                   const void *const *indices,
                                   GLsizei drawcount)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::MultiDrawElements, "glMultiDrawElements",
          "context = %d, GLenum mode = %s, const GLsizei *count = 0x%016" PRIxPTR
          ", GLenum type = %s, const void *const*indices = 0x%016" PRIxPTR
          ", GLsizei drawcount = %d",
          CID(context), GLenumToString(GLenumGroup::PrimitiveType, mode), (uintptr_t)count,
          GLenumToString(GLenumGroup::DrawElementsType, type), (uintptr_t)indices, drawcount);

    if (context)
    {
        PrimitiveMode modePacked                              = FromGL<PrimitiveMode>(mode);
        DrawElementsType typePacked                           = FromGL<DrawElementsType>(type);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() ||
             ValidateMultiDrawElements(context, modePacked, count, typePacked, indices, drawcount));
        if (isCallValid)
        {
            context->multiDrawElements(modePacked, count, typePacked, indices, drawcount);
        }
        ANGLE_CAPTURE(MultiDrawElements, isCallValid, context, modePacked, count, typePacked,
                      indices, drawcount);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY PointParameterf(GLenum pname, GLfloat param)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::PointParameterf, "glPointParameterf",
          "context = %d, GLenum pname = %s, GLfloat param = %f", CID(context),
          GLenumToString(GLenumGroup::DefaultGroup, pname), param);

    if (context)
    {
        PointParameter pnamePacked                            = FromGL<PointParameter>(pname);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidatePointParameterf(context, pnamePacked, param));
        if (isCallValid)
        {
            context->pointParameterf(pnamePacked, param);
        }
        ANGLE_CAPTURE(PointParameterf, isCallValid, context, pnamePacked, param);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY PointParameterfv(GLenum pname, const GLfloat *params)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::PointParameterfv, "glPointParameterfv",
          "context = %d, GLenum pname = %s, const GLfloat *params = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::DefaultGroup, pname), (uintptr_t)params);

    if (context)
    {
        PointParameter pnamePacked                            = FromGL<PointParameter>(pname);
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidatePointParameterfv(context, pnamePacked, params));
        if (isCallValid)
        {
            context->pointParameterfv(pnamePacked, params);
        }
        ANGLE_CAPTURE(PointParameterfv, isCallValid, context, pnamePacked, params);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY PointParameteri(GLenum pname, GLint param)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::PointParameteri, "glPointParameteri",
          "context = %d, GLenum pname = %s, GLint param = %d", CID(context),
          GLenumToString(GLenumGroup::DefaultGroup, pname), param);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidatePointParameteri(context, pname, param));
        if (isCallValid)
        {
            context->pointParameteri(pname, param);
        }
        ANGLE_CAPTURE(PointParameteri, isCallValid, context, pname, param);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY PointParameteriv(GLenum pname, const GLint *params)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::PointParameteriv, "glPointParameteriv",
          "context = %d, GLenum pname = %s, const GLint *params = 0x%016" PRIxPTR "", CID(context),
          GLenumToString(GLenumGroup::DefaultGroup, pname), (uintptr_t)params);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidatePointParameteriv(context, pname, params));
        if (isCallValid)
        {
            context->pointParameteriv(pname, params);
        }
        ANGLE_CAPTURE(PointParameteriv, isCallValid, context, pname, params);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3b, "glSecondaryColor3b",
          "context = %d, GLbyte red = %d, GLbyte green = %d, GLbyte blue = %d", CID(context), red,
          green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3b(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3b(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3b, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3bv(const GLbyte *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3bv, "glSecondaryColor3bv",
          "context = %d, const GLbyte *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3bv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3bv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3bv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3d, "glSecondaryColor3d",
          "context = %d, GLdouble red = %f, GLdouble green = %f, GLdouble blue = %f", CID(context),
          red, green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3d(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3d(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3d, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3dv(const GLdouble *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3dv, "glSecondaryColor3dv",
          "context = %d, const GLdouble *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3dv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3dv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3dv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3f, "glSecondaryColor3f",
          "context = %d, GLfloat red = %f, GLfloat green = %f, GLfloat blue = %f", CID(context),
          red, green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3f(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3f(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3f, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3fv(const GLfloat *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3fv, "glSecondaryColor3fv",
          "context = %d, const GLfloat *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3fv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3fv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3fv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3i(GLint red, GLint green, GLint blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3i, "glSecondaryColor3i",
          "context = %d, GLint red = %d, GLint green = %d, GLint blue = %d", CID(context), red,
          green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3i(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3i(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3i, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3iv(const GLint *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3iv, "glSecondaryColor3iv",
          "context = %d, const GLint *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3iv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3iv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3iv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3s(GLshort red, GLshort green, GLshort blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3s, "glSecondaryColor3s",
          "context = %d, GLshort red = %d, GLshort green = %d, GLshort blue = %d", CID(context),
          red, green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3s(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3s(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3s, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3sv(const GLshort *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3sv, "glSecondaryColor3sv",
          "context = %d, const GLshort *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3sv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3sv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3sv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3ub, "glSecondaryColor3ub",
          "context = %d, GLubyte red = %d, GLubyte green = %d, GLubyte blue = %d", CID(context),
          red, green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3ub(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3ub(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3ub, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3ubv(const GLubyte *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3ubv, "glSecondaryColor3ubv",
          "context = %d, const GLubyte *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3ubv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3ubv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3ubv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3ui(GLuint red, GLuint green, GLuint blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3ui, "glSecondaryColor3ui",
          "context = %d, GLuint red = %u, GLuint green = %u, GLuint blue = %u", CID(context), red,
          green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3ui(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3ui(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3ui, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3uiv(const GLuint *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3uiv, "glSecondaryColor3uiv",
          "context = %d, const GLuint *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3uiv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3uiv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3uiv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3us(GLushort red, GLushort green, GLushort blue)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3us, "glSecondaryColor3us",
          "context = %d, GLushort red = %u, GLushort green = %u, GLushort blue = %u", CID(context),
          red, green, blue);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateSecondaryColor3us(context, red, green, blue));
        if (isCallValid)
        {
            context->secondaryColor3us(red, green, blue);
        }
        ANGLE_CAPTURE(SecondaryColor3us, isCallValid, context, red, green, blue);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColor3usv(const GLushort *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColor3usv, "glSecondaryColor3usv",
          "context = %d, const GLushort *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateSecondaryColor3usv(context, v));
        if (isCallValid)
        {
            context->secondaryColor3usv(v);
        }
        ANGLE_CAPTURE(SecondaryColor3usv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::SecondaryColorPointer, "glSecondaryColorPointer",
          "context = %d, GLint size = %d, GLenum type = %s, GLsizei stride = %d, const void "
          "*pointer = 0x%016" PRIxPTR "",
          CID(context), size, GLenumToString(GLenumGroup::ColorPointerType, type), stride,
          (uintptr_t)pointer);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                                      = (context->skipValidation() ||
                            ValidateSecondaryColorPointer(context, size, type, stride, pointer));
        if (isCallValid)
        {
            context->secondaryColorPointer(size, type, stride, pointer);
        }
        ANGLE_CAPTURE(SecondaryColorPointer, isCallValid, context, size, type, stride, pointer);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2d(GLdouble x, GLdouble y)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2d, "glWindowPos2d",
          "context = %d, GLdouble x = %f, GLdouble y = %f", CID(context), x, y);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2d(context, x, y));
        if (isCallValid)
        {
            context->windowPos2d(x, y);
        }
        ANGLE_CAPTURE(WindowPos2d, isCallValid, context, x, y);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2dv(const GLdouble *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2dv, "glWindowPos2dv",
          "context = %d, const GLdouble *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2dv(context, v));
        if (isCallValid)
        {
            context->windowPos2dv(v);
        }
        ANGLE_CAPTURE(WindowPos2dv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2f(GLfloat x, GLfloat y)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2f, "glWindowPos2f",
          "context = %d, GLfloat x = %f, GLfloat y = %f", CID(context), x, y);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2f(context, x, y));
        if (isCallValid)
        {
            context->windowPos2f(x, y);
        }
        ANGLE_CAPTURE(WindowPos2f, isCallValid, context, x, y);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2fv(const GLfloat *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2fv, "glWindowPos2fv",
          "context = %d, const GLfloat *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2fv(context, v));
        if (isCallValid)
        {
            context->windowPos2fv(v);
        }
        ANGLE_CAPTURE(WindowPos2fv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2i(GLint x, GLint y)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2i, "glWindowPos2i",
          "context = %d, GLint x = %d, GLint y = %d", CID(context), x, y);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2i(context, x, y));
        if (isCallValid)
        {
            context->windowPos2i(x, y);
        }
        ANGLE_CAPTURE(WindowPos2i, isCallValid, context, x, y);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2iv(const GLint *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2iv, "glWindowPos2iv",
          "context = %d, const GLint *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2iv(context, v));
        if (isCallValid)
        {
            context->windowPos2iv(v);
        }
        ANGLE_CAPTURE(WindowPos2iv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2s(GLshort x, GLshort y)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2s, "glWindowPos2s",
          "context = %d, GLshort x = %d, GLshort y = %d", CID(context), x, y);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2s(context, x, y));
        if (isCallValid)
        {
            context->windowPos2s(x, y);
        }
        ANGLE_CAPTURE(WindowPos2s, isCallValid, context, x, y);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos2sv(const GLshort *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos2sv, "glWindowPos2sv",
          "context = %d, const GLshort *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos2sv(context, v));
        if (isCallValid)
        {
            context->windowPos2sv(v);
        }
        ANGLE_CAPTURE(WindowPos2sv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3d(GLdouble x, GLdouble y, GLdouble z)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3d, "glWindowPos3d",
          "context = %d, GLdouble x = %f, GLdouble y = %f, GLdouble z = %f", CID(context), x, y, z);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3d(context, x, y, z));
        if (isCallValid)
        {
            context->windowPos3d(x, y, z);
        }
        ANGLE_CAPTURE(WindowPos3d, isCallValid, context, x, y, z);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3dv(const GLdouble *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3dv, "glWindowPos3dv",
          "context = %d, const GLdouble *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3dv(context, v));
        if (isCallValid)
        {
            context->windowPos3dv(v);
        }
        ANGLE_CAPTURE(WindowPos3dv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3f(GLfloat x, GLfloat y, GLfloat z)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3f, "glWindowPos3f",
          "context = %d, GLfloat x = %f, GLfloat y = %f, GLfloat z = %f", CID(context), x, y, z);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3f(context, x, y, z));
        if (isCallValid)
        {
            context->windowPos3f(x, y, z);
        }
        ANGLE_CAPTURE(WindowPos3f, isCallValid, context, x, y, z);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3fv(const GLfloat *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3fv, "glWindowPos3fv",
          "context = %d, const GLfloat *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3fv(context, v));
        if (isCallValid)
        {
            context->windowPos3fv(v);
        }
        ANGLE_CAPTURE(WindowPos3fv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3i(GLint x, GLint y, GLint z)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3i, "glWindowPos3i",
          "context = %d, GLint x = %d, GLint y = %d, GLint z = %d", CID(context), x, y, z);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3i(context, x, y, z));
        if (isCallValid)
        {
            context->windowPos3i(x, y, z);
        }
        ANGLE_CAPTURE(WindowPos3i, isCallValid, context, x, y, z);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3iv(const GLint *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3iv, "glWindowPos3iv",
          "context = %d, const GLint *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3iv(context, v));
        if (isCallValid)
        {
            context->windowPos3iv(v);
        }
        ANGLE_CAPTURE(WindowPos3iv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3s(GLshort x, GLshort y, GLshort z)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3s, "glWindowPos3s",
          "context = %d, GLshort x = %d, GLshort y = %d, GLshort z = %d", CID(context), x, y, z);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3s(context, x, y, z));
        if (isCallValid)
        {
            context->windowPos3s(x, y, z);
        }
        ANGLE_CAPTURE(WindowPos3s, isCallValid, context, x, y, z);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}

void GL_APIENTRY WindowPos3sv(const GLshort *v)
{
    Context *context = GetValidGlobalContext();
    EVENT(context, gl::EntryPoint::WindowPos3sv, "glWindowPos3sv",
          "context = %d, const GLshort *v = 0x%016" PRIxPTR "", CID(context), (uintptr_t)v);

    if (context)
    {
        std::unique_lock<angle::GlobalMutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateWindowPos3sv(context, v));
        if (isCallValid)
        {
            context->windowPos3sv(v);
        }
        ANGLE_CAPTURE(WindowPos3sv, isCallValid, context, v);
    }
    else
    {
        GenerateContextLostErrorOnCurrentGlobalContext();
    }
}
}  // namespace gl
