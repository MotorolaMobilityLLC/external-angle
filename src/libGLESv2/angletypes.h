//
// Copyright (c) 2012-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// angletypes.h : Defines a variety of structures and enum types that are used throughout libGLESv2

#ifndef LIBGLESV2_ANGLETYPES_H_
#define LIBGLESV2_ANGLETYPES_H_

namespace gl
{

enum TextureType
{
    TEXTURE_2D,
    TEXTURE_CUBE,
    TEXTURE_3D,
    TEXTURE_2D_ARRAY,

    TEXTURE_TYPE_COUNT,
    TEXTURE_UNKNOWN
};

enum SamplerType
{
    SAMPLER_PIXEL,
    SAMPLER_VERTEX
};

template <typename T>
struct Color
{
    T red;
    T green;
    T blue;
    T alpha;

    Color() : red(0), green(0), blue(0), alpha(0) { }
    Color(T r, T g, T b, T a) : red(r), green(g), blue(b), alpha(a) { }
};

typedef Color<float> ColorF;
typedef Color<int> ColorI;
typedef Color<unsigned int> ColorUI;

struct Rectangle
{
    int x;
    int y;
    int width;
    int height;

    Rectangle() : x(0), y(0), width(0), height(0) { }
    Rectangle(int x_in, int y_in, int width_in, int height_in) : x(x_in), y(y_in), width(width_in), height(height_in) { }
};

struct Box
{
    int x;
    int y;
    int z;
    int width;
    int height;
    int depth;

    Box() : x(0), y(0), z(0), width(0), height(0), depth(0) { }
    Box(int x_in, int y_in, int z_in, int width_in, int height_in, int depth_in) : x(x_in), y(y_in), z(z_in), width(width_in), height(height_in), depth(depth_in) { }
};

struct Extents
{
    int width;
    int height;
    int depth;

    Extents() : width(0), height(0), depth(0) { }
    Extents(int width_, int height_, int depth_) : width(width_), height(height_), depth(depth_) { }
};

struct RasterizerState
{
    bool cullFace;
    GLenum cullMode;
    GLenum frontFace;

    bool polygonOffsetFill;
    GLfloat polygonOffsetFactor;
    GLfloat polygonOffsetUnits;

    bool pointDrawMode;
    bool multiSample;
};

struct BlendState
{
    bool blend;
    GLenum sourceBlendRGB;
    GLenum destBlendRGB;
    GLenum sourceBlendAlpha;
    GLenum destBlendAlpha;
    GLenum blendEquationRGB;
    GLenum blendEquationAlpha;

    bool colorMaskRed;
    bool colorMaskGreen;
    bool colorMaskBlue;
    bool colorMaskAlpha;

    bool sampleAlphaToCoverage;

    bool dither;
};

struct DepthStencilState
{
    bool depthTest;
    GLenum depthFunc;
    bool depthMask;

    bool stencilTest;
    GLenum stencilFunc;
    GLuint stencilMask;
    GLenum stencilFail;
    GLenum stencilPassDepthFail;
    GLenum stencilPassDepthPass;
    GLuint stencilWritemask;
    GLenum stencilBackFunc;
    GLuint stencilBackMask;
    GLenum stencilBackFail;
    GLenum stencilBackPassDepthFail;
    GLenum stencilBackPassDepthPass;
    GLuint stencilBackWritemask;
};

struct SamplerState
{
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    GLenum wrapR;
    float maxAnisotropy;
    int lodOffset;
};

struct ClearParameters
{
    GLbitfield mask;

    ColorF colorClearValue;
    bool colorMaskRed;
    bool colorMaskGreen;
    bool colorMaskBlue;
    bool colorMaskAlpha;

    float depthClearValue;

    GLint stencilClearValue;
    GLuint stencilWriteMask;
};

}

#endif // LIBGLESV2_ANGLETYPES_H_
