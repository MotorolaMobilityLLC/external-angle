#!/usr/bin/python
# Copyright 2018 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# gen_vk_internal_shaders.py:
#  Code generation for internal Vulkan shaders. Should be run when an internal
#  shader program is changed, added or removed.
#  Because this script can be slow direct invocation is supported. But before
#  code upload please run scripts/run_code_generation.py.

from datetime import date
import io
import json
import multiprocessing
import os
import platform
import re
import subprocess
import sys

out_file_cpp = 'vk_internal_shaders_autogen.cpp'
out_file_h = 'vk_internal_shaders_autogen.h'
out_file_gni = 'vk_internal_shaders_autogen.gni'

is_windows = platform.system() == 'Windows'
is_linux = platform.system() == 'Linux'

# Templates for the generated files:
template_shader_library_cpp = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {out_file_name}:
//   Pre-generated shader library for the ANGLE Vulkan back-end.

#include "libANGLE/renderer/vulkan/vk_internal_shaders_autogen.h"

namespace rx
{{
namespace vk
{{
namespace
{{
{internal_shader_includes}

// This is SPIR-V binary blob and the size.
struct ShaderBlob
{{
    const uint32_t *code;
    size_t codeSize;
}};

{shader_tables_cpp}

angle::Result GetShader(Context *context,
                        RefCounted<ShaderAndSerial> *shaders,
                        const ShaderBlob *shaderBlobs,
                        size_t shadersCount,
                        uint32_t shaderFlags,
                        RefCounted<ShaderAndSerial> **shaderOut)
{{
    ASSERT(shaderFlags < shadersCount);
    RefCounted<ShaderAndSerial> &shader = shaders[shaderFlags];
    *shaderOut                          = &shader;

    if (shader.get().valid())
    {{
        return angle::Result::Continue;
    }}

    // Create shader lazily. Access will need to be locked for multi-threading.
    const ShaderBlob &shaderCode = shaderBlobs[shaderFlags];
    ASSERT(shaderCode.code != nullptr);

    return InitShaderAndSerial(context, &shader.get(), shaderCode.code, shaderCode.codeSize);
}}
}}  // anonymous namespace


ShaderLibrary::ShaderLibrary()
{{
}}

ShaderLibrary::~ShaderLibrary()
{{
}}

void ShaderLibrary::destroy(VkDevice device)
{{
    {shader_destroy_calls}
}}

{shader_get_functions_cpp}
}}  // namespace vk
}}  // namespace rx
"""

template_shader_library_h = u"""// GENERATED FILE - DO NOT EDIT.
// Generated by {script_name} using data from {input_file_name}
//
// Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// {out_file_name}:
//   Pre-generated shader library for the ANGLE Vulkan back-end.

#ifndef LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_
#define LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_

#include "libANGLE/renderer/vulkan/vk_utils.h"

namespace rx
{{
namespace vk
{{
namespace InternalShader
{{
{shader_variation_definitions}
}}  // namespace InternalShader

class ShaderLibrary final : angle::NonCopyable
{{
  public:
    ShaderLibrary();
    ~ShaderLibrary();

    void destroy(VkDevice device);

    {shader_get_functions_h}

  private:
    {shader_tables_h}
}};
}}  // namespace vk
}}  // namespace rx

#endif  // LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_
"""

template_shader_includes_gni = u"""# GENERATED FILE - DO NOT EDIT.
# Generated by {script_name} using data from {input_file_name}
#
# Copyright {copyright_year} The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# {out_file_name}:
#   List of generated shaders for inclusion in ANGLE's build process.

