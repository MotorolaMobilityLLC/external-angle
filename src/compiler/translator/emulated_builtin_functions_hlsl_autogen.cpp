// GENERATED FILE - DO NOT EDIT.
// Generated by gen_emulated_builtin_function_tables.py using data from
// emulated_builtin_function_data_hlsl.json.
//
// Copyright 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// emulated_builtin_functions_hlsl:
//   HLSL code for emulating GLSL builtin functions not present in HLSL.

#include "compiler/translator/BuiltInFunctionEmulator.h"

namespace sh
{

namespace
{

struct FunctionPair
{
    constexpr FunctionPair(const MiniFunctionId &idIn, const char *bodyIn) : id(idIn), body(bodyIn)
    {
    }

    MiniFunctionId id;
    const char *body;
};

constexpr FunctionPair g_hlslFunctions[] = {
    {{EOpMod, ParamType::Float1, ParamType::Float1},
     "float mod_emu(float x, float y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float2, ParamType::Float2},
     "float2 mod_emu(float2 x, float2 y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float2, ParamType::Float1},
     "float2 mod_emu(float2 x, float y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float3, ParamType::Float3},
     "float3 mod_emu(float3 x, float3 y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float3, ParamType::Float1},
     "float3 mod_emu(float3 x, float y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float4, ParamType::Float4},
     "float4 mod_emu(float4 x, float4 y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpMod, ParamType::Float4, ParamType::Float1},
     "float4 mod_emu(float4 x, float y)\n"
     "{\n"
     "    return x - y * floor(x / y);\n"
     "}\n"},
    {{EOpFrexp, ParamType::Float1, ParamType::Int1},
     "float frexp_emu(float x, out int exp)\n"
     "{\n"
     "    float fexp;\n"
     "    float mantissa = frexp(abs(x), fexp) * sign(x);\n"
     "    exp = int(fexp);\n"
     "    return mantissa;\n"
     "}\n"},
    {{EOpFrexp, ParamType::Float2, ParamType::Int2},
     "float2 frexp_emu(float2 x, out int2 exp)\n"
     "{\n"
     "    float2 fexp;\n"
     "    float2 mantissa = frexp(abs(x), fexp) * sign(x);\n"
     "    exp = int2(fexp);\n"
     "    return mantissa;\n"
     "}\n"},
    {{EOpFrexp, ParamType::Float3, ParamType::Int3},
     "float3 frexp_emu(float3 x, out int3 exp)\n"
     "{\n"
     "    float3 fexp;\n"
     "    float3 mantissa = frexp(abs(x), fexp) * sign(x);\n"
     "    exp = int3(fexp);\n"
     "    return mantissa;\n"
     "}\n"},
    {{EOpFrexp, ParamType::Float4, ParamType::Int4},
     "float4 frexp_emu(float4 x, out int4 exp)\n"
     "{\n"
     "    float4 fexp;\n"
     "    float4 mantissa = frexp(abs(x), fexp) * sign(x);\n"
     "    exp = int4(fexp);\n"
     "    return mantissa;\n"
     "}\n"},
    {{EOpLdexp, ParamType::Float1, ParamType::Int1},
     "float ldexp_emu(float x, int exp)\n"
     "{\n"
     "    return ldexp(x, float(exp));\n"
     "}\n"},
    {{EOpLdexp, ParamType::Float2, ParamType::Int2},
     "float2 ldexp_emu(float2 x, int2 exp)\n"
     "{\n"
     "    return ldexp(x, float2(exp));\n"
     "}\n"},
    {{EOpLdexp, ParamType::Float3, ParamType::Int3},
     "float3 ldexp_emu(float3 x, int3 exp)\n"
     "{\n"
     "    return ldexp(x, float3(exp));\n"
     "}\n"},
    {{EOpLdexp, ParamType::Float4, ParamType::Int4},
     "float4 ldexp_emu(float4 x, int4 exp)\n"
     "{\n"
     "    return ldexp(x, float4(exp));\n"
     "}\n"},
    {{EOpFaceforward, ParamType::Float1, ParamType::Float1, ParamType::Float1},
     "float faceforward_emu(float N, float I, float Nref)\n"
     "{\n"
     "    if(dot(Nref, I) >= 0)\n"
     "    {\n"
     "        return -N;\n"
     "    }\n"
     "    else\n"
     "    {\n"
     "        return N;\n"
     "    }\n"
     "}\n"},
    {{EOpFaceforward, ParamType::Float2, ParamType::Float2, ParamType::Float2},
     "float2 faceforward_emu(float2 N, float2 I, float2 Nref)\n"
     "{\n"
     "    if(dot(Nref, I) >= 0)\n"
     "    {\n"
     "        return -N;\n"
     "    }\n"
     "    else\n"
     "    {\n"
     "        return N;\n"
     "    }\n"
     "}\n"},
    {{EOpFaceforward, ParamType::Float3, ParamType::Float3, ParamType::Float3},
     "float3 faceforward_emu(float3 N, float3 I, float3 Nref)\n"
     "{\n"
     "    if(dot(Nref, I) >= 0)\n"
     "    {\n"
     "        return -N;\n"
     "    }\n"
     "    else\n"
     "    {\n"
     "        return N;\n"
     "    }\n"
     "}\n"},
    {{EOpFaceforward, ParamType::Float4, ParamType::Float4, ParamType::Float4},
     "float4 faceforward_emu(float4 N, float4 I, float4 Nref)\n"
     "{\n"
     "    if(dot(Nref, I) >= 0)\n"
     "    {\n"
     "        return -N;\n"
     "    }\n"
     "    else\n"
     "    {\n"
     "        return N;\n"
     "    }\n"
     "}\n"},
    {{EOpAtan, ParamType::Float1, ParamType::Float1},
     "float atan_emu(float y, float x)\n"
     "{\n"
     "    if(x == 0 && y == 0) x = 1;\n"
     "    return atan2(y, x);\n"
     "}\n"},
    {{EOpAtan, ParamType::Float2, ParamType::Float2},
     "float2 atan_emu(float2 y, float2 x)\n"
     "{\n"
     "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
     "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
     "    return float2(atan2(y[0], x[0]), atan2(y[1], x[1]));\n"
     "}\n"},
    {{EOpAtan, ParamType::Float3, ParamType::Float3},
     "float3 atan_emu(float3 y, float3 x)\n"
     "{\n"
     "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
     "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
     "    if(x[2] == 0 && y[2] == 0) x[2] = 1;\n"
     "    return float3(atan2(y[0], x[0]), atan2(y[1], x[1]), atan2(y[2], x[2]));\n"
     "}\n"},
    {{EOpAtan, ParamType::Float4, ParamType::Float4},
     "float4 atan_emu(float4 y, float4 x)\n"
     "{\n"
     "    if(x[0] == 0 && y[0] == 0) x[0] = 1;\n"
     "    if(x[1] == 0 && y[1] == 0) x[1] = 1;\n"
     "    if(x[2] == 0 && y[2] == 0) x[2] = 1;\n"
     "    if(x[3] == 0 && y[3] == 0) x[3] = 1;\n"
     "    return float4(atan2(y[0], x[0]), atan2(y[1], x[1]), atan2(y[2], \n"
     "    x[2]), atan2(y[3], x[3]));\n"
     "}\n"},
    {{EOpAsinh, ParamType::Float1},
     "float asinh_emu(in float x)\n"
     "{\n"
     "    return log(x + sqrt(pow(x, 2.0) + 1.0));\n"
     "}\n"},
    {{EOpAsinh, ParamType::Float2},
     "float2 asinh_emu(in float2 x)\n"
     "{\n"
     "    return log(x + sqrt(pow(x, 2.0) + 1.0));\n"
     "}\n"},
    {{EOpAsinh, ParamType::Float3},
     "float3 asinh_emu(in float3 x)\n"
     "{\n"
     "    return log(x + sqrt(pow(x, 2.0) + 1.0));\n"
     "}\n"},
    {{EOpAsinh, ParamType::Float4},
     "float4 asinh_emu(in float4 x)\n"
     "{\n"
     "    return log(x + sqrt(pow(x, 2.0) + 1.0));\n"
     "}\n"},
    {{EOpAcosh, ParamType::Float1},
     "float acosh_emu(in float x)\n"
     "{\n"
     "    return log(x + sqrt(x + 1.0) * sqrt(x - 1.0));\n"
     "}\n"},
    {{EOpAcosh, ParamType::Float2},
     "float2 acosh_emu(in float2 x)\n"
     "{\n"
     "    return log(x + sqrt(x + 1.0) * sqrt(x - 1.0));\n"
     "}\n"},
    {{EOpAcosh, ParamType::Float3},
     "float3 acosh_emu(in float3 x)\n"
     "{\n"
     "    return log(x + sqrt(x + 1.0) * sqrt(x - 1.0));\n"
     "}\n"},
    {{EOpAcosh, ParamType::Float4},
     "float4 acosh_emu(in float4 x)\n"
     "{\n"
     "    return log(x + sqrt(x + 1.0) * sqrt(x - 1.0));\n"
     "}\n"},
    {{EOpAtanh, ParamType::Float1},
     "float atanh_emu(in float x)\n"
     "{\n"
     "    return 0.5 * log((1.0 + x) / (1.0 - x));\n"
     "}\n"},
    {{EOpAtanh, ParamType::Float2},
     "float2 atanh_emu(in float2 x)\n"
     "{\n"
     "    return 0.5 * log((1.0 + x) / (1.0 - x));\n"
     "}\n"},
    {{EOpAtanh, ParamType::Float3},
     "float3 atanh_emu(in float3 x)\n"
     "{\n"
     "    return 0.5 * log((1.0 + x) / (1.0 - x));\n"
     "}\n"},
    {{EOpAtanh, ParamType::Float4},
     "float4 atanh_emu(in float4 x)\n"
     "{\n"
     "    return 0.5 * log((1.0 + x) / (1.0 - x));\n"
     "}\n"},
    {{EOpRoundEven, ParamType::Float1},
     "float roundEven_emu(in float x)\n"
     "{\n"
     "    return (frac(x) == 0.5 && trunc(x) % 2.0 == 0.0) ? trunc(x) : round(x);\n"
     "}\n"},
    {{EOpRoundEven, ParamType::Float2},
     "float2 roundEven_emu(in float2 x)\n"
     "{\n"
     "    float2 v;\n"
     "    v[0] = (frac(x[0]) == 0.5 && trunc(x[0]) % 2.0 == 0.0) ? trunc(x[0]) : round(x[0]);\n"
     "    v[1] = (frac(x[1]) == 0.5 && trunc(x[1]) % 2.0 == 0.0) ? trunc(x[1]) : round(x[1]);\n"
     "    return v;\n"
     "}\n"},
    {{EOpRoundEven, ParamType::Float3},
     "float3 roundEven_emu(in float3 x)\n"
     "{\n"
     "    float3 v;\n"
     "    v[0] = (frac(x[0]) == 0.5 && trunc(x[0]) % 2.0 == 0.0) ? trunc(x[0]) : round(x[0]);\n"
     "    v[1] = (frac(x[1]) == 0.5 && trunc(x[1]) % 2.0 == 0.0) ? trunc(x[1]) : round(x[1]);\n"
     "    v[2] = (frac(x[2]) == 0.5 && trunc(x[2]) % 2.0 == 0.0) ? trunc(x[2]) : round(x[2]);\n"
     "    return v;\n"
     "}\n"},
    {{EOpRoundEven, ParamType::Float4},
     "float4 roundEven_emu(in float4 x)\n"
     "{\n"
     "    float4 v;\n"
     "    v[0] = (frac(x[0]) == 0.5 && trunc(x[0]) % 2.0 == 0.0) ? trunc(x[0]) : round(x[0]);\n"
     "    v[1] = (frac(x[1]) == 0.5 && trunc(x[1]) % 2.0 == 0.0) ? trunc(x[1]) : round(x[1]);\n"
     "    v[2] = (frac(x[2]) == 0.5 && trunc(x[2]) % 2.0 == 0.0) ? trunc(x[2]) : round(x[2]);\n"
     "    v[3] = (frac(x[3]) == 0.5 && trunc(x[3]) % 2.0 == 0.0) ? trunc(x[3]) : round(x[3]);\n"
     "    return v;\n"
     "}\n"},
    {{EOpPackSnorm2x16, ParamType::Float2},
     "int webgl_toSnorm16(in float x) {\n"
     "    return int(round(clamp(x, -1.0, 1.0) * 32767.0));\n"
     "}\n"
     "uint packSnorm2x16_emu(in float2 v)\n"
     "{\n"
     "    int x = webgl_toSnorm16(v.x);\n"
     "    int y = webgl_toSnorm16(v.y);\n"
     "    return (asuint(y) << 16) | (asuint(x) & 0xffffu);\n"
     "}\n"},
    {{EOpPackUnorm2x16, ParamType::Float2},
     "uint webgl_toUnorm16(in float x) {\n"
     "    return uint(round(clamp(x, 0.0, 1.0) * 65535.0));\n"
     "}\n"
     "uint packUnorm2x16_emu(in float2 v)\n"
     "{\n"
     "    uint x = webgl_toUnorm16(v.x);\n"
     "    uint y = webgl_toUnorm16(v.y);\n"
     "    return (y << 16) | x;\n"
     "}\n"},
    {{EOpPackHalf2x16, ParamType::Float2},
     "uint packHalf2x16_emu(in float2 v)\n"
     "{\n"
     "    uint x = f32tof16(v.x);\n"
     "    uint y = f32tof16(v.y);\n"
     "    return (y << 16) | x;\n"
     "}\n"},
    {{EOpUnpackSnorm2x16, ParamType::Uint1},
     "float webgl_fromSnorm16(in uint x) {\n"
     "    int xi = asint(x & 0x7fffu) - asint(x & 0x8000u);\n"
     "    return clamp(float(xi) / 32767.0, -1.0, 1.0);\n"
     "}\n"
     "float2 unpackSnorm2x16_emu(in uint u)\n"
     "{\n"
     "    uint y = (u >> 16);\n"
     "    uint x = u;\n"
     "    return float2(webgl_fromSnorm16(x), webgl_fromSnorm16(y));\n"
     "}\n"},
    {{EOpUnpackUnorm2x16, ParamType::Uint1},
     "float webgl_fromUnorm16(in uint x) {\n"
     "    return float(x) / 65535.0;\n"
     "}\n"
     "float2 unpackUnorm2x16_emu(in uint u)\n"
     "{\n"
     "    uint y = (u >> 16);\n"
     "    uint x = u & 0xffffu;\n"
     "    return float2(webgl_fromUnorm16(x), webgl_fromUnorm16(y));\n"
     "}\n"},
    {{EOpUnpackHalf2x16, ParamType::Uint1},
     "float2 unpackHalf2x16_emu(in uint u)\n"
     "{\n"
     "    uint y = (u >> 16);\n"
     "    uint x = u & 0xffffu;\n"
     "    return float2(f16tof32(x), f16tof32(y));\n"
     "}\n"},
    {{EOpPackSnorm4x8, ParamType::Float4},
     "int webgl_toSnorm8(in float x) {\n"
     "    return int(round(clamp(x, -1.0, 1.0) * 127.0));\n"
     "}\n"
     "uint packSnorm4x8_emu(in float4 v)\n"
     "{\n"
     "    int x = webgl_toSnorm8(v.x);\n"
     "    int y = webgl_toSnorm8(v.y);\n"
     "    int z = webgl_toSnorm8(v.z);\n"
     "    int w = webgl_toSnorm8(v.w);\n"
     "    return ((asuint(w) & 0xffu) << 24) | ((asuint(z) & 0xffu) << 16) \n"
     "    | ((asuint(y) & 0xffu) << 8) | (asuint(x) & 0xffu);\n"
     "}\n"},
    {{EOpPackUnorm4x8, ParamType::Float4},
     "uint webgl_toUnorm8(in float x) {\n"
     "    return uint(round(clamp(x, 0.0, 1.0) * 255.0));\n"
     "}\n"
     "uint packUnorm4x8_emu(in float4 v)\n"
     "{\n"
     "    uint x = webgl_toUnorm8(v.x);\n"
     "    uint y = webgl_toUnorm8(v.y);\n"
     "    uint z = webgl_toUnorm8(v.z);\n"
     "    uint w = webgl_toUnorm8(v.w);\n"
     "    return (w << 24) | (z << 16) | (y << 8) | x;\n"
     "}\n"},
    {{EOpUnpackSnorm4x8, ParamType::Uint1},
     "float webgl_fromSnorm8(in uint x) {\n"
     "    int xi = asint(x & 0x7fu) - asint(x & 0x80u);\n"
     "    return clamp(float(xi) / 127.0, -1.0, 1.0);\n"
     "}\n"
     "float4 unpackSnorm4x8_emu(in uint u)\n"
     "{\n"
     "    uint w = (u >> 24);\n"
     "    uint z = (u >> 16);\n"
     "    uint y = (u >> 8);\n"
     "    uint x = u;\n"
     "    return float4(webgl_fromSnorm8(x), webgl_fromSnorm8(y), \n"
     "    webgl_fromSnorm8(z), webgl_fromSnorm8(w));\n"
     "}\n"},
    {{EOpUnpackUnorm4x8, ParamType::Uint1},
     "float webgl_fromUnorm8(in uint x) {\n"
     "    return float(x) / 255.0;\n"
     "}\n"
     "float4 unpackUnorm4x8_emu(in uint u)\n"
     "{\n"
     "    uint w = (u >> 24) & 0xffu;\n"
     "    uint z = (u >> 16) & 0xffu;\n"
     "    uint y = (u >> 8) & 0xffu;\n"
     "    uint x = u & 0xffu;\n"
     "    return float4(webgl_fromUnorm8(x), webgl_fromUnorm8(y), \n"
     "    webgl_fromUnorm8(z), webgl_fromUnorm8(w));\n"
     "}\n"},
    // The matrix resulting from outer product needs to be transposed
    // (matrices are stored as transposed to simplify element access in HLSL).
    // So the function should return transpose(c * r) where c is a column vector
    // and r is a row vector. This can be simplified by using the following
    // formula:
    // transpose(c * r) = transpose(r) * transpose(c)
    // transpose(r) and transpose(c) are in a sense free, since to get the
    // transpose of r, we simply can build a column matrix out of the original
    // vector instead of a row matrix.
    {{EOpOuterProduct, ParamType::Float2, ParamType::Float2},
     "float2x2 outerProduct_emu(in float2 c, in float2 r)\n"
     "{\n"
     "    return mul(float2x1(r), float1x2(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float3, ParamType::Float3},
     "float3x3 outerProduct_emu(in float3 c, in float3 r)\n"
     "{\n"
     "    return mul(float3x1(r), float1x3(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float4, ParamType::Float4},
     "float4x4 outerProduct_emu(in float4 c, in float4 r)\n"
     "{\n"
     "    return mul(float4x1(r), float1x4(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float3, ParamType::Float2},
     "float2x3 outerProduct_emu(in float3 c, in float2 r)\n"
     "{\n"
     "    return mul(float2x1(r), float1x3(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float2, ParamType::Float3},
     "float3x2 outerProduct_emu(in float2 c, in float3 r)\n"
     "{\n"
     "    return mul(float3x1(r), float1x2(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float4, ParamType::Float2},
     "float2x4 outerProduct_emu(in float4 c, in float2 r)\n"
     "{\n"
     "    return mul(float2x1(r), float1x4(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float2, ParamType::Float4},
     "float4x2 outerProduct_emu(in float2 c, in float4 r)\n"
     "{\n"
     "    return mul(float4x1(r), float1x2(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float4, ParamType::Float3},
     "float3x4 outerProduct_emu(in float4 c, in float3 r)\n"
     "{\n"
     "    return mul(float3x1(r), float1x4(c));\n"
     "}\n"},
    {{EOpOuterProduct, ParamType::Float3, ParamType::Float4},
     "float4x3 outerProduct_emu(in float3 c, in float4 r)\n"
     "{\n"
     "    return mul(float4x1(r), float1x3(c));\n"
     "}\n"},
    // Remember here that the parameter matrix is actually the transpose
    // of the matrix that we're trying to invert, and the resulting matrix
    // should also be the transpose of the inverse.
    // When accessing the parameter matrix with m[a][b] it can be thought of so
    // that a is the column and b is the row of the matrix that we're inverting.
    // We calculate the inverse as the adjugate matrix divided by the
    // determinant of the matrix being inverted. However, as the result needs
    // to be transposed, we actually use of the transpose of the adjugate matrix
    // which happens to be the cofactor matrix. That's stored in 'cof'.
    // We don't need to care about divide-by-zero since results are undefined
    // for singular or poorly-conditioned matrices.
    {{EOpInverse, ParamType::Mat2},
     "float2x2 inverse_emu(in float2x2 m)\n"
     "{\n"
     "    float2x2 cof = { m[1][1], -m[0][1], -m[1][0], m[0][0] };\n"
     "    return cof / determinant(transpose(m));\n"
     "}\n"},
    // cofAB is the cofactor for column A and row B.
    {{EOpInverse, ParamType::Mat3},
     "float3x3 inverse_emu(in float3x3 m)\n"
     "{\n"
     "    float cof00 = m[1][1] * m[2][2] - m[2][1] * m[1][2];\n"
     "    float cof01 = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);\n"
     "    float cof02 = m[1][0] * m[2][1] - m[2][0] * m[1][1];\n"
     "    float cof10 = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);\n"
     "    float cof11 = m[0][0] * m[2][2] - m[2][0] * m[0][2];\n"
     "    float cof12 = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);\n"
     "    float cof20 = m[0][1] * m[1][2] - m[1][1] * m[0][2];\n"
     "    float cof21 = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);\n"
     "    float cof22 = m[0][0] * m[1][1] - m[1][0] * m[0][1];\n"
     "    float3x3 cof = { cof00, cof10, cof20, cof01, cof11, cof21, cof02, cof12, cof22 };\n"
     "    return cof / determinant(transpose(m));\n"
     "}\n"},
    {{EOpInverse, ParamType::Mat4},
     "float4x4 inverse_emu(in float4x4 m)\n"
     "{\n"
     "    float cof00 = m[1][1] * m[2][2] * m[3][3] + m[2][1] * m[3][2] * m[1][3] + m[3][1] * \n"
     "    m[1][2] * m[2][3]\n"
     "     - m[1][1] * m[3][2] * m[2][3] - m[2][1] * m[1][2] * m[3][3] - m[3][1] * m[2][2] * \n"
     "    m[1][3];\n"
     "    float cof01 = -(m[1][0] * m[2][2] * m[3][3] + m[2][0] * m[3][2] * m[1][3] + m[3][0] * \n"
     "    m[1][2] * m[2][3]\n"
     "     - m[1][0] * m[3][2] * m[2][3] - m[2][0] * m[1][2] * m[3][3] - m[3][0] * m[2][2] * \n"
     "    m[1][3]);\n"
     "    float cof02 = m[1][0] * m[2][1] * m[3][3] + m[2][0] * m[3][1] * m[1][3] + m[3][0] * \n"
     "    m[1][1] * m[2][3]\n"
     "     - m[1][0] * m[3][1] * m[2][3] - m[2][0] * m[1][1] * m[3][3] - m[3][0] * m[2][1] * \n"
     "    m[1][3];\n"
     "    float cof03 = -(m[1][0] * m[2][1] * m[3][2] + m[2][0] * m[3][1] * m[1][2] + m[3][0] * \n"
     "    m[1][1] * m[2][2]\n"
     "     - m[1][0] * m[3][1] * m[2][2] - m[2][0] * m[1][1] * m[3][2] - m[3][0] * m[2][1] * \n"
     "    m[1][2]);\n"
     "    float cof10 = -(m[0][1] * m[2][2] * m[3][3] + m[2][1] * m[3][2] * m[0][3] + m[3][1] * \n"
     "    m[0][2] * m[2][3]\n"
     "     - m[0][1] * m[3][2] * m[2][3] - m[2][1] * m[0][2] * m[3][3] - m[3][1] * m[2][2] * \n"
     "    m[0][3]);\n"
     "    float cof11 = m[0][0] * m[2][2] * m[3][3] + m[2][0] * m[3][2] * m[0][3] + m[3][0] * \n"
     "    m[0][2] * m[2][3]\n"
     "     - m[0][0] * m[3][2] * m[2][3] - m[2][0] * m[0][2] * m[3][3] - m[3][0] * m[2][2] * \n"
     "    m[0][3];\n"
     "    float cof12 = -(m[0][0] * m[2][1] * m[3][3] + m[2][0] * m[3][1] * m[0][3] + m[3][0] * \n"
     "    m[0][1] * m[2][3]\n"
     "     - m[0][0] * m[3][1] * m[2][3] - m[2][0] * m[0][1] * m[3][3] - m[3][0] * m[2][1] * \n"
     "    m[0][3]);\n"
     "    float cof13 = m[0][0] * m[2][1] * m[3][2] + m[2][0] * m[3][1] * m[0][2] + m[3][0] * \n"
     "    m[0][1] * m[2][2]\n"
     "     - m[0][0] * m[3][1] * m[2][2] - m[2][0] * m[0][1] * m[3][2] - m[3][0] * m[2][1] * \n"
     "    m[0][2];\n"
     "    float cof20 = m[0][1] * m[1][2] * m[3][3] + m[1][1] * m[3][2] * m[0][3] + m[3][1] * \n"
     "    m[0][2] * m[1][3]\n"
     "     - m[0][1] * m[3][2] * m[1][3] - m[1][1] * m[0][2] * m[3][3] - m[3][1] * m[1][2] * \n"
     "    m[0][3];\n"
     "    float cof21 = -(m[0][0] * m[1][2] * m[3][3] + m[1][0] * m[3][2] * m[0][3] + m[3][0] * \n"
     "    m[0][2] * m[1][3]\n"
     "     - m[0][0] * m[3][2] * m[1][3] - m[1][0] * m[0][2] * m[3][3] - m[3][0] * m[1][2] * \n"
     "    m[0][3]);\n"
     "    float cof22 = m[0][0] * m[1][1] * m[3][3] + m[1][0] * m[3][1] * m[0][3] + m[3][0] * \n"
     "    m[0][1] * m[1][3]\n"
     "     - m[0][0] * m[3][1] * m[1][3] - m[1][0] * m[0][1] * m[3][3] - m[3][0] * m[1][1] * \n"
     "    m[0][3];\n"
     "    float cof23 = -(m[0][0] * m[1][1] * m[3][2] + m[1][0] * m[3][1] * m[0][2] + m[3][0] * \n"
     "    m[0][1] * m[1][2]\n"
     "     - m[0][0] * m[3][1] * m[1][2] - m[1][0] * m[0][1] * m[3][2] - m[3][0] * m[1][1] * \n"
     "    m[0][2]);\n"
     "    float cof30 = -(m[0][1] * m[1][2] * m[2][3] + m[1][1] * m[2][2] * m[0][3] + m[2][1] * \n"
     "    m[0][2] * m[1][3]\n"
     "     - m[0][1] * m[2][2] * m[1][3] - m[1][1] * m[0][2] * m[2][3] - m[2][1] * m[1][2] * \n"
     "    m[0][3]);\n"
     "    float cof31 = m[0][0] * m[1][2] * m[2][3] + m[1][0] * m[2][2] * m[0][3] + m[2][0] * \n"
     "    m[0][2] * m[1][3]\n"
     "     - m[0][0] * m[2][2] * m[1][3] - m[1][0] * m[0][2] * m[2][3] - m[2][0] * m[1][2] * \n"
     "    m[0][3];\n"
     "    float cof32 = -(m[0][0] * m[1][1] * m[2][3] + m[1][0] * m[2][1] * m[0][3] + m[2][0] * \n"
     "    m[0][1] * m[1][3]\n"
     "     - m[0][0] * m[2][1] * m[1][3] - m[1][0] * m[0][1] * m[2][3] - m[2][0] * m[1][1] * \n"
     "    m[0][3]);\n"
     "    float cof33 = m[0][0] * m[1][1] * m[2][2] + m[1][0] * m[2][1] * m[0][2] + m[2][0] * \n"
     "    m[0][1] * m[1][2]\n"
     "     - m[0][0] * m[2][1] * m[1][2] - m[1][0] * m[0][1] * m[2][2] - m[2][0] * m[1][1] * \n"
     "    m[0][2];\n"
     "    float4x4 cof = { cof00, cof10, cof20, cof30, cof01, cof11, cof21, cof31,\n"
     "     cof02, cof12, cof22, cof32, cof03, cof13, cof23, cof33 };\n"
     "    return cof / determinant(transpose(m));\n"
     "}\n"},
    // Emulate ESSL3 variant of mix that takes last argument as boolean vector.
    // genType mix(genType x, genType y, genBType a): Selects which vector each returned component
    // comes from. For a component of 'a' that is false, the corresponding component of 'x' is
    // returned. For a component of 'a' that is true, the corresponding component of 'y' is
    // returned.
    {{EOpMix, ParamType::Float1, ParamType::Float1, ParamType::Bool1},
     "float mix_emu(float x, float y, bool a)\n"
     "{\n"
     "    return a ? y : x;\n"
     "}\n"},
    {{EOpMix, ParamType::Float2, ParamType::Float2, ParamType::Bool2},
     "float2 mix_emu(float2 x, float2 y, bool2 a)\n"
     "{\n"
     "    return a ? y : x;\n"
     "}\n"},
    {{EOpMix, ParamType::Float3, ParamType::Float3, ParamType::Bool3},
     "float3 mix_emu(float3 x, float3 y, bool3 a)\n"
     "{\n"
     "    return a ? y : x;\n"
     "}\n"},
    {{EOpMix, ParamType::Float4, ParamType::Float4, ParamType::Bool4},
     "float4 mix_emu(float4 x, float4 y, bool4 a)\n"
     "{\n"
     "    return a ? y : x;\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Uint1, ParamType::Int1, ParamType::Int1},
     "uint bitfieldExtract_emu(uint value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return 0u;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    return (value & mask) >> offset;\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Uint2, ParamType::Int1, ParamType::Int1},
     "uint2 bitfieldExtract_emu(uint2 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return uint2(0u, 0u);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    return (value & mask) >> offset;\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Uint3, ParamType::Int1, ParamType::Int1},
     "uint3 bitfieldExtract_emu(uint3 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return uint3(0u, 0u, 0u);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    return (value & mask) >> offset;\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Uint4, ParamType::Int1, ParamType::Int1},
     "uint4 bitfieldExtract_emu(uint4 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return uint4(0u, 0u, 0u, 0u);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    return (value & mask) >> offset;\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Int1, ParamType::Int1, ParamType::Int1},
     "int bitfieldExtract_emu(int value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return 0;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint resultUnsigned = (asuint(value) & mask) >> offset;\n"
     "    if (bits != 32 && (resultUnsigned & maskMsb) != 0)\n"
     "    {\n"
     "        uint higherBitsMask = ((1u << (32 - bits)) - 1u) << bits;\n"
     "        resultUnsigned |= higherBitsMask;\n"
     "    }\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Int2, ParamType::Int1, ParamType::Int1},
     "int2 bitfieldExtract_emu(int2 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return int2(0, 0);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint2 resultUnsigned = (asuint(value) & mask) >> offset;\n"
     "    if (bits != 32)\n"
     "    {\n"
     "        uint higherBitsMask = ((1u << (32 - bits)) - 1u) << bits;\n"
     "        resultUnsigned |= ((resultUnsigned & maskMsb) >> (bits - 1)) * higherBitsMask;\n"
     "    }\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Int3, ParamType::Int1, ParamType::Int1},
     "int3 bitfieldExtract_emu(int3 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return int3(0, 0, 0);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint3 resultUnsigned = (asuint(value) & mask) >> offset;\n"
     "    if (bits != 32)\n"
     "    {\n"
     "        uint higherBitsMask = ((1u << (32 - bits)) - 1u) << bits;\n"
     "        resultUnsigned |= ((resultUnsigned & maskMsb) >> (bits - 1)) * higherBitsMask;\n"
     "    }\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldExtract, ParamType::Int4, ParamType::Int1, ParamType::Int1},
     "int4 bitfieldExtract_emu(int4 value, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return int4(0, 0, 0, 0);\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint mask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint4 resultUnsigned = (asuint(value) & mask) >> offset;\n"
     "    if (bits != 32)\n"
     "    {\n"
     "        uint higherBitsMask = ((1u << (32 - bits)) - 1u) << bits;\n"
     "        resultUnsigned |= ((resultUnsigned & maskMsb) >> (bits - 1)) * higherBitsMask;\n"
     "    }\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Uint1, ParamType::Uint1, ParamType::Int1, ParamType::Int1},
     "uint bitfieldInsert_emu(uint base, uint insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    return (base & baseMask) | ((insert << offset) & insertMask);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Uint2, ParamType::Uint2, ParamType::Int1, ParamType::Int1},
     "uint2 bitfieldInsert_emu(uint2 base, uint2 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    return (base & baseMask) | ((insert << offset) & insertMask);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Uint3, ParamType::Uint3, ParamType::Int1, ParamType::Int1},
     "uint3 bitfieldInsert_emu(uint3 base, uint3 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    return (base & baseMask) | ((insert << offset) & insertMask);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Uint4, ParamType::Uint4, ParamType::Int1, ParamType::Int1},
     "uint4 bitfieldInsert_emu(uint4 base, uint4 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    return (base & baseMask) | ((insert << offset) & insertMask);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Int1, ParamType::Int1, ParamType::Int1, ParamType::Int1},
     "int bitfieldInsert_emu(int base, int insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    uint resultUnsigned = (asuint(base) & baseMask) | ((asuint(insert) << offset) & \n"
     "                           insertMask);\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Int2, ParamType::Int2, ParamType::Int1, ParamType::Int1},
     "int2 bitfieldInsert_emu(int2 base, int2 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    uint2 resultUnsigned = (asuint(base) & baseMask) | ((asuint(insert) << offset) & \n"
     "                            insertMask);\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Int3, ParamType::Int3, ParamType::Int1, ParamType::Int1},
     "int3 bitfieldInsert_emu(int3 base, int3 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    uint3 resultUnsigned = (asuint(base) & baseMask) | ((asuint(insert) << offset) & \n"
     "                            insertMask);\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpBitfieldInsert, ParamType::Int4, ParamType::Int4, ParamType::Int1, ParamType::Int1},
     "int4 bitfieldInsert_emu(int4 base, int4 insert, int offset, int bits)\n"
     "{\n"
     "    if (offset < 0 || bits <= 0 || offset >= 32 || bits > 32 || offset + bits > 32)\n"
     "    {\n"
     "        return base;\n"
     "    }\n"
     "    uint maskMsb = (1u << (bits - 1));\n"
     "    uint insertMask = ((maskMsb - 1u) | maskMsb) << offset;\n"
     "    uint baseMask = ~insertMask;\n"
     "    uint4 resultUnsigned = (asuint(base) & baseMask) | ((asuint(insert) << offset) & \n"
     "    insertMask);\n"
     "    return asint(resultUnsigned);\n"
     "}\n"},
    {{EOpUaddCarry, ParamType::Uint1, ParamType::Uint1, ParamType::Uint1},
     "uint uaddCarry_emu(uint x, uint y, out uint carry)\n"
     "{\n"
     "    carry = uint(x > (0xffffffffu - y));\n"
     "    return x + y;\n"
     "}\n"},
    {{EOpUaddCarry, ParamType::Uint2, ParamType::Uint2, ParamType::Uint2},
     "uint2 uaddCarry_emu(uint2 x, uint2 y, out uint2 carry)\n"
     "{\n"
     "    carry = uint2(x > (0xffffffffu - y));\n"
     "    return x + y;\n"
     "}\n"},
    {{EOpUaddCarry, ParamType::Uint3, ParamType::Uint3, ParamType::Uint3},
     "uint3 uaddCarry_emu(uint3 x, uint3 y, out uint3 carry)\n"
     "{\n"
     "    carry = uint3(x > (0xffffffffu - y));\n"
     "    return x + y;\n"
     "}\n"},
    {{EOpUaddCarry, ParamType::Uint4, ParamType::Uint4, ParamType::Uint4},
     "uint4 uaddCarry_emu(uint4 x, uint4 y, out uint4 carry)\n"
     "{\n"
     "    carry = uint4(x > (0xffffffffu - y));\n"
     "    return x + y;\n"
     "}\n"},
    {{EOpUsubBorrow, ParamType::Uint1, ParamType::Uint1, ParamType::Uint1},
     "uint usubBorrow_emu(uint x, uint y, out uint borrow)\n"
     "{\n"
     "    borrow = uint(x < y);\n"
     "    return x - y;\n"
     "}\n"},
    {{EOpUsubBorrow, ParamType::Uint2, ParamType::Uint2, ParamType::Uint2},
     "uint2 usubBorrow_emu(uint2 x, uint2 y, out uint2 borrow)\n"
     "{\n"
     "    borrow = uint2(x < y);\n"
     "    return x - y;\n"
     "}\n"},
    {{EOpUsubBorrow, ParamType::Uint3, ParamType::Uint3, ParamType::Uint3},
     "uint3 usubBorrow_emu(uint3 x, uint3 y, out uint3 borrow)\n"
     "{\n"
     "    borrow = uint3(x < y);\n"
     "    return x - y;\n"
     "}\n"},
    {{EOpUsubBorrow, ParamType::Uint4, ParamType::Uint4, ParamType::Uint4},
     "uint4 usubBorrow_emu(uint4 x, uint4 y, out uint4 borrow)\n"
     "{\n"
     "    borrow = uint4(x < y);\n"
     "    return x - y;\n"
     "}\n"},
    // We emulate tanh just to avoid overflow on large arguments.
    {{EOpTanh, ParamType::Float1},
     "float tanh_emu(float x)\n"
     "{\n"
     "    return (abs(x) > 15.0) ? sign(x) : tanh(x);\n"
     "}\n"},
    {{EOpTanh, ParamType::Float2},
     "float2 tanh_emu(float2 x)\n"
     "{\n"
     "    return (abs(x) > 15.0) ? sign(x) : tanh(x);\n"
     "}\n"},
    {{EOpTanh, ParamType::Float3},
     "float3 tanh_emu(float3 x)\n"
     "{\n"
     "    return (abs(x) > 15.0) ? sign(x) : tanh(x);\n"
     "}\n"},
    {{EOpTanh, ParamType::Float4},
     "float4 tanh_emu(float4 x)\n"
     "{\n"
     "    return (abs(x) > 15.0) ? sign(x) : tanh(x);\n"
     "}\n"},
};
}  // anonymous namespace

const char *FindHLSLFunction(const FunctionId &functionID)
{
    for (size_t index = 0; index < ArraySize(g_hlslFunctions); ++index)
    {
        const auto &function = g_hlslFunctions[index];
        if (function.id == functionID)
        {
            return function.body;
        }
    }

    return nullptr;
}
}  // namespace sh
