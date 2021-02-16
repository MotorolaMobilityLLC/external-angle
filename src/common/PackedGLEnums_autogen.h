// GENERATED FILE - DO NOT EDIT.
// Generated by gen_packed_gl_enums.py using data from packed_gl_enums.json.
//
// Copyright 2021 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// PackedGLEnums_autogen.h:
//   Declares ANGLE-specific enums classes for GLenums and functions operating
//   on them.

#ifndef COMMON_PACKEDGLENUMS_AUTOGEN_H_
#define COMMON_PACKEDGLENUMS_AUTOGEN_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <angle_gl.h>

#include <cstdint>
#include <ostream>

namespace gl
{

template <typename Enum>
Enum FromGLenum(GLenum from);

enum class AlphaTestFunc : uint8_t
{
    AlwaysPass = 0,
    Equal      = 1,
    Gequal     = 2,
    Greater    = 3,
    Lequal     = 4,
    Less       = 5,
    Never      = 6,
    NotEqual   = 7,

    InvalidEnum = 8,
    EnumCount   = 8,
};

template <>
AlphaTestFunc FromGLenum<AlphaTestFunc>(GLenum from);
GLenum ToGLenum(AlphaTestFunc from);
std::ostream &operator<<(std::ostream &os, AlphaTestFunc value);

enum class BufferBinding : uint8_t
{
    Array             = 0,
    AtomicCounter     = 1,
    CopyRead          = 2,
    CopyWrite         = 3,
    DispatchIndirect  = 4,
    DrawIndirect      = 5,
    ElementArray      = 6,
    PixelPack         = 7,
    PixelUnpack       = 8,
    ShaderStorage     = 9,
    Texture           = 10,
    TransformFeedback = 11,
    Uniform           = 12,

    InvalidEnum = 13,
    EnumCount   = 13,
};

template <>
BufferBinding FromGLenum<BufferBinding>(GLenum from);
GLenum ToGLenum(BufferBinding from);
std::ostream &operator<<(std::ostream &os, BufferBinding value);

enum class BufferUsage : uint8_t
{
    DynamicCopy = 0,
    DynamicDraw = 1,
    DynamicRead = 2,
    StaticCopy  = 3,
    StaticDraw  = 4,
    StaticRead  = 5,
    StreamCopy  = 6,
    StreamDraw  = 7,
    StreamRead  = 8,

    InvalidEnum = 9,
    EnumCount   = 9,
};

template <>
BufferUsage FromGLenum<BufferUsage>(GLenum from);
GLenum ToGLenum(BufferUsage from);
std::ostream &operator<<(std::ostream &os, BufferUsage value);

enum class ClientVertexArrayType : uint8_t
{
    Color        = 0,
    Normal       = 1,
    PointSize    = 2,
    TextureCoord = 3,
    Vertex       = 4,

    InvalidEnum = 5,
    EnumCount   = 5,
};

template <>
ClientVertexArrayType FromGLenum<ClientVertexArrayType>(GLenum from);
GLenum ToGLenum(ClientVertexArrayType from);
std::ostream &operator<<(std::ostream &os, ClientVertexArrayType value);

enum class CullFaceMode : uint8_t
{
    Back         = 0,
    Front        = 1,
    FrontAndBack = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
CullFaceMode FromGLenum<CullFaceMode>(GLenum from);
GLenum ToGLenum(CullFaceMode from);
std::ostream &operator<<(std::ostream &os, CullFaceMode value);

enum class FilterMode : uint8_t
{
    Nearest              = 0,
    Linear               = 1,
    NearestMipmapNearest = 2,
    NearestMipmapLinear  = 3,
    LinearMipmapLinear   = 4,

    InvalidEnum = 5,
    EnumCount   = 5,
};

template <>
FilterMode FromGLenum<FilterMode>(GLenum from);
GLenum ToGLenum(FilterMode from);
std::ostream &operator<<(std::ostream &os, FilterMode value);

enum class FogMode : uint8_t
{
    Exp    = 0,
    Exp2   = 1,
    Linear = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
FogMode FromGLenum<FogMode>(GLenum from);
GLenum ToGLenum(FogMode from);
std::ostream &operator<<(std::ostream &os, FogMode value);

enum class GraphicsResetStatus : uint8_t
{
    NoError              = 0,
    GuiltyContextReset   = 1,
    InnocentContextReset = 2,
    UnknownContextReset  = 3,
    PurgedContextResetNV = 4,

