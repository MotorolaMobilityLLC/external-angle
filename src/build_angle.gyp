# Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'target_defaults': {
    'defines': [
      'ANGLE_DISABLE_TRACE',
      'ANGLE_COMPILE_OPTIMIZATION_LEVEL=D3DCOMPILE_OPTIMIZATION_LEVEL0',
    ],
  },
  'targets': [
    {
      'target_name': 'preprocessor',
      'type': 'static_library',
      'include_dirs': [
      ],
      'sources': [
        'compiler/preprocessor/new/Diagnostics.cpp',
        'compiler/preprocessor/new/Diagnostics.h',
        'compiler/preprocessor/new/DirectiveHandler.cpp',
        'compiler/preprocessor/new/DirectiveHandler.h',
        'compiler/preprocessor/new/DirectiveParser.cpp',
        'compiler/preprocessor/new/DirectiveParser.h',
        'compiler/preprocessor/new/ExpressionParser.cpp',
        'compiler/preprocessor/new/ExpressionParser.h',
        'compiler/preprocessor/new/Input.cpp',
        'compiler/preprocessor/new/Input.h',
        'compiler/preprocessor/new/Lexer.cpp',
        'compiler/preprocessor/new/Lexer.h',
        'compiler/preprocessor/new/Macro.cpp',
        'compiler/preprocessor/new/Macro.h',
        'compiler/preprocessor/new/MacroExpander.cpp',
        'compiler/preprocessor/new/MacroExpander.h',
        'compiler/preprocessor/new/Preprocessor.cpp',
        'compiler/preprocessor/new/Preprocessor.h',
        'compiler/preprocessor/new/SourceLocation.h',
        'compiler/preprocessor/new/Token.cpp',
        'compiler/preprocessor/new/Token.h',
        'compiler/preprocessor/new/Tokenizer.cpp',
        'compiler/preprocessor/new/Tokenizer.h',
      ],
    },
    {
      'target_name': 'translator_common',
      'type': 'static_library',
      'dependencies': ['preprocessor'],
      'include_dirs': [
        '.',
        '../include',
      ],
      'defines': [
        'COMPILER_IMPLEMENTATION',
      ],
      'sources': [
        'compiler/BaseTypes.h',
        'compiler/BuiltInFunctionEmulator.cpp',
        'compiler/BuiltInFunctionEmulator.h',
        'compiler/Common.h',
        'compiler/Compiler.cpp',
        'compiler/ConstantUnion.h',
        'compiler/debug.cpp',
        'compiler/debug.h',
        'compiler/DetectRecursion.cpp',
        'compiler/DetectRecursion.h',
        'compiler/ForLoopUnroll.cpp',
        'compiler/ForLoopUnroll.h',
        'compiler/glslang.h',
        'compiler/glslang_lex.cpp',
        'compiler/glslang_tab.cpp',
        'compiler/glslang_tab.h',
        'compiler/InfoSink.cpp',
        'compiler/InfoSink.h',
        'compiler/Initialize.cpp',
        'compiler/Initialize.h',
        'compiler/InitializeDll.cpp',
        'compiler/InitializeDll.h',
        'compiler/InitializeGlobals.h',
        'compiler/InitializeParseContext.h',
        'compiler/Intermediate.cpp',
        'compiler/intermediate.h',
        'compiler/intermOut.cpp',
        'compiler/IntermTraverse.cpp',
        'compiler/localintermediate.h',
        'compiler/MapLongVariableNames.cpp',
        'compiler/MapLongVariableNames.h',
        'compiler/MMap.h',
        'compiler/osinclude.h',
        'compiler/parseConst.cpp',
        'compiler/ParseHelper.cpp',
        'compiler/ParseHelper.h',
        'compiler/PoolAlloc.cpp',
        'compiler/PoolAlloc.h',
        'compiler/QualifierAlive.cpp',
        'compiler/QualifierAlive.h',
        'compiler/RemoveTree.cpp',
        'compiler/RemoveTree.h',
        'compiler/ShHandle.h',
        'compiler/SymbolTable.cpp',
        'compiler/SymbolTable.h',
        'compiler/Types.h',
        'compiler/util.cpp',
        'compiler/util.h',
        'compiler/ValidateLimitations.cpp',
        'compiler/ValidateLimitations.h',
        'compiler/VariableInfo.cpp',
        'compiler/VariableInfo.h',
        # Old preprocessor
        'compiler/preprocessor/atom.c',
        'compiler/preprocessor/atom.h',
        'compiler/preprocessor/compile.h',
        'compiler/preprocessor/cpp.c',
        'compiler/preprocessor/cpp.h',
        'compiler/preprocessor/cppstruct.c',
        'compiler/preprocessor/length_limits.h',
        'compiler/preprocessor/lexer_glue.cpp',
        'compiler/preprocessor/lexer_glue.h',
        'compiler/preprocessor/memory.c',
        'compiler/preprocessor/memory.h',
        'compiler/preprocessor/parser.h',
        'compiler/preprocessor/preprocess.h',
        'compiler/preprocessor/scanner.c',
        'compiler/preprocessor/scanner.h',
        'compiler/preprocessor/slglobals.h',
        'compiler/preprocessor/symbols.c',
        'compiler/preprocessor/symbols.h',
        'compiler/preprocessor/tokens.c',
        'compiler/preprocessor/tokens.h',
        # Dependency graph
        'compiler/depgraph/DependencyGraph.cpp',
        'compiler/depgraph/DependencyGraph.h',
        'compiler/depgraph/DependencyGraphBuilder.cpp',
        'compiler/depgraph/DependencyGraphBuilder.h',
        'compiler/depgraph/DependencyGraphOutput.cpp',
        'compiler/depgraph/DependencyGraphOutput.h',
        'compiler/depgraph/DependencyGraphTraverse.cpp',
        # Timing restrictions
        'compiler/timing/RestrictFragmentShaderTiming.cpp',
        'compiler/timing/RestrictFragmentShaderTiming.h',
        'compiler/timing/RestrictVertexShaderTiming.cpp',
        'compiler/timing/RestrictVertexShaderTiming.h',
      ],
      'conditions': [
        ['OS=="win"', {
          'sources': ['compiler/ossource_win.cpp'],
        }, { # else: posix
          'sources': ['compiler/ossource_posix.cpp'],
        }],
      ],
    },
    {
      'target_name': 'translator_glsl',
      'type': '<(component)',
      'dependencies': ['translator_common'],
      'include_dirs': [
        '.',
        '../include',
      ],
      'defines': [
        'COMPILER_IMPLEMENTATION',
      ],
      'sources': [
        'compiler/CodeGenGLSL.cpp',
        'compiler/OutputESSL.cpp',
        'compiler/OutputESSL.h',        
        'compiler/OutputGLSLBase.cpp',
        'compiler/OutputGLSLBase.h',
        'compiler/OutputGLSL.cpp',
        'compiler/OutputGLSL.h',
        'compiler/ShaderLang.cpp',
        'compiler/TranslatorESSL.cpp',
        'compiler/TranslatorESSL.h',
        'compiler/TranslatorGLSL.cpp',
        'compiler/TranslatorGLSL.h',
        'compiler/VersionGLSL.cpp',
        'compiler/VersionGLSL.h',
      ],
    },
  ],
  'conditions': [
    ['OS=="win"', {
      'targets': [
        {
          'target_name': 'translator_hlsl',
          'type': '<(component)',
          'dependencies': ['translator_common'],
          'include_dirs': [
            '.',
            '../include',
          ],
          'defines': [
            'COMPILER_IMPLEMENTATION',
          ],
          'sources': [
            'compiler/ShaderLang.cpp',
            'compiler/DetectDiscontinuity.cpp',
            'compiler/DetectDiscontinuity.h',
            'compiler/CodeGenHLSL.cpp',
            'compiler/OutputHLSL.cpp',
            'compiler/OutputHLSL.h',
            'compiler/TranslatorHLSL.cpp',
            'compiler/TranslatorHLSL.h',
            'compiler/UnfoldShortCircuit.cpp',
            'compiler/UnfoldShortCircuit.h',
            'compiler/SearchSymbol.cpp',
            'compiler/SearchSymbol.h',
          ],
        },
        {
          'target_name': 'libGLESv2',
          'type': 'shared_library',
          'dependencies': ['translator_hlsl'],
          'include_dirs': [
            '.',
            '../include',
            '$(DXSDK_DIR)/include',
          ],
          'sources': [
            'common/angleutils.h',
            'common/debug.cpp',
            'common/debug.h',
            'common/RefCountObject.cpp',
            'common/RefCountObject.h',
            'common/version.h',
            'libGLESv2/IndexDataManager.cpp',
            'libGLESv2/IndexDataManager.h',
            'libGLESv2/vertexconversion.h',
            'libGLESv2/VertexDataManager.cpp',
            'libGLESv2/VertexDataManager.h',
            'libGLESv2/Blit.cpp',
            'libGLESv2/Blit.h',
            'libGLESv2/Buffer.cpp',
            'libGLESv2/Buffer.h',
            'libGLESv2/Context.cpp',
            'libGLESv2/Context.h',
            'libGLESv2/Fence.cpp',
            'libGLESv2/Fence.h',
            'libGLESv2/Framebuffer.cpp',
            'libGLESv2/Framebuffer.h',
            'libGLESv2/HandleAllocator.cpp',
            'libGLESv2/HandleAllocator.h',
            'libGLESv2/libGLESv2.cpp',
            'libGLESv2/libGLESv2.def',
            'libGLESv2/libGLESv2.rc',
            'libGLESv2/main.cpp',
            'libGLESv2/main.h',
            'libGLESv2/mathutil.h',
            'libGLESv2/Program.cpp',
            'libGLESv2/Program.h',
            'libGLESv2/ProgramBinary.cpp',
            'libGLESv2/ProgramBinary.h',
            'libGLESv2/Query.h',
            'libGLESv2/Query.cpp',
            'libGLESv2/Renderbuffer.cpp',
            'libGLESv2/Renderbuffer.h',
            'libGLESv2/ResourceManager.cpp',
            'libGLESv2/ResourceManager.h',
            'libGLESv2/Shader.cpp',
            'libGLESv2/Shader.h',
            'libGLESv2/Texture.cpp',
            'libGLESv2/Texture.h',
            'libGLESv2/utilities.cpp',
            'libGLESv2/utilities.h',
          ],
          'msvs_settings': {
            'VCLinkerTool': {
              'AdditionalLibraryDirectories': ['$(DXSDK_DIR)/lib/x86'],
              'AdditionalDependencies': [
                'd3d9.lib',
                'd3dx9.lib',
                'd3dcompiler.lib',
              ],
            }
          },
        },
        {
          'target_name': 'libEGL',
          'type': 'shared_library',
          'dependencies': ['libGLESv2'],
          'include_dirs': [
            '.',
            '../include',
          ],
          'sources': [
            'common/angleutils.h',
            'common/debug.cpp',
            'common/debug.h',
            'common/RefCountObject.cpp',
            'common/RefCountObject.h',
            'common/version.h',
            'libEGL/Config.cpp',
            'libEGL/Config.h',
            'libEGL/Display.cpp',
            'libEGL/Display.h',
            'libEGL/libEGL.cpp',
            'libEGL/libEGL.def',
            'libEGL/libEGL.rc',
            'libEGL/main.cpp',
            'libEGL/main.h',
            'libEGL/Surface.cpp',
            'libEGL/Surface.h',
          ],
          'msvs_settings': {
            'VCLinkerTool': {
              'AdditionalLibraryDirectories': ['$(DXSDK_DIR)/lib/x86'],
              'AdditionalDependencies': [
                'd3d9.lib',
                'dxguid.lib',
                'dwmapi.lib',
              ],
              'DelayLoadDLLs': [
                'dwmapi.dll',
              ]
            }
          },
        },
      ],
    }],
  ],
}

# Local Variables:
# tab-width:2
# indent-tabs-mode:nil
# End:
# vim: set expandtab tabstop=2 shiftwidth=2:
