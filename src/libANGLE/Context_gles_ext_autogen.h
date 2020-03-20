// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Context_gles_ext_autogen.h: Creates a macro for interfaces in Context.

#ifndef ANGLE_CONTEXT_GLES_EXT_AUTOGEN_H_
#define ANGLE_CONTEXT_GLES_EXT_AUTOGEN_H_

#define ANGLE_GLES_EXT_CONTEXT_API                                                                 \
                                                                                                   \
    /* GLES1 Extensions */                                                                         \
                                                                                                   \
    /* GL_OES_draw_texture */                                                                      \
    void drawTexf(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);                 \
    void drawTexfv(const GLfloat *coords);                                                         \
    void drawTexi(GLint x, GLint y, GLint z, GLint width, GLint height);                           \
    void drawTexiv(const GLint *coords);                                                           \
    void drawTexs(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);                 \
    void drawTexsv(const GLshort *coords);                                                         \
    void drawTexx(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);                 \
    void drawTexxv(const GLfixed *coords);                                                         \
    /* GL_OES_framebuffer_object */                                                                \
    /* GL_OES_matrix_palette */                                                                    \
    void currentPaletteMatrix(GLuint matrixpaletteindex);                                          \
    void loadPaletteFromModelViewMatrix();                                                         \
    void matrixIndexPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);         \
    void weightPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);              \
    /* GL_OES_point_size_array */                                                                  \
    void pointSizePointer(VertexAttribType typePacked, GLsizei stride, const void *pointer);       \
    /* GL_OES_query_matrix */                                                                      \
    GLbitfield queryMatrixx(GLfixed *mantissa, GLint *exponent);                                   \
    /* GL_OES_texture_cube_map */                                                                  \
    void getTexGenfv(GLenum coord, GLenum pname, GLfloat *params);                                 \
    void getTexGeniv(GLenum coord, GLenum pname, GLint *params);                                   \
    void getTexGenxv(GLenum coord, GLenum pname, GLfixed *params);                                 \
    void texGenf(GLenum coord, GLenum pname, GLfloat param);                                       \
    void texGenfv(GLenum coord, GLenum pname, const GLfloat *params);                              \
    void texGeni(GLenum coord, GLenum pname, GLint param);                                         \
    void texGeniv(GLenum coord, GLenum pname, const GLint *params);                                \
    void texGenx(GLenum coord, GLenum pname, GLfixed param);                                       \
    void texGenxv(GLenum coord, GLenum pname, const GLfixed *params);                              \
                                                                                                   \
    /* ANGLE Extensions */                                                                         \
                                                                                                   \
    /* GL_ANGLE_copy_texture_3d */                                                                 \
    void copyTexture3D(TextureID sourceIdPacked, GLint sourceLevel,                                \
                       TextureTarget destTargetPacked, TextureID destIdPacked, GLint destLevel,    \
                       GLint internalFormat, GLenum destType, GLboolean unpackFlipY,               \
                       GLboolean unpackPremultiplyAlpha, GLboolean unpackUnmultiplyAlpha);         \
    void copySubTexture3D(TextureID sourceIdPacked, GLint sourceLevel,                             \
                          TextureTarget destTargetPacked, TextureID destIdPacked, GLint destLevel, \
                          GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLint z,  \
                          GLint width, GLint height, GLint depth, GLboolean unpackFlipY,           \
                          GLboolean unpackPremultiplyAlpha, GLboolean unpackUnmultiplyAlpha);      \
    /* GL_ANGLE_get_image */                                                                       \
    void getTexImage(TextureTarget targetPacked, GLint level, GLenum format, GLenum type,          \
                     void *pixels);                                                                \
    void getRenderbufferImage(GLenum target, GLenum format, GLenum type, void *pixels);            \
    /* GL_ANGLE_program_binary */                                                                  \
    /* GL_ANGLE_request_extension */                                                               \
    void requestExtension(const GLchar *name);                                                     \
    void disableExtension(const GLchar *name);                                                     \
    /* GL_ANGLE_robust_client_memory */                                                            \
    void getBooleanvRobust(GLenum pname, GLsizei bufSize, GLsizei *length, GLboolean *params);     \
    void getBufferParameterivRobust(BufferBinding targetPacked, GLenum pname, GLsizei bufSize,     \
                                    GLsizei *length, GLint *params);                               \
    void getFloatvRobust(GLenum pname, GLsizei bufSize, GLsizei *length, GLfloat *params);         \
    void getFramebufferAttachmentParameterivRobust(GLenum target, GLenum attachment, GLenum pname, \
                                                   GLsizei bufSize, GLsizei *length,               \
                                                   GLint *params);                                 \
    void getIntegervRobust(GLenum pname, GLsizei bufSize, GLsizei *length, GLint *data);           \
    void getProgramivRobust(ShaderProgramID programPacked, GLenum pname, GLsizei bufSize,          \
                            GLsizei *length, GLint *params);                                       \
    void getRenderbufferParameterivRobust(GLenum target, GLenum pname, GLsizei bufSize,            \
                                          GLsizei *length, GLint *params);                         \
    void getShaderivRobust(ShaderProgramID shaderPacked, GLenum pname, GLsizei bufSize,            \
                           GLsizei *length, GLint *params);                                        \
    void getTexParameterfvRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,          \
                                 GLsizei *length, GLfloat *params);                                \
    void getTexParameterivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,          \
                                 GLsizei *length, GLint *params);                                  \
    void getUniformfvRobust(ShaderProgramID programPacked, UniformLocation locationPacked,         \
                            GLsizei bufSize, GLsizei *length, GLfloat *params);                    \
    void getUniformivRobust(ShaderProgramID programPacked, UniformLocation locationPacked,         \
                            GLsizei bufSize, GLsizei *length, GLint *params);                      \
    void getVertexAttribfvRobust(GLuint index, GLenum pname, GLsizei bufSize, GLsizei *length,     \
                                 GLfloat *params);                                                 \
    void getVertexAttribivRobust(GLuint index, GLenum pname, GLsizei bufSize, GLsizei *length,     \
                                 GLint *params);                                                   \
    void getVertexAttribPointervRobust(GLuint index, GLenum pname, GLsizei bufSize,                \
                                       GLsizei *length, void **pointer);                           \
    void readPixelsRobust(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,          \
                          GLenum type, GLsizei bufSize, GLsizei *length, GLsizei *columns,         \
                          GLsizei *rows, void *pixels);                                            \
    void texImage2DRobust(TextureTarget targetPacked, GLint level, GLint internalformat,           \
                          GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, \
                          GLsizei bufSize, const void *pixels);                                    \
    void texParameterfvRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,             \
                              const GLfloat *params);                                              \
    void texParameterivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,             \
                              const GLint *params);                                                \
    void texSubImage2DRobust(TextureTarget targetPacked, GLint level, GLint xoffset,               \
                             GLint yoffset, GLsizei width, GLsizei height, GLenum format,          \
                             GLenum type, GLsizei bufSize, const void *pixels);                    \
    void texImage3DRobust(TextureTarget targetPacked, GLint level, GLint internalformat,           \
                          GLsizei width, GLsizei height, GLsizei depth, GLint border,              \
                          GLenum format, GLenum type, GLsizei bufSize, const void *pixels);        \
    void texSubImage3DRobust(TextureTarget targetPacked, GLint level, GLint xoffset,               \
                             GLint yoffset, GLint zoffset, GLsizei width, GLsizei height,          \
                             GLsizei depth, GLenum format, GLenum type, GLsizei bufSize,           \
                             const void *pixels);                                                  \
    void compressedTexImage2DRobust(                                                               \
        TextureTarget targetPacked, GLint level, GLenum internalformat, GLsizei width,             \
        GLsizei height, GLint border, GLsizei imageSize, GLsizei dataSize, const GLvoid *data);    \
    void compressedTexSubImage2DRobust(                                                            \
        TextureTarget targetPacked, GLint level, GLsizei xoffset, GLsizei yoffset, GLsizei width,  \
        GLsizei height, GLenum format, GLsizei imageSize, GLsizei dataSize, const GLvoid *data);   \
    void compressedTexImage3DRobust(TextureTarget targetPacked, GLint level,                       \
                                    GLenum internalformat, GLsizei width, GLsizei height,          \
                                    GLsizei depth, GLint border, GLsizei imageSize,                \
                                    GLsizei dataSize, const GLvoid *data);                         \
    void compressedTexSubImage3DRobust(TextureTarget targetPacked, GLint level, GLint xoffset,     \
                                       GLint yoffset, GLint zoffset, GLsizei width,                \
                                       GLsizei height, GLsizei depth, GLenum format,               \
                                       GLsizei imageSize, GLsizei dataSize, const GLvoid *data);   \
    void getQueryivRobust(QueryType targetPacked, GLenum pname, GLsizei bufSize, GLsizei *length,  \
                          GLint *params);                                                          \
    void getQueryObjectuivRobust(QueryID idPacked, GLenum pname, GLsizei bufSize, GLsizei *length, \
                                 GLuint *params);                                                  \
    void getBufferPointervRobust(BufferBinding targetPacked, GLenum pname, GLsizei bufSize,        \
                                 GLsizei *length, void **params);                                  \
    void getIntegeri_vRobust(GLenum target, GLuint index, GLsizei bufSize, GLsizei *length,        \
                             GLint *data);                                                         \
    void getInternalformativRobust(GLenum target, GLenum internalformat, GLenum pname,             \
                                   GLsizei bufSize, GLsizei *length, GLint *params);               \
    void getVertexAttribIivRobust(GLuint index, GLenum pname, GLsizei bufSize, GLsizei *length,    \
                                  GLint *params);                                                  \
    void getVertexAttribIuivRobust(GLuint index, GLenum pname, GLsizei bufSize, GLsizei *length,   \
                                   GLuint *params);                                                \
    void getUniformuivRobust(ShaderProgramID programPacked, UniformLocation locationPacked,        \
                             GLsizei bufSize, GLsizei *length, GLuint *params);                    \
    void getActiveUniformBlockivRobust(ShaderProgramID programPacked, GLuint uniformBlockIndex,    \
                                       GLenum pname, GLsizei bufSize, GLsizei *length,             \
                                       GLint *params);                                             \
    void getInteger64vRobust(GLenum pname, GLsizei bufSize, GLsizei *length, GLint64 *data);       \
    void getInteger64i_vRobust(GLenum target, GLuint index, GLsizei bufSize, GLsizei *length,      \
                               GLint64 *data);                                                     \
    void getBufferParameteri64vRobust(BufferBinding targetPacked, GLenum pname, GLsizei bufSize,   \
                                      GLsizei *length, GLint64 *params);                           \
    void samplerParameterivRobust(SamplerID samplerPacked, GLuint pname, GLsizei bufSize,          \
                                  const GLint *param);                                             \
    void samplerParameterfvRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,          \
                                  const GLfloat *param);                                           \
    void getSamplerParameterivRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,       \
                                     GLsizei *length, GLint *params);                              \
    void getSamplerParameterfvRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,       \
                                     GLsizei *length, GLfloat *params);                            \
    void getFramebufferParameterivRobust(GLenum target, GLenum pname, GLsizei bufSize,             \
                                         GLsizei *length, GLint *params);                          \
    void getProgramInterfaceivRobust(ShaderProgramID programPacked, GLenum programInterface,       \
                                     GLenum pname, GLsizei bufSize, GLsizei *length,               \
                                     GLint *params);                                               \
    void getBooleani_vRobust(GLenum target, GLuint index, GLsizei bufSize, GLsizei *length,        \
                             GLboolean *data);                                                     \
    void getMultisamplefvRobust(GLenum pname, GLuint index, GLsizei bufSize, GLsizei *length,      \
                                GLfloat *val);                                                     \
    void getTexLevelParameterivRobust(TextureTarget targetPacked, GLint level, GLenum pname,       \
                                      GLsizei bufSize, GLsizei *length, GLint *params);            \
    void getTexLevelParameterfvRobust(TextureTarget targetPacked, GLint level, GLenum pname,       \
                                      GLsizei bufSize, GLsizei *length, GLfloat *params);          \
    void getPointervRobustANGLERobust(GLenum pname, GLsizei bufSize, GLsizei *length,              \
                                      void **params);                                              \
    void readnPixelsRobust(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format,         \
                           GLenum type, GLsizei bufSize, GLsizei *length, GLsizei *columns,        \
                           GLsizei *rows, void *data);                                             \
    void getnUniformfvRobust(ShaderProgramID programPacked, UniformLocation locationPacked,        \
                             GLsizei bufSize, GLsizei *length, GLfloat *params);                   \
    void getnUniformivRobust(ShaderProgramID programPacked, UniformLocation locationPacked,        \
                             GLsizei bufSize, GLsizei *length, GLint *params);                     \
    void getnUniformuivRobust(ShaderProgramID programPacked, UniformLocation locationPacked,       \
                              GLsizei bufSize, GLsizei *length, GLuint *params);                   \
    void texParameterIivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,            \
                               const GLint *params);                                               \
    void texParameterIuivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,           \
                                const GLuint *params);                                             \
    void getTexParameterIivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,         \
                                  GLsizei *length, GLint *params);                                 \
    void getTexParameterIuivRobust(TextureType targetPacked, GLenum pname, GLsizei bufSize,        \
                                   GLsizei *length, GLuint *params);                               \
    void samplerParameterIivRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,         \
                                   const GLint *param);                                            \
    void samplerParameterIuivRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,        \
                                    const GLuint *param);                                          \
    void getSamplerParameterIivRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,      \
                                      GLsizei *length, GLint *params);                             \
    void getSamplerParameterIuivRobust(SamplerID samplerPacked, GLenum pname, GLsizei bufSize,     \
                                       GLsizei *length, GLuint *params);                           \
    void getQueryObjectivRobust(QueryID idPacked, GLenum pname, GLsizei bufSize, GLsizei *length,  \
                                GLint *params);                                                    \
    void getQueryObjecti64vRobust(QueryID idPacked, GLenum pname, GLsizei bufSize,                 \
                                  GLsizei *length, GLint64 *params);                               \
    void getQueryObjectui64vRobust(QueryID idPacked, GLenum pname, GLsizei bufSize,                \
                                   GLsizei *length, GLuint64 *params);                             \
    /* GL_ANGLE_texture_external_update */                                                         \
    void texImage2DExternal(TextureTarget targetPacked, GLint level, GLint internalformat,         \
                            GLsizei width, GLsizei height, GLint border, GLenum format,            \
                            GLenum type);                                                          \
    void invalidateTexture(TextureType targetPacked);                                              \
    /* GL_CHROMIUM_bind_uniform_location */                                                        \
    void bindUniformLocation(ShaderProgramID programPacked, UniformLocation locationPacked,        \
                             const GLchar *name);                                                  \
    /* GL_CHROMIUM_copy_compressed_texture */                                                      \
    void compressedCopyTexture(TextureID sourceIdPacked, TextureID destIdPacked);                  \
    /* GL_CHROMIUM_copy_texture */                                                                 \
    void copyTexture(TextureID sourceIdPacked, GLint sourceLevel, TextureTarget destTargetPacked,  \
                     TextureID destIdPacked, GLint destLevel, GLint internalFormat,                \
                     GLenum destType, GLboolean unpackFlipY, GLboolean unpackPremultiplyAlpha,     \
                     GLboolean unpackUnmultiplyAlpha);                                             \
    void copySubTexture(TextureID sourceIdPacked, GLint sourceLevel,                               \
                        TextureTarget destTargetPacked, TextureID destIdPacked, GLint destLevel,   \
                        GLint xoffset, GLint yoffset, GLint x, GLint y, GLint width, GLint height, \
                        GLboolean unpackFlipY, GLboolean unpackPremultiplyAlpha,                   \
                        GLboolean unpackUnmultiplyAlpha);                                          \
    /* GL_CHROMIUM_framebuffer_mixed_samples */                                                    \
    void coverageModulation(GLenum components);                                                    \
    /* GL_CHROMIUM_lose_context */                                                                 \
    void loseContext(GraphicsResetStatus currentPacked, GraphicsResetStatus otherPacked);          \
    /* GL_CHROMIUM_path_rendering */                                                               \
                                                                                                   \
    /* GLES2+ Extensions */                                                                        \
                                                                                                   \
    /* GL_ANGLE_base_vertex_base_instance */                                                       \
    void drawArraysInstancedBaseInstance(PrimitiveMode modePacked, GLint first, GLsizei count,     \
                                         GLsizei instanceCount, GLuint baseInstance);              \
    void drawElementsInstancedBaseVertexBaseInstance(                                              \
        PrimitiveMode modePacked, GLsizei count, DrawElementsType typePacked,                      \
        const GLvoid *indices, GLsizei instanceCounts, GLint baseVertex, GLuint baseInstance);     \
    void multiDrawArraysInstancedBaseInstance(                                                     \
        PrimitiveMode modePacked, const GLint *firsts, const GLsizei *counts,                      \
        const GLsizei *instanceCounts, const GLuint *baseInstances, GLsizei drawcount);            \
    void multiDrawElementsInstancedBaseVertexBaseInstance(                                         \
        PrimitiveMode modePacked, const GLsizei *counts, DrawElementsType typePacked,              \
        const GLvoid *const *indices, const GLsizei *instanceCounts, const GLint *baseVertices,    \
        const GLuint *baseInstances, GLsizei drawcount);                                           \
    /* GL_ANGLE_framebuffer_blit */                                                                \
    /* GL_ANGLE_framebuffer_multisample */                                                         \
    /* GL_ANGLE_instanced_arrays */                                                                \
    /* GL_ANGLE_memory_object_fuchsia */                                                           \
    void importMemoryZirconHandle(MemoryObjectID memoryPacked, GLuint64 size,                      \
                                  HandleType handleTypePacked, GLuint handle);                     \
    /* GL_ANGLE_multi_draw */                                                                      \
    void multiDrawArrays(PrimitiveMode modePacked, const GLint *firsts, const GLsizei *counts,     \
                         GLsizei drawcount);                                                       \
    void multiDrawArraysInstanced(PrimitiveMode modePacked, const GLint *firsts,                   \
                                  const GLsizei *counts, const GLsizei *instanceCounts,            \
                                  GLsizei drawcount);                                              \
    void multiDrawElements(PrimitiveMode modePacked, const GLsizei *counts,                        \
                           DrawElementsType typePacked, const GLvoid *const *indices,              \
                           GLsizei drawcount);                                                     \
    void multiDrawElementsInstanced(PrimitiveMode modePacked, const GLsizei *counts,               \
                                    DrawElementsType typePacked, const GLvoid *const *indices,     \
                                    const GLsizei *instanceCounts, GLsizei drawcount);             \
    /* GL_ANGLE_provoking_vertex */                                                                \
    void provokingVertex(ProvokingVertexConvention modePacked);                                    \
    /* GL_ANGLE_semaphore_fuchsia */                                                               \
    void importSemaphoreZirconHandle(SemaphoreID semaphorePacked, HandleType handleTypePacked,     \
                                     GLuint handle);                                               \
    /* GL_ANGLE_texture_multisample */                                                             \
    /* GL_ANGLE_translated_shader_source */                                                        \
    void getTranslatedShaderSource(ShaderProgramID shaderPacked, GLsizei bufsize, GLsizei *length, \
                                   GLchar *source);                                                \
    /* GL_EXT_blend_func_extended */                                                               \
    void bindFragDataLocation(ShaderProgramID programPacked, GLuint color, const GLchar *name);    \
    void bindFragDataLocationIndexed(ShaderProgramID programPacked, GLuint colorNumber,            \
                                     GLuint index, const GLchar *name);                            \
    GLint getFragDataIndex(ShaderProgramID programPacked, const GLchar *name);                     \
    GLint getProgramResourceLocationIndex(ShaderProgramID programPacked, GLenum programInterface,  \
                                          const GLchar *name);                                     \
    /* GL_EXT_debug_marker */                                                                      \
    void insertEventMarker(GLsizei length, const GLchar *marker);                                  \
    void popGroupMarker();                                                                         \
    void pushGroupMarker(GLsizei length, const GLchar *marker);                                    \
    /* GL_EXT_discard_framebuffer */                                                               \
    void discardFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments);     \
    /* GL_EXT_disjoint_timer_query */                                                              \
    void getQueryObjecti64v(QueryID idPacked, GLenum pname, GLint64 *params);                      \
    void getQueryObjectiv(QueryID idPacked, GLenum pname, GLint *params);                          \
    void getQueryObjectui64v(QueryID idPacked, GLenum pname, GLuint64 *params);                    \
    void queryCounter(QueryID idPacked, QueryType targetPacked);                                   \
    /* GL_EXT_draw_buffers */                                                                      \
    /* GL_EXT_draw_buffers_indexed */                                                              \
    /* GL_EXT_draw_elements_base_vertex */                                                         \
    void multiDrawElementsBaseVertex(PrimitiveMode modePacked, const GLsizei *count,               \
                                     DrawElementsType typePacked, const void *const *indices,      \
                                     GLsizei primcount, const GLint *basevertex);                  \
    /* GL_EXT_geometry_shader */                                                                   \
    /* GL_EXT_instanced_arrays */                                                                  \
    /* GL_EXT_map_buffer_range */                                                                  \
    /* GL_EXT_memory_object */                                                                     \
    void bufferStorageMem(TextureType targetPacked, GLsizeiptr size, MemoryObjectID memoryPacked,  \
                          GLuint64 offset);                                                        \
    void createMemoryObjects(GLsizei n, MemoryObjectID *memoryObjectsPacked);                      \
    void deleteMemoryObjects(GLsizei n, const MemoryObjectID *memoryObjectsPacked);                \
    void getMemoryObjectParameteriv(MemoryObjectID memoryObjectPacked, GLenum pname,               \
                                    GLint *params);                                                \
    void getUnsignedBytev(GLenum pname, GLubyte *data);                                            \
    void getUnsignedBytei_v(GLenum target, GLuint index, GLubyte *data);                           \
    GLboolean isMemoryObject(MemoryObjectID memoryObjectPacked) const;                             \
    void memoryObjectParameteriv(MemoryObjectID memoryObjectPacked, GLenum pname,                  \
                                 const GLint *params);                                             \
    void texStorageMem2D(TextureType targetPacked, GLsizei levels, GLenum internalFormat,          \
                         GLsizei width, GLsizei height, MemoryObjectID memoryPacked,               \
                         GLuint64 offset);                                                         \
    void texStorageMem2DMultisample(TextureType targetPacked, GLsizei samples,                     \
                                    GLenum internalFormat, GLsizei width, GLsizei height,          \
                                    GLboolean fixedSampleLocations, MemoryObjectID memoryPacked,   \
                                    GLuint64 offset);                                              \
    void texStorageMem3D(TextureType targetPacked, GLsizei levels, GLenum internalFormat,          \
                         GLsizei width, GLsizei height, GLsizei depth,                             \
                         MemoryObjectID memoryPacked, GLuint64 offset);                            \
    void texStorageMem3DMultisample(TextureType targetPacked, GLsizei samples,                     \
                                    GLenum internalFormat, GLsizei width, GLsizei height,          \
                                    GLsizei depth, GLboolean fixedSampleLocations,                 \
                                    MemoryObjectID memoryPacked, GLuint64 offset);                 \
    /* GL_EXT_memory_object_fd */                                                                  \
    void importMemoryFd(MemoryObjectID memoryPacked, GLuint64 size, HandleType handleTypePacked,   \
                        GLint fd);                                                                 \
    /* GL_EXT_multisampled_render_to_texture */                                                    \
    void framebufferTexture2DMultisample(GLenum target, GLenum attachment, GLenum textarget,       \
                                         GLuint texture, GLint level, GLsizei samples);            \
    /* GL_EXT_occlusion_query_boolean */                                                           \
    /* GL_EXT_read_format_bgra */                                                                  \
    /* GL_EXT_robustness */                                                                        \
    /* GL_EXT_sRGB */                                                                              \
    /* GL_EXT_semaphore */                                                                         \
    void deleteSemaphores(GLsizei n, const SemaphoreID *semaphoresPacked);                         \
    void genSemaphores(GLsizei n, SemaphoreID *semaphoresPacked);                                  \
    void getSemaphoreParameterui64v(SemaphoreID semaphorePacked, GLenum pname, GLuint64 *params);  \
    GLboolean isSemaphore(SemaphoreID semaphorePacked) const;                                      \
    void semaphoreParameterui64v(SemaphoreID semaphorePacked, GLenum pname,                        \
                                 const GLuint64 *params);                                          \
    void signalSemaphore(SemaphoreID semaphorePacked, GLuint numBufferBarriers,                    \
                         const BufferID *buffersPacked, GLuint numTextureBarriers,                 \
                         const TextureID *texturesPacked, const GLenum *dstLayouts);               \
    void waitSemaphore(SemaphoreID semaphorePacked, GLuint numBufferBarriers,                      \
                       const BufferID *buffersPacked, GLuint numTextureBarriers,                   \
                       const TextureID *texturesPacked, const GLenum *srcLayouts);                 \
    /* GL_EXT_semaphore_fd */                                                                      \
    void importSemaphoreFd(SemaphoreID semaphorePacked, HandleType handleTypePacked, GLint fd);    \
    /* GL_EXT_texture_compression_bptc */                                                          \
    /* GL_EXT_texture_compression_dxt1 */                                                          \
    /* GL_EXT_texture_compression_rgtc */                                                          \
    /* GL_EXT_texture_compression_s3tc */                                                          \
    /* GL_EXT_texture_compression_s3tc_srgb */                                                     \
    /* GL_EXT_texture_filter_anisotropic */                                                        \
    /* GL_EXT_texture_format_BGRA8888 */                                                           \
    /* GL_EXT_texture_storage */                                                                   \
    void texStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);        \
    /* GL_KHR_debug */                                                                             \
    /* GL_KHR_parallel_shader_compile */                                                           \
    void maxShaderCompilerThreads(GLuint count);                                                   \
    /* GL_NV_fence */                                                                              \
    void deleteFencesNV(GLsizei n, const FenceNVID *fencesPacked);                                 \
    void finishFenceNV(FenceNVID fencePacked);                                                     \
    void genFencesNV(GLsizei n, FenceNVID *fencesPacked);                                          \
    void getFenceivNV(FenceNVID fencePacked, GLenum pname, GLint *params);                         \
    GLboolean isFenceNV(FenceNVID fencePacked) const;                                              \
    void setFenceNV(FenceNVID fencePacked, GLenum condition);                                      \
    GLboolean testFenceNV(FenceNVID fencePacked);                                                  \
    /* GL_OES_EGL_image */                                                                         \
    void eGLImageTargetRenderbufferStorage(GLenum target, GLeglImageOES image);                    \
    void eGLImageTargetTexture2D(TextureType targetPacked, GLeglImageOES image);                   \
    /* GL_OES_compressed_ETC1_RGB8_texture */                                                      \
    /* GL_OES_depth32 */                                                                           \
    /* GL_OES_draw_buffers_indexed */                                                              \
    /* GL_OES_draw_elements_base_vertex */                                                         \
    /* GL_OES_get_program_binary */                                                                \
    /* GL_OES_mapbuffer */                                                                         \
    void *mapBuffer(BufferBinding targetPacked, GLenum access);                                    \
    /* GL_OES_texture_3D */                                                                        \
    void framebufferTexture3D(GLenum target, GLenum attachment, TextureTarget textargetPacked,     \
                              TextureID texturePacked, GLint level, GLint zoffset);                \
    /* GL_OES_texture_border_clamp */                                                              \
    /* GL_OES_texture_half_float */                                                                \
    /* GL_OES_texture_storage_multisample_2d_array */                                              \
    /* GL_OES_vertex_array_object */                                                               \
    /* GL_OVR_multiview */                                                                         \
    void framebufferTextureMultiview(GLenum target, GLenum attachment, TextureID texturePacked,    \
                                     GLint level, GLint baseViewIndex, GLsizei numViews);          \
    /* GL_OVR_multiview2 */

#endif  // ANGLE_CONTEXT_API_EXT_AUTOGEN_H_
