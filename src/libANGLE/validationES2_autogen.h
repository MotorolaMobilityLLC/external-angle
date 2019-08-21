// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml and gl_angle_ext.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationES2_autogen.h:
//   Validation functions for the OpenGL ES 2.0 entry points.

#ifndef LIBANGLE_VALIDATION_ES2_AUTOGEN_H_
#define LIBANGLE_VALIDATION_ES2_AUTOGEN_H_

#include "common/PackedEnums.h"

namespace gl
{
class Context;

bool ValidateActiveTexture(Context *context, GLenum texture);
bool ValidateAttachShader(Context *context,
                          ShaderProgramID programPacked,
                          ShaderProgramID shaderPacked);
bool ValidateBindAttribLocation(Context *context,
                                ShaderProgramID programPacked,
                                GLuint index,
                                const GLchar *name);
bool ValidateBindBuffer(Context *context, BufferBinding targetPacked, BufferID bufferPacked);
bool ValidateBindFramebuffer(Context *context, GLenum target, GLuint framebuffer);
bool ValidateBindRenderbuffer(Context *context, GLenum target, RenderbufferID renderbufferPacked);
bool ValidateBindTexture(Context *context, TextureType targetPacked, TextureID texturePacked);
bool ValidateBlendColor(Context *context, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
bool ValidateBlendEquation(Context *context, GLenum mode);
bool ValidateBlendEquationSeparate(Context *context, GLenum modeRGB, GLenum modeAlpha);
bool ValidateBlendFunc(Context *context, GLenum sfactor, GLenum dfactor);
bool ValidateBlendFuncSeparate(Context *context,
                               GLenum sfactorRGB,
                               GLenum dfactorRGB,
                               GLenum sfactorAlpha,
                               GLenum dfactorAlpha);
bool ValidateBufferData(Context *context,
                        BufferBinding targetPacked,
                        GLsizeiptr size,
                        const void *data,
                        BufferUsage usagePacked);
bool ValidateBufferSubData(Context *context,
                           BufferBinding targetPacked,
                           GLintptr offset,
                           GLsizeiptr size,
                           const void *data);
bool ValidateCheckFramebufferStatus(Context *context, GLenum target);
bool ValidateClear(Context *context, GLbitfield mask);
bool ValidateClearColor(Context *context, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
bool ValidateClearDepthf(Context *context, GLfloat d);
bool ValidateClearStencil(Context *context, GLint s);
bool ValidateColorMask(Context *context,
                       GLboolean red,
                       GLboolean green,
                       GLboolean blue,
                       GLboolean alpha);
bool ValidateCompileShader(Context *context, ShaderProgramID shaderPacked);
bool ValidateCompressedTexImage2D(Context *context,
                                  TextureTarget targetPacked,
                                  GLint level,
                                  GLenum internalformat,
                                  GLsizei width,
                                  GLsizei height,
                                  GLint border,
                                  GLsizei imageSize,
                                  const void *data);
bool ValidateCompressedTexSubImage2D(Context *context,
                                     TextureTarget targetPacked,
                                     GLint level,
                                     GLint xoffset,
                                     GLint yoffset,
                                     GLsizei width,
                                     GLsizei height,
                                     GLenum format,
                                     GLsizei imageSize,
                                     const void *data);
bool ValidateCopyTexImage2D(Context *context,
                            TextureTarget targetPacked,
                            GLint level,
                            GLenum internalformat,
                            GLint x,
                            GLint y,
                            GLsizei width,
                            GLsizei height,
                            GLint border);
bool ValidateCopyTexSubImage2D(Context *context,
                               TextureTarget targetPacked,
                               GLint level,
                               GLint xoffset,
                               GLint yoffset,
                               GLint x,
                               GLint y,
                               GLsizei width,
                               GLsizei height);
bool ValidateCreateProgram(Context *context);
bool ValidateCreateShader(Context *context, ShaderType typePacked);
bool ValidateCullFace(Context *context, CullFaceMode modePacked);
bool ValidateDeleteBuffers(Context *context, GLsizei n, const BufferID *buffersPacked);
bool ValidateDeleteFramebuffers(Context *context, GLsizei n, const GLuint *framebuffers);
bool ValidateDeleteProgram(Context *context, ShaderProgramID programPacked);
bool ValidateDeleteRenderbuffers(Context *context,
                                 GLsizei n,
                                 const RenderbufferID *renderbuffersPacked);
bool ValidateDeleteShader(Context *context, ShaderProgramID shaderPacked);
bool ValidateDeleteTextures(Context *context, GLsizei n, const TextureID *texturesPacked);
bool ValidateDepthFunc(Context *context, GLenum func);
bool ValidateDepthMask(Context *context, GLboolean flag);
bool ValidateDepthRangef(Context *context, GLfloat n, GLfloat f);
bool ValidateDetachShader(Context *context,
                          ShaderProgramID programPacked,
                          ShaderProgramID shaderPacked);
bool ValidateDisable(Context *context, GLenum cap);
bool ValidateDisableVertexAttribArray(Context *context, GLuint index);
bool ValidateDrawArrays(Context *context, PrimitiveMode modePacked, GLint first, GLsizei count);
bool ValidateDrawElements(Context *context,
                          PrimitiveMode modePacked,
                          GLsizei count,
                          DrawElementsType typePacked,
                          const void *indices);
bool ValidateEnable(Context *context, GLenum cap);
bool ValidateEnableVertexAttribArray(Context *context, GLuint index);
bool ValidateFinish(Context *context);
bool ValidateFlush(Context *context);
bool ValidateFramebufferRenderbuffer(Context *context,
                                     GLenum target,
                                     GLenum attachment,
                                     GLenum renderbuffertarget,
                                     RenderbufferID renderbufferPacked);
bool ValidateFramebufferTexture2D(Context *context,
                                  GLenum target,
                                  GLenum attachment,
                                  TextureTarget textargetPacked,
                                  TextureID texturePacked,
                                  GLint level);
bool ValidateFrontFace(Context *context, GLenum mode);
bool ValidateGenBuffers(Context *context, GLsizei n, BufferID *buffersPacked);
bool ValidateGenFramebuffers(Context *context, GLsizei n, GLuint *framebuffers);
bool ValidateGenRenderbuffers(Context *context, GLsizei n, RenderbufferID *renderbuffersPacked);
bool ValidateGenTextures(Context *context, GLsizei n, TextureID *texturesPacked);
bool ValidateGenerateMipmap(Context *context, TextureType targetPacked);
bool ValidateGetActiveAttrib(Context *context,
                             ShaderProgramID programPacked,
                             GLuint index,
                             GLsizei bufSize,
                             GLsizei *length,
                             GLint *size,
                             GLenum *type,
                             GLchar *name);
bool ValidateGetActiveUniform(Context *context,
                              ShaderProgramID programPacked,
                              GLuint index,
                              GLsizei bufSize,
                              GLsizei *length,
                              GLint *size,
                              GLenum *type,
                              GLchar *name);
bool ValidateGetAttachedShaders(Context *context,
                                ShaderProgramID programPacked,
                                GLsizei maxCount,
                                GLsizei *count,
                                ShaderProgramID *shadersPacked);
bool ValidateGetAttribLocation(Context *context, ShaderProgramID programPacked, const GLchar *name);
bool ValidateGetBooleanv(Context *context, GLenum pname, GLboolean *data);
bool ValidateGetBufferParameteriv(Context *context,
                                  BufferBinding targetPacked,
                                  GLenum pname,
                                  GLint *params);
bool ValidateGetError(Context *context);
bool ValidateGetFloatv(Context *context, GLenum pname, GLfloat *data);
bool ValidateGetFramebufferAttachmentParameteriv(Context *context,
                                                 GLenum target,
                                                 GLenum attachment,
                                                 GLenum pname,
                                                 GLint *params);
bool ValidateGetIntegerv(Context *context, GLenum pname, GLint *data);
bool ValidateGetProgramInfoLog(Context *context,
                               ShaderProgramID programPacked,
                               GLsizei bufSize,
                               GLsizei *length,
                               GLchar *infoLog);
bool ValidateGetProgramiv(Context *context,
                          ShaderProgramID programPacked,
                          GLenum pname,
                          GLint *params);
bool ValidateGetRenderbufferParameteriv(Context *context,
                                        GLenum target,
                                        GLenum pname,
                                        GLint *params);
bool ValidateGetShaderInfoLog(Context *context,
                              ShaderProgramID shaderPacked,
                              GLsizei bufSize,
                              GLsizei *length,
                              GLchar *infoLog);
bool ValidateGetShaderPrecisionFormat(Context *context,
                                      GLenum shadertype,
                                      GLenum precisiontype,
                                      GLint *range,
                                      GLint *precision);
bool ValidateGetShaderSource(Context *context,
                             ShaderProgramID shaderPacked,
                             GLsizei bufSize,
                             GLsizei *length,
                             GLchar *source);
bool ValidateGetShaderiv(Context *context,
                         ShaderProgramID shaderPacked,
                         GLenum pname,
                         GLint *params);
bool ValidateGetString(Context *context, GLenum name);
bool ValidateGetTexParameterfv(Context *context,
                               TextureType targetPacked,
                               GLenum pname,
                               GLfloat *params);
bool ValidateGetTexParameteriv(Context *context,
                               TextureType targetPacked,
                               GLenum pname,
                               GLint *params);
bool ValidateGetUniformLocation(Context *context,
                                ShaderProgramID programPacked,
                                const GLchar *name);
bool ValidateGetUniformfv(Context *context,
                          ShaderProgramID programPacked,
                          GLint location,
                          GLfloat *params);
bool ValidateGetUniformiv(Context *context,
                          ShaderProgramID programPacked,
                          GLint location,
                          GLint *params);
bool ValidateGetVertexAttribPointerv(Context *context, GLuint index, GLenum pname, void **pointer);
bool ValidateGetVertexAttribfv(Context *context, GLuint index, GLenum pname, GLfloat *params);
bool ValidateGetVertexAttribiv(Context *context, GLuint index, GLenum pname, GLint *params);
bool ValidateHint(Context *context, GLenum target, GLenum mode);
bool ValidateIsBuffer(Context *context, BufferID bufferPacked);
bool ValidateIsEnabled(Context *context, GLenum cap);
bool ValidateIsFramebuffer(Context *context, GLuint framebuffer);
bool ValidateIsProgram(Context *context, ShaderProgramID programPacked);
bool ValidateIsRenderbuffer(Context *context, RenderbufferID renderbufferPacked);
bool ValidateIsShader(Context *context, ShaderProgramID shaderPacked);
bool ValidateIsTexture(Context *context, TextureID texturePacked);
bool ValidateLineWidth(Context *context, GLfloat width);
bool ValidateLinkProgram(Context *context, ShaderProgramID programPacked);
bool ValidatePixelStorei(Context *context, GLenum pname, GLint param);
bool ValidatePolygonOffset(Context *context, GLfloat factor, GLfloat units);
bool ValidateReadPixels(Context *context,
                        GLint x,
                        GLint y,
                        GLsizei width,
                        GLsizei height,
                        GLenum format,
                        GLenum type,
                        void *pixels);
bool ValidateReleaseShaderCompiler(Context *context);
bool ValidateRenderbufferStorage(Context *context,
                                 GLenum target,
                                 GLenum internalformat,
                                 GLsizei width,
                                 GLsizei height);
bool ValidateSampleCoverage(Context *context, GLfloat value, GLboolean invert);
bool ValidateScissor(Context *context, GLint x, GLint y, GLsizei width, GLsizei height);
bool ValidateShaderBinary(Context *context,
                          GLsizei count,
                          const ShaderProgramID *shadersPacked,
                          GLenum binaryformat,
                          const void *binary,
                          GLsizei length);
bool ValidateShaderSource(Context *context,
                          ShaderProgramID shaderPacked,
                          GLsizei count,
                          const GLchar *const *string,
                          const GLint *length);
bool ValidateStencilFunc(Context *context, GLenum func, GLint ref, GLuint mask);
bool ValidateStencilFuncSeparate(Context *context,
                                 GLenum face,
                                 GLenum func,
                                 GLint ref,
                                 GLuint mask);
bool ValidateStencilMask(Context *context, GLuint mask);
bool ValidateStencilMaskSeparate(Context *context, GLenum face, GLuint mask);
bool ValidateStencilOp(Context *context, GLenum fail, GLenum zfail, GLenum zpass);
bool ValidateStencilOpSeparate(Context *context,
                               GLenum face,
                               GLenum sfail,
                               GLenum dpfail,
                               GLenum dppass);
bool ValidateTexImage2D(Context *context,
                        TextureTarget targetPacked,
                        GLint level,
                        GLint internalformat,
                        GLsizei width,
                        GLsizei height,
                        GLint border,
                        GLenum format,
                        GLenum type,
                        const void *pixels);
bool ValidateTexParameterf(Context *context, TextureType targetPacked, GLenum pname, GLfloat param);
bool ValidateTexParameterfv(Context *context,
                            TextureType targetPacked,
                            GLenum pname,
                            const GLfloat *params);
bool ValidateTexParameteri(Context *context, TextureType targetPacked, GLenum pname, GLint param);
bool ValidateTexParameteriv(Context *context,
                            TextureType targetPacked,
                            GLenum pname,
                            const GLint *params);
bool ValidateTexSubImage2D(Context *context,
                           TextureTarget targetPacked,
                           GLint level,
                           GLint xoffset,
                           GLint yoffset,
                           GLsizei width,
                           GLsizei height,
                           GLenum format,
                           GLenum type,
                           const void *pixels);
bool ValidateUniform1f(Context *context, GLint location, GLfloat v0);
bool ValidateUniform1fv(Context *context, GLint location, GLsizei count, const GLfloat *value);
bool ValidateUniform1i(Context *context, GLint location, GLint v0);
bool ValidateUniform1iv(Context *context, GLint location, GLsizei count, const GLint *value);
bool ValidateUniform2f(Context *context, GLint location, GLfloat v0, GLfloat v1);
bool ValidateUniform2fv(Context *context, GLint location, GLsizei count, const GLfloat *value);
bool ValidateUniform2i(Context *context, GLint location, GLint v0, GLint v1);
bool ValidateUniform2iv(Context *context, GLint location, GLsizei count, const GLint *value);
bool ValidateUniform3f(Context *context, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
bool ValidateUniform3fv(Context *context, GLint location, GLsizei count, const GLfloat *value);
bool ValidateUniform3i(Context *context, GLint location, GLint v0, GLint v1, GLint v2);
bool ValidateUniform3iv(Context *context, GLint location, GLsizei count, const GLint *value);
bool ValidateUniform4f(Context *context,
                       GLint location,
                       GLfloat v0,
                       GLfloat v1,
                       GLfloat v2,
                       GLfloat v3);
bool ValidateUniform4fv(Context *context, GLint location, GLsizei count, const GLfloat *value);
bool ValidateUniform4i(Context *context, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
bool ValidateUniform4iv(Context *context, GLint location, GLsizei count, const GLint *value);
bool ValidateUniformMatrix2fv(Context *context,
                              GLint location,
                              GLsizei count,
                              GLboolean transpose,
                              const GLfloat *value);
bool ValidateUniformMatrix3fv(Context *context,
                              GLint location,
                              GLsizei count,
                              GLboolean transpose,
                              const GLfloat *value);
bool ValidateUniformMatrix4fv(Context *context,
                              GLint location,
                              GLsizei count,
                              GLboolean transpose,
                              const GLfloat *value);
bool ValidateUseProgram(Context *context, ShaderProgramID programPacked);
bool ValidateValidateProgram(Context *context, ShaderProgramID programPacked);
bool ValidateVertexAttrib1f(Context *context, GLuint index, GLfloat x);
bool ValidateVertexAttrib1fv(Context *context, GLuint index, const GLfloat *v);
bool ValidateVertexAttrib2f(Context *context, GLuint index, GLfloat x, GLfloat y);
bool ValidateVertexAttrib2fv(Context *context, GLuint index, const GLfloat *v);
bool ValidateVertexAttrib3f(Context *context, GLuint index, GLfloat x, GLfloat y, GLfloat z);
bool ValidateVertexAttrib3fv(Context *context, GLuint index, const GLfloat *v);
bool ValidateVertexAttrib4f(Context *context,
                            GLuint index,
                            GLfloat x,
                            GLfloat y,
                            GLfloat z,
                            GLfloat w);
bool ValidateVertexAttrib4fv(Context *context, GLuint index, const GLfloat *v);
bool ValidateVertexAttribPointer(Context *context,
                                 GLuint index,
                                 GLint size,
                                 VertexAttribType typePacked,
                                 GLboolean normalized,
                                 GLsizei stride,
                                 const void *pointer);
bool ValidateViewport(Context *context, GLint x, GLint y, GLsizei width, GLsizei height);
}  // namespace gl

#endif  // LIBANGLE_VALIDATION_ES2_AUTOGEN_H_
