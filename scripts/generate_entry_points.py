#!/usr/bin/python2
#
# Copyright 2017 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# generate_entry_points.py:
#   Generates the OpenGL bindings and entry point layers for ANGLE.

import sys, os, pprint, json
import xml.etree.ElementTree as etree
from datetime import date

# List of supported extensions. Add to this list to enable new extensions
# available in gl.xml.
# TODO(jmadill): Support extensions not in gl.xml.
supported_extensions = sorted([
    # ES1 (statically linked by some tests even if we don't support the extension)
    "GL_OES_point_size_array",
    "GL_OES_query_matrix",
    "GL_OES_matrix_palette",
    "GL_OES_draw_texture",
    # ES2+
    "GL_ANGLE_framebuffer_blit",
    "GL_ANGLE_framebuffer_multisample",
    "GL_ANGLE_instanced_arrays",
    "GL_ANGLE_translated_shader_source",
    "GL_EXT_debug_marker",
    "GL_EXT_discard_framebuffer",
    "GL_EXT_disjoint_timer_query",
    "GL_EXT_draw_buffers",
    "GL_EXT_map_buffer_range",
    "GL_EXT_occlusion_query_boolean",
    "GL_EXT_robustness",
    "GL_EXT_texture_storage",
    "GL_KHR_debug",
    "GL_NV_fence",
    "GL_OES_EGL_image",
    "GL_OES_get_program_binary",
    "GL_OES_mapbuffer",
    "GL_OES_vertex_array_object",
])

# This is a list of exceptions for entry points which don't want to have
# the EVENT macro. This is required for some debug marker entry points.
no_event_marker_exceptions_list = sorted([
    "glPushGroupMarkerEXT",
    "glPopGroupMarkerEXT",
    "glInsertEventMarkerEXT",
])

# Strip these suffixes from Context entry point names. NV is excluded (for now).
strip_suffixes = ["ANGLE", "EXT", "KHR", "OES"]

template_entry_point_header = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gles_{annotation_lower}_autogen.h:
//   Defines the GLES {comment} entry points.

#ifndef LIBGLESV2_ENTRY_POINTS_GLES_{annotation_upper}_AUTOGEN_H_
#define LIBGLESV2_ENTRY_POINTS_GLES_{annotation_upper}_AUTOGEN_H_

{includes}

namespace gl
{{
{entry_points}
}}  // namespace gl

#endif  // LIBGLESV2_ENTRY_POINTS_GLES_{annotation_upper}_AUTOGEN_H_
"""

template_entry_point_source = """// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {data_source_name}.
//
// Copyright {year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gles_{annotation_lower}_autogen.cpp:
//   Defines the GLES {comment} entry points.

{includes}

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
    {event_comment}EVENT("({format_params})"{comma_if_needed}{pass_params});

    Context *context = {context_getter}();
    if (context)
    {{{packed_gl_enum_conversions}
        context->gatherParams<EntryPoint::{name}>({internal_params});

        if (context->skipValidation() || Validate{name}({validate_params}))
        {{
            {return_if_needed}context->{name_lower_no_suffix}({internal_params});
        }}
    }}
{default_return_if_needed}}}
"""

def script_relative(path):
    return os.path.join(os.path.dirname(sys.argv[0]), path)

tree = etree.parse(script_relative('gl.xml'))
root = tree.getroot()
commands = root.find(".//commands[@namespace='GL']")

with open(script_relative('entry_point_packed_gl_enums.json')) as f:
    cmd_packed_gl_enums = json.loads(f.read())

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

def just_the_name_packed(param, reserved_set):
    name = just_the_name(param)
    if name in reserved_set:
        return name + 'Packed'
    else:
        return name

format_dict = {
    "GLbitfield": "0x%X",
    "GLboolean": "%u",
    "GLclampx": "0x%X",
    "GLenum": "0x%X",
    "GLfixed": "0x%X",
    "GLfloat": "%f",
    "GLint": "%d",
    "GLintptr": "%d",
    "GLshort": "%d",
    "GLsizei": "%d",
    "GLsizeiptr": "%d",
    "GLsync": "0x%0.8p",
    "GLubyte": "%d",
    "GLuint": "%u",
    "GLuint64": "%llu",
    "GLDEBUGPROC": "0x%0.8p",
    "GLDEBUGPROCKHR": "0x%0.8p",
    "GLeglImageOES": "0x%0.8p",
}

def param_format_string(param):
    if "*" in param:
        return param + " = 0x%0.8p"
    else:
        type_only = just_the_type(param)
        if type_only not in format_dict:
            raise Exception(type_only + " is not a known type in 'format_dict'")

        return param + " = " + format_dict[type_only]

def default_return_value(cmd_name, return_type):
    if return_type == "void":
        return ""
    return "GetDefaultReturnValue<EntryPoint::" + cmd_name[2:] + ", " + return_type + ">()"

def get_context_getter_function(cmd_name):
    if cmd_name == "glGetError":
        return "GetGlobalContext"
    else:
        return "GetValidGlobalContext"

template_event_comment = """// Don't run an EVENT() macro on the EXT_debug_marker entry points.
    // It can interfere with the debug events being set by the caller.
    // """

