//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

//
// Create strings that declare built-in definitions, add built-ins that
// cannot be expressed in the files, and establish mappings between 
// built-in functions and operators.
//

#include "compiler/Initialize.h"

#include "compiler/intermediate.h"

void InsertBuiltInFunctions(ShShaderType type, ShShaderSpec spec, const ShBuiltInResources &resources,
                            const TExtensionBehavior &extensionBehavior, TSymbolTable &symbolTable)
{
    TType *float1 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 1);
    TType *float2 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 2);
    TType *float3 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 3);
    TType *float4 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 4);

    TType *int2 = new TType(EbtInt, EbpUndefined, EvqGlobal, 2);
    TType *int3 = new TType(EbtInt, EbpUndefined, EvqGlobal, 3);
    TType *int4 = new TType(EbtInt, EbpUndefined, EvqGlobal, 4);

    //
    // Angle and Trigonometric Functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "radians", float1, "degrees");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "radians", float2, "degrees");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "radians", float3, "degrees");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "radians", float4, "degrees");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "degrees", float1, "radians");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "degrees", float2, "radians");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "degrees", float3, "radians");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "degrees", float4, "radians");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "sin", float1, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "sin", float2, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "sin", float3, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "sin", float4, "angle");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "cos", float1, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "cos", float2, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "cos", float3, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "cos", float4, "angle");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "tan", float1, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "tan", float2, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "tan", float3, "angle");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "tan", float4, "angle");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "asin", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "asin", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "asin", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "asin", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "acos", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "acos", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "acos", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "acos", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "atan", float1, "y", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "atan", float2, "y", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "atan", float3, "y", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "atan", float4, "y", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "atan", float1, "y_over_x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "atan", float2, "y_over_x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "atan", float3, "y_over_x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "atan", float4, "y_over_x");

    //
    // Exponential Functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "pow", float1, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "pow", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "pow", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "pow", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "exp", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "exp", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "exp", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "exp", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "log", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "log", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "log", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "log", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "exp2", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "exp2", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "exp2", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "exp2", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "log2", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "log2", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "log2", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "log2", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "sqrt", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "sqrt", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "sqrt", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "sqrt", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "inversesqrt", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "inversesqrt", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "inversesqrt", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "inversesqrt", float4, "x");

    //
    // Common Functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "abs", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "abs", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "abs", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "abs", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "sign", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "sign", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "sign", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "sign", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "floor", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "floor", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "floor", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "floor", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "ceil", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "ceil", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "ceil", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "ceil", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "fract", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "fract", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "fract", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "fract", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "mod", float1, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "mod", float2, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "mod", float3, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "mod", float4, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "mod", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "mod", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "mod", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "min", float1, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "min", float2, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "min", float3, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "min", float4, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "min", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "min", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "min", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "max", float1, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "max", float2, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "max", float3, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "max", float4, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "max", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "max", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "max", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "clamp", float1, "x", float1, "minVal", float1, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "clamp", float2, "x", float1, "minVal", float1, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "clamp", float3, "x", float1, "minVal", float1, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "clamp", float4, "x", float1, "minVal", float1, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "clamp", float2, "x", float2, "minVal", float2, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "clamp", float3, "x", float3, "minVal", float3, "maxVal");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "clamp", float4, "x", float4, "minVal", float4, "maxVal");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "mix", float1, "x", float1, "y", float1, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "mix", float2, "x", float2, "y", float1, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "mix", float3, "x", float3, "y", float1, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "mix", float4, "x", float4, "y", float1, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "mix", float2, "x", float2, "y", float2, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "mix", float3, "x", float3, "y", float3, "a");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "mix", float4, "x", float4, "y", float4, "a");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "step", float1, "edge", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "step", float2, "edge", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "step", float3, "edge", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "step", float4, "edge", float4, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "step", float1, "edge", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "step", float1, "edge", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "step", float1, "edge", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "smoothstep", float1, "edge0", float1, "edge1", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "smoothstep", float2, "edge0", float2, "edge1", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "smoothstep", float3, "edge0", float3, "edge1", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "smoothstep", float4, "edge0", float4, "edge1", float4, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "smoothstep", float1, "edge0", float1, "edge1", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "smoothstep", float1, "edge0", float1, "edge1", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "smoothstep", float1, "edge0", float1, "edge1", float4, "x");

    //
    // Geometric Functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "length", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "length", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "length", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "length", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "distance", float1, "p0", float1, "p1");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "distance", float2, "p0", float2, "p1");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "distance", float3, "p0", float3, "p1");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "distance", float4, "p0", float4, "p1");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "dot", float1, "x", float1, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "dot", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "dot", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "dot", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "cross", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "normalize", float1, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "normalize", float2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "normalize", float3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "normalize", float4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "faceforward", float1, "N", float1, "I", float1, "Nref");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "faceforward", float2, "N", float2, "I", float2, "Nref");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "faceforward", float3, "N", float3, "I", float3, "Nref");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "faceforward", float4, "N", float4, "I", float4, "Nref");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "reflect", float1, "I", float1, "N");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "reflect", float2, "I", float2, "N");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "reflect", float3, "I", float3, "N");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "reflect", float4, "I", float4, "N");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, float1, "refract", float1, "I", float1, "N", float1, "eta");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float2, "refract", float2, "I", float2, "N", float1, "eta");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float3, "refract", float3, "I", float3, "N", float1, "eta");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, float4, "refract", float4, "I", float4, "N", float1, "eta");

    TType *mat2 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 2, 2);
    TType *mat3 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 3, 3);
    TType *mat4 = new TType(EbtFloat, EbpUndefined, EvqGlobal, 4, 4);

    //
    // Matrix Functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, mat2, "matrixCompMult", mat2, "x", mat2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, mat3, "matrixCompMult", mat3, "x", mat3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, mat4, "matrixCompMult", mat4, "x", mat4, "y");

    TType *bool1 = new TType(EbtBool, EbpUndefined, EvqGlobal, 1);
    TType *bool2 = new TType(EbtBool, EbpUndefined, EvqGlobal, 2);
    TType *bool3 = new TType(EbtBool, EbpUndefined, EvqGlobal, 3);
    TType *bool4 = new TType(EbtBool, EbpUndefined, EvqGlobal, 4);

    //
    // Vector relational functions.
    //
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "lessThan", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "lessThan", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "lessThan", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "lessThan", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "lessThan", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "lessThan", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "lessThanEqual", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "lessThanEqual", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "lessThanEqual", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "lessThanEqual", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "lessThanEqual", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "lessThanEqual", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "greaterThan", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "greaterThan", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "greaterThan", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "greaterThan", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "greaterThan", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "greaterThan", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "greaterThanEqual", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "greaterThanEqual", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "greaterThanEqual", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "greaterThanEqual", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "greaterThanEqual", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "greaterThanEqual", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "equal", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "equal", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "equal", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "equal", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "equal", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "equal", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "equal", bool2, "x", bool2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "equal", bool3, "x", bool3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "equal", bool4, "x", bool4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "notEqual", float2, "x", float2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "notEqual", float3, "x", float3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "notEqual", float4, "x", float4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "notEqual", int2, "x", int2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "notEqual", int3, "x", int3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "notEqual", int4, "x", int4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "notEqual", bool2, "x", bool2, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "notEqual", bool3, "x", bool3, "y");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "notEqual", bool4, "x", bool4, "y");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "any", bool2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "any", bool3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "any", bool4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "all", bool2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "all", bool3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool1, "all", bool4, "x");

    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool2, "not", bool2, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool3, "not", bool3, "x");
    symbolTable.insertBuiltIn(COMMON_BUILTINS, bool4, "not", bool4, "x");

    TType *sampler2D = new TType(EbtSampler2D, EbpUndefined, EvqGlobal, 1);
    TType *samplerCube = new TType(EbtSamplerCube, EbpUndefined, EvqGlobal, 1);

    //
    // Texture Functions for GLSL ES 1.0
    //
    symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2D", sampler2D, "sampler", float2, "coord");
    symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", sampler2D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", sampler2D, "sampler", float4, "coord");
    symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "textureCube", samplerCube, "sampler", float3, "coord");

    if (resources.OES_EGL_image_external)
    {
        TType *samplerExternalOES = new TType(EbtSamplerExternalOES, EbpUndefined, EvqGlobal, 1);

        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2D", samplerExternalOES, "sampler", float2, "coord");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", samplerExternalOES, "sampler", float3, "coord");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", samplerExternalOES, "sampler", float4, "coord");
    }

    if (resources.ARB_texture_rectangle)
    {
        TType *sampler2DRect = new TType(EbtSampler2DRect, EbpUndefined, EvqGlobal, 1);

        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DRect", sampler2DRect, "sampler", float2, "coord");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DRectProj", sampler2DRect, "sampler", float3, "coord");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DRectProj", sampler2DRect, "sampler", float4, "coord");
    }

    if(type == SH_FRAGMENT_SHADER)
    {
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2D", sampler2D, "sampler", float2, "coord", float1, "bias");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", sampler2D, "sampler", float3, "coord", float1, "bias");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProj", sampler2D, "sampler", float4, "coord", float1, "bias");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "textureCube", samplerCube, "sampler", float3, "coord", float1, "bias");

        if (resources.OES_standard_derivatives)
        {
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float1, "dFdx", float1, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float2, "dFdx", float2, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float3, "dFdx", float3, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "dFdx", float4, "p");
            
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float1, "dFdy", float1, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float2, "dFdy", float2, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float3, "dFdy", float3, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "dFdy", float4, "p");

            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float1, "fwidth", float1, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float2, "fwidth", float2, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float3, "fwidth", float3, "p");
            symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "fwidth", float4, "p");
        }
    }

    if(type == SH_VERTEX_SHADER)
    {
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DLod", sampler2D, "sampler", float2, "coord", float1, "lod");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProjLod", sampler2D, "sampler", float3, "coord", float1, "lod");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "texture2DProjLod", sampler2D, "sampler", float4, "coord", float1, "lod");
        symbolTable.insertBuiltIn(ESSL1_BUILTINS, float4, "textureCubeLod", samplerCube, "sampler", float3, "coord", float1, "lod");
    }

    TType *sampler3D = new TType(EbtSampler3D, EbpUndefined, EvqGlobal, 1);

    //
    // Texture Functions for GLSL ES 3.0
    //
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "texture", sampler2D, "sampler", float2, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "texture", sampler3D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "texture", samplerCube, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "textureProj", sampler2D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "textureProj", sampler2D, "sampler", float4, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "textureProj", sampler3D, "sampler", float4, "coord");

    TType *isampler2D = new TType(EbtISampler2D, EbpUndefined, EvqGlobal, 1);
    TType *isampler3D = new TType(EbtISampler3D, EbpUndefined, EvqGlobal, 1);
    TType *isamplerCube = new TType(EbtISamplerCube, EbpUndefined, EvqGlobal, 1);

    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "texture", isampler2D, "sampler", float2, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "texture", isampler3D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "texture", isamplerCube, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "textureProj", isampler2D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "textureProj", isampler2D, "sampler", float4, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, int4, "textureProj", isampler3D, "sampler", float4, "coord");

    TType *usampler2D = new TType(EbtUSampler2D, EbpUndefined, EvqGlobal, 1);
    TType *usampler3D = new TType(EbtUSampler3D, EbpUndefined, EvqGlobal, 1);
    TType *usamplerCube = new TType(EbtUSamplerCube, EbpUndefined, EvqGlobal, 1);
    TType *uint4 = new TType(EbtUInt, EbpUndefined, EvqGlobal, 4);

    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "texture", usampler2D, "sampler", float2, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "texture", usampler3D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "texture", usamplerCube, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "textureProj", usampler2D, "sampler", float3, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "textureProj", usampler2D, "sampler", float4, "coord");
    symbolTable.insertBuiltIn(ESSL3_BUILTINS, uint4, "textureProj", usampler3D, "sampler", float4, "coord");

    if(type == SH_FRAGMENT_SHADER)
    {
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float1, "dFdx", float1, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float2, "dFdx", float2, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float3, "dFdx", float3, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "dFdx", float4, "p");
            
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float1, "dFdy", float1, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float2, "dFdy", float2, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float3, "dFdy", float3, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "dFdy", float4, "p");

        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float1, "fwidth", float1, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float2, "fwidth", float2, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float3, "fwidth", float3, "p");
        symbolTable.insertBuiltIn(ESSL3_BUILTINS, float4, "fwidth", float4, "p");
    }

    //
    // Depth range in window coordinates
    //
    TTypeList *members = NewPoolTTypeList();
    TTypeLine near = {new TType(EbtFloat, EbpHigh, EvqGlobal, 1), 0};
    TTypeLine far = {new TType(EbtFloat, EbpHigh, EvqGlobal, 1), 0};
    TTypeLine diff = {new TType(EbtFloat, EbpHigh, EvqGlobal, 1), 0};
    near.type->setFieldName("near");
    far.type->setFieldName("far");
    diff.type->setFieldName("diff");
    members->push_back(near);
    members->push_back(far);
    members->push_back(diff);
    TVariable *depthRangeParameters = new TVariable(NewPoolTString("gl_DepthRangeParameters"), TType(members, "gl_DepthRangeParameters"), true);
    symbolTable.insert(COMMON_BUILTINS, *depthRangeParameters);
    TVariable *depthRange = new TVariable(NewPoolTString("gl_DepthRange"), TType(members, "gl_DepthRangeParameters"));
    depthRange->setQualifier(EvqUniform);
    symbolTable.insert(COMMON_BUILTINS, *depthRange);

    //
    // Implementation dependent built-in constants.
    //
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxVertexAttribs", resources.MaxVertexAttribs);
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxVertexUniformVectors", resources.MaxVertexUniformVectors);
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxVertexTextureImageUnits", resources.MaxVertexTextureImageUnits);
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxCombinedTextureImageUnits", resources.MaxCombinedTextureImageUnits);
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxTextureImageUnits", resources.MaxTextureImageUnits);
    symbolTable.insertConstInt(COMMON_BUILTINS, "gl_MaxFragmentUniformVectors", resources.MaxFragmentUniformVectors);

    symbolTable.insertConstInt(ESSL1_BUILTINS, "gl_MaxVaryingVectors", resources.MaxVaryingVectors);

    if (spec != SH_CSS_SHADERS_SPEC)
    {
        TExtensionBehavior::const_iterator iter = extensionBehavior.find("GL_EXT_draw_buffers");
        const bool usingMRTExtension = (iter != extensionBehavior.end() && (iter->second == EBhEnable || iter->second == EBhRequire));
        const int maxDrawBuffers = (usingMRTExtension ? resources.MaxDrawBuffers : 1);

        symbolTable.insertConstInt(ESSL1_BUILTINS, "gl_MaxDrawBuffers", maxDrawBuffers);
    }

    symbolTable.insertConstInt(ESSL3_BUILTINS, "gl_MaxVertexOutputVectors", resources.MaxVertexOutputVectors);
    symbolTable.insertConstInt(ESSL3_BUILTINS, "gl_MaxFragmentInputVectors", resources.MaxFragmentInputVectors);
    symbolTable.insertConstInt(ESSL3_BUILTINS, "gl_MinProgramTexelOffset", resources.MinProgramTexelOffset);
    symbolTable.insertConstInt(ESSL3_BUILTINS, "gl_MaxProgramTexelOffset", resources.MaxProgramTexelOffset);
}

