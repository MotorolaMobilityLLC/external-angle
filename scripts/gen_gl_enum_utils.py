#!/usr/bin/python
#
# Copyright 2019 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_gl_enum_utils.py:
#   Generates GLenum value to string mapping for ANGLE
#   NOTE: don't run this script directly. Run scripts/run_code_generation.py.

import sys
import os
import re
from datetime import date
from collections import namedtuple

import registry_xml

template_gl_enums_header = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// gl_enum_utils_autogen.h:
//   mapping of GLenum value to string.

# ifndef LIBANGLE_GL_ENUM_UTILS_AUTOGEN_H_
# define LIBANGLE_GL_ENUM_UTILS_AUTOGEN_H_

#include <string>

namespace gl
{{

enum class GLenumGroup {{
    {gl_enum_groups}
}};


const char *GLenumToString(GLenumGroup enumGroup, unsigned int value);

std::string GLbitfieldToString(GLenumGroup enumGroup, unsigned int value);

}}

# endif  // LIBANGLE_GL_ENUM_UTILS_AUTOGEN_H_
"""

template_gl_enums_source = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// gl_enum_utils_autogen.cpp:
//   mapping of GLenum value to string.

#include "libANGLE/gl_enum_utils_autogen.h"

#include <sstream>

#include "common/debug.h"
#include "common/bitset_utils.h"

namespace gl
{{

const char *GLenumToString(GLenumGroup enumGroup, unsigned int value) {{
    switch (enumGroup) {{
        {gl_enums_value_to_string_table}
        default:
            UNREACHABLE();
            return "EnumUnknown";
    }}
}}


std::string GLbitfieldToString(GLenumGroup enumGroup, unsigned int value) {{
    std::stringstream st;

    const angle::BitSet<32> bitSet(value);
    bool first = true;
    for (const auto index : bitSet)
    {{
        if (!first)
        {{
            st << " | ";
        }}
        first = false;

        unsigned int mask = 1u << index;
        st << GLenumToString(enumGroup, mask);
    }}

    return st.str();
}}

}}

"""

template_enum_group_case = """case GLenumGroup::{group_name}: {{
    switch (value) {{
        {inner_group_cases}
        default:
            return "EnumUnknown";
    }}
}}
"""

template_enum_value_to_string_case = """case {value}: return {name};"""

export_apis = ['gles2']
export_extensions = registry_xml.supported_extensions

trivial_gl_enums = {'GL_FALSE', 'GL_TRUE', 'GL_NO_ERROR', 'GL_TIMEOUT_IGNORED', 'GL_INVALID_INDEX'}


def dump_value_to_string_mapping(gl_enum_in_groups, exporting_enums):
    exporting_groups = list()
    for group_name, inner_mapping in gl_enum_in_groups.iteritems():
        string_value_pairs = list(
            filter(lambda x: x[0] in exporting_enums, inner_mapping.iteritems()))
        if not string_value_pairs:
            continue

        # sort according values
        string_value_pairs.sort(key=lambda x: (x[1], x[0]))

        # remove all duplicate values from the pairs list
        # some value may have more than one GLenum mapped to them, such as:
        #     GL_DRAW_FRAMEBUFFER_BINDING and GL_FRAMEBUFFER_BINDING
        #     GL_BLEND_EQUATION_RGB and GL_BLEND_EQUATION
        # it is safe to output either one of them, for simplity here just
        # choose the shorter one which comes first in the sorted list
        exporting_string_value_pairs = list()
        for index, pair in enumerate(string_value_pairs):
            if index == 0 or pair[1] != string_value_pairs[index - 1][1]:
                exporting_string_value_pairs.append(pair)

        inner_code_block = "\n".join([
            template_enum_value_to_string_case.format(
                value=hex(value),
                name='"%s"' % name,
            ) for name, value in exporting_string_value_pairs
        ])

        exporting_groups.append((group_name, inner_code_block))

    return "\n".join([
        template_enum_group_case.format(
            group_name=group_name,
            inner_group_cases=inner_code_block,
        ) for group_name, inner_code_block in sorted(exporting_groups, key=lambda x: x[0])
    ])


def main(header_output_path, source_output_path):
    xml = registry_xml.RegistryXML('gl.xml', 'gl_angle_ext.xml')

    # build a map from GLenum name to its value
    all_gl_enums = dict()
    for enums_node in xml.root.findall('enums'):
        for enum in enums_node.findall('enum'):
            name = enum.attrib['name']
            value = int(enum.attrib['value'], base=16)
            all_gl_enums[name] = value

    # Parse groups of GLenums to build a {group, name} -> value mapping.
    gl_enum_in_groups = dict()
    enums_has_group = set()
    for enums_group_node in xml.root.findall('groups/group'):
        group_name = enums_group_node.attrib['name']
        if group_name not in gl_enum_in_groups:
            gl_enum_in_groups[group_name] = dict()

        for enum_node in enums_group_node.findall('enum'):
            enum_name = enum_node.attrib['name']
            enums_has_group.add(enum_name)
            gl_enum_in_groups[group_name][enum_name] = all_gl_enums[enum_name]

    # Find relevant GLenums according to enabled APIs and extensions.
    exporting_enums = set()
    for api in export_apis:
        xpath = ".//feature[@api='%s']//require//enum" % api
        for enum_tag in xml.root.findall(xpath):
            enum_name = enum_tag.attrib['name']
            exporting_enums.add(enum_name)

    for extension in export_extensions:
        xpath = ".//extensions//extension[@name='%s']//require//enum" % extension
        for enum_tag in xml.root.findall(xpath):
            enum_name = enum_tag.attrib['name']
            exporting_enums.add(enum_name)

    for enum in trivial_gl_enums:
        if enum in exporting_enums:
            exporting_enums.remove(enum)

    # For enums that do not have a group, add them to a default group
    default_group_name = registry_xml.default_enum_group_name
    gl_enum_in_groups[default_group_name] = dict()
    default_group = gl_enum_in_groups[default_group_name]
    for enum_name in exporting_enums:
        if enum_name not in enums_has_group:
            default_group[enum_name] = all_gl_enums[enum_name]

    # Write GLenum groups into the header file.
    header_content = template_gl_enums_header.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name="gl.xml and gl_angle_ext.xml",
        year=date.today().year,
        gl_enum_groups=',\n'.join(sorted(gl_enum_in_groups.iterkeys())))

    with open(header_output_path, 'w') as f:
        f.write(header_content)

    # Write mapping to source file
    gl_enums_value_to_string_table = dump_value_to_string_mapping(gl_enum_in_groups,
                                                                  exporting_enums)
    source_content = template_gl_enums_source.format(
        script_name=os.path.basename(sys.argv[0]),
        data_source_name="gl.xml and gl_angle_ext.xml",
        year=date.today().year,
        gl_enums_value_to_string_table=gl_enums_value_to_string_table,
    )

    source_output_path = registry_xml.script_relative(source_output_path)
    with open(source_output_path, 'w') as f:
        f.write(source_content)

    return 0


if __name__ == '__main__':
    inputs = [
        'gl.xml',
        'gl_angle_ext.xml',
    ]

    gl_enum_utils_autogen_base_path = '../src/libANGLE/gl_enum_utils_autogen'
    outputs = [
        gl_enum_utils_autogen_base_path + '.h',
        gl_enum_utils_autogen_base_path + '.cpp',
    ]

    if len(sys.argv) > 1:
        if sys.argv[1] == 'inputs':
            print ','.join(inputs)
        elif sys.argv[1] == 'outputs':
            print ','.join(outputs)
    else:
        sys.exit(
            main(
                registry_xml.script_relative(outputs[0]),
                registry_xml.script_relative(outputs[1])))
