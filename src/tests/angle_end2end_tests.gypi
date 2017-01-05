# Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# This .gypi describes all of the sources and dependencies to build a
# unified "angle_end2end_tests" target, which contains all of the
# tests that exercise the ANGLE implementation. It requires a parent
# target to include this gypi in an executable target containing a
# gtest harness in a main.cpp.

{
    # Everything below this is duplicated in the GN build.
    # If you change anything also change angle/src/tests/BUILD.gn
    'variables':
    {
        'angle_end2end_tests_sources':
        [
            '<(angle_path)/src/tests/gl_tests/BindGeneratesResourceTest.cpp',
            '<(angle_path)/src/tests/gl_tests/BindUniformLocationTest.cpp',
            '<(angle_path)/src/tests/gl_tests/BlendMinMaxTest.cpp',
            '<(angle_path)/src/tests/gl_tests/BlitFramebufferANGLETest.cpp',
            '<(angle_path)/src/tests/gl_tests/BufferDataTest.cpp',
            '<(angle_path)/src/tests/gl_tests/BuiltinVariableTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ClearTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ColorMaskTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ComputeShaderTest.cpp',
            '<(angle_path)/src/tests/gl_tests/CopyCompressedTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/CopyTexImageTest.cpp',
            '<(angle_path)/src/tests/gl_tests/CopyTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/CubeMapTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DebugMarkerTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DebugTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DepthStencilFormatsTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DiscardFramebufferEXTTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DrawBuffersTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DrawElementsTest.cpp',
            '<(angle_path)/src/tests/gl_tests/DXT1CompressedTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ETCTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/FenceSyncTests.cpp',
            '<(angle_path)/src/tests/gl_tests/FramebufferMixedSamplesTest.cpp',
            '<(angle_path)/src/tests/gl_tests/FramebufferRenderMipmapTest.cpp',
            '<(angle_path)/src/tests/gl_tests/FramebufferTest.cpp',
            '<(angle_path)/src/tests/gl_tests/GLSLTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ImageTest.cpp',
            '<(angle_path)/src/tests/gl_tests/IncompleteTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/IndexBufferOffsetTest.cpp',
            '<(angle_path)/src/tests/gl_tests/IndexedPointsTest.cpp',
            '<(angle_path)/src/tests/gl_tests/InstancingTest.cpp',
            '<(angle_path)/src/tests/gl_tests/LineLoopTest.cpp',
            '<(angle_path)/src/tests/gl_tests/MaxTextureSizeTest.cpp',
            '<(angle_path)/src/tests/gl_tests/MipmapTest.cpp',
            '<(angle_path)/src/tests/gl_tests/MultisampleCompatibilityTest.cpp',
            '<(angle_path)/src/tests/gl_tests/media/pixel.inl',
            '<(angle_path)/src/tests/gl_tests/PackUnpackTest.cpp',
            '<(angle_path)/src/tests/gl_tests/PathRenderingTest.cpp',
            '<(angle_path)/src/tests/gl_tests/PbufferTest.cpp',
            '<(angle_path)/src/tests/gl_tests/PBOExtensionTest.cpp',
            '<(angle_path)/src/tests/gl_tests/PointSpritesTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ProvokingVertexTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ObjectAllocationTest.cpp',
            '<(angle_path)/src/tests/gl_tests/OcclusionQueriesTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ProgramBinaryTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ReadPixelsTest.cpp',
            '<(angle_path)/src/tests/gl_tests/RendererTest.cpp',
            '<(angle_path)/src/tests/gl_tests/RobustClientMemoryTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SimpleOperationTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SixteenBppTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SRGBFramebufferTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SRGBTextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/StateChangeTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SwizzleTest.cpp',
            '<(angle_path)/src/tests/gl_tests/SyncQueriesTest.cpp',
            '<(angle_path)/src/tests/gl_tests/TextureTest.cpp',
            '<(angle_path)/src/tests/gl_tests/TimerQueriesTest.cpp',
            '<(angle_path)/src/tests/gl_tests/TransformFeedbackTest.cpp',
            '<(angle_path)/src/tests/gl_tests/UniformBufferTest.cpp',
            '<(angle_path)/src/tests/gl_tests/UniformTest.cpp',
            '<(angle_path)/src/tests/gl_tests/UnpackAlignmentTest.cpp',
            '<(angle_path)/src/tests/gl_tests/UnpackRowLength.cpp',
            '<(angle_path)/src/tests/gl_tests/VertexAttributeTest.cpp',
            '<(angle_path)/src/tests/gl_tests/ViewportTest.cpp',
            '<(angle_path)/src/tests/gl_tests/WebGLCompatibilityTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLContextCompatibilityTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLContextSharingTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLQueryContextTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLRobustnessTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLSanityCheckTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLSurfaceTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLVulkanEXTTest.cpp',
            '<(angle_path)/src/tests/test_utils/ANGLETest.cpp',
            '<(angle_path)/src/tests/test_utils/ANGLETest.h',
            '<(angle_path)/src/tests/test_utils/angle_test_configs.cpp',
            '<(angle_path)/src/tests/test_utils/angle_test_configs.h',
            '<(angle_path)/src/tests/test_utils/angle_test_instantiate.cpp',
            '<(angle_path)/src/tests/test_utils/angle_test_instantiate.h',
            '<(angle_path)/src/tests/test_utils/gl_raii.h',
        ],
        'angle_end2end_tests_win_sources':
        [
            '<(angle_path)/src/tests/gl_tests/D3DImageFormatConversionTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLDeviceTest.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLPresentPathD3D11Test.cpp',
            '<(angle_path)/src/tests/egl_tests/EGLStreamTest.cpp',
            # TODO(cwallez) for Linux, requires a portable implementation of threads
            '<(angle_path)/src/tests/egl_tests/EGLThreadTest.cpp',
            '<(angle_path)/src/tests/egl_tests/media/yuvtest.inl',
        ],
        'angle_end2end_tests_x11_sources':
        [
            '<(angle_path)/src/tests/egl_tests/EGLX11VisualTest.cpp',
        ],
    },
    'dependencies':
    [
        '<(angle_path)/src/angle.gyp:angle_image_util',
        # We use the D3D11 config for enabling Debug runtime error logging.
        '<(angle_path)/src/angle.gyp:libANGLE_d3d11_config',
        # This lets us filter test configs more intelligently.
        '<(angle_path)/src/angle.gyp:libANGLE_renderer_config',
        '<(angle_path)/src/angle.gyp:libEGL',
        '<(angle_path)/src/angle.gyp:libGLESv2',
        '<(angle_path)/src/tests/tests.gyp:angle_test_support',
        '<(angle_path)/util/util.gyp:angle_util',
    ],
    'include_dirs':
    [
        '<(angle_path)/include',
        '<(angle_path)/src/tests'
    ],
    'sources':
    [
        '<@(angle_end2end_tests_sources)',
    ],
    'conditions':
    [
        ['OS=="win"',
        {
            'sources':
            [
                '<@(angle_end2end_tests_win_sources)',
            ],
        }],
        ['use_x11==1',
        {
            'sources':
            [
                '<@(angle_end2end_tests_x11_sources)',
            ],
        }],
    ]
}
