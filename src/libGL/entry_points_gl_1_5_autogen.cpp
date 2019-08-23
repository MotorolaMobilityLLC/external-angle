// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_1_5_autogen.cpp:
//   Defines the GL 1.5 entry points.

#include "libGL/entry_points_gl_1_5_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/Context.inl.h"
#include "libANGLE/entry_points_utils.h"
#include "libANGLE/gl_enum_utils_autogen.h"
#include "libANGLE/validationEGL.h"
#include "libANGLE/validationES.h"
#include "libANGLE/validationES1.h"
#include "libANGLE/validationES2.h"
#include "libANGLE/validationES3.h"
#include "libANGLE/validationES31.h"
#include "libANGLE/validationESEXT.h"
#include "libANGLE/validationGL15_autogen.h"
#include "libGLESv2/global_state.h"

namespace gl
{
void GL_APIENTRY BeginQuery(GLenum target, GLuint id)
{
    Context *context = GetValidGlobalContext();
    EVENT("glBeginQuery", "context = %d, GLenum target = %s, GLuint id = %u", CID(context),
          GLenumToString(GLenumGroup::QueryTarget, target), id);

    if (context)
    {
        QueryType targetPacked                        = FromGL<QueryType>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateBeginQuery(context, targetPacked, id));
        if (isCallValid)
        {
            context->beginQuery(targetPacked, id);
        }
        ANGLE_CAPTURE(BeginQuery, isCallValid, context, targetPacked, id);
    }
}

void GL_APIENTRY BindBuffer(GLenum target, GLuint buffer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glBindBuffer", "context = %d, GLenum target = %s, GLuint buffer = %u", CID(context),
          GLenumToString(GLenumGroup::BufferTargetARB, target), buffer);

    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        BufferID bufferPacked                         = FromGL<BufferID>(buffer);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateBindBuffer(context, targetPacked, bufferPacked));
        if (isCallValid)
        {
            context->bindBuffer(targetPacked, bufferPacked);
        }
        ANGLE_CAPTURE(BindBuffer, isCallValid, context, targetPacked, bufferPacked);
    }
}

void GL_APIENTRY BufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
    Context *context = GetValidGlobalContext();
    EVENT("glBufferData",
          "context = %d, GLenum target = %s, GLsizeiptr size = %llu, const void *data = "
          "0x%016" PRIxPTR ", GLenum usage = %s",
          CID(context), GLenumToString(GLenumGroup::BufferTargetARB, target),
          static_cast<unsigned long long>(size), (uintptr_t)data,
          GLenumToString(GLenumGroup::BufferUsageARB, usage));

    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        BufferUsage usagePacked                       = FromGL<BufferUsage>(usage);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                              = (context->skipValidation() ||
                            ValidateBufferData(context, targetPacked, size, data, usagePacked));
        if (isCallValid)
        {
            context->bufferData(targetPacked, size, data, usagePacked);
        }
        ANGLE_CAPTURE(BufferData, isCallValid, context, targetPacked, size, data, usagePacked);
    }
}

void GL_APIENTRY BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{
    Context *context = GetValidGlobalContext();
    EVENT("glBufferSubData",
          "context = %d, GLenum target = %s, GLintptr offset = %llu, GLsizeiptr size = %llu, const "
          "void *data = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::BufferTargetARB, target),
          static_cast<unsigned long long>(offset), static_cast<unsigned long long>(size),
          (uintptr_t)data);

    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                              = (context->skipValidation() ||
                            ValidateBufferSubData(context, targetPacked, offset, size, data));
        if (isCallValid)
        {
            context->bufferSubData(targetPacked, offset, size, data);
        }
        ANGLE_CAPTURE(BufferSubData, isCallValid, context, targetPacked, offset, size, data);
    }
}

void GL_APIENTRY DeleteBuffers(GLsizei n, const GLuint *buffers)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDeleteBuffers",
          "context = %d, GLsizei n = %d, const GLuint *buffers = 0x%016" PRIxPTR "", CID(context),
          n, (uintptr_t)buffers);

    if (context)
    {
        const BufferID *buffersPacked                 = FromGL<const BufferID *>(buffers);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateDeleteBuffers(context, n, buffersPacked));
        if (isCallValid)
        {
            context->deleteBuffers(n, buffersPacked);
        }
        ANGLE_CAPTURE(DeleteBuffers, isCallValid, context, n, buffersPacked);
    }
}

