#!/usr/bin/python
#
# Copyright 2017 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# generate_entry_points.py:
#   Generates the OpenGL bindings and entry point layers for ANGLE.

import sys, os, pprint
import xml.etree.ElementTree as etree
from datetime import date

def script_relative(path):
    return os.path.join(os.path.dirname(sys.argv[0]), path)

tree = etree.parse(script_relative('gl.xml'))
root = tree.getroot()

gles2_xpath = ".//feature[@name='GL_ES_VERSION_2_0']//command"
gles2_commands = [cmd.attrib['name'] for cmd in root.findall(gles2_xpath)]

template_entry_point_header = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gles_{major_version}_{minor_version}_autogen.h:
//   Defines the GLES {major_version}.{minor_version} entry points.

#ifndef LIBGLESV2_ENTRYPOINTSGLES{major_version}{minor_version}_AUTOGEN_H_
#define LIBGLESV2_ENTRYPOINTSGLES{major_version}{minor_version}_AUTOGEN_H_

#include <GLES2/gl{major_version}.h>
#include <export.h>

namespace gl
{{
{entry_points}
}}  // namespace gl

#endif  // LIBGLESV2_ENTRYPOINTSGLES{major_version}{minor_version}_AUTOGEN_H_
"""

template_entry_point_source = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gles_{major_version}_{minor_version}_autogen.cpp:
//   Defines the GLES {major_version}.{minor_version} entry points.

#include "libANGLE/Context.h"
#include "libANGLE/validationES2.h"
#include "libGLESv2/global_state.h"

namespace gl
{{
{entry_points}}}  // namespace gl
"""

template_entry_points_enum_header = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_enum_autogen.h:
//   Defines the GLES entry points enumeration.

#ifndef LIBGLESV2_ENTRYPOINTSENUM_AUTOGEN_H_
#define LIBGLESV2_ENTRYPOINTSENUM_AUTOGEN_H_

namespace gl
{{
enum class EntryPoint
{{
{entry_points_list}
}};
}}  // namespace gl
#endif  // LIBGLESV2_ENTRY_POINTS_ENUM_AUTOGEN_H_
"""

template_entry_point_decl = """ANGLE_EXPORT {return_type}GL_APIENTRY {name}({params});"""

template_entry_point_def = """{return_type}GL_APIENTRY {name}({params})
{{
    EVENT("({format_params})"{comma_if_needed}{pass_params});

    Context *context = {context_getter}();
    if (context)
    {{
        context->gatherParams<EntryPoint::{name}>({pass_params});

        if (context->skipValidation() || Validate{name}({validate_params}))
        {{
            {return_if_needed}context->{name_lower}({pass_params});
        }}
    }}
{default_return_if_needed}}}
"""

commands = root.find(".//commands[@namespace='GL']")
entry_point_decls_gles_2_0 = []
entry_point_defs_gles_2_0 = []
cmd_names = []

def format_entry_point_decl(cmd_name, proto, params):
    return template_entry_point_decl.format(
        name = cmd_name[2:],
        return_type = proto[:-len(cmd_name)],
        params = ", ".join(params))

def type_name_sep_index(param):
    space = param.rfind(" ")
    pointer = param.rfind("*")
    return max(space, pointer)

def just_the_type(param):
    return param[:type_name_sep_index(param)]

def just_the_name(param):
    return param[type_name_sep_index(param)+1:]

format_dict = {
    "GLbitfield": "0x%X",
    "GLboolean": "%u",
    "GLenum": "0x%X",
    "GLfloat": "%f",
    "GLint": "%d",
    "GLintptr": "%d",
    "GLsizei": "%d",
    "GLsizeiptr": "%d",
    "GLuint": "%d"
}

def param_format_string(param):
    if "*" in param:
        return param + " = 0x%0.8p"
    else:
        return param + " = " + format_dict[just_the_type(param)]

def default_return_value(return_type):
    if return_type == "void":
        return ""
    elif return_type == "GLenum" or return_type == "GLint" or return_type == "GLuint":
        return "0"
    elif return_type == "GLboolean":
        return "GL_FALSE"
    elif "*" in return_type:
        return "nullptr"
    else:
        print(return_type)

def get_context_getter_function(cmd_name):
    if cmd_name == "glGetError":
        return "GetGlobalContext"
    else:
        return "GetValidGlobalContext"

def format_entry_point_def(cmd_name, proto, params):
    pass_params = [just_the_name(param) for param in params]
    format_params = [param_format_string(param) for param in params]
    return_type = proto[:-len(cmd_name)]
    default_return = default_return_value(return_type.strip())
    return template_entry_point_def.format(
        name = cmd_name[2:],
        name_lower = cmd_name[2:3].lower() + cmd_name[3:],
        return_type = return_type,
        params = ", ".join(params),
        pass_params = ", ".join(pass_params),
        comma_if_needed = ", " if len(params) > 0 else "",
        validate_params = ", ".join(["context"] + pass_params),
        format_params = ", ".join(format_params),
        return_if_needed = "" if default_return == "" else "return ",
        default_return_if_needed = "" if default_return == "" else "\n    return " + default_return + ";\n",
        context_getter = get_context_getter_function(cmd_name))

for cmd_name in gles2_commands:
    command_xpath = "command/proto[name='" + cmd_name + "']/.."
    command = commands.find(command_xpath)
    params = ["".join(param.itertext()) for param in command.findall("./param")]
    proto = "".join(command.find("./proto").itertext())
    cmd_names += [cmd_name]
    entry_point_decls_gles_2_0 += [format_entry_point_decl(cmd_name, proto, params)]
    entry_point_defs_gles_2_0 += [format_entry_point_def(cmd_name, proto, params)]

gles_2_0_header = template_entry_point_header.format(
    script_name = os.path.basename(sys.argv[0]),
    data_source_name = "gl.xml",
    year = date.today().year,
    major_version = 2,
    minor_version = 0,
    entry_points = "\n".join(entry_point_decls_gles_2_0))

gles_2_0_source = template_entry_point_source.format(
    script_name = os.path.basename(sys.argv[0]),
    data_source_name = "gl.xml",
    year = date.today().year,
    major_version = 2,
    minor_version = 0,
    entry_points = "\n".join(entry_point_defs_gles_2_0))

# TODO(jmadill): Remove manually added entry points.
manual_cmd_names = ["Invalid"] + [cmd[2:] for cmd in cmd_names] + ["DrawElementsInstanced", "DrawRangeElements", "DrawElementsInstancedANGLE"]
entry_points_enum = template_entry_points_enum_header.format(
    script_name = os.path.basename(sys.argv[0]),
    data_source_name = "gl.xml",
    year = date.today().year,
    entry_points_list = ",\n".join(["    " + cmd for cmd in manual_cmd_names]))

def path_to(folder, file):
    return os.path.join(script_relative(".."), "src", folder, file)

gles_2_0_header_path = path_to("libGLESv2", "entry_points_gles_2_0_autogen.h")
gles_2_0_source_path = path_to("libGLESv2", "entry_points_gles_2_0_autogen.cpp")
entry_points_enum_header_path = path_to("libANGLE", "entry_points_enum_autogen.h")

with open(gles_2_0_header_path, "w") as out:
    out.write(gles_2_0_header)
    out.close()

with open(gles_2_0_source_path, "w") as out:
    out.write(gles_2_0_source)
    out.close()

with open(entry_points_enum_header_path, "w") as out:
    out.write(entry_points_enum)
    out.close()