void IdentifyBuiltIns(ShShaderType type, ShShaderSpec spec,
                      const ShBuiltInResources &resources,
                      TSymbolTable &symbolTable)
{
    //
    // First, insert some special built-in variables that are not in 
    // the built-in header files.
    //
    switch(type) {
    case SH_FRAGMENT_SHADER:
        symbolTable.insert(COMMON_BUILTINS, *new TVariable(NewPoolTString("gl_FragCoord"), TType(EbtFloat, EbpMedium, EvqFragCoord,   4)));
        symbolTable.insert(COMMON_BUILTINS, *new TVariable(NewPoolTString("gl_FrontFacing"), TType(EbtBool,  EbpUndefined, EvqFrontFacing, 1)));
        symbolTable.insert(COMMON_BUILTINS, *new TVariable(NewPoolTString("gl_PointCoord"), TType(EbtFloat, EbpMedium, EvqPointCoord,  2)));

        //
        // In CSS Shaders, gl_FragColor, gl_FragData, and gl_MaxDrawBuffers are not available.
        // Instead, css_MixColor and css_ColorMatrix are available.
        //
        if (spec != SH_CSS_SHADERS_SPEC) {
            symbolTable.insert(ESSL1_BUILTINS, *new TVariable(NewPoolTString("gl_FragColor"), TType(EbtFloat, EbpMedium, EvqFragColor,   4)));
            symbolTable.insert(ESSL1_BUILTINS, *new TVariable(NewPoolTString("gl_FragData[gl_MaxDrawBuffers]"), TType(EbtFloat, EbpMedium, EvqFragData,    4)));
        } else {
            symbolTable.insert(ESSL1_BUILTINS, *new TVariable(NewPoolTString("css_MixColor"), TType(EbtFloat, EbpMedium, EvqGlobal,      4)));
            symbolTable.insert(ESSL1_BUILTINS, *new TVariable(NewPoolTString("css_ColorMatrix"), TType(EbtFloat, EbpMedium, EvqGlobal,      4, 4)));
        }

        break;

    case SH_VERTEX_SHADER:
        symbolTable.insert(COMMON_BUILTINS, *new TVariable(NewPoolTString("gl_Position"), TType(EbtFloat, EbpHigh, EvqPosition,    4)));
        symbolTable.insert(COMMON_BUILTINS, *new TVariable(NewPoolTString("gl_PointSize"), TType(EbtFloat, EbpMedium, EvqPointSize,   1)));
        break;

    default: assert(false && "Language not supported");
    }

    //
    // Next, identify which built-ins from the already loaded headers have
    // a mapping to an operator.  Those that are not identified as such are
    // expected to be resolved through a library of functions, versus as
    // operations.
    //
    symbolTable.relateToOperator(COMMON_BUILTINS, "matrixCompMult",   EOpMul);

    symbolTable.relateToOperator(COMMON_BUILTINS, "equal",            EOpVectorEqual);
    symbolTable.relateToOperator(COMMON_BUILTINS, "notEqual",         EOpVectorNotEqual);
    symbolTable.relateToOperator(COMMON_BUILTINS, "lessThan",         EOpLessThan);
    symbolTable.relateToOperator(COMMON_BUILTINS, "greaterThan",      EOpGreaterThan);
    symbolTable.relateToOperator(COMMON_BUILTINS, "lessThanEqual",    EOpLessThanEqual);
    symbolTable.relateToOperator(COMMON_BUILTINS, "greaterThanEqual", EOpGreaterThanEqual);
    
    symbolTable.relateToOperator(COMMON_BUILTINS, "radians",      EOpRadians);
    symbolTable.relateToOperator(COMMON_BUILTINS, "degrees",      EOpDegrees);
    symbolTable.relateToOperator(COMMON_BUILTINS, "sin",          EOpSin);
    symbolTable.relateToOperator(COMMON_BUILTINS, "cos",          EOpCos);
    symbolTable.relateToOperator(COMMON_BUILTINS, "tan",          EOpTan);
    symbolTable.relateToOperator(COMMON_BUILTINS, "asin",         EOpAsin);
    symbolTable.relateToOperator(COMMON_BUILTINS, "acos",         EOpAcos);
    symbolTable.relateToOperator(COMMON_BUILTINS, "atan",         EOpAtan);

    symbolTable.relateToOperator(COMMON_BUILTINS, "pow",          EOpPow);
    symbolTable.relateToOperator(COMMON_BUILTINS, "exp2",         EOpExp2);
    symbolTable.relateToOperator(COMMON_BUILTINS, "log",          EOpLog);
    symbolTable.relateToOperator(COMMON_BUILTINS, "exp",          EOpExp);
    symbolTable.relateToOperator(COMMON_BUILTINS, "log2",         EOpLog2);
    symbolTable.relateToOperator(COMMON_BUILTINS, "sqrt",         EOpSqrt);
    symbolTable.relateToOperator(COMMON_BUILTINS, "inversesqrt",  EOpInverseSqrt);

    symbolTable.relateToOperator(COMMON_BUILTINS, "abs",          EOpAbs);
    symbolTable.relateToOperator(COMMON_BUILTINS, "sign",         EOpSign);
    symbolTable.relateToOperator(COMMON_BUILTINS, "floor",        EOpFloor);
    symbolTable.relateToOperator(COMMON_BUILTINS, "ceil",         EOpCeil);
    symbolTable.relateToOperator(COMMON_BUILTINS, "fract",        EOpFract);
    symbolTable.relateToOperator(COMMON_BUILTINS, "mod",          EOpMod);
    symbolTable.relateToOperator(COMMON_BUILTINS, "min",          EOpMin);
    symbolTable.relateToOperator(COMMON_BUILTINS, "max",          EOpMax);
    symbolTable.relateToOperator(COMMON_BUILTINS, "clamp",        EOpClamp);
    symbolTable.relateToOperator(COMMON_BUILTINS, "mix",          EOpMix);
    symbolTable.relateToOperator(COMMON_BUILTINS, "step",         EOpStep);
    symbolTable.relateToOperator(COMMON_BUILTINS, "smoothstep",   EOpSmoothStep);

    symbolTable.relateToOperator(COMMON_BUILTINS, "length",       EOpLength);
    symbolTable.relateToOperator(COMMON_BUILTINS, "distance",     EOpDistance);
    symbolTable.relateToOperator(COMMON_BUILTINS, "dot",          EOpDot);
    symbolTable.relateToOperator(COMMON_BUILTINS, "cross",        EOpCross);
    symbolTable.relateToOperator(COMMON_BUILTINS, "normalize",    EOpNormalize);
    symbolTable.relateToOperator(COMMON_BUILTINS, "faceforward",  EOpFaceForward);
    symbolTable.relateToOperator(COMMON_BUILTINS, "reflect",      EOpReflect);
    symbolTable.relateToOperator(COMMON_BUILTINS, "refract",      EOpRefract);
    
    symbolTable.relateToOperator(COMMON_BUILTINS, "any",          EOpAny);
    symbolTable.relateToOperator(COMMON_BUILTINS, "all",          EOpAll);
    symbolTable.relateToOperator(COMMON_BUILTINS, "not",          EOpVectorLogicalNot);

    // Map language-specific operators.
    switch(type) {
    case SH_VERTEX_SHADER:
        break;
    case SH_FRAGMENT_SHADER:
        if (resources.OES_standard_derivatives) {
            symbolTable.relateToOperator(ESSL1_BUILTINS, "dFdx",   EOpDFdx);
            symbolTable.relateToOperator(ESSL1_BUILTINS, "dFdy",   EOpDFdy);
            symbolTable.relateToOperator(ESSL1_BUILTINS, "fwidth", EOpFwidth);

            symbolTable.relateToExtension(ESSL1_BUILTINS, "dFdx", "GL_OES_standard_derivatives");
            symbolTable.relateToExtension(ESSL1_BUILTINS, "dFdy", "GL_OES_standard_derivatives");
            symbolTable.relateToExtension(ESSL1_BUILTINS, "fwidth", "GL_OES_standard_derivatives");

            symbolTable.relateToOperator(ESSL3_BUILTINS, "dFdx",   EOpDFdx);
            symbolTable.relateToOperator(ESSL3_BUILTINS, "dFdy",   EOpDFdy);
            symbolTable.relateToOperator(ESSL3_BUILTINS, "fwidth", EOpFwidth);
        }
        break;
    default: break;
    }

    // Finally add resource-specific variables.
    switch(type) {
    case SH_FRAGMENT_SHADER:
        if (spec != SH_CSS_SHADERS_SPEC) {
            // Set up gl_FragData.  The array size.
            TType fragData(EbtFloat, EbpMedium, EvqFragData, 4, 1, true);
            fragData.setArraySize(resources.MaxDrawBuffers);
            symbolTable.insert(ESSL1_BUILTINS, *new TVariable(NewPoolTString("gl_FragData"), fragData));
        }
        break;
    default: break;
    }
}

void InitExtensionBehavior(const ShBuiltInResources& resources,
                           TExtensionBehavior& extBehavior)
{
    if (resources.OES_standard_derivatives)
        extBehavior["GL_OES_standard_derivatives"] = EBhUndefined;
    if (resources.OES_EGL_image_external)
        extBehavior["GL_OES_EGL_image_external"] = EBhUndefined;
    if (resources.ARB_texture_rectangle)
        extBehavior["GL_ARB_texture_rectangle"] = EBhUndefined;
    if (resources.EXT_draw_buffers)
        extBehavior["GL_EXT_draw_buffers"] = EBhUndefined;
}
