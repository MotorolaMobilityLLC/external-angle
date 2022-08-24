# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '10423ec659d301a0ff2daac8bbf38980abf27590',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '61c603f3baa5270e04bcfb6acf83c654e3c57679',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '0bcc624926a25a2a273d07877fd25a6ff5ba1cfb',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '3c1a14b2b609ae5a352e39ef6b5baf8f64c32ec7',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '715673702f5b18ffb8e5832e67cf731468d32ac6',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '40faec799ce6b17f46f4bf28ce81782a1bafbbb0',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '439026106ac98679e5961a499790327a8bf8f1d6',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '55f77c5de1f76866e03da60bb1b76a8f3242b632',
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
