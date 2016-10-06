// GENERATED FILE - DO NOT EDIT.
// Generated by gen_format_map.py using data from format_map_data.json.
//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// format_map:
//   Determining the sized internal format from a (format,type) pair.

#include "angle_gl.h"
#include "common/debug.h"

namespace gl
{

GLenum GetSizedFormatInternal(GLenum format, GLenum type)
{
    switch (format)
    {
        case GL_ALPHA:
            switch (type)
            {
                case GL_FLOAT:
                    return GL_ALPHA32F_EXT;
                case GL_HALF_FLOAT:
                    return GL_ALPHA16F_EXT;
                case GL_HALF_FLOAT_OES:
                    return GL_ALPHA16F_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_ALPHA8_EXT;
                default:
                    break;
            }
            break;

        case GL_BGRA_EXT:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_BGRA8_EXT;
                case GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT:
                    return GL_BGR5_A1_ANGLEX;
                case GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT:
                    return GL_BGRA4_ANGLEX;
                case GL_UNSIGNED_SHORT_5_6_5:
                    return GL_BGR565_ANGLEX;
                default:
                    break;
            }
            break;

        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                default:
                    break;
            }
            break;

        case GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE;
                default:
                    break;
            }
            break;

        case GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE;
                default:
                    break;
            }
            break;

        case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
                default:
                    break;
            }
            break;

        case GL_DEPTH_COMPONENT:
            switch (type)
            {
                case GL_FLOAT:
                    return GL_DEPTH_COMPONENT32F;
                case GL_UNSIGNED_INT:
                    return GL_DEPTH_COMPONENT32_OES;
                case GL_UNSIGNED_SHORT:
                    return GL_DEPTH_COMPONENT16;
                default:
                    break;
            }
            break;

        case GL_DEPTH_STENCIL:
            switch (type)
            {
                case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
                    return GL_DEPTH32F_STENCIL8;
                case GL_UNSIGNED_INT_24_8:
                    return GL_DEPTH24_STENCIL8;
                default:
                    break;
            }
            break;

        case GL_LUMINANCE:
            switch (type)
            {
                case GL_FLOAT:
                    return GL_LUMINANCE32F_EXT;
                case GL_HALF_FLOAT:
                    return GL_LUMINANCE16F_EXT;
                case GL_HALF_FLOAT_OES:
                    return GL_LUMINANCE16F_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_LUMINANCE8_EXT;
                default:
                    break;
            }
            break;

        case GL_LUMINANCE_ALPHA:
            switch (type)
            {
                case GL_FLOAT:
                    return GL_LUMINANCE_ALPHA32F_EXT;
                case GL_HALF_FLOAT:
                    return GL_LUMINANCE_ALPHA16F_EXT;
                case GL_HALF_FLOAT_OES:
                    return GL_LUMINANCE_ALPHA16F_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_LUMINANCE8_ALPHA8_EXT;
                default:
                    break;
            }
            break;

        case GL_RED:
            switch (type)
            {
                case GL_BYTE:
                    return GL_R8_SNORM;
                case GL_FLOAT:
                    return GL_R32F;
                case GL_HALF_FLOAT:
                    return GL_R16F;
                case GL_HALF_FLOAT_OES:
                    return GL_R16F;
                case GL_SHORT:
                    return GL_R16_SNORM_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_R8;
                case GL_UNSIGNED_SHORT:
                    return GL_R16_EXT;
                default:
                    break;
            }
            break;

        case GL_RED_INTEGER:
            switch (type)
            {
                case GL_BYTE:
                    return GL_R8I;
                case GL_INT:
                    return GL_R32I;
                case GL_SHORT:
                    return GL_R16I;
                case GL_UNSIGNED_BYTE:
                    return GL_R8UI;
                case GL_UNSIGNED_INT:
                    return GL_R32UI;
                case GL_UNSIGNED_SHORT:
                    return GL_R16UI;
                default:
                    break;
            }
            break;

        case GL_RG:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RG8_SNORM;
                case GL_FLOAT:
                    return GL_RG32F;
                case GL_HALF_FLOAT:
                    return GL_RG16F;
                case GL_HALF_FLOAT_OES:
                    return GL_RG16F;
                case GL_SHORT:
                    return GL_RG16_SNORM_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_RG8;
                case GL_UNSIGNED_SHORT:
                    return GL_RG16_EXT;
                default:
                    break;
            }
            break;

        case GL_RGB:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RGB8_SNORM;
                case GL_FLOAT:
                    return GL_RGB32F;
                case GL_HALF_FLOAT:
                    return GL_RGB16F;
                case GL_HALF_FLOAT_OES:
                    return GL_RGB16F;
                case GL_SHORT:
                    return GL_RGB16_SNORM_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_RGB8;
                case GL_UNSIGNED_INT_10F_11F_11F_REV:
                    return GL_R11F_G11F_B10F;
                case GL_UNSIGNED_INT_5_9_9_9_REV:
                    return GL_RGB9_E5;
                case GL_UNSIGNED_SHORT:
                    return GL_RGB16_EXT;
                case GL_UNSIGNED_SHORT_5_6_5:
                    return GL_RGB565;
                default:
                    break;
            }
            break;

        case GL_RGBA:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RGBA8_SNORM;
                case GL_FLOAT:
                    return GL_RGBA32F;
                case GL_HALF_FLOAT:
                    return GL_RGBA16F;
                case GL_HALF_FLOAT_OES:
                    return GL_RGBA16F;
                case GL_SHORT:
                    return GL_RGBA16_SNORM_EXT;
                case GL_UNSIGNED_BYTE:
                    return GL_RGBA8;
                case GL_UNSIGNED_INT_2_10_10_10_REV:
                    return GL_RGB10_A2;
                case GL_UNSIGNED_SHORT:
                    return GL_RGBA16_EXT;
                case GL_UNSIGNED_SHORT_4_4_4_4:
                    return GL_RGBA4;
                case GL_UNSIGNED_SHORT_5_5_5_1:
                    return GL_RGB5_A1;
                default:
                    break;
            }
            break;

        case GL_RGBA_INTEGER:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RGBA8I;
                case GL_INT:
                    return GL_RGBA32I;
                case GL_SHORT:
                    return GL_RGBA16I;
                case GL_UNSIGNED_BYTE:
                    return GL_RGBA8UI;
                case GL_UNSIGNED_INT:
                    return GL_RGBA32UI;
                case GL_UNSIGNED_INT_2_10_10_10_REV:
                    return GL_RGB10_A2UI;
                case GL_UNSIGNED_SHORT:
                    return GL_RGBA16UI;
                default:
                    break;
            }
            break;

        case GL_RGB_INTEGER:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RGB8I;
                case GL_INT:
                    return GL_RGB32I;
                case GL_SHORT:
                    return GL_RGB16I;
                case GL_UNSIGNED_BYTE:
                    return GL_RGB8UI;
                case GL_UNSIGNED_INT:
                    return GL_RGB32UI;
                case GL_UNSIGNED_SHORT:
                    return GL_RGB16UI;
                default:
                    break;
            }
            break;

        case GL_RG_INTEGER:
            switch (type)
            {
                case GL_BYTE:
                    return GL_RG8I;
                case GL_INT:
                    return GL_RG32I;
                case GL_SHORT:
                    return GL_RG16I;
                case GL_UNSIGNED_BYTE:
                    return GL_RG8UI;
                case GL_UNSIGNED_INT:
                    return GL_RG32UI;
                case GL_UNSIGNED_SHORT:
                    return GL_RG16UI;
                default:
                    break;
            }
            break;

        case GL_SRGB_ALPHA_EXT:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_SRGB8_ALPHA8;
                default:
                    break;
            }
            break;

        case GL_SRGB_EXT:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_SRGB8;
                default:
                    break;
            }
            break;

        case GL_STENCIL:
            switch (type)
            {
                case GL_UNSIGNED_BYTE:
                    return GL_STENCIL_INDEX8;
                default:
                    break;
            }
            break;

        case GL_NONE:
            return GL_NONE;

        default:
            break;
    }

    return GL_NONE;
}

}  // namespace gl
