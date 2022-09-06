# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': 'a53aa3e94f8b4bf22a6eb6e8a207fe91ab02b989',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': '210a80013067672b52847ec7aa70ff78b2f4d77e',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': '87d5b782bec60822aa878941e6b13c0a9a954c9b',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '5f45f793ae962a84c71a9b7ff434591c57cdad57',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': '9f4c61a31435a7a90a314fc68aeb386c92a09c0f',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'fdfdef6d1b75828c1c3658c867bbbc4adbec956c',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': '1ef7bc1547db9b85bedb5792f958fdcdb5ecd97a',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'b50285d33d6bf47796204dbb7e930fd29696c886',
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
