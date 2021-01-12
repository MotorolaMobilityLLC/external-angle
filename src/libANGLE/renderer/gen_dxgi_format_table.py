#!/usr/bin/python
# Copyright 2016 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_dxgi_format_table.py:
#  Code generation for DXGI format map.
#  NOTE: don't run this script directly. Run scripts/run_code_generation.py.

import sys
import angle_format

template_cpp = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DXGI format info:
//   Determining metadata about a DXGI format.

#include "libANGLE/renderer/Format.h"

using namespace angle;

namespace rx
{{

namespace d3d11
{{

GLenum GetComponentType(DXGI_FORMAT dxgiFormat)
{{
    switch (dxgiFormat)
    {{
{component_type_cases}        default:
            break;
    }}

    UNREACHABLE();
    return GL_NONE;
}}

}}  // namespace d3d11

namespace d3d11_angle
{{

const Format &GetFormat(DXGI_FORMAT dxgiFormat)
{{
    switch (dxgiFormat)
    {{
{format_cases}        default:
            break;
    }}

    UNREACHABLE();
    return Format::Get(FormatID::NONE);
}}

}}  // namespace d3d11_angle

}}  // namespace rx
"""

template_format_case = """        case DXGI_FORMAT_{dxgi_format}:
            return {result};
"""

template_undefined_case = """        case DXGI_FORMAT_{dxgi_format}:
            break;
"""


def format_case(dxgi_format, result):
    return template_format_case.format(dxgi_format=dxgi_format, result=result)


def undefined_case(dxgi_format):
    return template_undefined_case.format(dxgi_format=dxgi_format)


def main():

    # auto_script parameters.
    if len(sys.argv) > 1:
        inputs = [
            'angle_format.py',
            'angle_format_map.json',
            'dxgi_format_data.json',
        ]
        outputs = ['dxgi_format_map_autogen.cpp']

        if sys.argv[1] == 'inputs':
            print ','.join(inputs)
        elif sys.argv[1] == 'outputs':
            print ','.join(outputs)
        else:
            print('Invalid script parameters')
            return 1
        return 0

    component_cases = ""
    format_cases = ""

    input_data = 'dxgi_format_data.json'

    dxgi_map = angle_format.load_json(input_data)

    types = {
        'SNORM': 'GL_SIGNED_NORMALIZED',
        'UNORM': 'GL_UNSIGNED_NORMALIZED',
        'SINT': 'GL_INT',
        'UINT': 'GL_UNSIGNED_INT',
        'FLOAT': 'GL_FLOAT',
        'SHAREDEXP': 'GL_FLOAT'
    }

    all_angle = angle_format.get_all_angle_formats()

    for dxgi_format, a_format in sorted(dxgi_map.iteritems()):

        found = [ctype in dxgi_format for ctype in types.keys()]
        count = reduce((lambda a, b: int(a) + int(b)), found)

        component_type = 'GL_NONE'

        if count == 1:
            gltype = next(gltype for ctype, gltype in types.iteritems() if ctype in dxgi_format)
            component_cases += format_case(dxgi_format, gltype)
        else:
            component_cases += undefined_case(dxgi_format)

        if a_format == "":
            a_format = dxgi_format

        if a_format in all_angle:
            a_format = "Format::Get(FormatID::" + a_format + ")"
            format_cases += format_case(dxgi_format, a_format)
        else:
            format_cases += undefined_case(dxgi_format)

    with open('dxgi_format_map_autogen.cpp', 'wt') as out_file:
        output_cpp = template_cpp.format(
            script_name=sys.argv[0],
            data_source_name=input_data,
            component_type_cases=component_cases,
            format_cases=format_cases)
        out_file.write(output_cpp)
        out_file.close()
    return 0


if __name__ == '__main__':
    sys.exit(main())