    InvalidEnum = 5,
    EnumCount   = 5,
};

template <>
GraphicsResetStatus FromGLenum<GraphicsResetStatus>(GLenum from);
GLenum ToGLenum(GraphicsResetStatus from);
std::ostream &operator<<(std::ostream &os, GraphicsResetStatus value);

enum class HandleType : uint8_t
{
    OpaqueFd    = 0,
    ZirconVmo   = 1,
    ZirconEvent = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
HandleType FromGLenum<HandleType>(GLenum from);
GLenum ToGLenum(HandleType from);
std::ostream &operator<<(std::ostream &os, HandleType value);

enum class HintSetting : uint8_t
{
    DontCare = 0,
    Fastest  = 1,
    Nicest   = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
HintSetting FromGLenum<HintSetting>(GLenum from);
GLenum ToGLenum(HintSetting from);
std::ostream &operator<<(std::ostream &os, HintSetting value);

enum class ImageLayout : uint8_t
{
    Undefined                      = 0,
    General                        = 1,
    ColorAttachment                = 2,
    DepthStencilAttachment         = 3,
    DepthStencilReadOnlyAttachment = 4,
    ShaderReadOnly                 = 5,
    TransferSrc                    = 6,
    TransferDst                    = 7,
    DepthReadOnlyStencilAttachment = 8,
    DepthAttachmentStencilReadOnly = 9,

    InvalidEnum = 10,
    EnumCount   = 10,
};

template <>
ImageLayout FromGLenum<ImageLayout>(GLenum from);
GLenum ToGLenum(ImageLayout from);
std::ostream &operator<<(std::ostream &os, ImageLayout value);

enum class LightParameter : uint8_t
{
    Ambient              = 0,
    AmbientAndDiffuse    = 1,
    ConstantAttenuation  = 2,
    Diffuse              = 3,
    LinearAttenuation    = 4,
    Position             = 5,
    QuadraticAttenuation = 6,
    Specular             = 7,
    SpotCutoff           = 8,
    SpotDirection        = 9,
    SpotExponent         = 10,

    InvalidEnum = 11,
    EnumCount   = 11,
};

template <>
LightParameter FromGLenum<LightParameter>(GLenum from);
GLenum ToGLenum(LightParameter from);
std::ostream &operator<<(std::ostream &os, LightParameter value);

enum class LogicalOperation : uint8_t
{
    And          = 0,
    AndInverted  = 1,
    AndReverse   = 2,
    Clear        = 3,
    Copy         = 4,
    CopyInverted = 5,
    Equiv        = 6,
    Invert       = 7,
    Nand         = 8,
    Noop         = 9,
    Nor          = 10,
    Or           = 11,
    OrInverted   = 12,
    OrReverse    = 13,
    Set          = 14,
    Xor          = 15,

    InvalidEnum = 16,
    EnumCount   = 16,
};

template <>
LogicalOperation FromGLenum<LogicalOperation>(GLenum from);
GLenum ToGLenum(LogicalOperation from);
std::ostream &operator<<(std::ostream &os, LogicalOperation value);

enum class MaterialParameter : uint8_t
{
    Ambient           = 0,
    AmbientAndDiffuse = 1,
    Diffuse           = 2,
    Emission          = 3,
    Shininess         = 4,
    Specular          = 5,

    InvalidEnum = 6,
    EnumCount   = 6,
};

template <>
MaterialParameter FromGLenum<MaterialParameter>(GLenum from);
GLenum ToGLenum(MaterialParameter from);
std::ostream &operator<<(std::ostream &os, MaterialParameter value);

enum class MatrixType : uint8_t
{
    Modelview  = 0,
    Projection = 1,
    Texture    = 2,

