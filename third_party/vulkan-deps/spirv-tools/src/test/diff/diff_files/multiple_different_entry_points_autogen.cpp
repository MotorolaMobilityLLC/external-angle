// GENERATED FILE - DO NOT EDIT.
// Generated by generate_tests.py
//
// Copyright (c) 2022 Google LLC.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "../diff_test_utils.h"

#include "gtest/gtest.h"

namespace spvtools {
namespace diff {
namespace {

// Basic test for multiple entry points.  The entry points have different
// execution models and so can be trivially matched.
constexpr char kSrc[] = R"(               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %mainv "mainv" %vo %a
               OpEntryPoint Fragment %mainf "mainf" %color %vi
	       OpExecutionMode %mainf OriginUpperLeft
               OpSource ESSL 310
               OpName %mainv "mainv"
               OpName %mainf "mainf"
               OpName %a "a"
               OpName %vo "v"
               OpName %vi "v"
               OpName %color "color"
               OpDecorate %a Location 0
               OpDecorate %vo Location 0
               OpDecorate %vi Location 0
               OpDecorate %color Location 0
	       OpDecorate %color RelaxedPrecision
	       OpDecorate %vi RelaxedPrecision
               OpDecorate %12 RelaxedPrecision
               OpDecorate %13 RelaxedPrecision

       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4

%_ptr_Input_float = OpTypePointer Input %float
          %a = OpVariable %_ptr_Input_float Input
%_ptr_Output_float = OpTypePointer Output %float
         %vo = OpVariable %_ptr_Output_float Output
         %vi = OpVariable %_ptr_Input_float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %color = OpVariable %_ptr_Output_v4float Output

      %mainv = OpFunction %void None %3
          %5 = OpLabel
         %11 = OpLoad %float %a
               OpStore %vo %11
               OpReturn
               OpFunctionEnd

      %mainf = OpFunction %void None %3
          %6 = OpLabel
         %12 = OpLoad %float %vi
	 %13 = OpCompositeConstruct %v4float %12 %12 %12 %12
               OpStore %color %13
               OpReturn
               OpFunctionEnd)";
constexpr char kDst[] = R"(               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %frag "frag" %vi %color
               OpEntryPoint Vertex %vert "vert" %a %vo
	       OpExecutionMode %frag OriginUpperLeft
               OpSource ESSL 310
               OpName %frag "frag"
               OpName %vert "vert"
               OpName %vo "v"
               OpName %a "a"
               OpName %color "color"
               OpName %vi "v"
               OpDecorate %vi Location 0
               OpDecorate %color Location 0
               OpDecorate %a Location 0
               OpDecorate %vo Location 0
	       OpDecorate %color RelaxedPrecision
	       OpDecorate %vi RelaxedPrecision
               OpDecorate %14 RelaxedPrecision
               OpDecorate %17 RelaxedPrecision

      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
       %void = OpTypeVoid
          %3 = OpTypeFunction %void

%_ptr_Output_float = OpTypePointer Output %float
         %vo = OpVariable %_ptr_Output_float Output
%_ptr_Input_float = OpTypePointer Input %float
          %a = OpVariable %_ptr_Input_float Input
         %vi = OpVariable %_ptr_Input_float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %color = OpVariable %_ptr_Output_v4float Output

       %frag = OpFunction %void None %3
          %7 = OpLabel
         %14 = OpLoad %float %vi
	 %17 = OpCompositeConstruct %v4float %14 %14 %14 %14
               OpStore %color %17
               OpReturn
               OpFunctionEnd

       %vert = OpFunction %void None %3
          %8 = OpLabel
         %13 = OpLoad %float %a
               OpStore %vo %13
               OpReturn
               OpFunctionEnd
)";

TEST(DiffTest, MultipleDifferentEntryPoints) {
  constexpr char kDiff[] = R"( ; SPIR-V
 ; Version: 1.6
 ; Generator: Khronos SPIR-V Tools Assembler; 0
 ; Bound: 20
 ; Schema: 0
 OpCapability Shader
 %1 = OpExtInstImport "GLSL.std.450"
 OpMemoryModel Logical GLSL450
-OpEntryPoint Vertex %2 "mainv" %4 %7
+OpEntryPoint Vertex %2 "vert" %7 %4
-OpEntryPoint Fragment %8 "mainf" %9 %10
+OpEntryPoint Fragment %8 "frag" %10 %9
 OpExecutionMode %8 OriginUpperLeft
 OpSource ESSL 310
-OpName %2 "mainv"
+OpName %2 "vert"
-OpName %8 "mainf"
+OpName %8 "frag"
 OpName %7 "a"
 OpName %4 "v"
 OpName %10 "v"
 OpName %9 "color"
 OpDecorate %7 Location 0
 OpDecorate %4 Location 0
 OpDecorate %10 Location 0
 OpDecorate %9 Location 0
 OpDecorate %9 RelaxedPrecision
 OpDecorate %10 RelaxedPrecision
 OpDecorate %12 RelaxedPrecision
 OpDecorate %13 RelaxedPrecision
 %14 = OpTypeVoid
 %3 = OpTypeFunction %14
 %15 = OpTypeFloat 32
 %16 = OpTypeVector %15 4
 %17 = OpTypePointer Input %15
 %7 = OpVariable %17 Input
 %18 = OpTypePointer Output %15
 %4 = OpVariable %18 Output
 %10 = OpVariable %17 Input
 %19 = OpTypePointer Output %16
 %9 = OpVariable %19 Output
 %8 = OpFunction %14 None %3
 %6 = OpLabel
 %12 = OpLoad %15 %10
 %13 = OpCompositeConstruct %16 %12 %12 %12 %12
 OpStore %9 %13
 OpReturn
 OpFunctionEnd
 %2 = OpFunction %14 None %3
 %5 = OpLabel
 %11 = OpLoad %15 %7
 OpStore %4 %11
 OpReturn
 OpFunctionEnd
)";
  Options options;
  DoStringDiffTest(kSrc, kDst, kDiff, options);
}

