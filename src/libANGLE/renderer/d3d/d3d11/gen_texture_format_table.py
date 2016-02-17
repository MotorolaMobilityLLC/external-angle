#!/usr/bin/python
# Copyright 2015 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_texture_format_table.py:
#  Code generation for texture format map
#

import json
import pprint
import re

template_texture_format_table_autogen_h = """// GENERATED FILE - DO NOT EDIT.
// Generated by gen_texture_format_table.py using data from texture_format_data.json
//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

namespace rx
{{

namespace d3d11
{{

enum ANGLEFormat
{{
{angle_format_enum}
}};

}}  // namespace d3d11

}}  // namespace rx
"""

template_texture_format_table_autogen_cpp = """// GENERATED FILE - DO NOT EDIT.
// Generated by gen_texture_format_table.py using data from texture_format_data.json
//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// texture_format_table:
//   Queries for full textureFormat information based in internalFormat
//

#include "libANGLE/renderer/d3d/d3d11/texture_format_table.h"

#include "libANGLE/renderer/d3d/d3d11/formatutils11.h"
#include "libANGLE/renderer/d3d/d3d11/load_functions_table.h"
#include "libANGLE/renderer/d3d/d3d11/renderer11_utils.h"
#include "libANGLE/renderer/d3d/d3d11/swizzle_format_info.h"
#include "libANGLE/renderer/d3d/loadimage.h"

namespace rx
{{

namespace d3d11
{{

namespace
{{

typedef bool (*FormatSupportFunction)(const Renderer11DeviceCaps &);

bool OnlyFL10Plus(const Renderer11DeviceCaps &deviceCaps)
{{
    return (deviceCaps.featureLevel >= D3D_FEATURE_LEVEL_10_0);
}}

bool OnlyFL9_3(const Renderer11DeviceCaps &deviceCaps)
{{
    return (deviceCaps.featureLevel == D3D_FEATURE_LEVEL_9_3);
}}

template <DXGI_FORMAT format, bool requireSupport>
bool SupportsFormat(const Renderer11DeviceCaps &deviceCaps)
{{
    // Must support texture, SRV and RTV support
    UINT mustSupport = D3D11_FORMAT_SUPPORT_TEXTURE2D | D3D11_FORMAT_SUPPORT_TEXTURECUBE |
                       D3D11_FORMAT_SUPPORT_SHADER_SAMPLE | D3D11_FORMAT_SUPPORT_MIP |
                       D3D11_FORMAT_SUPPORT_RENDER_TARGET;

    if (d3d11_gl::GetMaximumClientVersion(deviceCaps.featureLevel) > 2)
    {{
        mustSupport |= D3D11_FORMAT_SUPPORT_TEXTURE3D;
    }}

    bool fullSupport = false;
    if (format == DXGI_FORMAT_B5G6R5_UNORM)
    {{
        // All hardware that supports DXGI_FORMAT_B5G6R5_UNORM should support autogen mipmaps, but
        // check anyway.
        mustSupport |= D3D11_FORMAT_SUPPORT_MIP_AUTOGEN;
        fullSupport = ((deviceCaps.B5G6R5support & mustSupport) == mustSupport);
    }}
    else if (format == DXGI_FORMAT_B4G4R4A4_UNORM)
    {{
        fullSupport = ((deviceCaps.B4G4R4A4support & mustSupport) == mustSupport);
    }}
    else if (format == DXGI_FORMAT_B5G5R5A1_UNORM)
    {{
        fullSupport = ((deviceCaps.B5G5R5A1support & mustSupport) == mustSupport);
    }}
    else
    {{
        UNREACHABLE();
        return false;
    }}

    // This 'SupportsFormat' function is used by individual entries in the D3D11 Format Map below,
    // which maps GL formats to DXGI formats.
    if (requireSupport)
    {{
        // This means that ANGLE would like to use the entry in the map if the inputted DXGI format
        // *IS* supported.
        // e.g. the entry might map GL_RGB5_A1 to DXGI_FORMAT_B5G5R5A1, which should only be used if
        // DXGI_FORMAT_B5G5R5A1 is supported.
        // In this case, we should only return 'true' if the format *IS* supported.
        return fullSupport;
    }}
    else
    {{
        // This means that ANGLE would like to use the entry in the map if the inputted DXGI format
        // *ISN'T* supported.
        // This might be a fallback entry. e.g. for ANGLE to use DXGI_FORMAT_R8G8B8A8_UNORM if
        // DXGI_FORMAT_B5G5R5A1 isn't supported.
        // In this case, we should only return 'true' if the format *ISN'T* supported.
        return !fullSupport;
    }}
}}

// End Format Support Functions
}}  // namespace

DXGIFormatSet::DXGIFormatSet()
    : texFormat(DXGI_FORMAT_UNKNOWN),
      srvFormat(DXGI_FORMAT_UNKNOWN),
      rtvFormat(DXGI_FORMAT_UNKNOWN),
      dsvFormat(DXGI_FORMAT_UNKNOWN)
{{
}}

// For sized GL internal formats, there are several possible corresponding D3D11 formats depending
// on device capabilities.
// This function allows querying for the DXGI texture formats to use for textures, SRVs, RTVs and
// DSVs given a GL internal format.
TextureFormat::TextureFormat(GLenum internalFormat,
                             const DXGIFormatSet &formatSet,
                             InitializeTextureDataFunction internalFormatInitializer)
    : formatSet(formatSet), dataInitializerFunction(internalFormatInitializer)
{{

    // Compute the swizzle formats
    const gl::InternalFormat &formatInfo = gl::GetInternalFormatInfo(internalFormat);
    if (internalFormat != GL_NONE && formatInfo.pixelBytes > 0)
    {{
        if (formatInfo.componentCount != 4 || formatSet.texFormat == DXGI_FORMAT_UNKNOWN ||
            formatSet.srvFormat == DXGI_FORMAT_UNKNOWN ||
            formatSet.rtvFormat == DXGI_FORMAT_UNKNOWN)
        {{
            // Get the maximum sized component
            unsigned int maxBits = 1;
            if (formatInfo.compressed)
            {{
                unsigned int compressedBitsPerBlock = formatInfo.pixelBytes * 8;
                unsigned int blockSize =
                    formatInfo.compressedBlockWidth * formatInfo.compressedBlockHeight;
                maxBits = std::max(compressedBitsPerBlock / blockSize, maxBits);
            }}
            else
            {{
                maxBits = std::max(maxBits, formatInfo.alphaBits);
                maxBits = std::max(maxBits, formatInfo.redBits);
                maxBits = std::max(maxBits, formatInfo.greenBits);
                maxBits = std::max(maxBits, formatInfo.blueBits);
                maxBits = std::max(maxBits, formatInfo.luminanceBits);
                maxBits = std::max(maxBits, formatInfo.depthBits);
            }}

            maxBits = roundUp(maxBits, 8U);

            const SwizzleFormatInfo &swizzleInfo =
                GetSwizzleFormatInfo(maxBits, formatInfo.componentType);
            swizzleFormatSet.texFormat = swizzleInfo.mTexFormat;
            swizzleFormatSet.srvFormat = swizzleInfo.mSRVFormat;
            swizzleFormatSet.rtvFormat = swizzleInfo.mRTVFormat;
        }}
        else
        {{
            // The original texture format is suitable for swizzle operations
            swizzleFormatSet = formatSet;
        }}
    }}
    else
    {{
        // Not possible to swizzle with this texture format since it is either unsized or GL_NONE
        ASSERT(swizzleFormatSet.texFormat == DXGI_FORMAT_UNKNOWN);
        ASSERT(swizzleFormatSet.srvFormat == DXGI_FORMAT_UNKNOWN);
        ASSERT(swizzleFormatSet.rtvFormat == DXGI_FORMAT_UNKNOWN);
    }}

    // Gather all the load functions for this internal format
    loadFunctions = GetLoadFunctionsMap(internalFormat, formatSet.texFormat);

    ASSERT(loadFunctions.size() != 0 || internalFormat == GL_NONE);
}}

DXGIFormatSet::DXGIFormatSet(DXGI_FORMAT texFormat,
                             DXGI_FORMAT srvFormat,
                             DXGI_FORMAT rtvFormat,
                             DXGI_FORMAT dsvFormat)
    : texFormat(texFormat), srvFormat(srvFormat), rtvFormat(rtvFormat), dsvFormat(dsvFormat)
{{
}}

const DXGIFormatSet &GetANGLEFormatSet(ANGLEFormat angleFormat)
{{
    // clang-format off
    switch (angleFormat)
    {{
{angle_format_info_cases}
        default:
            break;
    }}
    // clang-format on

    UNREACHABLE();
    static const DXGIFormatSet defaultInfo;
    return defaultInfo;
}}

const TextureFormat &GetTextureFormatInfo(GLenum internalFormat,
                                          const Renderer11DeviceCaps &renderer11DeviceCaps)
{{
    // clang-format off
    switch (internalFormat)
    {{
{texture_format_info_cases}
        default:
            break;
    }}
    // clang-format on

    static const TextureFormat defaultInfo(GL_NONE, DXGIFormatSet(), nullptr);
    return defaultInfo;
}}  // GetTextureFormatInfo

}}  // namespace d3d11

}}  // namespace rx
"""