angle_vulkan_internal_shaders = [
{shaders_list}
]
"""


# Gets the constant variable name for a generated shader.
def get_var_name(output, prefix='k'):
    return prefix + output.replace(".", "_")


# Gets the namespace name given to constants generated from shader_file
def get_namespace_name(shader_file):
    return get_var_name(os.path.basename(shader_file), '')


# Gets the namespace name given to constants generated from shader_file
def get_variation_table_name(shader_file, prefix='k'):
    return get_var_name(os.path.basename(shader_file), prefix) + '_shaders'


# Gets the internal ID string for a particular shader.
def get_shader_id(shader):
    file = os.path.splitext(os.path.basename(shader))[0]
    return file.replace(".", "_")


# Returns the name of the generated SPIR-V file for a shader.
def get_output_path(name):
    return os.path.join('shaders', 'gen', name + ".inc")


# Finds a path to GN's out directory
def get_linux_glslang_exe_path():
    return '../../../../tools/glslang/glslang_validator'


def get_win_glslang_exe_path():
    return get_linux_glslang_exe_path() + '.exe'


def get_glslang_exe_path():
    glslang_exe = get_win_glslang_exe_path() if is_windows else get_linux_glslang_exe_path()
    if not os.path.isfile(glslang_exe):
        raise Exception('Could not find %s' % glslang_exe)
    return glslang_exe


# Generates the code for a shader blob array entry.
def gen_shader_blob_entry(shader):
    var_name = get_var_name(os.path.basename(shader))[0:-4]
    return "{%s, %s}" % (var_name, "sizeof(%s)" % var_name)


def slash(s):
    return s.replace('\\', '/')


def gen_shader_include(shader):
    return '#include "libANGLE/renderer/vulkan/%s"' % slash(shader)


def get_shader_variations(shader):
    variation_file = shader + '.json'
    if not os.path.exists(variation_file):
        # If there is no variation file, assume none.
        return ({}, [])

    with open(variation_file) as fin:
        variations = json.loads(fin.read())
        flags = {}
        enums = []

        for key, value in variations.iteritems():
            if key == "Description":
                continue
            elif key == "Flags":
                flags = value
            elif len(value) > 0:
                enums.append((key, value))

        # sort enums so the ones with the most waste ends up last, reducing the table size
        enums.sort(key=lambda enum: (1 << (len(enum[1]) - 1).bit_length()) / float(len(enum[1])))

        return (flags, enums)


def get_variation_bits(flags, enums):
    flags_bits = len(flags)
    enum_bits = [(len(enum[1]) - 1).bit_length() for enum in enums]
    return (flags_bits, enum_bits)


def next_enum_variation(enums, enum_indices):
    """Loop through indices from [0, 0, ...] to [L0-1, L1-1, ...]
    where Li is len(enums[i]).  The list can be thought of as a number with many
    digits, where each digit is in [0, Li), and this function effectively implements
    the increment operation, with the least-significant digit being the first item."""
    for i in range(len(enums)):
        current = enum_indices[i]
        # if current digit has room, increment it.
        if current + 1 < len(enums[i][1]):
            enum_indices[i] = current + 1
            return True
        # otherwise reset it to 0 and carry to the next digit.
        enum_indices[i] = 0

    # if this is reached, the number has overflowed and the loop is finished.
    return False


compact_newlines_regex = re.compile(r"\n\s*\n", re.MULTILINE)


def cleanup_preprocessed_shader(shader_text):
    return compact_newlines_regex.sub('\n\n', shader_text.strip())


class CompileQueue:

    class AppendPreprocessorOutput:

        def __init__(self, shader_file, preprocessor_args, output_path):
            # Asynchronously launch the preprocessor job.
            self.process = subprocess.Popen(
                preprocessor_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            # Store the file name for output to be appended to.
            self.output_path = output_path
            # Store info for error description.
            self.shader_file = shader_file

        def wait(self, queue):
            (out, err) = self.process.communicate()
            if self.process.returncode == 0:
                # Use unix line endings.
                out = out.replace('\r\n', '\n')
                # Clean up excessive empty lines.
                out = cleanup_preprocessed_shader(out)
                # Comment it out!
                out = '\n'.join([('// ' + line).strip() for line in out.splitlines()])
                # Append preprocessor output to the output file.
                with open(self.output_path, 'ab') as incfile:
                    incfile.write('\n\n// Generated from:\n//\n')
                    incfile.write(out + '\n')
                out = None
            return (out, err, self.process.returncode, None,
                    "Error running preprocessor on " + self.shader_file)

    class CompileToSPIRV:

        def __init__(self, shader_file, shader_basename, variation_string, output_path,
                     compile_args, preprocessor_args):
            # Asynchronously launch the compile job.
            self.process = subprocess.Popen(
                compile_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            # Store info for launching the preprocessor.
            self.preprocessor_args = preprocessor_args
            self.output_path = output_path
            # Store info for job and error description.
            self.shader_file = shader_file
            self.shader_basename = shader_basename
            self.variation_string = variation_string

        def wait(self, queue):
            (out, err) = self.process.communicate()
            if self.process.returncode == 0:
                # Insert the preprocessor job in the queue.
                queue.append(
                    CompileQueue.AppendPreprocessorOutput(self.shader_file, self.preprocessor_args,
                                                          self.output_path))
            # If all the output says is the source file name, don't bother printing it.
            if out.strip() == self.shader_file:
                out = None
            description = self.output_path + ': ' + self.shader_basename + self.variation_string
            return (out, err, self.process.returncode, description,
                    "Error compiling " + self.shader_file)

    def __init__(self):
        # Compile with as many CPU threads are detected.  Once a shader is compiled, another job is
        # automatically added to the queue to append the preprocessor output to the generated file.
        self.queue = []
        self.thread_count = multiprocessing.cpu_count()

    def _wait_first(self, ignore_output=False):
        (out, err, returncode, description, exception_description) = self.queue[0].wait(self.queue)
        self.queue.pop(0)
        if not ignore_output:
            if description:
                print description
            if out and out.strip():
                print out.strip()
            if err and err.strip():
                print err
            if returncode != 0:
                return exception_description
        return None

    # Wait for all pending tasks.  If called after error is detected, ignore_output can be used to
    # make sure errors in later jobs are suppressed to avoid cluttering the output.  This is
    # because the same compile error is likely present in other variations of the same shader and
    # outputting the same error multiple times is not useful.
    def _wait_all(self, ignore_output=False):
        exception_description = None
        while len(self.queue) > 0:
            this_job_exception = self._wait_first(ignore_output)
            # If encountered an error, keep it to be raised, ignoring errors from following jobs.
            if this_job_exception and not ignore_output:
                exception_description = this_job_exception
                ignore_output = True

        return exception_description

    def add_job(self, shader_file, shader_basename, variation_string, output_path, compile_args,
                preprocessor_args):
        # If the queue is full, wait until there is at least one slot available.
        while len(self.queue) >= self.thread_count:
            exception = self._wait_first(False)
            # If encountered an exception, cleanup following jobs and raise it.
            if exception:
                self._wait_all(True)
                raise Exception(exception)

        # Add a compile job
        self.queue.append(
            CompileQueue.CompileToSPIRV(shader_file, shader_basename, variation_string,
                                        output_path, compile_args, preprocessor_args))

    def finish(self):
        exception = self._wait_all(False)
        # If encountered an exception, cleanup following jobs and raise it.
        if exception is not None:
            raise Exception(exception)


# If the option is just a string, that's the name.  Otherwise, it could be
# [ name, arg1, ..., argN ].  In that case, name is option[0] and option[1:] are extra arguments
# that need to be passed to glslang_validator for this variation.
def get_variation_name(option):
    return option if isinstance(option, unicode) else option[0]


def get_variation_args(option):
    return [] if isinstance(option, unicode) else option[1:]


def compile_variation(glslang_path, compile_queue, shader_file, shader_basename, flags, enums,
                      flags_active, enum_indices, flags_bits, enum_bits, output_shaders):

    glslang_args = [glslang_path]

    # generate -D defines and the output file name
    #
    # The variations are given a bit pattern to be able to OR different flags into a variation. The
    # least significant bits are the flags, where there is one bit per flag.  After that, each enum
    # takes up as few bits as needed to count that many enum values.
    variation_bits = 0
    variation_string = ''
    variation_extra_args = []
    for f in range(len(flags)):
        if flags_active & (1 << f):
            flag = flags[f]
            flag_name = get_variation_name(flag)
            variation_extra_args += get_variation_args(flag)
            glslang_args.append('-D' + flag_name + '=1')

            variation_bits |= 1 << f
            variation_string += '|' + flag_name

    current_bit_start = flags_bits

    for e in range(len(enums)):
        enum = enums[e][1][enum_indices[e]]
        enum_name = get_variation_name(enum)
        variation_extra_args += get_variation_args(enum)
        glslang_args.append('-D' + enum_name + '=1')

        variation_bits |= enum_indices[e] << current_bit_start
        current_bit_start += enum_bits[e]
        variation_string += '|' + enum_name

    output_name = '%s.%08X' % (shader_basename, variation_bits)
    output_path = get_output_path(output_name)
    output_shaders.append(output_path)

    if glslang_path is not None:
        glslang_preprocessor_output_args = glslang_args + ['-E']
        glslang_preprocessor_output_args.append(shader_file)  # Input GLSL shader

        glslang_args += variation_extra_args

        glslang_args += ['-V']  # Output mode is Vulkan
        glslang_args += ['--variable-name', get_var_name(output_name)]  # C-style variable name
        glslang_args += ['-o', output_path]  # Output file
        glslang_args.append(shader_file)  # Input GLSL shader

        compile_queue.add_job(shader_file, shader_basename, variation_string, output_path,
                              glslang_args, glslang_preprocessor_output_args)


class ShaderAndVariations:

    def __init__(self, shader_file):
        self.shader_file = shader_file
        (self.flags, self.enums) = get_shader_variations(shader_file)
        get_variation_bits(self.flags, self.enums)
        (self.flags_bits, self.enum_bits) = get_variation_bits(self.flags, self.enums)
        # Maximum index value has all flags set and all enums at max value.
        max_index = (1 << self.flags_bits) - 1
        current_bit_start = self.flags_bits
        for (name, values), bits in zip(self.enums, self.enum_bits):
            max_index |= (len(values) - 1) << current_bit_start
            current_bit_start += bits
        # Minimum array size is one more than the maximum value.
        self.array_len = max_index + 1


def get_variation_definition(shader_and_variation):
    shader_file = shader_and_variation.shader_file
    flags = shader_and_variation.flags
    enums = shader_and_variation.enums
    flags_bits = shader_and_variation.flags_bits
    enum_bits = shader_and_variation.enum_bits
    array_len = shader_and_variation.array_len

    namespace_name = get_namespace_name(shader_file)

    definition = 'namespace %s\n{\n' % namespace_name
    if len(flags) > 0:
        definition += 'enum flags\n{\n'
        definition += ''.join([
            'k%s = 0x%08X,\n' % (get_variation_name(flags[f]), 1 << f) for f in range(len(flags))
        ])
        definition += '};\n'

    current_bit_start = flags_bits

    for e in range(len(enums)):
        enum = enums[e]
        enum_name = enum[0]
        definition += 'enum %s\n{\n' % enum_name
        definition += ''.join([
            'k%s = 0x%08X,\n' % (get_variation_name(enum[1][v]), v << current_bit_start)
            for v in range(len(enum[1]))
        ])
        definition += '};\n'
        current_bit_start += enum_bits[e]

    definition += 'constexpr size_t kArrayLen = 0x%08X;\n' % array_len

    definition += '}  // namespace %s\n' % namespace_name
    return definition


def get_shader_table_h(shader_and_variation):
    shader_file = shader_and_variation.shader_file
    flags = shader_and_variation.flags
    enums = shader_and_variation.enums

    table_name = get_variation_table_name(shader_file, 'm')

    table = 'RefCounted<ShaderAndSerial> %s[' % table_name

    namespace_name = "InternalShader::" + get_namespace_name(shader_file)

    table += '%s::kArrayLen' % namespace_name

    table += '];'
    return table


def get_shader_table_cpp(shader_and_variation):
    shader_file = shader_and_variation.shader_file
    enums = shader_and_variation.enums
    flags_bits = shader_and_variation.flags_bits
    enum_bits = shader_and_variation.enum_bits
    array_len = shader_and_variation.array_len

    # Cache max and mask value of each enum to quickly know when a possible variation is invalid
    enum_maxes = []
    enum_masks = []
    current_bit_start = flags_bits

    for e in range(len(enums)):
        enum_values = enums[e][1]
        enum_maxes.append((len(enum_values) - 1) << current_bit_start)
        enum_masks.append(((1 << enum_bits[e]) - 1) << current_bit_start)
        current_bit_start += enum_bits[e]

    table_name = get_variation_table_name(shader_file)
    var_name = get_var_name(os.path.basename(shader_file))

    table = 'constexpr ShaderBlob %s[] = {\n' % table_name

    for variation in range(array_len):
        # if any variation is invalid, output an empty entry
        if any([(variation & enum_masks[e]) > enum_maxes[e] for e in range(len(enums))]):
            table += '{nullptr, 0}, // 0x%08X\n' % variation
        else:
            entry = '%s_%08X' % (var_name, variation)
            table += '{%s, sizeof(%s)},\n' % (entry, entry)

    table += '};'
    return table


def get_get_function_h(shader_and_variation):
    shader_file = shader_and_variation.shader_file

    function_name = get_var_name(os.path.basename(shader_file), 'get')

    definition = 'angle::Result %s' % function_name
    definition += '(Context *context, uint32_t shaderFlags, RefCounted<ShaderAndSerial> **shaderOut);'

    return definition


def get_get_function_cpp(shader_and_variation):
    shader_file = shader_and_variation.shader_file
    enums = shader_and_variation.enums

    function_name = get_var_name(os.path.basename(shader_file), 'get')
    namespace_name = "InternalShader::" + get_namespace_name(shader_file)
    member_table_name = get_variation_table_name(shader_file, 'm')
    constant_table_name = get_variation_table_name(shader_file)

    definition = 'angle::Result ShaderLibrary::%s' % function_name
    definition += '(Context *context, uint32_t shaderFlags, RefCounted<ShaderAndSerial> **shaderOut)\n{\n'
    definition += 'return GetShader(context, %s, %s, ArraySize(%s), shaderFlags, shaderOut);\n}\n' % (
        member_table_name, constant_table_name, constant_table_name)

    return definition


def get_destroy_call(shader_and_variation):
    shader_file = shader_and_variation.shader_file

    table_name = get_variation_table_name(shader_file, 'm')

    destroy = 'for (RefCounted<ShaderAndSerial> &shader : %s)\n' % table_name
    destroy += '{\nshader.get().destroy(device);\n}'
    return destroy


def shader_path(shader):
    return '"%s"' % slash(shader)


def main():
    # STEP 0: Handle inputs/outputs for run_code_generation.py's auto_script
    shaders_dir = os.path.join('shaders', 'src')
    if not os.path.isdir(shaders_dir):
        raise Exception("Could not find shaders directory")

    print_inputs = len(sys.argv) == 2 and sys.argv[1] == 'inputs'
    print_outputs = len(sys.argv) == 2 and sys.argv[1] == 'outputs'
    # If an argument X is given that's not inputs or outputs, compile shaders that match *X*.
    # This is useful in development to build only the shader of interest.
    shader_files_to_compile = os.listdir(shaders_dir)
    if not (print_inputs or print_outputs or len(sys.argv) < 2):
        shader_files_to_compile = [f for f in shader_files_to_compile if f.find(sys.argv[1]) != -1]

    valid_extensions = ['.vert', '.frag', '.comp']
    input_shaders = sorted([
        os.path.join(shaders_dir, shader)
        for shader in os.listdir(shaders_dir)
        if any([os.path.splitext(shader)[1] == ext for ext in valid_extensions])
    ])
    if print_inputs:
        glslang_binaries = [get_linux_glslang_exe_path(), get_win_glslang_exe_path()]
        glslang_binary_hashes = [path + '.sha1' for path in glslang_binaries]
        print(",".join(input_shaders + glslang_binary_hashes))
        return 0

    # STEP 1: Call glslang to generate the internal shaders into small .inc files.
    # Iterates over the shaders and call glslang with the right arguments.

    glslang_path = None
    if not print_outputs:
        glslang_path = get_glslang_exe_path()

    output_shaders = []

    input_shaders_and_variations = [
        ShaderAndVariations(shader_file) for shader_file in input_shaders
    ]

    compile_queue = CompileQueue()

    for shader_and_variation in input_shaders_and_variations:
        shader_file = shader_and_variation.shader_file
        flags = shader_and_variation.flags
        enums = shader_and_variation.enums
        flags_bits = shader_and_variation.flags_bits
        enum_bits = shader_and_variation.enum_bits

        # an array where each element i is in [0, len(enums[i])),
        # telling which enum is currently selected
        enum_indices = [0] * len(enums)

        output_name = os.path.basename(shader_file)

        while True:
            do_compile = not print_outputs and output_name in shader_files_to_compile
            # a number where each bit says whether a flag is active or not,
            # with values in [0, 2^len(flags))
            for flags_active in range(1 << len(flags)):
                compile_variation(glslang_path if do_compile else None, compile_queue, shader_file,
                                  output_name, flags, enums, flags_active, enum_indices,
                                  flags_bits, enum_bits, output_shaders)

            if not next_enum_variation(enums, enum_indices):
                break

    output_shaders = sorted(output_shaders)
    outputs = output_shaders + [out_file_cpp, out_file_h]

    if print_outputs:
        print(','.join(outputs))
        return 0

    compile_queue.finish()

    # STEP 2: Consolidate the .inc files into an auto-generated cpp/h library.
    with open(out_file_cpp, 'w') as outfile:
        includes = "\n".join([gen_shader_include(shader) for shader in output_shaders])
        shader_tables_cpp = '\n'.join(
            [get_shader_table_cpp(s) for s in input_shaders_and_variations])
        shader_destroy_calls = '\n'.join(
            [get_destroy_call(s) for s in input_shaders_and_variations])
        shader_get_functions_cpp = '\n'.join(
            [get_get_function_cpp(s) for s in input_shaders_and_variations])

        outcode = template_shader_library_cpp.format(
            script_name=__file__,
            copyright_year=date.today().year,
            out_file_name=out_file_cpp,
            input_file_name='shaders/src/*',
            internal_shader_includes=includes,
            shader_tables_cpp=shader_tables_cpp,
            shader_destroy_calls=shader_destroy_calls,
            shader_get_functions_cpp=shader_get_functions_cpp)
        outfile.write(outcode)
        outfile.close()

    with open(out_file_h, 'w') as outfile:
        shader_variation_definitions = '\n'.join(
            [get_variation_definition(s) for s in input_shaders_and_variations])
        shader_get_functions_h = '\n'.join(
            [get_get_function_h(s) for s in input_shaders_and_variations])
        shader_tables_h = '\n'.join([get_shader_table_h(s) for s in input_shaders_and_variations])
        outcode = template_shader_library_h.format(
            script_name=__file__,
            copyright_year=date.today().year,
            out_file_name=out_file_h,
            input_file_name='shaders/src/*',
            shader_variation_definitions=shader_variation_definitions,
            shader_get_functions_h=shader_get_functions_h,
            shader_tables_h=shader_tables_h)
        outfile.write(outcode)
        outfile.close()

    # STEP 3: Create a gni file with the generated files.
    with io.open(out_file_gni, 'w', newline='\n') as outfile:
        outcode = template_shader_includes_gni.format(
            script_name=__file__,
            copyright_year=date.today().year,
            out_file_name=out_file_gni,
            input_file_name='shaders/src/*',
            shaders_list=',\n'.join([shader_path(shader) for shader in output_shaders]))
        outfile.write(outcode)
        outfile.close()

    return 0


if __name__ == '__main__':
    sys.exit(main())
