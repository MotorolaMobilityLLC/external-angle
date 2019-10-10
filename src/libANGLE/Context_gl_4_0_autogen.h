// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Context_gl_4_0_autogen.h: Creates a macro for interfaces in Context.

#ifndef ANGLE_CONTEXT_GL_4_0_AUTOGEN_H_
#define ANGLE_CONTEXT_GL_4_0_AUTOGEN_H_

#define ANGLE_GL_4_0_CONTEXT_API                                                                 \
    void beginQueryIndexed(GLenum target, GLuint index, QueryID idPacked);                       \
    void drawTransformFeedback(GLenum mode, TransformFeedbackID idPacked);                       \
    void drawTransformFeedbackStream(GLenum mode, TransformFeedbackID idPacked, GLuint stream);  \
    void endQueryIndexed(GLenum target, GLuint index);                                           \
    void getActiveSubroutineName(ShaderProgramID programPacked, GLenum shadertype, GLuint index, \
                                 GLsizei bufsize, GLsizei *length, GLchar *name);                \
    void getActiveSubroutineUniformName(ShaderProgramID programPacked, GLenum shadertype,        \
                                        GLuint index, GLsizei bufsize, GLsizei *length,          \
                                        GLchar *name);                                           \
    void getActiveSubroutineUniformiv(ShaderProgramID programPacked, GLenum shadertype,          \
                                      GLuint index, GLenum pname, GLint *values);                \
    void getProgramStageiv(ShaderProgramID programPacked, GLenum shadertype, GLenum pname,       \
                           GLint *values);                                                       \
    void getQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params);            \
    GLuint getSubroutineIndex(ShaderProgramID programPacked, GLenum shadertype,                  \
                              const GLchar *name);                                               \
    GLint getSubroutineUniformLocation(ShaderProgramID programPacked, GLenum shadertype,         \
                                       const GLchar *name);                                      \
    void getUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params);             \
    void getUniformdv(ShaderProgramID programPacked, GLint location, GLdouble *params);          \
    void patchParameterfv(GLenum pname, const GLfloat *values);                                  \
    void uniform1d(GLint location, GLdouble x);                                                  \
    void uniform1dv(GLint location, GLsizei count, const GLdouble *value);                       \
    void uniform2d(GLint location, GLdouble x, GLdouble y);                                      \
    void uniform2dv(GLint location, GLsizei count, const GLdouble *value);                       \
    void uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z);                          \
    void uniform3dv(GLint location, GLsizei count, const GLdouble *value);                       \
    void uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);              \
    void uniform4dv(GLint location, GLsizei count, const GLdouble *value);                       \
    void uniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose,                    \
                          const GLdouble *value);                                                \
    void uniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose,                    \
                          const GLdouble *value);                                                \
    void uniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose,                    \
                          const GLdouble *value);                                                \
    void uniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose,                  \
                            const GLdouble *value);                                              \
    void uniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices);

#endif  // ANGLE_CONTEXT_API_4_0_AUTOGEN_H_
