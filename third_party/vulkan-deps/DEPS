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
  'spirv_cross_revision': '4ec1fb0aa9dc136887a1a43d0c12579b0dc72db9',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '0e994ee9c4d4118ae56a7bdb4a7517b6443d2b81',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '0b8426346dfe4fe439ebad557d13f57320fdce95',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'aa18f182ebba65438b1cfdbd571f020bb2e34d04',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '6524b598f6c649c4b1881f7cd266d58779169fea',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '078d44e4664b7efa0b6c96ebced1995c4425d57a',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '89749bc34ed08444bc79fa645be2a2d8eea001bb',
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
