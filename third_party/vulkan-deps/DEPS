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
  'spirv_cross_revision': 'ba3e6ffe037e47a17dd233a2e50eb0c0a434bb25',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '36c0c1596225e728bd49abb7ef56a3953e7ed468',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '2eff41e70709de47b84ec8cc70c0db34e7775c82',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '3be1df310be8963c29125c35fce25ee0af12ff70',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '477fb9e188ff7de3181bc44f489eb3171c251405',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '6f57b1fa230f4ba88c34eeed9af31a4257df7fe8',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '620b378993dfbc0837b0be8d6371a7498b48635a',
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