# TODO(oetuaho): Expand this code so that it could generate the gl format info tables as well.
def gl_format_channels(internal_format):
    if internal_format == 'GL_BGR5_A1_ANGLEX':
        return 'bgra'
    if internal_format == 'GL_R11F_G11F_B10F':
        return 'rgb'
    if internal_format == 'GL_RGB5_A1':
        return 'rgba'
    if internal_format.find('GL_RGB10_A2') == 0:
        return 'rgba'

    channels_pattern = re.compile('GL_(COMPRESSED_)?(SIGNED_)?(ETC\d_)?([A-Z]+)')
    match = re.search(channels_pattern, internal_format)
    channels_string = match.group(4)

    if channels_string == 'ALPHA':
        return 'a'
    if channels_string == 'LUMINANCE':
        if (internal_format.find('ALPHA') >= 0):
            return 'la'
        return 'l'
    if channels_string == 'SRGB':
        if (internal_format.find('ALPHA') >= 0):
            return 'rgba'
        return 'rgb'
    if channels_string == 'DEPTH':
        if (internal_format.find('STENCIL') >= 0):
            return 'ds'
        return 'd'
    if channels_string == 'STENCIL':
        return 's'
    return channels_string.lower()

def get_internal_format_initializer(internal_format, angle_format):
    internal_format_initializer = 'nullptr'
    gl_channels = gl_format_channels(internal_format)
    gl_format_no_alpha = gl_channels == 'rgb' or gl_channels == 'l'
    if gl_format_no_alpha and angle_format['channels'] == 'rgba':
        if angle_format['texFormat'] == 'DXGI_FORMAT_BC1_UNORM':
            # BC1 is a special case since the texture data determines whether each block has an alpha channel or not.
            # This if statement is hit by COMPRESSED_RGB_S3TC_DXT1, which is a bit of a mess.
            # TODO(oetuaho): Look into whether COMPRESSED_RGB_S3TC_DXT1 works right in general.
            # Reference: https://www.opengl.org/registry/specs/EXT/texture_compression_s3tc.txt
            pass
        elif 'componentType' not in angle_format:
            raise ValueError('warning: internal format initializer could not be generated and may be needed for ' + internal_format)
        elif angle_format['componentType'] == 'byte_uint':
            internal_format_initializer = 'Initialize4ComponentData<GLubyte, 0x00, 0x00, 0x00, 0x01>'
        elif angle_format['componentType'] == 'byte_unorm':
            internal_format_initializer = 'Initialize4ComponentData<GLubyte, 0x00, 0x00, 0x00, 0xFF>'
        elif angle_format['componentType'] == 'byte_int':
            internal_format_initializer = 'Initialize4ComponentData<GLbyte, 0x00, 0x00, 0x00, 0x01>'
        elif angle_format['componentType'] == 'byte_snorm':
            internal_format_initializer = 'Initialize4ComponentData<GLbyte, 0x00, 0x00, 0x00, 0x7F>'
        elif angle_format['componentType'] == 'half':
            internal_format_initializer = 'Initialize4ComponentData<GLhalf, 0x0000, 0x0000, 0x0000, gl::Float16One>'
        elif angle_format['componentType'] == 'short_uint':
            internal_format_initializer = 'Initialize4ComponentData<GLushort, 0x0000, 0x0000, 0x0000, 0x0001>'
        elif angle_format['componentType'] == 'short_int':
            internal_format_initializer = 'Initialize4ComponentData<GLshort, 0x0000, 0x0000, 0x0000, 0x0001>'
        elif angle_format['componentType'] == 'float':
            internal_format_initializer = 'Initialize4ComponentData<GLfloat, 0x00000000, 0x00000000, 0x00000000, gl::Float32One>'
        elif angle_format['componentType'] == 'int':
            internal_format_initializer = 'Initialize4ComponentData<GLint, 0x00000000, 0x00000000, 0x00000000, 0x00000001>'
        elif angle_format['componentType'] == 'uint':
            internal_format_initializer = 'Initialize4ComponentData<GLuint, 0x00000000, 0x00000000, 0x00000000, 0x00000001>'
        else:
            raise ValueError('warning: internal format initializer could not be generated and may be needed for ' + internal_format)

    return internal_format_initializer