def format_entry_point_def(cmd_name, proto, params):
    packed_gl_enums = cmd_packed_gl_enums.get(cmd_name, {})
    internal_params = [just_the_name_packed(param, packed_gl_enums) for param in params]
    packed_gl_enum_conversions = []
    for param in params:
        name = just_the_name(param)
        if name in packed_gl_enums:
            internal_name = name + "Packed"
            internal_type = packed_gl_enums[name]
            packed_gl_enum_conversions += ["\n        " + internal_type + " " + internal_name +" = FromGLenum<" +
                                          internal_type + ">(" + name + ");"]

    pass_params = [just_the_name(param) for param in params]
    format_params = [param_format_string(param) for param in params]
    return_type = proto[:-len(cmd_name)]
    default_return = default_return_value(cmd_name, return_type.strip())
    event_comment = template_event_comment if cmd_name in no_event_marker_exceptions_list else ""
    name_lower_no_suffix = cmd_name[2:3].lower() + cmd_name[3:]

    for suffix in strip_suffixes:
        if name_lower_no_suffix.endswith(suffix):
            name_lower_no_suffix = name_lower_no_suffix[0:-len(suffix)]

    return template_entry_point_def.format(
        name = cmd_name[2:],
        name_lower_no_suffix = name_lower_no_suffix,
        return_type = return_type,
        params = ", ".join(params),
        internal_params = ", ".join(internal_params),
        packed_gl_enum_conversions = "".join(packed_gl_enum_conversions),
        pass_params = ", ".join(pass_params),
        comma_if_needed = ", " if len(params) > 0 else "",
        validate_params = ", ".join(["context"] + internal_params),
        format_params = ", ".join(format_params),
        return_if_needed = "" if default_return == "" else "return ",
        default_return_if_needed = "" if default_return == "" else "\n    return " + default_return + ";\n",
        context_getter = get_context_getter_function(cmd_name),
        event_comment = event_comment)

def path_to(folder, file):
    return os.path.join(script_relative(".."), "src", folder, file)

def get_entry_points(all_commands, gles_commands):
    decls = []
    defs = []
    for command in all_commands:
        proto = command.find('proto')
        cmd_name = proto.find('name').text

        if cmd_name not in gles_commands:
            continue

        param_text = ["".join(param.itertext()) for param in command.findall('param')]
        proto_text = "".join(proto.itertext())
        decls.append(format_entry_point_decl(cmd_name, proto_text, param_text))
        defs.append(format_entry_point_def(cmd_name, proto_text, param_text))

    return decls, defs

def write_file(annotation, comment, template, entry_points, suffix, includes):

    content = template.format(
        script_name = os.path.basename(sys.argv[0]),
        data_source_name = "gl.xml",
        year = date.today().year,
        annotation_lower = annotation.lower(),
        annotation_upper = annotation.upper(),
        comment = comment,
        includes = includes,
        entry_points = entry_points)

    path = path_to("libGLESv2", "entry_points_gles_{}_autogen.{}".format(
        annotation.lower(), suffix))

    with open(path, "w") as out:
        out.write(content)
        out.close()

all_commands = root.findall('commands/command')
all_cmd_names = []

template_header_includes = """#include <GLES{major}/gl{major}{minor}.h>
#include <export.h>"""

template_sources_includes = """#include "libGLESv2/entry_points_gles_{}_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/validationES{}{}.h"
#include "libGLESv2/global_state.h"
"""

