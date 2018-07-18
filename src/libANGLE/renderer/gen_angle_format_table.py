#!/usr/bin/python
# Copyright 2016 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_angle_format_table.py:
#  Code generation for ANGLE format map.
#

import angle_format
from datetime import date
import json
import math
import pprint
import re
import sys

template_autogen_h = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ANGLE format enumeration.

namespace angle
{{

enum class FormatID
{{
{angle_format_enum}
}};

constexpr uint32_t kNumANGLEFormats = {num_angle_formats};

}}  // namespace angle
"""

template_autogen_inl = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ANGLE Format table:
//   Queries for typed format information from the ANGLE format enum.

#include "libANGLE/renderer/Format.h"

#include "image_util/copyimage.h"
#include "image_util/generatemip.h"
#include "image_util/loadimage.h"

namespace angle
{{

static constexpr rx::FastCopyFunctionMap::Entry BGRAEntry = {{GL_RGBA, GL_UNSIGNED_BYTE,
                                                             CopyBGRA8ToRGBA8}};
static constexpr rx::FastCopyFunctionMap BGRACopyFunctions = {{&BGRAEntry, 1}};
static constexpr rx::FastCopyFunctionMap NoCopyFunctions;

constexpr Format g_formatInfoTable[] = {{
    // clang-format off
    {{ FormatID::NONE, GL_NONE, GL_NONE, nullptr, NoCopyFunctions, nullptr, nullptr, GL_NONE, 0, 0, 0, 0, 0, 0, 0, false }},
{angle_format_info_cases}    // clang-format on
}};

// static
FormatID Format::InternalFormatToID(GLenum internalFormat)
{{
    switch (internalFormat)
    {{
{angle_format_switch}
    }}
}}

// static
const Format &Format::Get(FormatID id)
{{
    return g_formatInfoTable[static_cast<size_t>(id)];
}}

}}  // namespace angle
"""

def get_channel_struct(angle_format):
    if 'bits' not in angle_format or angle_format['bits'] is None:
        return None
    if 'BLOCK' in angle_format['id']:
        return None
    bits = angle_format['bits']
    if 'D' in bits or 'S' in bits:
        return None

    if 'channelStruct' in angle_format:
        return angle_format['channelStruct']

    struct_name = ''
    for channel in angle_format['channels']:
        if channel == 'r':
            struct_name += 'R{}'.format(bits['R'])
        if channel == 'g':
            struct_name += 'G{}'.format(bits['G'])
        if channel == 'b':
            struct_name += 'B{}'.format(bits['B'])
        if channel == 'a':
            struct_name += 'A{}'.format(bits['A'])
        if channel == 'l':
            struct_name += 'L{}'.format(bits['L'])
    if angle_format['componentType'] == 'float':
        struct_name += 'F'
    if angle_format['componentType'] == 'int' or angle_format['componentType'] == 'snorm':
        struct_name += 'S'
    return struct_name

def get_mip_generation_function(angle_format):
    channel_struct = get_channel_struct(angle_format)
    if channel_struct == None or "BLOCK" in angle_format["id"]:
        return 'nullptr'
    return 'GenerateMip<' + channel_struct + '>'

def get_color_read_write_component_type(angle_format):
    component_type_map = {
        'uint': 'GLuint',
        'int': 'GLint',
        'unorm': 'GLfloat',
        'snorm': 'GLfloat',
        'float': 'GLfloat'
    }
    return component_type_map[angle_format['componentType']]

def get_color_read_function(angle_format):
    channel_struct = get_channel_struct(angle_format)
    if channel_struct == None:
        return 'nullptr'
    read_component_type = get_color_read_write_component_type(angle_format)
    return 'ReadColor<' + channel_struct + ', '+ read_component_type + '>'

def get_color_write_function(angle_format):
    channel_struct = get_channel_struct(angle_format)
    if channel_struct == None:
        return 'nullptr'
    write_component_type = get_color_read_write_component_type(angle_format)
    return 'WriteColor<' + channel_struct + ', '+ write_component_type + '>'


format_entry_template = """    {{ FormatID::{id}, {glInternalFormat}, {fboImplementationInternalFormat}, {mipGenerationFunction}, {fastCopyFunctions}, {colorReadFunction}, {colorWriteFunction}, {namedComponentType}, {R}, {G}, {B}, {A}, {D}, {S}, {pixelBytes}, {isBlock} }},
"""