def get_texture_format_item(idx, internal_format, requirements_fn, angle_format_id, angle_format):
    table_data = '';

    internal_format_initializer = get_internal_format_initializer(internal_format, angle_format)

    indent = '            '
    if requirements_fn != None:
        if idx == 0:
            table_data += '            if (' + requirements_fn + '(renderer11DeviceCaps))\n'
        else:
            table_data += '            else if (' + requirements_fn + '(renderer11DeviceCaps))\n'
        table_data += '            {\n'
        indent += '    '

    table_data += indent + 'static const TextureFormat textureFormat(internalFormat,\n'
    table_data += indent + '                                         GetANGLEFormatSet(' + angle_format_id + '),\n'
    table_data += indent + '                                         ' + internal_format_initializer + ');\n'
    table_data += indent + 'return textureFormat;\n'

    if requirements_fn != None:
        table_data += '            }\n'

    return table_data

def parse_json_into_switch_texture_format_string(json_map, json_data):
    table_data = ''
    angle_format_map = {}

    for internal_format_item in sorted(json_map.iteritems()):
        internal_format = internal_format_item[0]
        table_data += '        case ' + internal_format + ':\n'
        table_data += '        {\n'

        if isinstance(json_map[internal_format], basestring):
            angle_format_id = json_map[internal_format]
            table_data += get_texture_format_item(0, internal_format, None, angle_format_id, json_data[angle_format_id])
        else:
            for idx, requirements_map in enumerate(sorted(json_map[internal_format].iteritems())):
                angle_format_id = requirements_map[1]
                table_data += get_texture_format_item(idx, internal_format, requirements_map[0], angle_format_id, json_data[angle_format_id])
            table_data += '            else\n'
            table_data += '            {\n'
            table_data += '                break;\n'
            table_data += '            }\n'

        table_data += '        }\n'

    return table_data

