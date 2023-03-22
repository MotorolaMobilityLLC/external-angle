# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '14e5a04e70057972eef8a40df422e30a3b70e4b5',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '763dbe14abc116744cfa385bfe6e83bc89eefd64',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '1feaf4414eb2b353764d01d88f8aa4bcc67b60db',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '90f6a2875fe606dc5f375e8c7da0af30f29bad06',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'fa204df59c6caea6b9be3cf0754a88cd89056a87',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '889e6b7223f00e8e97742e482d05db5b962ed7ae',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'f196c8d3cafcaf7e628b7b76a799c940999ee984',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '8b4a4eb257f88e69eadbf30974680bf8cb6d9b84',
}

deps = {
  'glslang/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/glslang@{glslang_revision}',
  },

  'spirv-cross/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Cross@{spirv_cross_revision}',
  },

  'spirv-headers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Headers@{spirv_headers_revision}',
  },

  'spirv-tools/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/SPIRV-Tools@{spirv_tools_revision}',
  },

  'vulkan-headers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Headers@{vulkan_headers_revision}',
  },

  'vulkan-loader/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Loader@{vulkan_loader_revision}',
  },

  'vulkan-tools/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-Tools@{vulkan_tools_revision}',
  },

  'vulkan-validation-layers/src': {
    'url': '{chromium_git}/external/github.com/KhronosGroup/Vulkan-ValidationLayers@{vulkan_validation_revision}',
  },
}
