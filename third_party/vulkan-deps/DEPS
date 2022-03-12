# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '538231d8b46c22474a558671f89f80b25fcec72d',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '0b51794f0142a3124f4e351cfc0616a48268ba97',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '0e994ee9c4d4118ae56a7bdb4a7517b6443d2b81',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '0741f427381db53068fe23fb69cf2573f3984e23',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '2c45218b9008dd80f6004b419777758e6459ac16',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '42d5db3f59d6e6f843a8fd4e469127358f5ba13b',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '795bad232dd3651c042f61c6f929143aa4654204',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '09227446c8d3a6bc1f7814adee401573cdcc8c0f',
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
