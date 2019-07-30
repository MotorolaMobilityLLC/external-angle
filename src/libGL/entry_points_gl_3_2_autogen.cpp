// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_3_2_autogen.cpp:
//   Defines the GL 3.2 entry points.

#include "libGL/entry_points_gl_3_2_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/Context.inl.h"
#include "libANGLE/entry_points_utils.h"
#include "libANGLE/validationEGL.h"
#include "libANGLE/validationES.h"
#include "libANGLE/validationES1.h"
#include "libANGLE/validationES2.h"
#include "libANGLE/validationES3.h"
#include "libANGLE/validationES31.h"
#include "libANGLE/validationESEXT.h"
#include "libANGLE/validationGL32_autogen.h"
#include "libGLESv2/global_state.h"

namespace gl
{
GLenum GL_APIENTRY ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    EVENT("(GLsync sync = 0x%016" PRIxPTR ", GLbitfield flags = 0x%X, GLuint64 timeout = %llu)",
          (uintptr_t)sync, flags, static_cast<unsigned long long>(timeout));

    Context *context = GetValidGlobalContext();
    GLenum returnValue;
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateClientWaitSync(context, sync, flags, timeout));
        if (isCallValid)
        {
            returnValue = context->clientWaitSync(sync, flags, timeout);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::ClientWaitSync, GLenum>();
        }
        ANGLE_CAPTURE(ClientWaitSync, isCallValid, context, sync, flags, timeout);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::ClientWaitSync, GLenum>();
    }
    return returnValue;
}

void GL_APIENTRY DeleteSync(GLsync sync)
{
    EVENT("(GLsync sync = 0x%016" PRIxPTR ")", (uintptr_t)sync);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() || ValidateDeleteSync(context, sync));
        if (isCallValid)
        {
            context->deleteSync(sync);
        }
        ANGLE_CAPTURE(DeleteSync, isCallValid, context, sync);
    }
}

void GL_APIENTRY DrawElementsBaseVertex(GLenum mode,
                                        GLsizei count,
                                        GLenum type,
                                        const void *indices,
                                        GLint basevertex)
{
    EVENT(
        "(GLenum mode = 0x%X, GLsizei count = %d, GLenum type = 0x%X, const void *indices = "
        "0x%016" PRIxPTR ", GLint basevertex = %d)",
        mode, count, type, (uintptr_t)indices, basevertex);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() ||
             ValidateDrawElementsBaseVertex(context, mode, count, type, indices, basevertex));
        if (isCallValid)
        {
            context->drawElementsBaseVertex(mode, count, type, indices, basevertex);
        }
        ANGLE_CAPTURE(DrawElementsBaseVertex, isCallValid, context, mode, count, type, indices,
                      basevertex);
    }
}

void GL_APIENTRY DrawElementsInstancedBaseVertex(GLenum mode,
                                                 GLsizei count,
                                                 GLenum type,
                                                 const void *indices,
                                                 GLsizei instancecount,
                                                 GLint basevertex)
{
    EVENT(
        "(GLenum mode = 0x%X, GLsizei count = %d, GLenum type = 0x%X, const void *indices = "
        "0x%016" PRIxPTR ", GLsizei instancecount = %d, GLint basevertex = %d)",
        mode, count, type, (uintptr_t)indices, instancecount, basevertex);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() ||
                            ValidateDrawElementsInstancedBaseVertex(
                                context, mode, count, type, indices, instancecount, basevertex));
        if (isCallValid)
        {
            context->drawElementsInstancedBaseVertex(mode, count, type, indices, instancecount,
                                                     basevertex);
        }
        ANGLE_CAPTURE(DrawElementsInstancedBaseVertex, isCallValid, context, mode, count, type,
                      indices, instancecount, basevertex);
    }
}

void GL_APIENTRY DrawRangeElementsBaseVertex(GLenum mode,
                                             GLuint start,
                                             GLuint end,
                                             GLsizei count,
                                             GLenum type,
                                             const void *indices,
                                             GLint basevertex)
{
    EVENT(
        "(GLenum mode = 0x%X, GLuint start = %u, GLuint end = %u, GLsizei count = %d, GLenum type "
        "= 0x%X, const void *indices = 0x%016" PRIxPTR ", GLint basevertex = %d)",
        mode, start, end, count, type, (uintptr_t)indices, basevertex);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() ||
                            ValidateDrawRangeElementsBaseVertex(context, mode, start, end, count,
                                                                type, indices, basevertex));
        if (isCallValid)
        {
            context->drawRangeElementsBaseVertex(mode, start, end, count, type, indices,
                                                 basevertex);
        }
        ANGLE_CAPTURE(DrawRangeElementsBaseVertex, isCallValid, context, mode, start, end, count,
                      type, indices, basevertex);
    }
}

