# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'b40f87f1d3ee11051a3ada1f874ee7473e2edf65',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'ddaa2da6295c456e8f3b65e4a9e026a115e65627',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '87d5b782bec60822aa878941e6b13c0a9a954c9b',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '11d0d162279b7cd19f82dac3934149dd97a3a42c',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '5177b119bbdf463b7b909855a83230253c2d8b68',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '3090fc12bd202eeb6792a59480a4217a250cb9a4',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '5b4f2218195eaebf8aa19f870ff7b1ee0064ac60',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '221bb37645c72db356277aa1353af4e07a75b677',
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