TEST(DiffTest, MultipleDifferentEntryPointsNoDebug) {
  constexpr char kSrcNoDebug[] = R"(               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Vertex %mainv "mainv" %vo %a
               OpEntryPoint Fragment %mainf "mainf" %color %vi
	       OpExecutionMode %mainf OriginUpperLeft
               OpSource ESSL 310
               OpDecorate %a Location 0
               OpDecorate %vo Location 0
               OpDecorate %vi Location 0
               OpDecorate %color Location 0
	       OpDecorate %color RelaxedPrecision
	       OpDecorate %vi RelaxedPrecision
               OpDecorate %12 RelaxedPrecision
               OpDecorate %13 RelaxedPrecision

       %void = OpTypeVoid
          %3 = OpTypeFunction %void
      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4

%_ptr_Input_float = OpTypePointer Input %float
          %a = OpVariable %_ptr_Input_float Input
%_ptr_Output_float = OpTypePointer Output %float
         %vo = OpVariable %_ptr_Output_float Output
         %vi = OpVariable %_ptr_Input_float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %color = OpVariable %_ptr_Output_v4float Output

      %mainv = OpFunction %void None %3
          %5 = OpLabel
         %11 = OpLoad %float %a
               OpStore %vo %11
               OpReturn
               OpFunctionEnd

      %mainf = OpFunction %void None %3
          %6 = OpLabel
         %12 = OpLoad %float %vi
	 %13 = OpCompositeConstruct %v4float %12 %12 %12 %12
               OpStore %color %13
               OpReturn
               OpFunctionEnd
)";
  constexpr char kDstNoDebug[] = R"(               OpCapability Shader
          %1 = OpExtInstImport "GLSL.std.450"
               OpMemoryModel Logical GLSL450
               OpEntryPoint Fragment %frag "frag" %vi %color
               OpEntryPoint Vertex %vert "vert" %a %vo
	       OpExecutionMode %frag OriginUpperLeft
               OpSource ESSL 310
               OpDecorate %vi Location 0
               OpDecorate %color Location 0
               OpDecorate %a Location 0
               OpDecorate %vo Location 0
	       OpDecorate %color RelaxedPrecision
	       OpDecorate %vi RelaxedPrecision
               OpDecorate %14 RelaxedPrecision
               OpDecorate %17 RelaxedPrecision

      %float = OpTypeFloat 32
    %v4float = OpTypeVector %float 4
       %void = OpTypeVoid
          %3 = OpTypeFunction %void

%_ptr_Output_float = OpTypePointer Output %float
         %vo = OpVariable %_ptr_Output_float Output
%_ptr_Input_float = OpTypePointer Input %float
          %a = OpVariable %_ptr_Input_float Input
         %vi = OpVariable %_ptr_Input_float Input
%_ptr_Output_v4float = OpTypePointer Output %v4float
      %color = OpVariable %_ptr_Output_v4float Output

       %frag = OpFunction %void None %3
          %7 = OpLabel
         %14 = OpLoad %float %vi
	 %17 = OpCompositeConstruct %v4float %14 %14 %14 %14
               OpStore %color %17
               OpReturn
               OpFunctionEnd

       %vert = OpFunction %void None %3
          %8 = OpLabel
         %13 = OpLoad %float %a
               OpStore %vo %13
               OpReturn
               OpFunctionEnd
)";
  constexpr char kDiff[] = R"( ; SPIR-V
 ; Version: 1.6
 ; Generator: Khronos SPIR-V Tools Assembler; 0
 ; Bound: 20
 ; Schema: 0
 OpCapability Shader
 %1 = OpExtInstImport "GLSL.std.450"
 OpMemoryModel Logical GLSL450
-OpEntryPoint Vertex %2 "mainv" %4 %7
+OpEntryPoint Vertex %2 "vert" %7 %4
-OpEntryPoint Fragment %8 "mainf" %9 %10
+OpEntryPoint Fragment %8 "frag" %10 %9
 OpExecutionMode %8 OriginUpperLeft
 OpSource ESSL 310
 OpDecorate %7 Location 0
 OpDecorate %4 Location 0
 OpDecorate %10 Location 0
 OpDecorate %9 Location 0
 OpDecorate %9 RelaxedPrecision
 OpDecorate %10 RelaxedPrecision
 OpDecorate %12 RelaxedPrecision
 OpDecorate %13 RelaxedPrecision
 %14 = OpTypeVoid
 %3 = OpTypeFunction %14
 %15 = OpTypeFloat 32
 %16 = OpTypeVector %15 4
 %17 = OpTypePointer Input %15
 %7 = OpVariable %17 Input
 %18 = OpTypePointer Output %15
 %4 = OpVariable %18 Output
 %10 = OpVariable %17 Input
 %19 = OpTypePointer Output %16
 %9 = OpVariable %19 Output
 %8 = OpFunction %14 None %3
 %6 = OpLabel
 %12 = OpLoad %15 %10
 %13 = OpCompositeConstruct %16 %12 %12 %12 %12
 OpStore %9 %13
 OpReturn
 OpFunctionEnd
 %2 = OpFunction %14 None %3
 %5 = OpLabel
 %11 = OpLoad %15 %7
 OpStore %4 %11
 OpReturn
 OpFunctionEnd
)";
  Options options;
  DoStringDiffTest(kSrcNoDebug, kDstNoDebug, kDiff, options);
}

}  // namespace
}  // namespace diff
}  // namespace spvtools
