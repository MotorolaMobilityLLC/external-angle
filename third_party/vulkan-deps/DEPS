# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'e3bca2add61a83cc87b0db199c1fbd45690dbf0b',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '0c8a79b0b5c71e1fa59d20577589b5cb58ccb4f1',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '46b7918218d02b678b9405da538928a0f2c286bb',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '46492aa45ae5da92eb1ec8a8051d6a4a98df70af',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '8ba8294c86d0e99fcb457bedbd573dd678ccc9b3',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': '191e2614953908c5829d7826a5ac5265e4ad2a03',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'a9d2badae2349c6806116a4dd72b76dbeeeec017',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': '75a5d5459f576e49ea3f53bf6ee0bcc7e5f30f1b',
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
