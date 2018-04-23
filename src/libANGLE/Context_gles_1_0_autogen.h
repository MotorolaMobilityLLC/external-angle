// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Context_gles_1_0_autogen.h: Creates a macro for interfaces in Context.

#ifndef ANGLE_CONTEXT_GLES_1_0_AUTOGEN_H_
#define ANGLE_CONTEXT_GLES_1_0_AUTOGEN_H_

#define ANGLE_GLES1_CONTEXT_API                                                            \
    void alphaFunc(AlphaTestFunc funcPacked, GLfloat ref);                                 \
    void alphaFuncx(AlphaTestFunc funcPacked, GLfixed ref);                                \
    void clearColorx(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);             \
    void clearDepthx(GLfixed depth);                                                       \
    void clientActiveTexture(GLenum texture);                                              \
    void clipPlanef(GLenum p, const GLfloat *eqn);                                         \
    void clipPlanex(GLenum plane, const GLfixed *equation);                                \
    void color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);                 \
    void color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);                \
    void color4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);                 \
    void colorPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);       \
    void depthRangex(GLfixed n, GLfixed f);                                                \
    void disableClientState(ClientVertexArrayType arrayPacked);                            \
    void enableClientState(ClientVertexArrayType arrayPacked);                             \
    void fogf(GLenum pname, GLfloat param);                                                \
    void fogfv(GLenum pname, const GLfloat *params);                                       \
    void fogx(GLenum pname, GLfixed param);                                                \
    void fogxv(GLenum pname, const GLfixed *param);                                        \
    void frustumf(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);       \
    void frustumx(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);       \
    void getClipPlanef(GLenum plane, GLfloat *equation);                                   \
    void getClipPlanex(GLenum plane, GLfixed *equation);                                   \
    void getFixedv(GLenum pname, GLfixed *params);                                         \
    void getLightfv(GLenum light, GLenum pname, GLfloat *params);                          \
    void getLightxv(GLenum light, GLenum pname, GLfixed *params);                          \
    void getMaterialfv(GLenum face, GLenum pname, GLfloat *params);                        \
    void getMaterialxv(GLenum face, GLenum pname, GLfixed *params);                        \
    void getTexEnvfv(GLenum target, GLenum pname, GLfloat *params);                        \
    void getTexEnviv(GLenum target, GLenum pname, GLint *params);                          \
    void getTexEnvxv(GLenum target, GLenum pname, GLfixed *params);                        \
    void getTexParameterxv(TextureType targetPacked, GLenum pname, GLfixed *params);       \
    void lightModelf(GLenum pname, GLfloat param);                                         \
    void lightModelfv(GLenum pname, const GLfloat *params);                                \
    void lightModelx(GLenum pname, GLfixed param);                                         \
    void lightModelxv(GLenum pname, const GLfixed *param);                                 \
    void lightf(GLenum light, GLenum pname, GLfloat param);                                \
    void lightfv(GLenum light, GLenum pname, const GLfloat *params);                       \
    void lightx(GLenum light, GLenum pname, GLfixed param);                                \
    void lightxv(GLenum light, GLenum pname, const GLfixed *params);                       \
    void lineWidthx(GLfixed width);                                                        \
    void loadIdentity();                                                                   \
    void loadMatrixf(const GLfloat *m);                                                    \
    void loadMatrixx(const GLfixed *m);                                                    \
    void logicOp(GLenum opcode);                                                           \
    void materialf(GLenum face, GLenum pname, GLfloat param);                              \
    void materialfv(GLenum face, GLenum pname, const GLfloat *params);                     \
    void materialx(GLenum face, GLenum pname, GLfixed param);                              \
    void materialxv(GLenum face, GLenum pname, const GLfixed *param);                      \
    void matrixMode(MatrixType modePacked);                                                \
    void multMatrixf(const GLfloat *m);                                                    \
    void multMatrixx(const GLfixed *m);                                                    \
    void multiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);       \
    void multiTexCoord4x(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q);      \
    void normal3f(GLfloat nx, GLfloat ny, GLfloat nz);                                     \
    void normal3x(GLfixed nx, GLfixed ny, GLfixed nz);                                     \
    void normalPointer(GLenum type, GLsizei stride, const void *pointer);                  \
    void orthof(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);         \
    void orthox(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f);         \
    void pointParameterf(GLenum pname, GLfloat param);                                     \
    void pointParameterfv(GLenum pname, const GLfloat *params);                            \
    void pointParameterx(GLenum pname, GLfixed param);                                     \
    void pointParameterxv(GLenum pname, const GLfixed *params);                            \
    void pointSize(GLfloat size);                                                          \
    void pointSizex(GLfixed size);                                                         \
    void polygonOffsetx(GLfixed factor, GLfixed units);                                    \
    void popMatrix();                                                                      \
    void pushMatrix();                                                                     \
    void rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);                          \
    void rotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);                          \
    void sampleCoveragex(GLclampx value, GLboolean invert);                                \
    void scalef(GLfloat x, GLfloat y, GLfloat z);                                          \
    void scalex(GLfixed x, GLfixed y, GLfixed z);                                          \
    void shadeModel(GLenum mode);                                                          \
    void texCoordPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);    \
    void texEnvf(GLenum target, GLenum pname, GLfloat param);                              \
    void texEnvfv(GLenum target, GLenum pname, const GLfloat *params);                     \
    void texEnvi(GLenum target, GLenum pname, GLint param);                                \
    void texEnviv(GLenum target, GLenum pname, const GLint *params);                       \
    void texEnvx(GLenum target, GLenum pname, GLfixed param);                              \
    void texEnvxv(GLenum target, GLenum pname, const GLfixed *params);                     \
    void texParameterx(TextureType targetPacked, GLenum pname, GLfixed param);             \
    void texParameterxv(TextureType targetPacked, GLenum pname, const GLfixed *params);    \
    void translatef(GLfloat x, GLfloat y, GLfloat z);                                      \
    void translatex(GLfixed x, GLfixed y, GLfixed z);                                      \
    void vertexPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);      \
    /* GL_OES_draw_texture */                                                              \
    void drawTexf(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);         \
    void drawTexfv(const GLfloat *coords);                                                 \
    void drawTexi(GLint x, GLint y, GLint z, GLint width, GLint height);                   \
    void drawTexiv(const GLint *coords);                                                   \
    void drawTexs(GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);         \
    void drawTexsv(const GLshort *coords);                                                 \
    void drawTexx(GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);         \
    void drawTexxv(const GLfixed *coords);                                                 \
    /* GL_OES_framebuffer_object */                                                        \
    /* GL_OES_matrix_palette */                                                            \
    void currentPaletteMatrix(GLuint matrixpaletteindex);                                  \
    void loadPaletteFromModelViewMatrix();                                                 \
    void matrixIndexPointer(GLint size, GLenum type, GLsizei stride, const void *pointer); \
    void weightPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);      \
    /* GL_OES_point_size_array */                                                          \
    void pointSizePointer(GLenum type, GLsizei stride, const void *pointer);               \
    /* GL_OES_query_matrix */                                                              \
    GLbitfield queryMatrixx(GLfixed *mantissa, GLint *exponent);                           \
    /* GL_OES_texture_cube_map */                                                          \
    void getTexGenfv(GLenum coord, GLenum pname, GLfloat *params);                         \
    void getTexGeniv(GLenum coord, GLenum pname, GLint *params);                           \
    void getTexGenxv(GLenum coord, GLenum pname, GLfixed *params);                         \
    void texGenf(GLenum coord, GLenum pname, GLfloat param);                               \
    void texGenfv(GLenum coord, GLenum pname, const GLfloat *params);                      \
    void texGeni(GLenum coord, GLenum pname, GLint param);                                 \
    void texGeniv(GLenum coord, GLenum pname, const GLint *params);                        \
    void texGenx(GLenum coord, GLenum pname, GLfixed param);                               \
    void texGenxv(GLenum coord, GLenum pname, const GLfixed *params);

#endif  // ANGLE_CONTEXT_API_1_0_AUTOGEN_H_
