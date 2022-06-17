# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'bffcf209cb67f718bd8faafd43d0379f943c116f',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '197a273fd494321157f40a962c51b5fa8c9c3581',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '36c0c1596225e728bd49abb7ef56a3953e7ed468',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '76ebfb989f9de24b54930a36096c6daa3656627c',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'ec9b96aae53e152f6812e66fa43757c1256369a0',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '71e43122c90f19aca9c387cb43903a0d2e002b08',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '2661f654ad5df0e02ae04f6bdbe9be51864c8d6a',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'd667189bc865d6f502cd21f5d5cf786195c0487f',
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