def get_named_component_type(component_type):
    if component_type == "snorm":
        return "GL_SIGNED_NORMALIZED"
    elif component_type == "unorm":
        return "GL_UNSIGNED_NORMALIZED"
    elif component_type == "float":
        return "GL_FLOAT"
    elif component_type == "uint":
        return "GL_UNSIGNED_INT"
    elif component_type == "int":
        return "GL_INT"
    elif component_type == "none":
        return "GL_NONE"
    else:
        raise ValueError("Unknown component type for " + component_type)

def json_to_table_data(format_id, json, angle_to_gl):

    table_data = ""

    parsed = {
        "id": format_id,
        "fastCopyFunctions": "NoCopyFunctions",
    }

    for k, v in json.iteritems():
        parsed[k] = v

    if "glInternalFormat" not in parsed:
        parsed["glInternalFormat"] = angle_to_gl[format_id]

    if "fboImplementationInternalFormat" not in parsed:
        parsed["fboImplementationInternalFormat"] = parsed["glInternalFormat"]

    if "componentType" not in parsed:
        parsed["componentType"] = angle_format.get_component_type(format_id)

    if "channels" not in parsed:
        parsed["channels"] = angle_format.get_channels(format_id)

    if "bits" not in parsed:
        parsed["bits"] = angle_format.get_bits(format_id)

    # Derived values.
    parsed["mipGenerationFunction"] = get_mip_generation_function(parsed)
    parsed["colorReadFunction"] = get_color_read_function(parsed)
    parsed["colorWriteFunction"] = get_color_write_function(parsed)

    for channel in angle_format.kChannels:
        if parsed["bits"] != None and channel in parsed["bits"]:
            parsed[channel] = parsed["bits"][channel]
        else:
            parsed[channel] = "0"

    parsed["namedComponentType"] = get_named_component_type(parsed["componentType"])

    if format_id == "B8G8R8A8_UNORM":
        parsed["fastCopyFunctions"] = "BGRACopyFunctions"

    sum_of_bits = 0
    for channel in angle_format.kChannels:
        sum_of_bits += int(parsed[channel])
    parsed["pixelBytes"] = sum_of_bits / 8
    parsed["isBlock"] = "true" if format_id.endswith("_BLOCK") else "false"

    return format_entry_template.format(**parsed)

def parse_angle_format_table(all_angle, json_data, angle_to_gl):
    table_data = ''
    for format_id in sorted(all_angle):
        if format_id != "NONE":
            format_info = json_data[format_id] if format_id in json_data else {}
            table_data += json_to_table_data(format_id, format_info, angle_to_gl)

    return table_data

def gen_enum_string(all_angle):
    enum_data = '    NONE'
    for format_id in sorted(all_angle):
        if format_id == 'NONE':
            continue
        enum_data += ',\n    ' + format_id
    return enum_data

case_template = """        case {gl_format}:
            return FormatID::{angle_format};
"""

def gen_map_switch_string(gl_to_angle):
    switch_data = '';
    for gl_format in sorted(gl_to_angle.keys()):
        angle_format = gl_to_angle[gl_format]
        switch_data += case_template.format(
            gl_format=gl_format,
            angle_format=angle_format)
    switch_data += "        default:\n"
    switch_data += "            return FormatID::NONE;"
    return switch_data;

gl_to_angle = angle_format.load_forward_table('angle_format_map.json')
angle_to_gl = angle_format.load_inverse_table('angle_format_map.json')
data_source_name = 'angle_format_data.json'
json_data = angle_format.load_json(data_source_name)
all_angle = angle_to_gl.keys()

angle_format_cases = parse_angle_format_table(
    all_angle, json_data, angle_to_gl)
switch_data = gen_map_switch_string(gl_to_angle)
output_cpp = template_autogen_inl.format(
    script_name = sys.argv[0],
    copyright_year = date.today().year,
    angle_format_info_cases = angle_format_cases,
    angle_format_switch = switch_data,
    data_source_name = data_source_name)
with open('Format_table_autogen.cpp', 'wt') as out_file:
    out_file.write(output_cpp)
    out_file.close()

enum_data = gen_enum_string(all_angle)
num_angle_formats = len(all_angle)
output_h = template_autogen_h.format(
    script_name = sys.argv[0],
    copyright_year = date.today().year,
    angle_format_enum = enum_data,
    data_source_name = data_source_name,
    num_angle_formats = num_angle_formats)
with open('FormatID_autogen.inc', 'wt') as out_file:
    out_file.write(output_h)
    out_file.close()