GLsync GL_APIENTRY FenceSync(GLenum condition, GLbitfield flags)
{
    EVENT("(GLenum condition = 0x%X, GLbitfield flags = 0x%X)", condition, flags);

    Context *context = GetValidGlobalContext();
    GLsync returnValue;
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateFenceSync(context, condition, flags));
        if (isCallValid)
        {
            returnValue = context->fenceSync(condition, flags);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::FenceSync, GLsync>();
        }
        ANGLE_CAPTURE(FenceSync, isCallValid, context, condition, flags);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::FenceSync, GLsync>();
    }
    return returnValue;
}

void GL_APIENTRY FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
    EVENT("(GLenum target = 0x%X, GLenum attachment = 0x%X, GLuint texture = %u, GLint level = %d)",
          target, attachment, texture, level);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() ||
             ValidateFramebufferTexture(context, target, attachment, texture, level));
        if (isCallValid)
        {
            context->framebufferTexture(target, attachment, texture, level);
        }
        ANGLE_CAPTURE(FramebufferTexture, isCallValid, context, target, attachment, texture, level);
    }
}

void GL_APIENTRY GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
{
    EVENT("(GLenum target = 0x%X, GLenum pname = 0x%X, GLint64 *params = 0x%016" PRIxPTR ")",
          target, pname, (uintptr_t)params);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        BufferBinding targetPacked = FromGLenum<BufferBinding>(target);
        bool isCallValid           = (context->skipValidation() ||
                            ValidateGetBufferParameteri64v(context, targetPacked, pname, params));
        if (isCallValid)
        {
            context->getBufferParameteri64v(targetPacked, pname, params);
        }
        ANGLE_CAPTURE(GetBufferParameteri64v, isCallValid, context, targetPacked, pname, params);
    }
}

void GL_APIENTRY GetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
{
    EVENT("(GLenum target = 0x%X, GLuint index = %u, GLint64 *data = 0x%016" PRIxPTR ")", target,
          index, (uintptr_t)data);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateGetInteger64i_v(context, target, index, data));
        if (isCallValid)
        {
            context->getInteger64i_v(target, index, data);
        }
        ANGLE_CAPTURE(GetInteger64i_v, isCallValid, context, target, index, data);
    }
}

void GL_APIENTRY GetInteger64v(GLenum pname, GLint64 *data)
{
    EVENT("(GLenum pname = 0x%X, GLint64 *data = 0x%016" PRIxPTR ")", pname, (uintptr_t)data);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateGetInteger64v(context, pname, data));
        if (isCallValid)
        {
            context->getInteger64v(pname, data);
        }
        ANGLE_CAPTURE(GetInteger64v, isCallValid, context, pname, data);
    }
}

void GL_APIENTRY GetMultisamplefv(GLenum pname, GLuint index, GLfloat *val)
{
    EVENT("(GLenum pname = 0x%X, GLuint index = %u, GLfloat *val = 0x%016" PRIxPTR ")", pname,
          index, (uintptr_t)val);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateGetMultisamplefv(context, pname, index, val));
        if (isCallValid)
        {
            context->getMultisamplefv(pname, index, val);
        }
        ANGLE_CAPTURE(GetMultisamplefv, isCallValid, context, pname, index, val);
    }
}

void GL_APIENTRY
GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)
{
    EVENT("(GLsync sync = 0x%016" PRIxPTR
          ", GLenum pname = 0x%X, GLsizei bufSize = %d, GLsizei *length = 0x%016" PRIxPTR
          ", GLint *values = 0x%016" PRIxPTR ")",
          (uintptr_t)sync, pname, bufSize, (uintptr_t)length, (uintptr_t)values);

    Context *context = GetGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() ||
                            ValidateGetSynciv(context, sync, pname, bufSize, length, values));
        if (isCallValid)
        {
            context->getSynciv(sync, pname, bufSize, length, values);
        }
        ANGLE_CAPTURE(GetSynciv, isCallValid, context, sync, pname, bufSize, length, values);
    }
}

GLboolean GL_APIENTRY IsSync(GLsync sync)
{
    EVENT("(GLsync sync = 0x%016" PRIxPTR ")", (uintptr_t)sync);

    Context *context = GetValidGlobalContext();
    GLboolean returnValue;
    if (context)
    {
        bool isCallValid = (context->skipValidation() || ValidateIsSync(context, sync));
        if (isCallValid)
        {
            returnValue = context->isSync(sync);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::IsSync, GLboolean>();
        }
        ANGLE_CAPTURE(IsSync, isCallValid, context, sync);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::IsSync, GLboolean>();
    }
    return returnValue;
}

