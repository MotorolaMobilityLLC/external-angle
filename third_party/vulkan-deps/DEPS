# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '9b20b25138bfe916173c9341075b996be14baa69',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'e9cc6403341baf0edd430a4027b074d0a06b782f',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'eddd4dfc930f1374a70797460240a501c7d333f7',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': 'df2aad68b98279412494a6d449bd71b6756e699b',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'e005e1f8175d006adc3676b40ac3dd2212961a68',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'a11162fcaca808eb91c0fa4fbcce99bbcd5d3be2',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '05c6171c04df6f3747f1c9ab6e7b50ef3256ac03',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '0965e77eb083b8b4becf01cd8aa39284e56e6338',
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
