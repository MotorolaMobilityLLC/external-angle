# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'ed257e2bdf34fa2c33946ab120915cd6e038b83d',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'c77b09b57c27837dc2d41aa371ed3d236ce9ce47',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '1d31a100405cf8783ca7a31e31cdd727c9fc54c3',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '9c6a925c87d4c6e203e440ecc8a57018e5bb8c4b',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'bf3b3fb14e088c189be88edfc70f514b7d679656',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '82d4232f0f348f66582dd4d5ac15cdb449e08ca1',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'ce45337c51ed53e6f1b337aa746a5a96c5018f86',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '1e422524e79b2cab9948d42e16b2d1fdaab9a71f',
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
