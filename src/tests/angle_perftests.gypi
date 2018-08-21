# Copyright 2015 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

angle_perf_tests_sources =
[
  "src/tests/perf_tests/ANGLEPerfTest.cpp",
  "src/tests/perf_tests/ANGLEPerfTest.h",
  "src/tests/perf_tests/BlitFramebufferPerf.cpp",
  "src/tests/perf_tests/BindingPerf.cpp",
  "src/tests/perf_tests/BitSetIteratorPerf.cpp",
  "src/tests/perf_tests/BufferSubData.cpp",
  "src/tests/perf_tests/CompilerPerf.cpp",
  "src/tests/perf_tests/DispatchComputePerf.cpp",
  "src/tests/perf_tests/DrawCallPerf.cpp",
  "src/tests/perf_tests/DrawCallPerfParams.cpp",
  "src/tests/perf_tests/DrawCallPerfParams.h",
  "src/tests/perf_tests/DrawElementsPerf.cpp",
  "src/tests/perf_tests/DynamicPromotionPerfTest.cpp",
  "src/tests/perf_tests/EGLInitializePerf.cpp",
  "src/tests/perf_tests/EGLMakeCurrentPerf.cpp",
  "src/tests/perf_tests/ResultPerf.cpp",
  "src/tests/perf_tests/IndexConversionPerf.cpp",
  "src/tests/perf_tests/InstancingPerf.cpp",
  "src/tests/perf_tests/InterleavedAttributeData.cpp",
  "src/tests/perf_tests/LinkProgramPerfTest.cpp",
  "src/tests/perf_tests/MultiviewPerf.cpp",
  "src/tests/perf_tests/PointSprites.cpp",
  "src/tests/perf_tests/TexSubImage.cpp",
  "src/tests/perf_tests/TextureSampling.cpp",
  "src/tests/perf_tests/TexturesPerf.cpp",
  "src/tests/perf_tests/UniformsPerf.cpp",
  "src/tests/perf_tests/third_party/perf/perf_test.cc",
  "src/tests/perf_tests/third_party/perf/perf_test.h",
  "src/tests/test_utils/angle_test_configs.cpp",
  "src/tests/test_utils/angle_test_configs.h",
  "src/tests/test_utils/angle_test_instantiate.cpp",
  "src/tests/test_utils/angle_test_instantiate.h",
  "src/tests/test_utils/draw_call_perf_utils.cpp",
  "src/tests/test_utils/draw_call_perf_utils.h",
]
angle_perf_tests_win_sources =
[
  "src/tests/perf_tests/IndexDataManagerTest.cpp",
]
angle_perf_tests_vulkan_sources =
[
  "src/tests/perf_tests/VulkanPipelineCachePerf.cpp",
]
# Currently Vulkan Command Buffer Perf Tests compile on Android/Linux
angle_perf_tests_vulkan_command_buffer_sources =
[
  "src/tests/perf_tests/VulkanCommandBufferPerf.cpp",
  "src/tests/test_utils/third_party/vulkan_command_buffer_utils.cpp",
  "src/tests/test_utils/third_party/vulkan_command_buffer_utils.h"
]
