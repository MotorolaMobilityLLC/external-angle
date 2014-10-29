# Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
    'variables':
    {
        # These file lists are shared with the GN build.
        'angle_libangle_sources':
        [
            '../include/EGL/egl.h',
            '../include/EGL/eglext.h',
            '../include/EGL/eglplatform.h',
            '../include/GLES2/gl2.h',
            '../include/GLES2/gl2ext.h',
            '../include/GLES2/gl2platform.h',
            '../include/GLES3/gl3.h',
            '../include/GLES3/gl3ext.h',
            '../include/GLES3/gl3platform.h',
            '../include/GLSLANG/ShaderLang.h',
            '../include/GLSLANG/ShaderVars.h',
            '../include/KHR/khrplatform.h',
            '../include/angle_gl.h',
            'common/RefCountObject.cpp',
            'common/RefCountObject.h',
            'common/angleutils.cpp',
            'common/angleutils.h',
            'common/blocklayout.cpp',
            'common/blocklayout.h',
            'common/debug.cpp',
            'common/debug.h',
            'common/event_tracer.cpp',
            'common/event_tracer.h',
            'common/features.h',
            'common/mathutil.cpp',
            'common/mathutil.h',
            'common/platform.h',
            'common/NativeWindow.h',
            'common/tls.cpp',
            'common/tls.h',
            'common/utilities.cpp',
            'common/utilities.h',
            'common/version.h',
            'libGLESv2/BinaryStream.h',
            'libGLESv2/Buffer.cpp',
            'libGLESv2/Buffer.h',
            'libGLESv2/Caps.cpp',
            'libGLESv2/Caps.h',
            'libGLESv2/Constants.h',
            'libGLESv2/Context.cpp',
            'libGLESv2/Context.h',
            'libGLESv2/Error.cpp',
            'libGLESv2/Error.h',
            'libGLESv2/Fence.cpp',
            'libGLESv2/Fence.h',
            'libGLESv2/Float16ToFloat32.cpp',
            'libGLESv2/Framebuffer.cpp',
            'libGLESv2/Framebuffer.h',
            'libGLESv2/FramebufferAttachment.cpp',
            'libGLESv2/FramebufferAttachment.h',
            'libGLESv2/HandleAllocator.cpp',
            'libGLESv2/HandleAllocator.h',
            'libGLESv2/ImageIndex.h',
            'libGLESv2/ImageIndex.cpp',
            'libGLESv2/Program.cpp',
            'libGLESv2/Program.h',
            'libGLESv2/ProgramBinary.cpp',
            'libGLESv2/ProgramBinary.h',
            'libGLESv2/Query.cpp',
            'libGLESv2/Query.h',
            'libGLESv2/Renderbuffer.cpp',
            'libGLESv2/Renderbuffer.h',
            'libGLESv2/ResourceManager.cpp',
            'libGLESv2/ResourceManager.h',
            'libGLESv2/Sampler.cpp',
            'libGLESv2/Sampler.h',
            'libGLESv2/Shader.cpp',
            'libGLESv2/Shader.h',
            'libGLESv2/State.cpp',
            'libGLESv2/State.h',
            'libGLESv2/Texture.cpp',
            'libGLESv2/Texture.h',
            'libGLESv2/TransformFeedback.cpp',
            'libGLESv2/TransformFeedback.h',
            'libGLESv2/Uniform.cpp',
            'libGLESv2/Uniform.h',
            'libGLESv2/VertexArray.cpp',
            'libGLESv2/VertexArray.h',
            'libGLESv2/VertexAttribute.cpp',
            'libGLESv2/VertexAttribute.h',
            'libGLESv2/angletypes.cpp',
            'libGLESv2/angletypes.h',
            'libGLESv2/formatutils.cpp',
            'libGLESv2/formatutils.h',
            'libGLESv2/main.cpp',
            'libGLESv2/main.h',
            'libGLESv2/queryconversions.cpp',
            'libGLESv2/queryconversions.h',
            'libGLESv2/renderer/BufferImpl.h',
            'libGLESv2/renderer/FenceImpl.h',
            'libGLESv2/renderer/Image.cpp',
            'libGLESv2/renderer/Image.h',
            'libGLESv2/renderer/IndexRangeCache.cpp',
            'libGLESv2/renderer/IndexRangeCache.h',
            'libGLESv2/renderer/ProgramImpl.cpp',
            'libGLESv2/renderer/ProgramImpl.h',
            'libGLESv2/renderer/QueryImpl.h',
            'libGLESv2/renderer/RenderbufferImpl.h',
            'libGLESv2/renderer/RenderbufferImpl.cpp',
            'libGLESv2/renderer/Renderer.cpp',
            'libGLESv2/renderer/Renderer.h',
            'libGLESv2/renderer/RenderTarget.h',
            'libGLESv2/renderer/ShaderExecutable.h',
            'libGLESv2/renderer/ShaderImpl.h',
            'libGLESv2/renderer/SwapChain.h',
            'libGLESv2/renderer/TextureImpl.h',
            'libGLESv2/renderer/TransformFeedbackImpl.h',
            'libGLESv2/renderer/VertexArrayImpl.h',
            'libGLESv2/renderer/Workarounds.h',
            'libGLESv2/renderer/copyimage.cpp',
            'libGLESv2/renderer/copyimage.h',
            'libGLESv2/renderer/copyimage.inl',
            'libGLESv2/renderer/copyvertex.h',
            'libGLESv2/renderer/copyvertex.inl',
            'libGLESv2/renderer/generatemip.h',
            'libGLESv2/renderer/generatemip.inl',
            'libGLESv2/renderer/imageformats.h',
            'libGLESv2/renderer/loadimage.cpp',
            'libGLESv2/renderer/loadimage.h',
            'libGLESv2/renderer/loadimage.inl',
            'libGLESv2/renderer/loadimageSSE2.cpp',
            'libGLESv2/renderer/vertexconversion.h',
            'libGLESv2/resource.h',
            'libGLESv2/validationES.cpp',
            'libGLESv2/validationES.h',
            'libGLESv2/validationES2.cpp',
            'libGLESv2/validationES2.h',
            'libGLESv2/validationES3.cpp',
            'libGLESv2/validationES3.h',
            'third_party/murmurhash/MurmurHash3.cpp',
            'third_party/murmurhash/MurmurHash3.h',
            'third_party/systeminfo/SystemInfo.cpp',
            'third_party/systeminfo/SystemInfo.h',
        ],
        'angle_libangle_win_sources':
        [
            # TODO(kbr): port NativeWindow to other EGL platforms.
            'common/win32/NativeWindow.cpp',
        ],
        'angle_libangle_winrt_sources':
        [
            'common/winrt/CoreWindowNativeWindow.cpp',
            'common/winrt/CoreWindowNativeWindow.h',
            'common/winrt/IInspectableNativeWindow.cpp',
            'common/winrt/IInspectableNativeWindow.h',
        ],
        'angle_d3d_shared_sources':
        [
            'libGLESv2/renderer/d3d/BufferD3D.cpp',
            'libGLESv2/renderer/d3d/BufferD3D.h',
            'libGLESv2/renderer/d3d/DynamicHLSL.cpp',
            'libGLESv2/renderer/d3d/DynamicHLSL.h',
            'libGLESv2/renderer/d3d/HLSLCompiler.cpp',
            'libGLESv2/renderer/d3d/HLSLCompiler.h',
            'libGLESv2/renderer/d3d/ImageD3D.cpp',
            'libGLESv2/renderer/d3d/ImageD3D.h',
            'libGLESv2/renderer/d3d/IndexBuffer.cpp',
            'libGLESv2/renderer/d3d/IndexBuffer.h',
            'libGLESv2/renderer/d3d/IndexDataManager.cpp',
            'libGLESv2/renderer/d3d/IndexDataManager.h',
            'libGLESv2/renderer/d3d/MemoryBuffer.cpp',
            'libGLESv2/renderer/d3d/MemoryBuffer.h',
            'libGLESv2/renderer/d3d/ProgramD3D.cpp',
            'libGLESv2/renderer/d3d/ProgramD3D.h',
            'libGLESv2/renderer/d3d/RenderbufferD3D.cpp',
            'libGLESv2/renderer/d3d/RenderbufferD3D.h',
            'libGLESv2/renderer/d3d/ShaderD3D.cpp',
            'libGLESv2/renderer/d3d/ShaderD3D.h',
            'libGLESv2/renderer/d3d/TextureD3D.cpp',
            'libGLESv2/renderer/d3d/TextureD3D.h',
            'libGLESv2/renderer/d3d/TextureStorage.cpp',
            'libGLESv2/renderer/d3d/TextureStorage.h',
            'libGLESv2/renderer/d3d/TransformFeedbackD3D.cpp',
            'libGLESv2/renderer/d3d/TransformFeedbackD3D.h',
            'libGLESv2/renderer/d3d/VertexBuffer.cpp',
            'libGLESv2/renderer/d3d/VertexBuffer.h',
            'libGLESv2/renderer/d3d/VertexDataManager.cpp',
            'libGLESv2/renderer/d3d/VertexDataManager.h',
        ],
        'angle_d3d9_sources':
        [
            'libGLESv2/renderer/d3d/d3d9/Blit9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Blit9.h',
            'libGLESv2/renderer/d3d/d3d9/Buffer9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Buffer9.h',
            'libGLESv2/renderer/d3d/d3d9/Fence9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Fence9.h',
            'libGLESv2/renderer/d3d/d3d9/formatutils9.cpp',
            'libGLESv2/renderer/d3d/d3d9/formatutils9.h',
            'libGLESv2/renderer/d3d/d3d9/Image9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Image9.h',
            'libGLESv2/renderer/d3d/d3d9/IndexBuffer9.cpp',
            'libGLESv2/renderer/d3d/d3d9/IndexBuffer9.h',
            'libGLESv2/renderer/d3d/d3d9/Query9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Query9.h',
            'libGLESv2/renderer/d3d/d3d9/Renderer9.cpp',
            'libGLESv2/renderer/d3d/d3d9/Renderer9.h',
            'libGLESv2/renderer/d3d/d3d9/renderer9_utils.cpp',
            'libGLESv2/renderer/d3d/d3d9/renderer9_utils.h',
            'libGLESv2/renderer/d3d/d3d9/RenderTarget9.cpp',
            'libGLESv2/renderer/d3d/d3d9/RenderTarget9.h',
            'libGLESv2/renderer/d3d/d3d9/ShaderCache.h',
            'libGLESv2/renderer/d3d/d3d9/ShaderExecutable9.cpp',
            'libGLESv2/renderer/d3d/d3d9/shaders/compiled/componentmaskps.h',
            'libGLESv2/renderer/d3d/d3d9/shaders/compiled/flipyvs.h',
            'libGLESv2/renderer/d3d/d3d9/shaders/compiled/luminanceps.h',
            'libGLESv2/renderer/d3d/d3d9/shaders/compiled/passthroughps.h',
            'libGLESv2/renderer/d3d/d3d9/shaders/compiled/standardvs.h',
            'libGLESv2/renderer/d3d/d3d9/SwapChain9.cpp',
            'libGLESv2/renderer/d3d/d3d9/SwapChain9.h',
            'libGLESv2/renderer/d3d/d3d9/TextureStorage9.cpp',
            'libGLESv2/renderer/d3d/d3d9/TextureStorage9.h',
            'libGLESv2/renderer/d3d/d3d9/VertexArray9.h',
            'libGLESv2/renderer/d3d/d3d9/VertexBuffer9.cpp',
            'libGLESv2/renderer/d3d/d3d9/VertexBuffer9.h',
            'libGLESv2/renderer/d3d/d3d9/VertexDeclarationCache.cpp',
            'libGLESv2/renderer/d3d/d3d9/VertexDeclarationCache.h',
        ],
        'angle_d3d11_sources':
        [
            'libGLESv2/renderer/d3d/d3d11/Blit11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Blit11.h',
            'libGLESv2/renderer/d3d/d3d11/Buffer11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Buffer11.h',
            'libGLESv2/renderer/d3d/d3d11/Clear11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Clear11.h',
            'libGLESv2/renderer/d3d/d3d11/Fence11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Fence11.h',
            'libGLESv2/renderer/d3d/d3d11/formatutils11.cpp',
            'libGLESv2/renderer/d3d/d3d11/formatutils11.h',
            'libGLESv2/renderer/d3d/d3d11/Image11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Image11.h',
            'libGLESv2/renderer/d3d/d3d11/IndexBuffer11.cpp',
            'libGLESv2/renderer/d3d/d3d11/IndexBuffer11.h',
            'libGLESv2/renderer/d3d/d3d11/InputLayoutCache.cpp',
            'libGLESv2/renderer/d3d/d3d11/InputLayoutCache.h',
            'libGLESv2/renderer/d3d/d3d11/PixelTransfer11.cpp',
            'libGLESv2/renderer/d3d/d3d11/PixelTransfer11.h',
            'libGLESv2/renderer/d3d/d3d11/Query11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Query11.h',
            'libGLESv2/renderer/d3d/d3d11/Renderer11.cpp',
            'libGLESv2/renderer/d3d/d3d11/Renderer11.h',
            'libGLESv2/renderer/d3d/d3d11/renderer11_utils.cpp',
            'libGLESv2/renderer/d3d/d3d11/renderer11_utils.h',
            'libGLESv2/renderer/d3d/d3d11/RenderStateCache.cpp',
            'libGLESv2/renderer/d3d/d3d11/RenderStateCache.h',
            'libGLESv2/renderer/d3d/d3d11/RenderTarget11.cpp',
            'libGLESv2/renderer/d3d/d3d11/RenderTarget11.h',
            'libGLESv2/renderer/d3d/d3d11/ShaderExecutable11.cpp',
            'libGLESv2/renderer/d3d/d3d11/ShaderExecutable11.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_gs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4f.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4i.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_ps_4ui.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/buffertotexture11_vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearfloat11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearfloat11vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearsint11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearsint11vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearuint11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/clearuint11vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthrough2d11vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthrough3d11gs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthrough3d11vs.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughdepth2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughlum2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughlum3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughlumalpha2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughlumalpha3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr2di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr2dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr3di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughr3dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg2di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg2dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg3di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrg3dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb2di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb2dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb3di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgb3dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba2d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba2di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba2dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba3d11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba3di11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/passthroughrgba3dui11ps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlef2darrayps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlef2dps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlef3dps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlei2darrayps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlei2dps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzlei3dps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzleui2darrayps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzleui2dps.h',
            'libGLESv2/renderer/d3d/d3d11/shaders/compiled/swizzleui3dps.h',
            'libGLESv2/renderer/d3d/d3d11/SwapChain11.cpp',
            'libGLESv2/renderer/d3d/d3d11/SwapChain11.h',
            'libGLESv2/renderer/d3d/d3d11/TextureStorage11.cpp',
            'libGLESv2/renderer/d3d/d3d11/TextureStorage11.h',
            'libGLESv2/renderer/d3d/d3d11/VertexArray11.h',
            'libGLESv2/renderer/d3d/d3d11/VertexBuffer11.cpp',
            'libGLESv2/renderer/d3d/d3d11/VertexBuffer11.h',
        ]
    },
    # Everything below this is duplicated in the GN build. If you change
    # anything also change angle/BUILD.gn
    'targets':
    [
        {
            'target_name': 'libANGLE',
            #TODO(jamdill/geofflang): support shared
            'type': 'static_library',
            'dependencies': [ 'translator', 'commit_id', ],
            'includes': [ '../build/common_defines.gypi', ],

            'include_dirs':
            [
                '.',
                '../include',
                'libGLESv2',
            ],
            'sources':
            [
                '<@(angle_libangle_sources)',
            ],
            'defines':
            [
                'GL_APICALL=',
                'GL_GLEXT_PROTOTYPES=',
                'EGLAPI=',
                'ANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES={ "d3dcompiler_46.dll", "d3dcompiler_43.dll" }',
            ],
            'direct_dependent_settings':
            {
                'include_dirs':
                [
                    '.',
                    '../include',
                    'libGLESv2',
                ],
                'defines':
                [
                    'GL_APICALL=',
                    'GL_GLEXT_PROTOTYPES=',
                    'EGLAPI=',
                    'ANGLE_PRELOADED_D3DCOMPILER_MODULE_NAMES={ "d3dcompiler_46.dll", "d3dcompiler_43.dll" }',
                ],
            },
            'conditions':
            [
                ['angle_enable_d3d9==1 or angle_enable_d3d11==1',
                {
                    'sources':
                    [
                        '<@(angle_d3d_shared_sources)',
                    ],
                }],
                ['angle_enable_d3d9==1',
                {
                    'sources':
                    [
                        '<@(angle_d3d9_sources)',
                    ],
                    'defines':
                    [
                        'ANGLE_ENABLE_D3D9',
                    ],
                    'link_settings':
                    {
                        'msvs_settings':
                        {
                            'VCLinkerTool':
                            {
                                'AdditionalDependencies':
                                [
                                    'd3d9.lib',
                                ]
                            }
                        },
                    },
                }],
                ['angle_enable_d3d11==1',
                {
                    'sources':
                    [
                        '<@(angle_d3d11_sources)',
                    ],
                    'defines':
                    [
                        'ANGLE_ENABLE_D3D11',
                    ],
                    'link_settings':
                    {
                        'msvs_settings':
                        {
                            'VCLinkerTool':
                            {
                                'conditions':
                                [
                                    ['angle_build_winrt==0',
                                    {
                                        'AdditionalDependencies':
                                        [
                                            'dxguid.lib',
                                        ],
                                    }],
                                    ['angle_build_winrt==1',
                                    {
                                        'AdditionalDependencies':
                                        [
                                            'dxguid.lib',
                                            'd3d11.lib',
                                            'd3dcompiler.lib',
                                        ],
                                    }],
                                ],
                            }
                        },
                    },
                }],
                ['angle_build_winrt==0 and OS=="win"',
                {
                    'sources':
                    [
                        '<@(angle_libangle_win_sources)',
                    ],
                    'dependencies':
                    [
                        'copy_compiler_dll'
                    ],
                }],
                ['angle_build_winrt==1',
                {
                    'sources':
                    [
                        '<@(angle_libangle_winrt_sources)',
                    ],
                    'defines':
                    [
                        'NTDDI_VERSION=NTDDI_WINBLUE',
                    ],
                    'msvs_enable_winrt' : '1',
                    'msvs_requires_importlibrary' : 'true',
                    'msvs_settings':
                    {
                        'VCLinkerTool':
                        {
                            'EnableCOMDATFolding': '1',
                            'OptimizeReferences': '1',
                        }
                    },
                }],
                ['angle_build_winphone==1',
                {
                    'msvs_enable_winphone' : '1',
                }],
            ],
            'configurations':
            {
                'Debug_Base':
                {
                    'defines':
                    [
                        'ANGLE_ENABLE_DEBUG_ANNOTATIONS',
                        'ANGLE_GENERATE_SHADER_DEBUG_INFO'
                    ],
                    'msvs_settings':
                    {
                        'VCLinkerTool':
                        {
                            'AdditionalDependencies':
                            [
                                'd3d9.lib',
                            ]
                        }
                    },
                },
            },
        },
        {
            'target_name': 'libGLESv2',
            'type': 'shared_library',
            'dependencies': [ 'libANGLE' ],
            'includes': [ '../build/common_defines.gypi', ],
            'sources':
            [
                'libGLESv2/libGLESv2.cpp',
                'libGLESv2/libGLESv2.def',
                'libGLESv2/libGLESv2.rc',
            ],
            'conditions':
            [
                ['angle_build_winrt==1',
                {
                    'msvs_enable_winrt' : '1',
                    'msvs_requires_importlibrary' : 'true',
                    'msvs_settings':
                    {
                        'VCLinkerTool':
                        {
                            'EnableCOMDATFolding': '1',
                            'OptimizeReferences': '1',
                        }
                    },
                }],
                ['angle_build_winphone==1',
                {
                    'msvs_enable_winphone' : '1',
                }],
            ],
            'configurations':
            {
                'Debug_Base':
                {
                    'defines':
                    [
                        'ANGLE_ENABLE_DEBUG_ANNOTATIONS',
                    ],
                },
            },
        },
        {
            'target_name': 'libGLESv2_static',
            'type': 'static_library',
            # make sure we depend on commit_id as a hard dependency, otherwise
            # we will try to build the static_lib in parallel
            'dependencies': [ 'libANGLE', 'commit_id' ],
            'includes': [ '../build/common_defines.gypi', ],
            'sources':
            [
                'libGLESv2/libGLESv2.cpp',
                'libGLESv2/libGLESv2.rc',
            ],
            'conditions':
            [
                ['angle_build_winrt==1',
                {
                    'msvs_enable_winrt' : '1',
                    'msvs_requires_importlibrary' : 'true',
                    'msvs_settings':
                    {
                        'VCLinkerTool':
                        {
                            'EnableCOMDATFolding': '1',
                            'OptimizeReferences': '1',
                        }
            },
                }],
                ['angle_build_winphone==1',
                {
                    'msvs_enable_winphone' : '1',
                }],
            ],
        },
    ],
}