void GL_APIENTRY MultiDrawElementsBaseVertex(GLenum mode,
                                             const GLsizei *count,
                                             GLenum type,
                                             const void *const *indices,
                                             GLsizei drawcount,
                                             const GLint *basevertex)
{
    EVENT("(GLenum mode = 0x%X, const GLsizei *count = 0x%016" PRIxPTR
          ", GLenum type = 0x%X, const void *const*indices = 0x%016" PRIxPTR
          ", GLsizei drawcount = %d, const GLint *basevertex = 0x%016" PRIxPTR ")",
          mode, (uintptr_t)count, type, (uintptr_t)indices, drawcount, (uintptr_t)basevertex);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() ||
                            ValidateMultiDrawElementsBaseVertex(context, mode, count, type, indices,
                                                                drawcount, basevertex));
        if (isCallValid)
        {
            context->multiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
        }
        ANGLE_CAPTURE(MultiDrawElementsBaseVertex, isCallValid, context, mode, count, type, indices,
                      drawcount, basevertex);
    }
}

void GL_APIENTRY ProvokingVertex(GLenum mode)
{
    EVENT("(GLenum mode = 0x%X)", mode);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        ProvokingVertexConvention modePacked = FromGLenum<ProvokingVertexConvention>(mode);
        bool isCallValid =
            (context->skipValidation() || ValidateProvokingVertex(context, modePacked));
        if (isCallValid)
        {
            context->provokingVertex(modePacked);
        }
        ANGLE_CAPTURE(ProvokingVertex, isCallValid, context, modePacked);
    }
}

void GL_APIENTRY SampleMaski(GLuint maskNumber, GLbitfield mask)
{
    EVENT("(GLuint maskNumber = %u, GLbitfield mask = 0x%X)", maskNumber, mask);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateSampleMaski(context, maskNumber, mask));
        if (isCallValid)
        {
            context->sampleMaski(maskNumber, mask);
        }
        ANGLE_CAPTURE(SampleMaski, isCallValid, context, maskNumber, mask);
    }
}

void GL_APIENTRY TexImage2DMultisample(GLenum target,
                                       GLsizei samples,
                                       GLenum internalformat,
                                       GLsizei width,
                                       GLsizei height,
                                       GLboolean fixedsamplelocations)
{
    EVENT(
        "(GLenum target = 0x%X, GLsizei samples = %d, GLenum internalformat = 0x%X, GLsizei width "
        "= %d, GLsizei height = %d, GLboolean fixedsamplelocations = %u)",
        target, samples, internalformat, width, height, fixedsamplelocations);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid = (context->skipValidation() ||
                            ValidateTexImage2DMultisample(context, target, samples, internalformat,
                                                          width, height, fixedsamplelocations));
        if (isCallValid)
        {
            context->texImage2DMultisample(target, samples, internalformat, width, height,
                                           fixedsamplelocations);
        }
        ANGLE_CAPTURE(TexImage2DMultisample, isCallValid, context, target, samples, internalformat,
                      width, height, fixedsamplelocations);
    }
}

void GL_APIENTRY TexImage3DMultisample(GLenum target,
                                       GLsizei samples,
                                       GLenum internalformat,
                                       GLsizei width,
                                       GLsizei height,
                                       GLsizei depth,
                                       GLboolean fixedsamplelocations)
{
    EVENT(
        "(GLenum target = 0x%X, GLsizei samples = %d, GLenum internalformat = 0x%X, GLsizei width "
        "= %d, GLsizei height = %d, GLsizei depth = %d, GLboolean fixedsamplelocations = %u)",
        target, samples, internalformat, width, height, depth, fixedsamplelocations);

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() ||
             ValidateTexImage3DMultisample(context, target, samples, internalformat, width, height,
                                           depth, fixedsamplelocations));
        if (isCallValid)
        {
            context->texImage3DMultisample(target, samples, internalformat, width, height, depth,
                                           fixedsamplelocations);
        }
        ANGLE_CAPTURE(TexImage3DMultisample, isCallValid, context, target, samples, internalformat,
                      width, height, depth, fixedsamplelocations);
    }
}

void GL_APIENTRY WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    EVENT("(GLsync sync = 0x%016" PRIxPTR ", GLbitfield flags = 0x%X, GLuint64 timeout = %llu)",
          (uintptr_t)sync, flags, static_cast<unsigned long long>(timeout));

    Context *context = GetValidGlobalContext();
    if (context)
    {
        bool isCallValid =
            (context->skipValidation() || ValidateWaitSync(context, sync, flags, timeout));
        if (isCallValid)
        {
            context->waitSync(sync, flags, timeout);
        }
        ANGLE_CAPTURE(WaitSync, isCallValid, context, sync, flags, timeout);
    }
}
}  // namespace gl