# First run through the main GLES entry points.
for major_version, minor_version in [[1, 0], [2, 0], [3, 0], [3, 1]]:
    annotation = "{}_{}".format(major_version, minor_version)
    name_prefix = "GL_ES_VERSION_"
    if major_version == 1:
        name_prefix = "GL_VERSION_ES_CM_"
    comment = annotation.replace("_", ".")
    gles_xpath = ".//feature[@name='{}{}']//command".format(name_prefix, annotation)
    gles_commands = [cmd.attrib['name'] for cmd in root.findall(gles_xpath)]

    # Remove commands that have already been processed
    gles_commands = [cmd for cmd in gles_commands if cmd not in all_cmd_names]

    all_cmd_names += gles_commands

    decls, defs = get_entry_points(all_commands, gles_commands)

    major_if_not_one = major_version if major_version != 1 else ""
    minor_if_not_zero = minor_version if minor_version != 0 else ""

    header_includes = template_header_includes.format(
        major=major_if_not_one, minor=minor_if_not_zero)

    # We include the platform.h header since it undefines the conflicting MemoryBarrier macro.
    if major_version == 3 and minor_version == 1:
        header_includes += "\n#include \"common/platform.h\"\n"

    source_includes = template_sources_includes.format(
        annotation.lower(), major_version,minor_if_not_zero)

    write_file(annotation, comment, template_entry_point_header,
               "\n".join(decls), "h", header_includes)
    write_file(annotation, comment, template_entry_point_source,
               "\n".join(defs), "cpp", source_includes)

# After we finish with the main entry points, we process the extensions.
extension_defs = []
extension_decls = []

# Use a first step to run through the extensions so we can generate them
# in sorted order.
ext_data = {}

for extension in root.findall("extensions/extension"):
    extension_name = extension.attrib['name']
    if not extension_name in supported_extensions:
        continue

    ext_cmd_names = []

    # There's an extra step here to filter out 'api=gl' extensions. This
    # is necessary for handling KHR extensions, which have separate entry
    # point signatures (without the suffix) for desktop GL. Note that this
    # extra step is necessary because of Etree's limited Xpath support.
    for require in extension.findall('require'):
        if 'api' in require.attrib and require.attrib['api'] != 'gles2' and require.attrib['api'] != 'gles1':
            continue

        # Another special case for EXT_texture_storage
        filter_out_comment = "Supported only if GL_EXT_direct_state_access is supported"
        if 'comment' in require.attrib and require.attrib['comment'] == filter_out_comment:
            continue

        extension_commands = require.findall('command')
        ext_cmd_names += [command.attrib['name'] for command in extension_commands]

    ext_data[extension_name] = sorted(ext_cmd_names)

for extension_name, ext_cmd_names in sorted(ext_data.iteritems()):

    # Detect and filter duplicate extensions.
    dupes = []
    for ext_cmd in ext_cmd_names:
        if ext_cmd in all_cmd_names:
            dupes.append(ext_cmd)

    for dupe in dupes:
        ext_cmd_names.remove(dupe)

    all_cmd_names += ext_cmd_names

    decls, defs = get_entry_points(all_commands, ext_cmd_names)

    # Avoid writing out entry points defined by a prior extension.
    for dupe in dupes:
        msg = "// {} is already defined.\n".format(dupe[2:])
        defs.append(msg)

    # Write the extension name as a comment before the first EP.
    comment = "\n// {}".format(extension_name)
    defs.insert(0, comment)
    decls.insert(0, comment)

    extension_defs += defs
    extension_decls += decls

header_includes = template_header_includes.format(
    major="", minor="")
header_includes += """
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
"""

source_includes = template_sources_includes.format("ext", "", "")
source_includes += """
#include "libANGLE/validationES.h"
#include "libANGLE/validationES1.h"
#include "libANGLE/validationES3.h"
#include "libANGLE/validationES31.h"
"""

write_file("ext", "extension", template_entry_point_header,
           "\n".join([item for item in extension_decls]), "h", header_includes)
write_file("ext", "extension", template_entry_point_source,
           "\n".join([item for item in extension_defs]), "cpp", source_includes)

sorted_cmd_names = ["Invalid"] + [cmd[2:] for cmd in sorted(all_cmd_names)]

entry_points_enum = template_entry_points_enum_header.format(
    script_name = os.path.basename(sys.argv[0]),
    data_source_name = "gl.xml",
    year = date.today().year,
    entry_points_list = ",\n".join(["    " + cmd for cmd in sorted_cmd_names]))

entry_points_enum_header_path = path_to("libANGLE", "entry_points_enum_autogen.h")
with open(entry_points_enum_header_path, "w") as out:
    out.write(entry_points_enum)
    out.close()
