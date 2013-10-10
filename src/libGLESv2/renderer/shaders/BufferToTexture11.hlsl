Buffer<float4>    Buffer4F  : register(t0);
Buffer<float2>    Buffer2F  : register(t0);
Buffer<float1>    Buffer1F  : register(t0);

Buffer<int4>      Buffer4I  : register(t0);
Buffer<int2>      Buffer2I  : register(t0);
Buffer<int1>      Buffer1I  : register(t0);

Buffer<uint4>     Buffer4UI : register(t0);
Buffer<uint2>     Buffer2UI : register(t0);
Buffer<uint1>     Buffer1UI : register(t0);

struct VS_OUTPUT
{
    float4 position : SV_Position;
    uint index      : TEXCOORD0;
    uint slice      : LAYER;
};

cbuffer BufferCopyParams : register(b0)
{
    uint FirstPixelOffset;
    uint PixelsPerRow;
    uint RowStride;
    uint RowsPerSlice;
    float2 PositionOffset;
    float2 PositionScale;
    int2 TexLocationOffset;
    int2 TexLocationScale;
}

void ComputePositionAndIndex(uint vertexID, out VS_OUTPUT outVertex)
{
    uint PixelsPerSlice = PixelsPerRow * RowsPerSlice;
    uint SliceStride    = RowStride * RowsPerSlice;

    uint slice          = vertexID / PixelsPerSlice;
    uint sliceOffset    = slice * PixelsPerSlice;
    uint row            = (vertexID - sliceOffset) / PixelsPerRow;
    uint col            = vertexID - sliceOffset - (row * PixelsPerRow);

    float2 coords       = float2(float(col), float(row));

    outVertex.position  = float4(PositionOffset + PositionScale * coords, 0.0f, 1.0f);
    outVertex.index     = FirstPixelOffset + slice * SliceStride + row * RowStride + col;
    outVertex.slice     = slice;
}

void VS_BufferToTexture(in uint vertexID : SV_VertexID, out VS_OUTPUT outVertex)
{
    ComputePositionAndIndex(vertexID, outVertex);
}

float4 PS_BufferToTexture_4F(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer4F.Load(inIndex);
}

float2 PS_BufferToTexture_2F(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer2F.Load(inIndex);
}

float1 PS_BufferToTexture_1F(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer1F.Load(inIndex);
}

int4 PS_BufferToTexture_4I(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer4I.Load(inIndex);
}

int2 PS_BufferToTexture_2I(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer2I.Load(inIndex);
}

int1 PS_BufferToTexture_1I(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer1I.Load(inIndex);
}

uint4 PS_BufferToTexture_4UI(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer4UI.Load(inIndex);
}

uint2 PS_BufferToTexture_2UI(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer2UI.Load(inIndex);
}

uint1 PS_BufferToTexture_1UI(in float4 inPosition : SV_Position, in uint inIndex : TEXCOORD0) : SV_Target
{
    return Buffer1UI.Load(inIndex);
}