    InvalidEnum = 3,
    EnumCount   = 3,
};

template <>
MatrixType FromGLenum<MatrixType>(GLenum from);
GLenum ToGLenum(MatrixType from);
std::ostream &operator<<(std::ostream &os, MatrixType value);

enum class PointParameter : uint8_t
{
    PointSizeMin             = 0,
    PointSizeMax             = 1,
    PointFadeThresholdSize   = 2,
    PointDistanceAttenuation = 3,

    InvalidEnum = 4,
    EnumCount   = 4,
};

template <>
PointParameter FromGLenum<PointParameter>(GLenum from);
GLenum ToGLenum(PointParameter from);
std::ostream &operator<<(std::ostream &os, PointParameter value);

enum class ProvokingVertexConvention : uint8_t
{
    FirstVertexConvention = 0,
    LastVertexConvention  = 1,

    InvalidEnum = 2,
    EnumCount   = 2,
};

template <>
ProvokingVertexConvention FromGLenum<ProvokingVertexConvention>(GLenum from);
GLenum ToGLenum(ProvokingVertexConvention from);
std::ostream &operator<<(std::ostream &os, ProvokingVertexConvention value);

enum class QueryType : uint8_t
{
    AnySamples                         = 0,
    AnySamplesConservative             = 1,
    CommandsCompleted                  = 2,
    PrimitivesGenerated                = 3,
    TimeElapsed                        = 4,
    Timestamp                          = 5,
    TransformFeedbackPrimitivesWritten = 6,

    InvalidEnum = 7,
    EnumCount   = 7,
};

template <>
QueryType FromGLenum<QueryType>(GLenum from);
GLenum ToGLenum(QueryType from);
std::ostream &operator<<(std::ostream &os, QueryType value);

enum class ShaderType : uint8_t
{
    Vertex         = 0,
    TessControl    = 1,
    TessEvaluation = 2,
    Geometry       = 3,
    Fragment       = 4,
    Compute        = 5,

    InvalidEnum = 6,
    EnumCount   = 6,
};

template <>
ShaderType FromGLenum<ShaderType>(GLenum from);
GLenum ToGLenum(ShaderType from);
std::ostream &operator<<(std::ostream &os, ShaderType value);

enum class ShadingModel : uint8_t
{
    Flat   = 0,
    Smooth = 1,

    InvalidEnum = 2,
    EnumCount   = 2,
};

template <>
ShadingModel FromGLenum<ShadingModel>(GLenum from);
GLenum ToGLenum(ShadingModel from);
std::ostream &operator<<(std::ostream &os, ShadingModel value);

enum class TextureCombine : uint8_t
{
    Add         = 0,
    AddSigned   = 1,
    Dot3Rgb     = 2,
    Dot3Rgba    = 3,
    Interpolate = 4,
    Modulate    = 5,
    Replace     = 6,
    Subtract    = 7,

    InvalidEnum = 8,
    EnumCount   = 8,
};

template <>
TextureCombine FromGLenum<TextureCombine>(GLenum from);
GLenum ToGLenum(TextureCombine from);
std::ostream &operator<<(std::ostream &os, TextureCombine value);

enum class TextureEnvMode : uint8_t
{
    Add      = 0,
    Blend    = 1,
    Combine  = 2,
    Decal    = 3,
    Modulate = 4,
    Replace  = 5,

    InvalidEnum = 6,
    EnumCount   = 6,
};

template <>
TextureEnvMode FromGLenum<TextureEnvMode>(GLenum from);
GLenum ToGLenum(TextureEnvMode from);
std::ostream &operator<<(std::ostream &os, TextureEnvMode value);

enum class TextureEnvParameter : uint8_t
{
    Mode              = 0,
    Color             = 1,
    CombineRgb        = 2,
    CombineAlpha      = 3,
    RgbScale          = 4,
    AlphaScale        = 5,
    Src0Rgb           = 6,
    Src1Rgb           = 7,
    Src2Rgb           = 8,
    Src0Alpha         = 9,
    Src1Alpha         = 10,
    Src2Alpha         = 11,
    Op0Rgb            = 12,
    Op1Rgb            = 13,
    Op2Rgb            = 14,
    Op0Alpha          = 15,
    Op1Alpha          = 16,
    Op2Alpha          = 17,
    PointCoordReplace = 18,