void GL_APIENTRY DeleteQueries(GLsizei n, const GLuint *ids)
{
    Context *context = GetValidGlobalContext();
    EVENT("glDeleteQueries", "context = %d, GLsizei n = %d, const GLuint *ids = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)ids);

    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateDeleteQueries(context, n, ids));
        if (isCallValid)
        {
            context->deleteQueries(n, ids);
        }
        ANGLE_CAPTURE(DeleteQueries, isCallValid, context, n, ids);
    }
}

void GL_APIENTRY EndQuery(GLenum target)
{
    Context *context = GetValidGlobalContext();
    EVENT("glEndQuery", "context = %d, GLenum target = %s", CID(context),
          GLenumToString(GLenumGroup::QueryTarget, target));

    if (context)
    {
        QueryType targetPacked                        = FromGL<QueryType>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateEndQuery(context, targetPacked));
        if (isCallValid)
        {
            context->endQuery(targetPacked);
        }
        ANGLE_CAPTURE(EndQuery, isCallValid, context, targetPacked);
    }
}

void GL_APIENTRY GenBuffers(GLsizei n, GLuint *buffers)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGenBuffers", "context = %d, GLsizei n = %d, GLuint *buffers = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)buffers);

    if (context)
    {
        BufferID *buffersPacked                       = FromGL<BufferID *>(buffers);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGenBuffers(context, n, buffersPacked));
        if (isCallValid)
        {
            context->genBuffers(n, buffersPacked);
        }
        ANGLE_CAPTURE(GenBuffers, isCallValid, context, n, buffersPacked);
    }
}

void GL_APIENTRY GenQueries(GLsizei n, GLuint *ids)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGenQueries", "context = %d, GLsizei n = %d, GLuint *ids = 0x%016" PRIxPTR "",
          CID(context), n, (uintptr_t)ids);

    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateGenQueries(context, n, ids));
        if (isCallValid)
        {
            context->genQueries(n, ids);
        }
        ANGLE_CAPTURE(GenQueries, isCallValid, context, n, ids);
    }
}

void GL_APIENTRY GetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetBufferParameteriv",
          "context = %d, GLenum target = %s, GLenum pname = %s, GLint *params = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::BufferTargetARB, target),
          GLenumToString(GLenumGroup::DefaultGroup, pname), (uintptr_t)params);

    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                              = (context->skipValidation() ||
                            ValidateGetBufferParameteriv(context, targetPacked, pname, params));
        if (isCallValid)
        {
            context->getBufferParameteriv(targetPacked, pname, params);
        }
        ANGLE_CAPTURE(GetBufferParameteriv, isCallValid, context, targetPacked, pname, params);
    }
}

void GL_APIENTRY GetBufferPointerv(GLenum target, GLenum pname, void **params)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetBufferPointerv",
          "context = %d, GLenum target = %s, GLenum pname = %s, void **params = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::BufferTargetARB, target),
          GLenumToString(GLenumGroup::DefaultGroup, pname), (uintptr_t)params);

    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                              = (context->skipValidation() ||
                            ValidateGetBufferPointerv(context, targetPacked, pname, params));
        if (isCallValid)
        {
            context->getBufferPointerv(targetPacked, pname, params);
        }
        ANGLE_CAPTURE(GetBufferPointerv, isCallValid, context, targetPacked, pname, params);
    }
}

void GL_APIENTRY GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetBufferSubData",
          "context = %d, GLenum target = %s, GLintptr offset = %llu, GLsizeiptr size = %llu, void "
          "*data = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::BufferTargetARB, target),
          static_cast<unsigned long long>(offset), static_cast<unsigned long long>(size),
          (uintptr_t)data);

    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid                              = (context->skipValidation() ||
                            ValidateGetBufferSubData(context, target, offset, size, data));
        if (isCallValid)
        {
            context->getBufferSubData(target, offset, size, data);
        }
        ANGLE_CAPTURE(GetBufferSubData, isCallValid, context, target, offset, size, data);
    }
}

void GL_APIENTRY GetQueryObjectiv(GLuint id, GLenum pname, GLint *params)
{
    Context *context = GetGlobalContext();
    EVENT("glGetQueryObjectiv",
          "context = %d, GLuint id = %u, GLenum pname = %s, GLint *params = 0x%016" PRIxPTR "",
          CID(context), id, GLenumToString(GLenumGroup::QueryObjectParameterName, pname),
          (uintptr_t)params);

    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGetQueryObjectiv(context, id, pname, params));
        if (isCallValid)
        {
            context->getQueryObjectiv(id, pname, params);
        }
        ANGLE_CAPTURE(GetQueryObjectiv, isCallValid, context, id, pname, params);
    }
}

