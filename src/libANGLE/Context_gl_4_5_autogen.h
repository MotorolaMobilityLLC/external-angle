// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Context_gl_4_5_autogen.h: Creates a macro for interfaces in Context.

#ifndef ANGLE_CONTEXT_GL_4_5_AUTOGEN_H_
#define ANGLE_CONTEXT_GL_4_5_AUTOGEN_H_

#define ANGLE_GL_4_5_CONTEXT_API                                                                   \
    void bindTextureUnit(GLuint unit, GLuint texture);                                             \
    void blitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0,         \
                              GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,     \
                              GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);           \
    GLenum checkNamedFramebufferStatus(GLuint framebuffer, GLenum target);                         \
    void clearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type,    \
                              const void *data);                                                   \
    void clearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset,            \
                                 GLsizeiptr size, GLenum format, GLenum type, const void *data);   \
    void clearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer,              \
                                 GLfloat depth, GLint stencil);                                    \
    void clearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer,              \
                                 const GLfloat *value);                                            \
    void clearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer,              \
                                 const GLint *value);                                              \
    void clearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer,             \
                                  const GLuint *value);                                            \
    void clipControl(GLenum origin, GLenum depth);                                                 \
    void compressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width,    \
                                     GLenum format, GLsizei imageSize, const void *data);          \
    void compressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,    \
                                     GLsizei width, GLsizei height, GLenum format,                 \
                                     GLsizei imageSize, const void *data);                         \
    void compressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,    \
                                     GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,  \
                                     GLenum format, GLsizei imageSize, const void *data);          \
    void copyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset,        \
                                GLintptr writeOffset, GLsizeiptr size);                            \
    void copyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y,       \
                               GLsizei width);                                                     \
    void copyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, \
                               GLint y, GLsizei width, GLsizei height);                            \
    void copyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,          \
                               GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);    \
    void createBuffers(GLsizei n, GLuint *buffers);                                                \
    void createFramebuffers(GLsizei n, GLuint *framebuffers);                                      \
    void createProgramPipelines(GLsizei n, GLuint *pipelines);                                     \
    void createQueries(GLenum target, GLsizei n, GLuint *ids);                                     \
    void createRenderbuffers(GLsizei n, GLuint *renderbuffers);                                    \
    void createSamplers(GLsizei n, GLuint *samplers);                                              \
    void createTextures(GLenum target, GLsizei n, GLuint *textures);                               \
    void createTransformFeedbacks(GLsizei n, GLuint *ids);                                         \
    void createVertexArrays(GLsizei n, GLuint *arrays);                                            \
    void disableVertexArrayAttrib(GLuint vaobj, GLuint index);                                     \
    void enableVertexArrayAttrib(GLuint vaobj, GLuint index);                                      \
    void flushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length);           \
    void generateTextureMipmap(GLuint texture);                                                    \
    void getCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void *pixels);    \
    void getCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset,   \
                                      GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, \
                                      GLsizei bufSize, void *pixels);                              \
    void getNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 *params);                \
    void getNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint *params);                    \
    void getNamedBufferPointerv(GLuint buffer, GLenum pname, void **params);                       \
    void getNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);       \
    void getNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment,           \
                                                  GLenum pname, GLint *params);                    \
    void getNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint *param);           \
    void getNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint *params);        \
    void getQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);        \
    void getQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);          \
    void getQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);       \
    void getQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);         \
    void getTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, \
                         void *pixels);                                                            \
    void getTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat *params);   \
    void getTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint *params);     \
    void getTextureParameterIiv(GLuint texture, GLenum pname, GLint *params);                      \
    void getTextureParameterIuiv(GLuint texture, GLenum pname, GLuint *params);                    \
    void getTextureParameterfv(GLuint texture, GLenum pname, GLfloat *params);                     \
    void getTextureParameteriv(GLuint texture, GLenum pname, GLint *params);                       \
    void getTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset,             \
                            GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,           \
                            GLenum format, GLenum type, GLsizei bufSize, void *pixels);            \
    void getTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 *param);        \
    void getTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint *param);            \
    void getTransformFeedbackiv(GLuint xfb, GLenum pname, GLint *param);                           \
    void getVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);      \
    void getVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint *param);          \
    void getVertexArrayiv(GLuint vaobj, GLenum pname, GLint *param);                               \
    void getnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void *table);  \
    void getnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void *pixels);          \
    void getnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize,         \
                               void *image);                                                       \
    void getnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type,                 \
                       GLsizei bufSize, void *values);                                             \
    void getnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble *v);                     \
    void getnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat *v);                      \
    void getnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint *v);                        \
    void getnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize,   \
                    void *values);                                                                 \
    void getnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat *values);                             \
    void getnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint *values);                             \
    void getnPixelMapusv(GLenum map, GLsizei bufSize, GLushort *values);                           \
    void getnPolygonStipple(GLsizei bufSize, GLubyte *pattern);                                    \
    void getnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize,        \
                             void *row, GLsizei columnBufSize, void *column, void *span);          \
    void getnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize,     \
                      void *pixels);                                                               \
    void getnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble *params);         \
    void getnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint *params);          \
    void invalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments,                \
                                        const GLenum *attachments);                                \
    void invalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments,             \
                                           const GLenum *attachments, GLint x, GLint y,            \
                                           GLsizei width, GLsizei height);                         \
    void *mapNamedBuffer(GLuint buffer, GLenum access);                                            \
    void *mapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length,                   \
                              GLbitfield access);                                                  \
    void namedBufferData(GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);          \
    void namedBufferStorage(GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);   \
    void namedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);    \
    void namedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);                               \
    void namedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum *bufs);           \
    void namedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param);                \
    void namedFramebufferReadBuffer(GLuint framebuffer, GLenum src);                               \
    void namedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment,                       \
                                      GLenum renderbuffertarget, GLuint renderbuffer);             \
    void namedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture,            \
                                 GLint level);                                                     \
    void namedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture,       \
                                      GLint level, GLint layer);                                   \
    void namedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width,       \
                                  GLsizei height);                                                 \
    void namedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples,                 \
                                             GLenum internalformat, GLsizei width,                 \
                                             GLsizei height);                                      \
    void textureBarrier();                                                                         \
    void textureBuffer(GLuint texture, GLenum internalformat, GLuint buffer);                      \
    void textureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, \
                            GLsizeiptr size);                                                      \
    void textureParameterIiv(GLuint texture, GLenum pname, const GLint *params);                   \
    void textureParameterIuiv(GLuint texture, GLenum pname, const GLuint *params);                 \
    void textureParameterf(GLuint texture, GLenum pname, GLfloat param);                           \
    void textureParameterfv(GLuint texture, GLenum pname, const GLfloat *param);                   \
    void textureParameteri(GLuint texture, GLenum pname, GLint param);                             \
    void textureParameteriv(GLuint texture, GLenum pname, const GLint *param);                     \
    void textureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);   \
    void textureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width,    \
                          GLsizei height);                                                         \
    void textureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat,       \
                                     GLsizei width, GLsizei height,                                \
                                     GLboolean fixedsamplelocations);                              \
    void textureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width,    \
                          GLsizei height, GLsizei depth);                                          \
    void textureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat,       \
                                     GLsizei width, GLsizei height, GLsizei depth,                 \
                                     GLboolean fixedsamplelocations);                              \
    void textureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width,              \
                           GLenum format, GLenum type, const void *pixels);                        \
    void textureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,              \
                           GLsizei width, GLsizei height, GLenum format, GLenum type,              \
                           const void *pixels);                                                    \
    void textureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,              \
                           GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,            \
                           GLenum format, GLenum type, const void *pixels);                        \
    void transformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer);                     \
    void transformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset,    \
                                      GLsizeiptr size);                                            \
    GLboolean unmapNamedBuffer(GLuint buffer);                                                     \
    void vertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex);          \
    void vertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,        \
                                 GLboolean normalized, GLuint relativeoffset);                     \
    void vertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,       \
                                  GLuint relativeoffset);                                          \
    void vertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type,       \
                                  GLuint relativeoffset);                                          \
    void vertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor);             \
    void vertexArrayElementBuffer(GLuint vaobj, GLuint buffer);                                    \
    void vertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer,                 \
                                 GLintptr offset, GLsizei stride);                                 \
    void vertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count,                       \
                                  const GLuint *buffers, const GLintptr *offsets,                  \
                                  const GLsizei *strides);

#endif  // ANGLE_CONTEXT_API_4_5_AUTOGEN_H_