    InvalidEnum = 19,
    EnumCount   = 19,
};

template <>
TextureEnvParameter FromGLenum<TextureEnvParameter>(GLenum from);
GLenum ToGLenum(TextureEnvParameter from);
std::ostream &operator<<(std::ostream &os, TextureEnvParameter value);

enum class TextureEnvTarget : uint8_t
{
    Env         = 0,
    PointSprite = 1,

    InvalidEnum = 2,
    EnumCount   = 2,
};

template <>
TextureEnvTarget FromGLenum<TextureEnvTarget>(GLenum from);
GLenum ToGLenum(TextureEnvTarget from);
std::ostream &operator<<(std::ostream &os, TextureEnvTarget value);

enum class TextureOp : uint8_t
{
    OneMinusSrcAlpha = 0,
    OneMinusSrcColor = 1,
    SrcAlpha         = 2,
    SrcColor         = 3,

    InvalidEnum = 4,
    EnumCount   = 4,
};

template <>
TextureOp FromGLenum<TextureOp>(GLenum from);
GLenum ToGLenum(TextureOp from);
std::ostream &operator<<(std::ostream &os, TextureOp value);

enum class TextureSrc : uint8_t
{
    Constant     = 0,
    Previous     = 1,
    PrimaryColor = 2,
    Texture      = 3,

    InvalidEnum = 4,
    EnumCount   = 4,
};

template <>
TextureSrc FromGLenum<TextureSrc>(GLenum from);
GLenum ToGLenum(TextureSrc from);
std::ostream &operator<<(std::ostream &os, TextureSrc value);

enum class TextureTarget : uint8_t
{
    _2D                 = 0,
    _2DArray            = 1,
    _2DMultisample      = 2,
    _2DMultisampleArray = 3,
    _3D                 = 4,
    External            = 5,
    Rectangle           = 6,
    CubeMapPositiveX    = 7,
    CubeMapNegativeX    = 8,
    CubeMapPositiveY    = 9,
    CubeMapNegativeY    = 10,
    CubeMapPositiveZ    = 11,
    CubeMapNegativeZ    = 12,
    CubeMapArray        = 13,
    VideoImage          = 14,
    Buffer              = 15,

    InvalidEnum = 16,
    EnumCount   = 16,
};

template <>
TextureTarget FromGLenum<TextureTarget>(GLenum from);
GLenum ToGLenum(TextureTarget from);
std::ostream &operator<<(std::ostream &os, TextureTarget value);

enum class TextureType : uint8_t
{
    _2D                 = 0,
    _2DArray            = 1,
    _2DMultisample      = 2,
    _2DMultisampleArray = 3,
    _3D                 = 4,
    External            = 5,
    Rectangle           = 6,
    CubeMap             = 7,
    CubeMapArray        = 8,
    VideoImage          = 9,
    Buffer              = 10,

    InvalidEnum = 11,
    EnumCount   = 11,
};

template <>
TextureType FromGLenum<TextureType>(GLenum from);
GLenum ToGLenum(TextureType from);
std::ostream &operator<<(std::ostream &os, TextureType value);

enum class VertexArrayType : uint8_t
{
    Color        = 0,
    Normal       = 1,
    PointSize    = 2,
    TextureCoord = 3,
    Vertex       = 4,

    InvalidEnum = 5,
    EnumCount   = 5,
};

template <>
VertexArrayType FromGLenum<VertexArrayType>(GLenum from);
GLenum ToGLenum(VertexArrayType from);
std::ostream &operator<<(std::ostream &os, VertexArrayType value);

enum class WrapMode : uint8_t
{
    ClampToEdge    = 0,
    ClampToBorder  = 1,
    MirroredRepeat = 2,
    Repeat         = 3,

    InvalidEnum = 4,
    EnumCount   = 4,
};

template <>
WrapMode FromGLenum<WrapMode>(GLenum from);
GLenum ToGLenum(WrapMode from);
std::ostream &operator<<(std::ostream &os, WrapMode value);

}  // namespace gl

#endif  // COMMON_PACKEDGLENUMS_AUTOGEN_H_
