# This file is used to manage Vulkan dependencies for several repos. It is
# used by gclient to determine what version of each dependency to check out, and
# where.

# Avoids the need for a custom root variable.
use_relative_paths = True

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  # Current revision of glslang, the Khronos SPIRV compiler.
  'glslang_revision': '57e25195ebff3355f4463735f9bb820442caeab3',

  # Current revision of spirv-cross, the Khronos SPIRV cross compiler.
  'spirv_cross_revision': 'fe5a0aa72fd855d03f16ff7b93de95722be5a9c8',

  # Current revision fo the SPIRV-Headers Vulkan support library.
  'spirv_headers_revision': 'b8047fbe45f426f5918fadc67e8408f5b108c3c9',

  # Current revision of SPIRV-Tools for Vulkan.
  'spirv_tools_revision': '05c839ca018b7aa2f9278ef83f86be972f655e9b',

  # Current revision of Khronos Vulkan-Headers.
  'vulkan_headers_revision': 'd99496fcb1f4aecbeb25c1e70eda0cdee7e1eba5',

  # Current revision of Khronos Vulkan-Loader.
  'vulkan_loader_revision': 'a72d5bc3eb413b53ff9d5165afc6ded9fcf8e115',

  # Current revision of Khronos Vulkan-Tools.
  'vulkan_tools_revision': 'd15ff77bda1ef895ea5cf23d19472b7442e878cb',

  # Current revision of Khronos Vulkan-ValidationLayers.
  'vulkan_validation_revision': 'd18a6f03cf944c7b1ddf4931b999abe139f5c42f',
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