def parse_json_into_switch_angle_format_string(json_data):
    table_data = ''
    for angle_format_item in sorted(json_data.iteritems()):
        table_data += '        case ' + angle_format_item[0] + ':\n'
        angle_format = angle_format_item[1]
        tex_format = angle_format["texFormat"] if "texFormat" in angle_format else "DXGI_FORMAT_UNKNOWN"
        srv_format = angle_format["srvFormat"] if "srvFormat" in angle_format else "DXGI_FORMAT_UNKNOWN"
        rtv_format = angle_format["rtvFormat"] if "rtvFormat" in angle_format else "DXGI_FORMAT_UNKNOWN"
        dsv_format = angle_format["dsvFormat"] if "dsvFormat" in angle_format else "DXGI_FORMAT_UNKNOWN"
        table_data += '        {\n'
        table_data += '            static const DXGIFormatSet formatInfo(' + tex_format + ',\n'
        table_data += '                                                  ' + srv_format + ',\n'
        table_data += '                                                  ' + rtv_format + ',\n'
        table_data += '                                                  ' + dsv_format + ');\n'
        table_data += '            return formatInfo;\n'
        table_data += '        }\n'
    return table_data

def parse_json_into_angle_format_enum_string(json_data):
    enum_data = ''
    index = 0
    for angle_format_item in sorted(json_data.iteritems()):
        if index > 0:
            enum_data += ',\n'
        enum_data += '    ' + angle_format_item[0]
        index += 1
    return enum_data

def reject_duplicate_keys(pairs):
    found_keys = {}
    for key, value in pairs:
        if key in found_keys:
           raise ValueError("duplicate key: %r" % (key,))
        else:
           found_keys[key] = value
    return found_keys

with open('texture_format_map.json') as texture_format_map_file:
    with open('texture_format_data.json') as texture_format_json_file:
        texture_format_map = texture_format_map_file.read()
        texture_format_data = texture_format_json_file.read()
        texture_format_map_file.close()
        texture_format_json_file.close()
        json_map = json.loads(texture_format_map, object_pairs_hook=reject_duplicate_keys)
        json_data = json.loads(texture_format_data, object_pairs_hook=reject_duplicate_keys)

        texture_format_cases = parse_json_into_switch_texture_format_string(json_map, json_data)
        angle_format_cases = parse_json_into_switch_angle_format_string(json_data)
        output_cpp = template_texture_format_table_autogen_cpp.format(texture_format_info_cases=texture_format_cases, angle_format_info_cases=angle_format_cases)
        with open('texture_format_table_autogen.cpp', 'wt') as out_file:
            out_file.write(output_cpp)
            out_file.close()

        enum_data = parse_json_into_angle_format_enum_string(json_data)
        output_h = template_texture_format_table_autogen_h.format(angle_format_enum=enum_data)
        with open('texture_format_table_autogen.h', 'wt') as out_file:
            out_file.write(output_h)
            out_file.close()