void GL_APIENTRY GetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetQueryObjectuiv",
          "context = %d, GLuint id = %u, GLenum pname = %s, GLuint *params = 0x%016" PRIxPTR "",
          CID(context), id, GLenumToString(GLenumGroup::QueryObjectParameterName, pname),
          (uintptr_t)params);

    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGetQueryObjectuiv(context, id, pname, params));
        if (isCallValid)
        {
            context->getQueryObjectuiv(id, pname, params);
        }
        ANGLE_CAPTURE(GetQueryObjectuiv, isCallValid, context, id, pname, params);
    }
}

void GL_APIENTRY GetQueryiv(GLenum target, GLenum pname, GLint *params)
{
    Context *context = GetValidGlobalContext();
    EVENT("glGetQueryiv",
          "context = %d, GLenum target = %s, GLenum pname = %s, GLint *params = 0x%016" PRIxPTR "",
          CID(context), GLenumToString(GLenumGroup::QueryTarget, target),
          GLenumToString(GLenumGroup::QueryParameterName, pname), (uintptr_t)params);

    if (context)
    {
        QueryType targetPacked                        = FromGL<QueryType>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateGetQueryiv(context, targetPacked, pname, params));
        if (isCallValid)
        {
            context->getQueryiv(targetPacked, pname, params);
        }
        ANGLE_CAPTURE(GetQueryiv, isCallValid, context, targetPacked, pname, params);
    }
}

GLboolean GL_APIENTRY IsBuffer(GLuint buffer)
{
    Context *context = GetValidGlobalContext();
    EVENT("glIsBuffer", "context = %d, GLuint buffer = %u", CID(context), buffer);

    GLboolean returnValue;
    if (context)
    {
        BufferID bufferPacked                         = FromGL<BufferID>(buffer);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateIsBuffer(context, bufferPacked));
        if (isCallValid)
        {
            returnValue = context->isBuffer(bufferPacked);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::IsBuffer, GLboolean>();
        }
        ANGLE_CAPTURE(IsBuffer, isCallValid, context, bufferPacked, returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::IsBuffer, GLboolean>();
    }
    return returnValue;
}

GLboolean GL_APIENTRY IsQuery(GLuint id)
{
    Context *context = GetValidGlobalContext();
    EVENT("glIsQuery", "context = %d, GLuint id = %u", CID(context), id);

    GLboolean returnValue;
    if (context)
    {
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid = (context->skipValidation() || ValidateIsQuery(context, id));
        if (isCallValid)
        {
            returnValue = context->isQuery(id);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::IsQuery, GLboolean>();
        }
        ANGLE_CAPTURE(IsQuery, isCallValid, context, id, returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::IsQuery, GLboolean>();
    }
    return returnValue;
}

void *GL_APIENTRY MapBuffer(GLenum target, GLenum access)
{
    Context *context = GetValidGlobalContext();
    EVENT("glMapBuffer", "context = %d, GLenum target = %s, GLenum access = %s", CID(context),
          GLenumToString(GLenumGroup::BufferTargetARB, target),
          GLenumToString(GLenumGroup::BufferAccessARB, access));

    void *returnValue;
    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateMapBuffer(context, targetPacked, access));
        if (isCallValid)
        {
            returnValue = context->mapBuffer(targetPacked, access);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::MapBuffer, void *>();
        }
        ANGLE_CAPTURE(MapBuffer, isCallValid, context, targetPacked, access, returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::MapBuffer, void *>();
    }
    return returnValue;
}

GLboolean GL_APIENTRY UnmapBuffer(GLenum target)
{
    Context *context = GetValidGlobalContext();
    EVENT("glUnmapBuffer", "context = %d, GLenum target = %s", CID(context),
          GLenumToString(GLenumGroup::BufferTargetARB, target));

    GLboolean returnValue;
    if (context)
    {
        BufferBinding targetPacked                    = FromGL<BufferBinding>(target);
        std::unique_lock<std::mutex> shareContextLock = GetShareGroupLock(context);
        bool isCallValid =
            (context->skipValidation() || ValidateUnmapBuffer(context, targetPacked));
        if (isCallValid)
        {
            returnValue = context->unmapBuffer(targetPacked);
        }
        else
        {
            returnValue = GetDefaultReturnValue<EntryPoint::UnmapBuffer, GLboolean>();
        }
        ANGLE_CAPTURE(UnmapBuffer, isCallValid, context, targetPacked, returnValue);
    }
    else
    {
        returnValue = GetDefaultReturnValue<EntryPoint::UnmapBuffer, GLboolean>();
    }
    return returnValue;
}
}  // namespace gl
