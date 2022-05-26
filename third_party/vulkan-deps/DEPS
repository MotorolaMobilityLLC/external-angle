# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '2f5bc0b7414f5d063b9c2fcf231469aec1e549d3',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'd0c8dc30450351321e611b2888a48f8410226a4c',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'b765c355f488837ca4c77980ba69484f3ff277f5',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '98340ec500e92a534dc8384d5c45d2f488e40f6a',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '33d4dd987fc8fc6475ff9ca2b4f0c3cc6e793337',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '5aa2ee48c9da55ff6682ff2e5802d60eb52dcf1f',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'c5d859fbe327f1b673a7f3825f3a570862b5d590',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'c08c0860bd3a7d5f76f8c31568f509025d236934',
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
