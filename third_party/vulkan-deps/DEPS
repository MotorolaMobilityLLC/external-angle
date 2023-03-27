# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '45405e1d942e7af1a1f2fad94a8b9ddf2600af0d',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '09e60d74f6a1c8deed2c02c998661b2ec7dd712e',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '90547c54e24e01aae41a68124e7a304d0ec11dd0',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'f9f31fa5a903fc4a0c5d5272d9a7781d3ffef319',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '9b9fd871b08110cd8f0b74e721b03213d9cc3081',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'd72476300bedea334aa764c994dd191cb6d7088b',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '211fec7e9af1af7ce13c31885537bc73c4862b23',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '9124f788b7de42a4b2589b7ede812dd887447f0c',
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
