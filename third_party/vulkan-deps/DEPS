# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'b8955549ef3c5c247573573ffbeb0ebde857529a',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'fc9bee27f445644635e83ef111ef54944bb6e3af',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'cfbe4feef20c3c0628712c2792624f0221e378ac',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '25ad5e19f193429b737433d5f6151062ddbc1680',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '8a397558c4d2a4bf9e64e900c45a7e65664c32b2',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '4be91725abb01e8004be966203b95a181c06e1a0',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'db7475424c5deed3a8d2acf1b5022ad4accf206f',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'c827791afe7bbf9f45ff1255545987386c5c9226',
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
