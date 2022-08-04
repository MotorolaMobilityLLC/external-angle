# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'adf7bf0113ba99fb8e49b23ba7f30c6ee277d14b',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '0cccd0a65a67f33922f8d0742b5930fd15353fa7',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '0bcc624926a25a2a273d07877fd25a6ff5ba1cfb',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '08c542d344c697142b1bbea469b2b4152fa1c074',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '2b55157592bf4c639b76cc16d64acaef565cc4b5',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'd4801c93c599053e2c7f297906ea65144aff370a',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '8ac3b50e9d2f4aa11339c4b6f68038862b282971',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '3a10ae8223cab09fecca3e9ed4a7d675916095a7',
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
