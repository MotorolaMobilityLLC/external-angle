//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ContextMtl.mm:
//    Implements the class methods for ContextMtl.
//

#include "libANGLE/renderer/metal/ContextMtl.h"

#include <TargetConditionals.h>

#include "common/debug.h"
#include "libANGLE/TransformFeedback.h"
#include "libANGLE/renderer/metal/BufferMtl.h"
#include "libANGLE/renderer/metal/CompilerMtl.h"
#include "libANGLE/renderer/metal/DisplayMtl.h"
#include "libANGLE/renderer/metal/FrameBufferMtl.h"
#include "libANGLE/renderer/metal/ProgramMtl.h"
#include "libANGLE/renderer/metal/QueryMtl.h"
#include "libANGLE/renderer/metal/RenderBufferMtl.h"
#include "libANGLE/renderer/metal/RenderTargetMtl.h"
#include "libANGLE/renderer/metal/SamplerMtl.h"
#include "libANGLE/renderer/metal/ShaderMtl.h"
#include "libANGLE/renderer/metal/SyncMtl.h"
#include "libANGLE/renderer/metal/TextureMtl.h"
#include "libANGLE/renderer/metal/TransformFeedbackMtl.h"
#include "libANGLE/renderer/metal/VertexArrayMtl.h"
#include "libANGLE/renderer/metal/mtl_command_buffer.h"
#include "libANGLE/renderer/metal/mtl_format_utils.h"
#include "libANGLE/renderer/metal/mtl_utils.h"

namespace rx
{

namespace
{
#if TARGET_OS_OSX
// Unlimited triangle fan buffers
constexpr uint32_t kMaxTriFanLineLoopBuffersPerFrame = 0;
#else
// Allow up to 10 buffers for trifan/line loop generation without stalling the GPU.
constexpr uint32_t kMaxTriFanLineLoopBuffersPerFrame = 10;
#endif

#define ANGLE_MTL_XFB_DRAW(DRAW_PROC)                                                       \
    if (!mState.isTransformFeedbackActiveUnpaused())                                        \
    {                                                                                       \
        /* Normal draw call */                                                              \
        DRAW_PROC(false);                                                                   \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        /* First pass: write to XFB buffers in vertex shader, fragment shader inactive */   \
        DRAW_PROC(true);                                                                    \
        if (!mState.isRasterizerDiscardEnabled())                                           \
        {                                                                                   \
            /* Second pass: full rasterization: vertex shader + fragment shader are active. \
               Vertex shader writes to stage output but won't write to XFB buffers */       \
            invalidateRenderPipeline();                                                     \
            DRAW_PROC(false);                                                               \
        }                                                                                   \
    }

angle::Result AllocateTriangleFanBufferFromPool(ContextMtl *context,
                                                GLsizei vertexCount,
                                                mtl::BufferPool *pool,
                                                mtl::BufferRef *bufferOut,
                                                uint32_t *offsetOut,
                                                uint32_t *numElemsOut)
{
    uint32_t numIndices;
    ANGLE_TRY(mtl::GetTriangleFanIndicesCount(context, vertexCount, &numIndices));

    size_t offset;
    pool->releaseInFlightBuffers(context);
    ANGLE_TRY(pool->allocate(context, numIndices * sizeof(uint32_t), nullptr, bufferOut, &offset,
                             nullptr));

    *offsetOut   = static_cast<uint32_t>(offset);
    *numElemsOut = numIndices;

    return angle::Result::Continue;
}

angle::Result AllocateLineLoopBufferFromPool(ContextMtl *context,
                                             GLsizei indicesToReserve,
                                             mtl::BufferPool *pool,
                                             mtl::BufferRef *bufferOut,
                                             uint32_t *offsetOut)
{
    size_t offset;
    pool->releaseInFlightBuffers(context);
    ANGLE_TRY(pool->allocate(context, indicesToReserve * sizeof(uint32_t), nullptr, bufferOut,
                             &offset, nullptr));

    *offsetOut = static_cast<uint32_t>(offset);

    return angle::Result::Continue;
}

bool NeedToInvertDepthRange(float near, float far)
{
    return near > far;
}

bool IsTransformFeedbackOnly(const gl::State &glState)
{
    return glState.isTransformFeedbackActiveUnpaused() && glState.isRasterizerDiscardEnabled();
}

std::string ConvertMarkerToString(GLsizei length, const char *marker)
{
    std::string cppString;
    if (length == 0)
    {
        cppString = marker;
    }
    else
    {
        cppString.assign(marker, length);
    }
    return cppString;
}

// This class constructs line loop's last segment buffer inside begin() method
// and perform the draw of the line loop's last segment inside destructor
class LineLoopLastSegmentHelper
{
  public:
    LineLoopLastSegmentHelper() {}

    ~LineLoopLastSegmentHelper()
    {
        if (!mLineLoopIndexBuffer)
        {
            return;
        }

        // Draw last segment of line loop here
        mtl::RenderCommandEncoder *encoder = mContextMtl->getRenderCommandEncoder();
        ASSERT(encoder);
        encoder->drawIndexed(MTLPrimitiveTypeLine, 2, MTLIndexTypeUInt32, mLineLoopIndexBuffer, 0);
    }

    angle::Result begin(const gl::Context *context,
                        mtl::BufferPool *indexBufferPool,
                        GLint firstVertex,
                        GLsizei vertexOrIndexCount,
                        gl::DrawElementsType indexTypeOrNone,
                        const void *indices)
    {
        mContextMtl = mtl::GetImpl(context);

        indexBufferPool->releaseInFlightBuffers(mContextMtl);

        ANGLE_TRY(indexBufferPool->allocate(mContextMtl, 2 * sizeof(uint32_t), nullptr,
                                            &mLineLoopIndexBuffer, nullptr, nullptr));

        if (indexTypeOrNone == gl::DrawElementsType::InvalidEnum)
        {
            ANGLE_TRY(mContextMtl->getDisplay()->getUtils().generateLineLoopLastSegment(
                mContextMtl, firstVertex, firstVertex + vertexOrIndexCount - 1,
                mLineLoopIndexBuffer, 0));
        }
        else
        {
            ASSERT(firstVertex == 0);
            ANGLE_TRY(
                mContextMtl->getDisplay()->getUtils().generateLineLoopLastSegmentFromElementsArray(
                    mContextMtl,
                    {indexTypeOrNone, vertexOrIndexCount, indices, mLineLoopIndexBuffer, 0}));
        }

        ANGLE_TRY(indexBufferPool->commit(mContextMtl));

        return angle::Result::Continue;
    }

  private:
    ContextMtl *mContextMtl = nullptr;
    mtl::BufferRef mLineLoopIndexBuffer;
};

}  // namespace

ContextMtl::ContextMtl(const gl::State &state, gl::ErrorSet *errorSet, DisplayMtl *display)
    : ContextImpl(state, errorSet),
      mtl::Context(display),
      mCmdBuffer(&display->cmdQueue()),
      mRenderEncoder(&mCmdBuffer, mOcclusionQueryPool),
      mBlitEncoder(&mCmdBuffer),
      mComputeEncoder(&mCmdBuffer)
{}

ContextMtl::~ContextMtl() {}

angle::Result ContextMtl::initialize()
{
    mBlendDesc.reset();
    mDepthStencilDesc.reset();

    mTriFanIndexBuffer.initialize(this, 0, mtl::kIndexBufferOffsetAlignment,
                                  kMaxTriFanLineLoopBuffersPerFrame);
    mLineLoopIndexBuffer.initialize(this, 0, mtl::kIndexBufferOffsetAlignment,
                                    kMaxTriFanLineLoopBuffersPerFrame);
    mLineLoopLastSegmentIndexBuffer.initialize(this, 2 * sizeof(uint32_t),
                                               mtl::kIndexBufferOffsetAlignment,
                                               kMaxTriFanLineLoopBuffersPerFrame);

    return angle::Result::Continue;
}

void ContextMtl::onDestroy(const gl::Context *context)
{
    mTriFanIndexBuffer.destroy(this);
    mLineLoopIndexBuffer.destroy(this);
    mLineLoopLastSegmentIndexBuffer.destroy(this);
    mOcclusionQueryPool.destroy(this);

    mIncompleteTextures.onDestroy(context);
    mIncompleteTexturesInitialized = false;

    mDummyXFBRenderTexture = nullptr;
}

angle::Result ContextMtl::ensureIncompleteTexturesCreated(const gl::Context *context)
{
    if (ANGLE_LIKELY(mIncompleteTexturesInitialized))
    {
        return angle::Result::Continue;
    }
    constexpr gl::TextureType supportedTextureTypes[] = {gl::TextureType::_2D, gl::TextureType::_3D,
                                                         gl::TextureType::_2DArray,
                                                         gl::TextureType::CubeMap};
    for (gl::TextureType texType : supportedTextureTypes)
    {
        gl::Texture *texture;
        ANGLE_TRY(mIncompleteTextures.getIncompleteTexture(context, texType, nullptr, &texture));

        TextureMtl *textureMtl                      = mtl::GetImpl(texture);
        textureMtl->getNativeTexture()->get().label = @"IncompleteTexture";
    }
    mIncompleteTexturesInitialized = true;

    return angle::Result::Continue;
}

// Flush and finish.
angle::Result ContextMtl::flush(const gl::Context *context)
{
    flushCommandBufer();
    return angle::Result::Continue;
}
angle::Result ContextMtl::finish(const gl::Context *context)
{
    ANGLE_TRY(finishCommandBuffer());
    return angle::Result::Continue;
}

// Drawing methods.
angle::Result ContextMtl::drawTriFanArraysWithBaseVertex(const gl::Context *context,
                                                         GLint first,
                                                         GLsizei count,
                                                         GLsizei instances)
{
    ASSERT((getDisplay()->getFeatures().hasBaseVertexInstancedDraw.enabled));

    uint32_t genIndicesCount;
    ANGLE_TRY(mtl::GetTriangleFanIndicesCount(this, count, &genIndicesCount));

    size_t indexBufferSize = genIndicesCount * sizeof(uint32_t);
    // We can reuse the previously generated index buffer if it has more than enough indices
    // data already.
    if (mTriFanArraysIndexBuffer == nullptr || mTriFanArraysIndexBuffer->size() < indexBufferSize)
    {
        // Re-generate a new index buffer, which the first index will be zero.
        ANGLE_TRY(
            mtl::Buffer::MakeBuffer(this, indexBufferSize, nullptr, &mTriFanArraysIndexBuffer));
        ANGLE_TRY(getDisplay()->getUtils().generateTriFanBufferFromArrays(
            this, {0, static_cast<uint32_t>(count), mTriFanArraysIndexBuffer, 0}));
    }

    ASSERT(!getState().isTransformFeedbackActiveUnpaused());

    ANGLE_TRY(setupDraw(context, gl::PrimitiveMode::TriangleFan, first, count, instances,
                        gl::DrawElementsType::InvalidEnum, reinterpret_cast<const void *>(0),
                        false));

    // Draw with the zero starting index buffer, shift the vertex index using baseVertex instanced
    // draw:
    mRenderEncoder.drawIndexedInstancedBaseVertex(MTLPrimitiveTypeTriangle, genIndicesCount,
                                                  MTLIndexTypeUInt32, mTriFanArraysIndexBuffer, 0,
                                                  instances, first);

    return angle::Result::Continue;
}
angle::Result ContextMtl::drawTriFanArraysLegacy(const gl::Context *context,
                                                 GLint first,
                                                 GLsizei count,
                                                 GLsizei instances)
{
    // Legacy method is only used for GPU lacking instanced base vertex draw capabilities.
    mtl::BufferRef genIdxBuffer;
    uint32_t genIdxBufferOffset;
    uint32_t genIndicesCount;
    ANGLE_TRY(AllocateTriangleFanBufferFromPool(this, count, &mTriFanIndexBuffer, &genIdxBuffer,
                                                &genIdxBufferOffset, &genIndicesCount));
    ANGLE_TRY(getDisplay()->getUtils().generateTriFanBufferFromArrays(
        this, {static_cast<uint32_t>(first), static_cast<uint32_t>(count), genIdxBuffer,
               genIdxBufferOffset}));

    ANGLE_TRY(mTriFanIndexBuffer.commit(this));

    ASSERT(!getState().isTransformFeedbackActiveUnpaused());

    ANGLE_TRY(setupDraw(context, gl::PrimitiveMode::TriangleFan, first, count, instances,
                        gl::DrawElementsType::InvalidEnum, reinterpret_cast<const void *>(0),
                        false));

    mRenderEncoder.drawIndexed(MTLPrimitiveTypeTriangle, genIndicesCount, MTLIndexTypeUInt32,
                               genIdxBuffer, genIdxBufferOffset);

    return angle::Result::Continue;
}
angle::Result ContextMtl::drawTriFanArrays(const gl::Context *context,
                                           GLint first,
                                           GLsizei count,
                                           GLsizei instances)
{
    if (count <= 3)
    {
        return drawArraysInstanced(context, gl::PrimitiveMode::Triangles, first, count, instances);
    }
    if (getDisplay()->getFeatures().hasBaseVertexInstancedDraw.enabled)
    {
        return drawTriFanArraysWithBaseVertex(context, first, count, instances);
    }
    return drawTriFanArraysLegacy(context, first, count, instances);
}

angle::Result ContextMtl::drawLineLoopArraysNonInstanced(const gl::Context *context,
                                                         GLint first,
                                                         GLsizei count)
{
    // Generate line loop's last segment. It will be rendered when this function exits.
    LineLoopLastSegmentHelper lineloopHelper;
    // Line loop helper needs to generate last segment indices before rendering command encoder
    // starts.
    ANGLE_TRY(lineloopHelper.begin(context, &mLineLoopLastSegmentIndexBuffer, first, count,
                                   gl::DrawElementsType::InvalidEnum, nullptr));

    return drawArraysImpl(context, gl::PrimitiveMode::LineStrip, first, count, 0);
}

angle::Result ContextMtl::drawLineLoopArrays(const gl::Context *context,
                                             GLint first,
                                             GLsizei count,
                                             GLsizei instances)
{
    if (instances <= 1)
    {
        return drawLineLoopArraysNonInstanced(context, first, count);
    }

    mtl::BufferRef genIdxBuffer;
    uint32_t genIdxBufferOffset;
    uint32_t genIndicesCount = count + 1;

    ANGLE_TRY(AllocateLineLoopBufferFromPool(this, genIndicesCount, &mLineLoopIndexBuffer,
                                             &genIdxBuffer, &genIdxBufferOffset));
    ANGLE_TRY(getDisplay()->getUtils().generateLineLoopBufferFromArrays(
        this, {static_cast<uint32_t>(first), static_cast<uint32_t>(count), genIdxBuffer,
               genIdxBufferOffset}));

    ANGLE_TRY(mLineLoopIndexBuffer.commit(this));

    ASSERT(!getState().isTransformFeedbackActiveUnpaused());

    ANGLE_TRY(setupDraw(context, gl::PrimitiveMode::LineLoop, first, count, instances,
                        gl::DrawElementsType::InvalidEnum, nullptr, false));

    mRenderEncoder.drawIndexedInstanced(MTLPrimitiveTypeLineStrip, genIndicesCount,
                                        MTLIndexTypeUInt32, genIdxBuffer, genIdxBufferOffset,
                                        instances);

    return angle::Result::Continue;
}

angle::Result ContextMtl::drawArraysImpl(const gl::Context *context,
                                         gl::PrimitiveMode mode,
                                         GLint first,
                                         GLsizei count,
                                         GLsizei instances)
{
    // Real instances count. Zero means this is not instanced draw.
    GLsizei instanceCount = instances ? instances : 1;

    if (mCullAllPolygons && gl::IsPolygonMode(mode))
    {
        return angle::Result::Continue;
    }

    if (mode == gl::PrimitiveMode::TriangleFan)
    {
        return drawTriFanArrays(context, first, count, instanceCount);
    }
    else if (mode == gl::PrimitiveMode::LineLoop)
    {
        return drawLineLoopArrays(context, first, count, instanceCount);
    }

    MTLPrimitiveType mtlType = mtl::GetPrimitiveType(mode);

#define DRAW_GENERIC_ARRAY(xfbPass)                                                                \
    ANGLE_TRY(setupDraw(context, mode, first, count, instances, gl::DrawElementsType::InvalidEnum, \
                        nullptr, xfbPass));                                                        \
                                                                                                   \
    if (instances == 0)                                                                            \
    {                                                                                              \
        /* This method is called from normal drawArrays() */                                       \
        mRenderEncoder.draw(mtlType, first, count);                                                \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
        mRenderEncoder.drawInstanced(mtlType, first, count, instanceCount);                        \
    }

    ANGLE_MTL_XFB_DRAW(DRAW_GENERIC_ARRAY)

    return angle::Result::Continue;
}

angle::Result ContextMtl::drawArrays(const gl::Context *context,
                                     gl::PrimitiveMode mode,
                                     GLint first,
                                     GLsizei count)
{
    return drawArraysImpl(context, mode, first, count, 0);
}

angle::Result ContextMtl::drawArraysInstanced(const gl::Context *context,
                                              gl::PrimitiveMode mode,
                                              GLint first,
                                              GLsizei count,
                                              GLsizei instances)
{
    if (instances == 0)
    {
        return angle::Result::Continue;
    }
    return drawArraysImpl(context, mode, first, count, instances);
}

angle::Result ContextMtl::drawArraysInstancedBaseInstance(const gl::Context *context,
                                                          gl::PrimitiveMode mode,
                                                          GLint first,
                                                          GLsizei count,
                                                          GLsizei instanceCount,
                                                          GLuint baseInstance)
{
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::drawTriFanElements(const gl::Context *context,
                                             GLsizei count,
                                             gl::DrawElementsType type,
                                             const void *indices,
                                             GLsizei instances)
{
    if (count > 3)
    {
        mtl::BufferRef genIdxBuffer;
        uint32_t genIdxBufferOffset;
        uint32_t genIndicesCount;
        bool primitiveRestart = getState().isPrimitiveRestartEnabled();
        ANGLE_TRY(AllocateTriangleFanBufferFromPool(this, count, &mTriFanIndexBuffer, &genIdxBuffer,
                                                    &genIdxBufferOffset, &genIndicesCount));

        ANGLE_TRY(getDisplay()->getUtils().generateTriFanBufferFromElementsArray(
            this, {type, count, indices, genIdxBuffer, genIdxBufferOffset, primitiveRestart}));

        ANGLE_TRY(mTriFanIndexBuffer.commit(this));

        ANGLE_TRY(setupDraw(context, gl::PrimitiveMode::TriangleFan, 0, count, instances, type,
                            indices, false));

        mRenderEncoder.drawIndexedInstanced(MTLPrimitiveTypeTriangle, genIndicesCount,
                                            MTLIndexTypeUInt32, genIdxBuffer, genIdxBufferOffset,
                                            instances);

        return angle::Result::Continue;
    }  // if (count > 3)
    return drawElementsInstanced(context, gl::PrimitiveMode::Triangles, count, type, indices,
                                 instances);
}

angle::Result ContextMtl::drawLineLoopElementsNonInstancedNoPrimitiveRestart(
    const gl::Context *context,
    GLsizei count,
    gl::DrawElementsType type,
    const void *indices)
{
    // Generate line loop's last segment. It will be rendered when this function exits.
    LineLoopLastSegmentHelper lineloopHelper;
    // Line loop helper needs to generate index before rendering command encoder starts.
    ANGLE_TRY(
        lineloopHelper.begin(context, &mLineLoopLastSegmentIndexBuffer, 0, count, type, indices));

    return drawElementsImpl(context, gl::PrimitiveMode::LineStrip, count, type, indices, 0);
}

angle::Result ContextMtl::drawLineLoopElements(const gl::Context *context,
                                               GLsizei count,
                                               gl::DrawElementsType type,
                                               const void *indices,
                                               GLsizei instances)
{
    if (count >= 2)
    {
        bool primitiveRestart = getState().isPrimitiveRestartEnabled();
        if (instances <= 1 && !primitiveRestart)
        {
            // Non instanced draw and no primitive restart, just use faster version.
            return drawLineLoopElementsNonInstancedNoPrimitiveRestart(context, count, type,
                                                                      indices);
        }

        mtl::BufferRef genIdxBuffer;
        uint32_t genIdxBufferOffset;
        uint32_t reservedIndices = count * 2;
        uint32_t genIndicesCount;
        ANGLE_TRY(AllocateLineLoopBufferFromPool(this, reservedIndices, &mLineLoopIndexBuffer,
                                                 &genIdxBuffer, &genIdxBufferOffset));

        ANGLE_TRY(getDisplay()->getUtils().generateLineLoopBufferFromElementsArray(
            this, {type, count, indices, genIdxBuffer, genIdxBufferOffset, primitiveRestart},
            &genIndicesCount));

        ANGLE_TRY(mLineLoopIndexBuffer.commit(this));

        ANGLE_TRY(setupDraw(context, gl::PrimitiveMode::LineLoop, 0, count, instances, type,
                            indices, false));

        mRenderEncoder.drawIndexedInstanced(MTLPrimitiveTypeLineStrip, genIndicesCount,
                                            MTLIndexTypeUInt32, genIdxBuffer, genIdxBufferOffset,
                                            instances);

        return angle::Result::Continue;
    }  // if (count >= 2)
    return drawElementsInstanced(context, gl::PrimitiveMode::Lines, count, type, indices,
                                 instances);
}

angle::Result ContextMtl::drawElementsImpl(const gl::Context *context,
                                           gl::PrimitiveMode mode,
                                           GLsizei count,
                                           gl::DrawElementsType type,
                                           const void *indices,
                                           GLsizei instances)
{
    // Real instances count. Zero means this is not instanced draw.
    GLsizei instanceCount = instances ? instances : 1;

    if (mCullAllPolygons && gl::IsPolygonMode(mode))
    {
        return angle::Result::Continue;
    }

    if (mode == gl::PrimitiveMode::TriangleFan)
    {
        return drawTriFanElements(context, count, type, indices, instanceCount);
    }
    else if (mode == gl::PrimitiveMode::LineLoop)
    {
        return drawLineLoopElements(context, count, type, indices, instanceCount);
    }

    mtl::BufferRef idxBuffer;
    size_t convertedOffset             = 0;
    gl::DrawElementsType convertedType = type;

    ANGLE_TRY(mVertexArray->getIndexBuffer(context, type, count, indices, &idxBuffer,
                                           &convertedOffset, &convertedType));

    ASSERT(idxBuffer);
    ASSERT((convertedOffset % mtl::kIndexBufferOffsetAlignment) == 0);

    ANGLE_TRY(setupDraw(context, mode, 0, count, instances, type, indices, false));

    MTLPrimitiveType mtlType = mtl::GetPrimitiveType(mode);

    MTLIndexType mtlIdxType = mtl::GetIndexType(convertedType);

    if (instances == 0)
    {
        // Normal draw
        mRenderEncoder.drawIndexed(mtlType, count, mtlIdxType, idxBuffer, convertedOffset);
    }
    else
    {
        // Instanced draw
        mRenderEncoder.drawIndexedInstanced(mtlType, count, mtlIdxType, idxBuffer, convertedOffset,
                                            instanceCount);
    }

    return angle::Result::Continue;
}

angle::Result ContextMtl::drawElements(const gl::Context *context,
                                       gl::PrimitiveMode mode,
                                       GLsizei count,
                                       gl::DrawElementsType type,
                                       const void *indices)
{
    return drawElementsImpl(context, mode, count, type, indices, 0);
}

angle::Result ContextMtl::drawElementsBaseVertex(const gl::Context *context,
                                                 gl::PrimitiveMode mode,
                                                 GLsizei count,
                                                 gl::DrawElementsType type,
                                                 const void *indices,
                                                 GLint baseVertex)
{
    // NOTE(hqle): ES 3.2
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::drawElementsInstanced(const gl::Context *context,
                                                gl::PrimitiveMode mode,
                                                GLsizei count,
                                                gl::DrawElementsType type,
                                                const void *indices,
                                                GLsizei instanceCount)
{
    if (instanceCount == 0)
    {
        return angle::Result::Continue;
    }
    return drawElementsImpl(context, mode, count, type, indices, instanceCount);
}

angle::Result ContextMtl::drawElementsInstancedBaseVertex(const gl::Context *context,
                                                          gl::PrimitiveMode mode,
                                                          GLsizei count,
                                                          gl::DrawElementsType type,
                                                          const void *indices,
                                                          GLsizei instanceCount,
                                                          GLint baseVertex)
{
    // NOTE(hqle): ES 3.2
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::drawElementsInstancedBaseVertexBaseInstance(const gl::Context *context,
                                                                      gl::PrimitiveMode mode,
                                                                      GLsizei count,
                                                                      gl::DrawElementsType type,
                                                                      const void *indices,
                                                                      GLsizei instances,
                                                                      GLint baseVertex,
                                                                      GLuint baseInstance)
{
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::drawRangeElements(const gl::Context *context,
                                            gl::PrimitiveMode mode,
                                            GLuint start,
                                            GLuint end,
                                            GLsizei count,
                                            gl::DrawElementsType type,
                                            const void *indices)
{
    return drawElementsImpl(context, mode, count, type, indices, 0);
}

angle::Result ContextMtl::drawRangeElementsBaseVertex(const gl::Context *context,
                                                      gl::PrimitiveMode mode,
                                                      GLuint start,
                                                      GLuint end,
                                                      GLsizei count,
                                                      gl::DrawElementsType type,
                                                      const void *indices,
                                                      GLint baseVertex)
{
    // NOTE(hqle): ES 3.2
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::drawArraysIndirect(const gl::Context *context,
                                             gl::PrimitiveMode mode,
                                             const void *indirect)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}
angle::Result ContextMtl::drawElementsIndirect(const gl::Context *context,
                                               gl::PrimitiveMode mode,
                                               gl::DrawElementsType type,
                                               const void *indirect)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::multiDrawArrays(const gl::Context *context,
                                          gl::PrimitiveMode mode,
                                          const GLint *firsts,
                                          const GLsizei *counts,
                                          GLsizei drawcount)
{
    return rx::MultiDrawArraysGeneral(this, context, mode, firsts, counts, drawcount);
}

angle::Result ContextMtl::multiDrawArraysInstanced(const gl::Context *context,
                                                   gl::PrimitiveMode mode,
                                                   const GLint *firsts,
                                                   const GLsizei *counts,
                                                   const GLsizei *instanceCounts,
                                                   GLsizei drawcount)
{
    return rx::MultiDrawArraysInstancedGeneral(this, context, mode, firsts, counts, instanceCounts,
                                               drawcount);
}

angle::Result ContextMtl::multiDrawElements(const gl::Context *context,
                                            gl::PrimitiveMode mode,
                                            const GLsizei *counts,
                                            gl::DrawElementsType type,
                                            const GLvoid *const *indices,
                                            GLsizei drawcount)
{
    return rx::MultiDrawElementsGeneral(this, context, mode, counts, type, indices, drawcount);
}

angle::Result ContextMtl::multiDrawElementsInstanced(const gl::Context *context,
                                                     gl::PrimitiveMode mode,
                                                     const GLsizei *counts,
                                                     gl::DrawElementsType type,
                                                     const GLvoid *const *indices,
                                                     const GLsizei *instanceCounts,
                                                     GLsizei drawcount)
{
    return rx::MultiDrawElementsInstancedGeneral(this, context, mode, counts, type, indices,
                                                 instanceCounts, drawcount);
}

angle::Result ContextMtl::multiDrawArraysInstancedBaseInstance(const gl::Context *context,
                                                               gl::PrimitiveMode mode,
                                                               const GLint *firsts,
                                                               const GLsizei *counts,
                                                               const GLsizei *instanceCounts,
                                                               const GLuint *baseInstances,
                                                               GLsizei drawcount)
{
    return rx::MultiDrawArraysInstancedBaseInstanceGeneral(
        this, context, mode, firsts, counts, instanceCounts, baseInstances, drawcount);
}

angle::Result ContextMtl::multiDrawElementsInstancedBaseVertexBaseInstance(
    const gl::Context *context,
    gl::PrimitiveMode mode,
    const GLsizei *counts,
    gl::DrawElementsType type,
    const GLvoid *const *indices,
    const GLsizei *instanceCounts,
    const GLint *baseVertices,
    const GLuint *baseInstances,
    GLsizei drawcount)
{
    return rx::MultiDrawElementsInstancedBaseVertexBaseInstanceGeneral(
        this, context, mode, counts, type, indices, instanceCounts, baseVertices, baseInstances,
        drawcount);
}

// Device loss
gl::GraphicsResetStatus ContextMtl::getResetStatus()
{
    return gl::GraphicsResetStatus::NoError;
}

// Vendor and description strings.
std::string ContextMtl::getVendorString() const
{
    return getDisplay()->getVendorString();
}
std::string ContextMtl::getRendererDescription() const
{
    return getDisplay()->getRendererDescription();
}

// EXT_debug_marker
angle::Result ContextMtl::insertEventMarker(GLsizei length, const char *marker)
{
    return angle::Result::Continue;
}

angle::Result ContextMtl::pushGroupMarker(GLsizei length, const char *marker)
{
    mCmdBuffer.pushDebugGroup(ConvertMarkerToString(length, marker));
    return angle::Result::Continue;
}

angle::Result ContextMtl::popGroupMarker()
{
    mCmdBuffer.popDebugGroup();
    return angle::Result::Continue;
}

// KHR_debug
angle::Result ContextMtl::pushDebugGroup(const gl::Context *context,
                                         GLenum source,
                                         GLuint id,
                                         const std::string &message)
{
    return angle::Result::Continue;
}

angle::Result ContextMtl::popDebugGroup(const gl::Context *context)
{
    return angle::Result::Continue;
}

// State sync with dirty bits.
angle::Result ContextMtl::syncState(const gl::Context *context,
                                    const gl::State::DirtyBits &dirtyBits,
                                    const gl::State::DirtyBits &bitMask)
{
    const gl::State &glState = context->getState();

    // Initialize incomplete texture set.
    ANGLE_TRY(ensureIncompleteTexturesCreated(context));

    for (size_t dirtyBit : dirtyBits)
    {
        switch (dirtyBit)
        {
            case gl::State::DIRTY_BIT_SCISSOR_TEST_ENABLED:
            case gl::State::DIRTY_BIT_SCISSOR:
                updateScissor(glState);
                break;
            case gl::State::DIRTY_BIT_VIEWPORT:
            {
                FramebufferMtl *framebufferMtl = mtl::GetImpl(glState.getDrawFramebuffer());
                updateViewport(framebufferMtl, glState.getViewport(), glState.getNearPlane(),
                               glState.getFarPlane());
                // Update the scissor, which will be constrained to the viewport
                updateScissor(glState);
                break;
            }
            case gl::State::DIRTY_BIT_DEPTH_RANGE:
                updateDepthRange(glState.getNearPlane(), glState.getFarPlane());
                break;
            case gl::State::DIRTY_BIT_BLEND_COLOR:
                mDirtyBits.set(DIRTY_BIT_BLEND_COLOR);
                break;
            case gl::State::DIRTY_BIT_BLEND_ENABLED:
                mBlendDesc.updateBlendEnabled(glState.getBlendState());
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_BLEND_FUNCS:
                mBlendDesc.updateBlendFactors(glState.getBlendState());
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_BLEND_EQUATIONS:
                mBlendDesc.updateBlendOps(glState.getBlendState());
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_COLOR_MASK:
                mBlendDesc.updateWriteMask(glState.getBlendState());
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_SAMPLE_ALPHA_TO_COVERAGE_ENABLED:
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_SAMPLE_COVERAGE_ENABLED:
                invalidateRenderPipeline();
                break;
            case gl::State::DIRTY_BIT_SAMPLE_COVERAGE:
                invalidateDriverUniforms();
                break;
            case gl::State::DIRTY_BIT_SAMPLE_MASK_ENABLED:
                // NOTE(hqle): 3.1 MSAA support
                break;
            case gl::State::DIRTY_BIT_SAMPLE_MASK:
                // NOTE(hqle): 3.1 MSAA support
                break;
            case gl::State::DIRTY_BIT_DEPTH_TEST_ENABLED:
                mDepthStencilDesc.updateDepthTestEnabled(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_DEPTH_FUNC:
                mDepthStencilDesc.updateDepthCompareFunc(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_DEPTH_MASK:
                mDepthStencilDesc.updateDepthWriteEnabled(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_STENCIL_TEST_ENABLED:
                mDepthStencilDesc.updateStencilTestEnabled(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_STENCIL_FUNCS_FRONT:
                mDepthStencilDesc.updateStencilFrontFuncs(glState.getDepthStencilState());
                mStencilRefFront = glState.getStencilRef();  // clamped on the frontend
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                mDirtyBits.set(DIRTY_BIT_STENCIL_REF);
                break;
            case gl::State::DIRTY_BIT_STENCIL_FUNCS_BACK:
                mDepthStencilDesc.updateStencilBackFuncs(glState.getDepthStencilState());
                mStencilRefBack = glState.getStencilBackRef();  // clamped on the frontend
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                mDirtyBits.set(DIRTY_BIT_STENCIL_REF);
                break;
            case gl::State::DIRTY_BIT_STENCIL_OPS_FRONT:
                mDepthStencilDesc.updateStencilFrontOps(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_STENCIL_OPS_BACK:
                mDepthStencilDesc.updateStencilBackOps(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_STENCIL_WRITEMASK_FRONT:
                mDepthStencilDesc.updateStencilFrontWriteMask(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_STENCIL_WRITEMASK_BACK:
                mDepthStencilDesc.updateStencilBackWriteMask(glState.getDepthStencilState());
                mDirtyBits.set(DIRTY_BIT_DEPTH_STENCIL_DESC);
                break;
            case gl::State::DIRTY_BIT_CULL_FACE_ENABLED:
            case gl::State::DIRTY_BIT_CULL_FACE:
                updateCullMode(glState);
                break;
            case gl::State::DIRTY_BIT_FRONT_FACE:
                updateFrontFace(glState);
                break;
            case gl::State::DIRTY_BIT_POLYGON_OFFSET_FILL_ENABLED:
            case gl::State::DIRTY_BIT_POLYGON_OFFSET:
                updateDepthBias(glState);
                break;
            case gl::State::DIRTY_BIT_RASTERIZER_DISCARD_ENABLED:
                mDirtyBits.set(DIRTY_BIT_RASTERIZER_DISCARD);
                break;
            case gl::State::DIRTY_BIT_LINE_WIDTH:
                // Do nothing
                break;
            case gl::State::DIRTY_BIT_PRIMITIVE_RESTART_ENABLED:
                // NOTE(hqle): ES 3.0 feature.
                break;
            case gl::State::DIRTY_BIT_CLEAR_COLOR:
                mClearColor = mtl::ClearColorValue(
                    glState.getColorClearValue().red, glState.getColorClearValue().green,
                    glState.getColorClearValue().blue, glState.getColorClearValue().alpha);
                break;
            case gl::State::DIRTY_BIT_CLEAR_DEPTH:
                break;
            case gl::State::DIRTY_BIT_CLEAR_STENCIL:
                mClearStencil = glState.getStencilClearValue() & mtl::kStencilMaskAll;
                break;
            case gl::State::DIRTY_BIT_UNPACK_STATE:
                // This is a no-op, its only important to use the right unpack state when we do
                // setImage or setSubImage in TextureMtl, which is plumbed through the frontend call
                break;
            case gl::State::DIRTY_BIT_UNPACK_BUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_PACK_STATE:
                // This is a no-op, its only important to use the right pack state when we do
                // call readPixels later on.
                break;
            case gl::State::DIRTY_BIT_PACK_BUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_DITHER_ENABLED:
                break;
            case gl::State::DIRTY_BIT_READ_FRAMEBUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_DRAW_FRAMEBUFFER_BINDING:
                updateDrawFrameBufferBinding(context);
                break;
            case gl::State::DIRTY_BIT_RENDERBUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_VERTEX_ARRAY_BINDING:
                updateVertexArray(context);
                break;
            case gl::State::DIRTY_BIT_DRAW_INDIRECT_BUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_DISPATCH_INDIRECT_BUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_PROGRAM_BINDING:
                mProgram = mtl::GetImpl(glState.getProgram());
                break;
            case gl::State::DIRTY_BIT_PROGRAM_EXECUTABLE:
                updateProgramExecutable(context);
                break;
            case gl::State::DIRTY_BIT_TEXTURE_BINDINGS:
                invalidateCurrentTextures();
                break;
            case gl::State::DIRTY_BIT_SAMPLER_BINDINGS:
                invalidateCurrentTextures();
                break;
            case gl::State::DIRTY_BIT_TRANSFORM_FEEDBACK_BINDING:
                // Nothing to do.
                break;
            case gl::State::DIRTY_BIT_SHADER_STORAGE_BUFFER_BINDING:
                // NOTE(hqle): ES 3.0 feature.
                break;
            case gl::State::DIRTY_BIT_UNIFORM_BUFFER_BINDINGS:
                mDirtyBits.set(DIRTY_BIT_UNIFORM_BUFFERS_BINDING);
                break;
            case gl::State::DIRTY_BIT_ATOMIC_COUNTER_BUFFER_BINDING:
                break;
            case gl::State::DIRTY_BIT_IMAGE_BINDINGS:
                // NOTE(hqle): properly handle GLSL images.
                invalidateCurrentTextures();
                break;
            case gl::State::DIRTY_BIT_MULTISAMPLING:
                // NOTE(hqle): MSAA on/off.
                break;
            case gl::State::DIRTY_BIT_SAMPLE_ALPHA_TO_ONE:
                // NOTE(hqle): this is part of EXT_multisample_compatibility.
                // NOTE(hqle): MSAA feature.
                break;
            case gl::State::DIRTY_BIT_COVERAGE_MODULATION:
                break;
            case gl::State::DIRTY_BIT_FRAMEBUFFER_SRGB:
                break;
            case gl::State::DIRTY_BIT_CURRENT_VALUES:
            {
                invalidateDefaultAttributes(glState.getAndResetDirtyCurrentValues());
                break;
            }
            case gl::State::DIRTY_BIT_PROVOKING_VERTEX:
                break;
            case gl::State::DIRTY_BIT_EXTENDED:
                updateExtendedState(glState);
                break;
            case gl::State::DIRTY_BIT_SAMPLE_SHADING:
                // Nothing to do until OES_sample_shading is implemented.
                break;
            default:
                UNREACHABLE();
                break;
        }
    }

    return angle::Result::Continue;
}

void ContextMtl::updateExtendedState(const gl::State &glState)
{
    // Handling clip distance enabled flags, mipmap generation hint & shader derivative
    // hint.
    invalidateDriverUniforms();
}

// Disjoint timer queries
GLint ContextMtl::getGPUDisjoint()
{
    UNIMPLEMENTED();
    return 0;
}
GLint64 ContextMtl::getTimestamp()
{
    UNIMPLEMENTED();
    return 0;
}

// Context switching
angle::Result ContextMtl::onMakeCurrent(const gl::Context *context)
{
    invalidateState(context);
    return angle::Result::Continue;
}
angle::Result ContextMtl::onUnMakeCurrent(const gl::Context *context)
{
    flushCommandBufer();
    return angle::Result::Continue;
}

// Native capabilities, unmodified by gl::Context.
gl::Caps ContextMtl::getNativeCaps() const
{
    return getDisplay()->getNativeCaps();
}
const gl::TextureCapsMap &ContextMtl::getNativeTextureCaps() const
{
    return getDisplay()->getNativeTextureCaps();
}
const gl::Extensions &ContextMtl::getNativeExtensions() const
{
    return getDisplay()->getNativeExtensions();
}
const gl::Limitations &ContextMtl::getNativeLimitations() const
{
    return getDisplay()->getNativeLimitations();
}

// Shader creation
CompilerImpl *ContextMtl::createCompiler()
{
    return new CompilerMtl();
}
ShaderImpl *ContextMtl::createShader(const gl::ShaderState &state)
{
    return new ShaderMtl(state);
}
ProgramImpl *ContextMtl::createProgram(const gl::ProgramState &state)
{
    return new ProgramMtl(state);
}

// Framebuffer creation
FramebufferImpl *ContextMtl::createFramebuffer(const gl::FramebufferState &state)
{
    return new FramebufferMtl(state, false, nullptr);
}

// Texture creation
TextureImpl *ContextMtl::createTexture(const gl::TextureState &state)
{
    return new TextureMtl(state);
}

// Renderbuffer creation
RenderbufferImpl *ContextMtl::createRenderbuffer(const gl::RenderbufferState &state)
{
    return new RenderbufferMtl(state);
}

// Buffer creation
BufferImpl *ContextMtl::createBuffer(const gl::BufferState &state)
{
    return new BufferMtl(state);
}

// Vertex Array creation
VertexArrayImpl *ContextMtl::createVertexArray(const gl::VertexArrayState &state)
{
    return new VertexArrayMtl(state, this);
}

// Query and Fence creation
QueryImpl *ContextMtl::createQuery(gl::QueryType type)
{
    return new QueryMtl(type);
}
FenceNVImpl *ContextMtl::createFenceNV()
{
    return new FenceNVMtl();
}
SyncImpl *ContextMtl::createSync()
{
    return new SyncMtl();
}

// Transform Feedback creation
TransformFeedbackImpl *ContextMtl::createTransformFeedback(const gl::TransformFeedbackState &state)
{
    // NOTE(hqle): ES 3.0
    return new TransformFeedbackMtl(state);
}

// Sampler object creation
SamplerImpl *ContextMtl::createSampler(const gl::SamplerState &state)
{
    return new SamplerMtl(state);
}

// Program Pipeline object creation
ProgramPipelineImpl *ContextMtl::createProgramPipeline(const gl::ProgramPipelineState &data)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return nullptr;
}

// Memory object creation.
MemoryObjectImpl *ContextMtl::createMemoryObject()
{
    UNIMPLEMENTED();
    return nullptr;
}

// Semaphore creation.
SemaphoreImpl *ContextMtl::createSemaphore()
{
    UNIMPLEMENTED();
    return nullptr;
}

OverlayImpl *ContextMtl::createOverlay(const gl::OverlayState &state)
{
    UNIMPLEMENTED();
    return nullptr;
}

angle::Result ContextMtl::dispatchCompute(const gl::Context *context,
                                          GLuint numGroupsX,
                                          GLuint numGroupsY,
                                          GLuint numGroupsZ)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}
angle::Result ContextMtl::dispatchComputeIndirect(const gl::Context *context, GLintptr indirect)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result ContextMtl::memoryBarrier(const gl::Context *context, GLbitfield barriers)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}
angle::Result ContextMtl::memoryBarrierByRegion(const gl::Context *context, GLbitfield barriers)
{
    // NOTE(hqle): ES 3.0
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

// override mtl::ErrorHandler
void ContextMtl::handleError(GLenum glErrorCode,
                             const char *file,
                             const char *function,
                             unsigned int line)
{
    std::stringstream errorStream;
    errorStream << "Metal backend encountered an error. Code=" << glErrorCode << ".";

    mErrors->handleError(glErrorCode, errorStream.str().c_str(), file, function, line);
}

void ContextMtl::handleError(NSError *nserror,
                             const char *file,
                             const char *function,
                             unsigned int line)
{
    if (!nserror)
    {
        return;
    }

    std::stringstream errorStream;
    errorStream << "Metal backend encountered an error: \n"
                << nserror.localizedDescription.UTF8String;

    mErrors->handleError(GL_INVALID_OPERATION, errorStream.str().c_str(), file, function, line);
}

void ContextMtl::invalidateState(const gl::Context *context)
{
    mDirtyBits.set();

    invalidateDefaultAttributes(context->getStateCache().getActiveDefaultAttribsMask());
}

void ContextMtl::invalidateDefaultAttribute(size_t attribIndex)
{
    mDirtyDefaultAttribsMask.set(attribIndex);
    mDirtyBits.set(DIRTY_BIT_DEFAULT_ATTRIBS);
}

void ContextMtl::invalidateDefaultAttributes(const gl::AttributesMask &dirtyMask)
{
    if (dirtyMask.any())
    {
        mDirtyDefaultAttribsMask |= dirtyMask;
        mDirtyBits.set(DIRTY_BIT_DEFAULT_ATTRIBS);
    }
}

void ContextMtl::invalidateCurrentTextures()
{
    mDirtyBits.set(DIRTY_BIT_TEXTURES);
}

void ContextMtl::invalidateDriverUniforms()
{
    mDirtyBits.set(DIRTY_BIT_DRIVER_UNIFORMS);
}

void ContextMtl::invalidateRenderPipeline()
{
    mDirtyBits.set(DIRTY_BIT_RENDER_PIPELINE);
}

const mtl::ClearColorValue &ContextMtl::getClearColorValue() const
{
    return mClearColor;
}
MTLColorWriteMask ContextMtl::getColorMask() const
{
    return mBlendDesc.writeMask;
}
float ContextMtl::getClearDepthValue() const
{
    return getState().getDepthClearValue();
}
uint32_t ContextMtl::getClearStencilValue() const
{
    return mClearStencil;
}
uint32_t ContextMtl::getStencilMask() const
{
    return getState().getDepthStencilState().stencilWritemask & mtl::kStencilMaskAll;
}

bool ContextMtl::getDepthMask() const
{
    return getState().getDepthStencilState().depthMask;
}

const mtl::Format &ContextMtl::getPixelFormat(angle::FormatID angleFormatId) const
{
    return getDisplay()->getPixelFormat(angleFormatId);
}

// See mtl::FormatTable::getVertexFormat()
const mtl::VertexFormat &ContextMtl::getVertexFormat(angle::FormatID angleFormatId,
                                                     bool tightlyPacked) const
{
    return getDisplay()->getVertexFormat(angleFormatId, tightlyPacked);
}

const mtl::FormatCaps &ContextMtl::getNativeFormatCaps(MTLPixelFormat mtlFormat) const
{
    return getDisplay()->getNativeFormatCaps(mtlFormat);
}

angle::Result ContextMtl::getIncompleteTexture(const gl::Context *context,
                                               gl::TextureType type,
                                               gl::Texture **textureOut)
{
    return mIncompleteTextures.getIncompleteTexture(context, type, nullptr, textureOut);
}

void ContextMtl::endRenderEncoding(mtl::RenderCommandEncoder *encoder)
{
    // End any pending visibility query in the render pass
    if (mOcclusionQuery)
    {
        disableActiveOcclusionQueryInRenderPass();
    }

    encoder->endEncoding();

    // Resolve visibility results
    mOcclusionQueryPool.resolveVisibilityResults(this);
}

void ContextMtl::endEncoding(bool forceSaveRenderPassContent)
{
    if (mRenderEncoder.valid())
    {
        if (forceSaveRenderPassContent)
        {
            // Save the work in progress.
            mRenderEncoder.setStoreAction(MTLStoreActionStore);
        }

        endRenderEncoding(&mRenderEncoder);
    }

    if (mBlitEncoder.valid())
    {
        mBlitEncoder.endEncoding();
    }

    if (mComputeEncoder.valid())
    {
        mComputeEncoder.endEncoding();
    }
}

void ContextMtl::flushCommandBufer()
{
    if (!mCmdBuffer.ready())
    {
        return;
    }

    endEncoding(true);
    mCmdBuffer.commit();
}

void ContextMtl::present(const gl::Context *context, id<CAMetalDrawable> presentationDrawable)
{
    ensureCommandBufferReady();

    FramebufferMtl *currentframebuffer = mtl::GetImpl(getState().getDrawFramebuffer());
    if (currentframebuffer)
    {
        currentframebuffer->onFrameEnd(context);
    }

    endEncoding(false);
    mCmdBuffer.present(presentationDrawable);
    mCmdBuffer.commit();
}

angle::Result ContextMtl::finishCommandBuffer()
{
    flushCommandBufer();

    mCmdBuffer.finish();

    return angle::Result::Continue;
}

bool ContextMtl::hasStartedRenderPass(const mtl::RenderPassDesc &desc)
{
    return mRenderEncoder.valid() &&
           mRenderEncoder.renderPassDesc().equalIgnoreLoadStoreOptions(desc);
}

// Get current render encoder
mtl::RenderCommandEncoder *ContextMtl::getRenderCommandEncoder()
{
    if (!mRenderEncoder.valid())
    {
        return nullptr;
    }

    return &mRenderEncoder;
}

mtl::RenderCommandEncoder *ContextMtl::getRenderPassCommandEncoder(const mtl::RenderPassDesc &desc)
{
    if (hasStartedRenderPass(desc))
    {
        return &mRenderEncoder;
    }

    endEncoding(false);

    ensureCommandBufferReady();

    // Need to re-apply everything on next draw call.
    mDirtyBits.set();

    return &mRenderEncoder.restart(desc);
}

// Utilities to quickly create render command encoder to a specific texture:
// The previous content of texture will be loaded
mtl::RenderCommandEncoder *ContextMtl::getTextureRenderCommandEncoder(
    const mtl::TextureRef &textureTarget,
    const mtl::ImageNativeIndex &index)
{
    ASSERT(textureTarget && textureTarget->valid());

    mtl::RenderPassDesc rpDesc;

    rpDesc.colorAttachments[0].texture      = textureTarget;
    rpDesc.colorAttachments[0].level        = index.getNativeLevel();
    rpDesc.colorAttachments[0].sliceOrDepth = index.hasLayer() ? index.getLayerIndex() : 0;
    rpDesc.numColorAttachments              = 1;
    rpDesc.sampleCount                      = textureTarget->samples();

    return getRenderPassCommandEncoder(rpDesc);
}

// The previous content of texture will be loaded if clearColor is not provided
mtl::RenderCommandEncoder *ContextMtl::getRenderTargetCommandEncoderWithClear(
    const RenderTargetMtl &renderTarget,
    const Optional<MTLClearColor> &clearColor)
{
    ASSERT(renderTarget.getTexture());

    mtl::RenderPassDesc rpDesc;
    renderTarget.toRenderPassAttachmentDesc(&rpDesc.colorAttachments[0]);
    rpDesc.numColorAttachments = 1;
    rpDesc.sampleCount         = renderTarget.getRenderSamples();

    if (clearColor.valid())
    {
        rpDesc.colorAttachments[0].loadAction = MTLLoadActionClear;
        rpDesc.colorAttachments[0].clearColor = mtl::EmulatedAlphaClearColor(
            clearColor.value(), renderTarget.getTexture()->getColorWritableMask());

        endEncoding(true);
    }

    return getRenderPassCommandEncoder(rpDesc);
}
// The previous content of texture will be loaded
mtl::RenderCommandEncoder *ContextMtl::getRenderTargetCommandEncoder(
    const RenderTargetMtl &renderTarget)
{
    return getRenderTargetCommandEncoderWithClear(renderTarget, Optional<MTLClearColor>());
}

mtl::BlitCommandEncoder *ContextMtl::getBlitCommandEncoder()
{
    if (mBlitEncoder.valid())
    {
        return &mBlitEncoder;
    }

    endEncoding(true);

    ensureCommandBufferReady();

    return &mBlitEncoder.restart();
}

mtl::ComputeCommandEncoder *ContextMtl::getComputeCommandEncoder()
{
    if (mComputeEncoder.valid())
    {
        return &mComputeEncoder;
    }

    endEncoding(true);

    ensureCommandBufferReady();

    return &mComputeEncoder.restart();
}

void ContextMtl::ensureCommandBufferReady()
{
    if (!mCmdBuffer.ready())
    {
        mCmdBuffer.restart();
    }

    ASSERT(mCmdBuffer.ready());
}

void ContextMtl::updateViewport(FramebufferMtl *framebufferMtl,
                                const gl::Rectangle &viewport,
                                float nearPlane,
                                float farPlane)
{
    mViewport = mtl::GetViewport(viewport, framebufferMtl->getState().getDimensions().height,
                                 framebufferMtl->flipY(), nearPlane, farPlane);
    mDirtyBits.set(DIRTY_BIT_VIEWPORT);

    invalidateDriverUniforms();
}

void ContextMtl::updateDepthRange(float nearPlane, float farPlane)
{
    if (NeedToInvertDepthRange(nearPlane, farPlane))
    {
        // We also need to invert the depth in shader later by using scale value stored in driver
        // uniform depthRange.reserved
        std::swap(nearPlane, farPlane);
    }
    mViewport.znear = nearPlane;
    mViewport.zfar  = farPlane;
    mDirtyBits.set(DIRTY_BIT_VIEWPORT);

    invalidateDriverUniforms();
}

void ContextMtl::updateScissor(const gl::State &glState)
{
    FramebufferMtl *framebufferMtl = mtl::GetImpl(glState.getDrawFramebuffer());
    gl::Rectangle renderArea       = framebufferMtl->getCompleteRenderArea();

    ANGLE_MTL_LOG("renderArea = %d,%d,%d,%d", renderArea.x, renderArea.y, renderArea.width,
                  renderArea.height);

    // Clip the render area to the viewport.
    gl::Rectangle viewportClippedRenderArea;
    gl::ClipRectangle(renderArea, glState.getViewport(), &viewportClippedRenderArea);

    gl::Rectangle scissoredArea = ClipRectToScissor(getState(), viewportClippedRenderArea, false);
    if (framebufferMtl->flipY())
    {
        scissoredArea.y = renderArea.height - scissoredArea.y - scissoredArea.height;
    }

    ANGLE_MTL_LOG("scissoredArea = %d,%d,%d,%d", scissoredArea.x, scissoredArea.y,
                  scissoredArea.width, scissoredArea.height);

    mScissorRect = mtl::GetScissorRect(scissoredArea);
    mDirtyBits.set(DIRTY_BIT_SCISSOR);
}

void ContextMtl::updateCullMode(const gl::State &glState)
{
    const gl::RasterizerState &rasterState = glState.getRasterizerState();

    mCullAllPolygons = false;
    if (!rasterState.cullFace)
    {
        mCullMode = MTLCullModeNone;
    }
    else
    {
        switch (rasterState.cullMode)
        {
            case gl::CullFaceMode::Back:
                mCullMode = MTLCullModeBack;
                break;
            case gl::CullFaceMode::Front:
                mCullMode = MTLCullModeFront;
                break;
            case gl::CullFaceMode::FrontAndBack:
                mCullAllPolygons = true;
                break;
            default:
                UNREACHABLE();
                break;
        }
    }

    mDirtyBits.set(DIRTY_BIT_CULL_MODE);
}

void ContextMtl::updateFrontFace(const gl::State &glState)
{
    FramebufferMtl *framebufferMtl = mtl::GetImpl(glState.getDrawFramebuffer());
    mWinding =
        mtl::GetFontfaceWinding(glState.getRasterizerState().frontFace, !framebufferMtl->flipY());
    mDirtyBits.set(DIRTY_BIT_WINDING);
}

void ContextMtl::updateDepthBias(const gl::State &glState)
{
    mDirtyBits.set(DIRTY_BIT_DEPTH_BIAS);
}

void ContextMtl::updateDrawFrameBufferBinding(const gl::Context *context)
{
    const gl::State &glState = getState();

    mDrawFramebuffer = mtl::GetImpl(glState.getDrawFramebuffer());

    mDrawFramebuffer->onStartedDrawingToFrameBuffer(context);

    onDrawFrameBufferChangedState(context, mDrawFramebuffer, true);
}

void ContextMtl::onDrawFrameBufferChangedState(const gl::Context *context,
                                               FramebufferMtl *framebuffer,
                                               bool renderPassChanged)
{
    const gl::State &glState = getState();
    ASSERT(framebuffer == mtl::GetImpl(glState.getDrawFramebuffer()));

    updateViewport(framebuffer, glState.getViewport(), glState.getNearPlane(),
                   glState.getFarPlane());
    updateFrontFace(glState);
    updateScissor(glState);

    if (renderPassChanged)
    {
        // End any render encoding using the old render pass.
        endEncoding(false);
        // Need to re-apply state to RenderCommandEncoder
        invalidateState(context);
    }
    else
    {
        // Invalidate current pipeline only.
        invalidateRenderPipeline();
    }
}

void ContextMtl::onBackbufferResized(const gl::Context *context, WindowSurfaceMtl *backbuffer)
{
    const gl::State &glState    = getState();
    FramebufferMtl *framebuffer = mtl::GetImpl(glState.getDrawFramebuffer());
    if (framebuffer->getAttachedBackbuffer() != backbuffer)
    {
        return;
    }

    onDrawFrameBufferChangedState(context, framebuffer, true);
}

angle::Result ContextMtl::onOcclusionQueryBegin(const gl::Context *context, QueryMtl *query)
{
    ASSERT(mOcclusionQuery == nullptr);
    mOcclusionQuery = query;

    if (mRenderEncoder.valid())
    {
        // if render pass has started, start the query in the encoder
        return startOcclusionQueryInRenderPass(query, true);
    }
    else
    {
        query->resetVisibilityResult(this);
    }

    return angle::Result::Continue;
}
void ContextMtl::onOcclusionQueryEnd(const gl::Context *context, QueryMtl *query)
{
    ASSERT(mOcclusionQuery == query);

    if (mRenderEncoder.valid())
    {
        // if render pass has started, end the query in the encoder
        disableActiveOcclusionQueryInRenderPass();
    }

    mOcclusionQuery = nullptr;
}
void ContextMtl::onOcclusionQueryDestroy(const gl::Context *context, QueryMtl *query)
{
    if (query->getAllocatedVisibilityOffsets().empty())
    {
        return;
    }
    if (mOcclusionQuery == query)
    {
        onOcclusionQueryEnd(context, query);
    }
    mOcclusionQueryPool.deallocateQueryOffset(this, query);
}

void ContextMtl::disableActiveOcclusionQueryInRenderPass()
{
    if (!mOcclusionQuery || mOcclusionQuery->getAllocatedVisibilityOffsets().empty())
    {
        return;
    }

    ASSERT(mRenderEncoder.valid());
    mRenderEncoder.setVisibilityResultMode(MTLVisibilityResultModeDisabled,
                                           mOcclusionQuery->getAllocatedVisibilityOffsets().back());
}

angle::Result ContextMtl::restartActiveOcclusionQueryInRenderPass()
{
    if (!mOcclusionQuery || mOcclusionQuery->getAllocatedVisibilityOffsets().empty())
    {
        return angle::Result::Continue;
    }

    return startOcclusionQueryInRenderPass(mOcclusionQuery, false);
}

angle::Result ContextMtl::startOcclusionQueryInRenderPass(QueryMtl *query, bool clearOldValue)
{
    ASSERT(mRenderEncoder.valid());

    ANGLE_TRY(mOcclusionQueryPool.allocateQueryOffset(this, query, clearOldValue));

    mRenderEncoder.setVisibilityResultMode(MTLVisibilityResultModeBoolean,
                                           query->getAllocatedVisibilityOffsets().back());

    // We need to mark the query's buffer as being written in this command buffer now. Since the
    // actual writing is deferred until the render pass ends and user could try to read the query
    // result before the render pass ends.
    mCmdBuffer.setWriteDependency(query->getVisibilityResultBuffer());

    return angle::Result::Continue;
}

void ContextMtl::onTransformFeedbackActive(const gl::Context *context, TransformFeedbackMtl *xfb)
{
    // NOTE(hqle): We have to end current render pass to enable synchronization before XFB
    // buffers could be used as vertex input. Consider a better approach.
    endEncoding(true);
}

void ContextMtl::onTransformFeedbackInactive(const gl::Context *context, TransformFeedbackMtl *xfb)
{
    // NOTE(hqle): We have to end current render pass to enable synchronization before XFB
    // buffers could be used as vertex input. Consider a better approach.
    endEncoding(true);
}

void ContextMtl::queueEventSignal(const mtl::SharedEventRef &event, uint64_t value)
{
    ensureCommandBufferReady();
    mCmdBuffer.queueEventSignal(event, value);
}

void ContextMtl::serverWaitEvent(const mtl::SharedEventRef &event, uint64_t value)
{
    ensureCommandBufferReady();

    // Event waiting cannot be encoded if there is active encoder.
    endEncoding(true);

    mCmdBuffer.serverWaitEvent(event, value);
}

void ContextMtl::updateProgramExecutable(const gl::Context *context)
{
    // Need to rebind textures
    invalidateCurrentTextures();
    // Need to re-upload default attributes
    invalidateDefaultAttributes(context->getStateCache().getActiveDefaultAttribsMask());
    // Render pipeline need to be re-applied
    invalidateRenderPipeline();
}

void ContextMtl::updateVertexArray(const gl::Context *context)
{
    const gl::State &glState = getState();
    mVertexArray             = mtl::GetImpl(glState.getVertexArray());
    invalidateDefaultAttributes(context->getStateCache().getActiveDefaultAttribsMask());
    invalidateRenderPipeline();
}

angle::Result ContextMtl::updateDefaultAttribute(size_t attribIndex)
{
    const gl::State &glState = mState;
    const gl::VertexAttribCurrentValueData &defaultValue =
        glState.getVertexAttribCurrentValues()[attribIndex];

    constexpr size_t kDefaultGLAttributeValueSize =
        sizeof(gl::VertexAttribCurrentValueData::Values);

    static_assert(kDefaultGLAttributeValueSize == mtl::kDefaultAttributeSize,
                  "Unexpected default attribute size");
    memcpy(mDefaultAttributes[attribIndex].values, &defaultValue.Values,
           mtl::kDefaultAttributeSize);

    return angle::Result::Continue;
}

angle::Result ContextMtl::setupDraw(const gl::Context *context,
                                    gl::PrimitiveMode mode,
                                    GLint firstVertex,
                                    GLsizei vertexOrIndexCount,
                                    GLsizei instances,
                                    gl::DrawElementsType indexTypeOrNone,
                                    const void *indices,
                                    bool xfbPass)
{
    ASSERT(mProgram);

    // instances=0 means no instanced draw.
    GLsizei instanceCount = instances ? instances : 1;

    if (context->getStateCache().hasAnyActiveClientAttrib())
    {
        ANGLE_TRY(mVertexArray->updateClientAttribs(context, firstVertex, vertexOrIndexCount,
                                                    instanceCount, indexTypeOrNone, indices));
    }
    // This must be called before render command encoder is started.
    bool textureChanged = false;
    if (mDirtyBits.test(DIRTY_BIT_TEXTURES))
    {
        textureChanged = true;
        ANGLE_TRY(handleDirtyActiveTextures(context));
    }

    if (mDirtyBits.test(DIRTY_BIT_RASTERIZER_DISCARD))
    {
        if (getState().isTransformFeedbackActiveUnpaused())
        {
            // If XFB is active we need to reset render pass since we could use a dummy render
            // target if only XFB is needed.
            invalidateState(context);
        }
        else
        {
            invalidateRenderPipeline();
        }
    }

    if (!mRenderEncoder.valid())
    {
        // re-apply everything
        invalidateState(context);
    }

    if (mDirtyBits.test(DIRTY_BIT_DRAW_FRAMEBUFFER))
    {
        ANGLE_TRY(handleDirtyRenderPass(context));
    }

    if (mOcclusionQuery && mOcclusionQueryPool.getNumRenderPassAllocatedQueries() == 0)
    {
        // The occlusion query is still active, and a new render pass has started.
        // We need to continue the querying process in the new render encoder.
        ANGLE_TRY(startOcclusionQueryInRenderPass(mOcclusionQuery, false));
    }

    bool isPipelineDescChanged;
    ANGLE_TRY(checkIfPipelineChanged(context, mode, xfbPass, &isPipelineDescChanged));

    bool uniformBuffersDirty = false;

    if (IsTransformFeedbackOnly(getState()))
    {
        // Filter out unneeded dirty bits
        filterOutXFBOnlyDirtyBits(context);
    }

    for (size_t bit : mDirtyBits)
    {
        switch (bit)
        {
            case DIRTY_BIT_TEXTURES:
                // Already handled.
                break;
            case DIRTY_BIT_DEFAULT_ATTRIBS:
                ANGLE_TRY(handleDirtyDefaultAttribs(context));
                break;
            case DIRTY_BIT_DRIVER_UNIFORMS:
                ANGLE_TRY(handleDirtyDriverUniforms(context, firstVertex, vertexOrIndexCount));
                break;
            case DIRTY_BIT_DEPTH_STENCIL_DESC:
                ANGLE_TRY(handleDirtyDepthStencilState(context));
                break;
            case DIRTY_BIT_DEPTH_BIAS:
                ANGLE_TRY(handleDirtyDepthBias(context));
                break;
            case DIRTY_BIT_STENCIL_REF:
                mRenderEncoder.setStencilRefVals(mStencilRefFront, mStencilRefBack);
                break;
            case DIRTY_BIT_BLEND_COLOR:
                mRenderEncoder.setBlendColor(
                    mState.getBlendColor().red, mState.getBlendColor().green,
                    mState.getBlendColor().blue, mState.getBlendColor().alpha);
                break;
            case DIRTY_BIT_VIEWPORT:
                mRenderEncoder.setViewport(mViewport);
                break;
            case DIRTY_BIT_SCISSOR:
                mRenderEncoder.setScissorRect(mScissorRect);
                break;
            case DIRTY_BIT_DRAW_FRAMEBUFFER:
                // Already handled.
                break;
            case DIRTY_BIT_CULL_MODE:
                mRenderEncoder.setCullMode(mCullMode);
                break;
            case DIRTY_BIT_WINDING:
                mRenderEncoder.setFrontFacingWinding(mWinding);
                break;
            case DIRTY_BIT_RENDER_PIPELINE:
                // Already handled. See checkIfPipelineChanged().
                break;
            case DIRTY_BIT_UNIFORM_BUFFERS_BINDING:
                uniformBuffersDirty = true;
                break;
            case DIRTY_BIT_RASTERIZER_DISCARD:
                // Already handled.
                break;
            default:
                UNREACHABLE();
                break;
        }
    }

    if (xfbPass && !mDirtyBits.test(DIRTY_BIT_DRIVER_UNIFORMS))
    {
        // If handleDirtyDriverUniforms() was not called and this is XFB pass, we still need to
        // update XFB related uniforms
        ANGLE_TRY(
            fillDriverXFBUniforms(firstVertex, vertexOrIndexCount, /** skippedInstances */ 0));
        mRenderEncoder.setVertexData(mDriverUniforms, mtl::kDriverUniformsBindingIndex);
    }

    mDirtyBits.reset();

    ANGLE_TRY(mProgram->setupDraw(context, &mRenderEncoder, mRenderPipelineDesc,
                                  isPipelineDescChanged, textureChanged, uniformBuffersDirty));

    return angle::Result::Continue;
}

void ContextMtl::filterOutXFBOnlyDirtyBits(const gl::Context *context)
{
    ASSERT(IsTransformFeedbackOnly(getState()));

    ASSERT(mRenderEncoder.renderPassDesc().colorAttachments[0].texture == mDummyXFBRenderTexture);

    // In transform feedback only pass, only vertex shader's related states are needed.
    constexpr size_t kUnneededBits =
        angle::Bit<size_t>(DIRTY_BIT_DEPTH_STENCIL_DESC) |
        angle::Bit<size_t>(DIRTY_BIT_DEPTH_BIAS) | angle::Bit<size_t>(DIRTY_BIT_STENCIL_REF) |
        angle::Bit<size_t>(DIRTY_BIT_BLEND_COLOR) | angle::Bit<size_t>(DIRTY_BIT_VIEWPORT) |
        angle::Bit<size_t>(DIRTY_BIT_SCISSOR) | angle::Bit<size_t>(DIRTY_BIT_CULL_MODE) |
        angle::Bit<size_t>(DIRTY_BIT_WINDING);

    mDirtyBits &= ~kUnneededBits;
}

angle::Result ContextMtl::handleDirtyRenderPass(const gl::Context *context)
{
    if (!IsTransformFeedbackOnly(mState))
    {
        // Start new render command encoder
        ANGLE_MTL_TRY(this, mDrawFramebuffer->ensureRenderPassStarted(context));
    }
    else
    {
        // XFB is active and rasterization is disabled. Use dummy render target.
        // We currently need to end the render pass when XFB is activated/deactivated so using
        // a small dummy render target would make the render pass ending very cheap.
        if (!mDummyXFBRenderTexture)
        {
            ANGLE_TRY(mtl::Texture::Make2DTexture(this,
                                                  getPixelFormat(angle::FormatID::R8G8B8A8_UNORM),
                                                  1, 1, 1, true, false, &mDummyXFBRenderTexture));
        }
        mtl::RenderCommandEncoder *encoder = getTextureRenderCommandEncoder(
            mDummyXFBRenderTexture,
            mtl::ImageNativeIndex::FromBaseZeroGLIndex(gl::ImageIndex::Make2D(0)));
        encoder->setColorLoadAction(MTLLoadActionDontCare, MTLClearColor(), 0);
        encoder->setColorStoreAction(MTLStoreActionDontCare);

#ifndef NDEBUG
        encoder->setLabel(@"TransformFeedbackOnlyPass");
#endif
    }

    // re-apply everything
    invalidateState(context);

    return angle::Result::Continue;
}

angle::Result ContextMtl::handleDirtyActiveTextures(const gl::Context *context)
{
    const gl::State &glState   = mState;
    const gl::Program *program = glState.getProgram();

    const gl::ActiveTexturesCache &textures     = glState.getActiveTexturesCache();
    const gl::ActiveTextureMask &activeTextures = program->getExecutable().getActiveSamplersMask();

    for (size_t textureUnit : activeTextures)
    {
        gl::Texture *texture = textures[textureUnit];

        if (texture == nullptr)
        {
            continue;
        }

        TextureMtl *textureMtl = mtl::GetImpl(texture);

        // Make sure texture's images update will be transferred to GPU.
        ANGLE_TRY(textureMtl->ensureTextureCreated(context));

        // The binding of this texture will be done by ProgramMtl.
    }

    return angle::Result::Continue;
}

angle::Result ContextMtl::handleDirtyDefaultAttribs(const gl::Context *context)
{
    for (size_t attribIndex : mDirtyDefaultAttribsMask)
    {
        ANGLE_TRY(updateDefaultAttribute(attribIndex));
    }

    ASSERT(mRenderEncoder.valid());
    mRenderEncoder.setVertexData(mDefaultAttributes, mtl::kDefaultAttribsBindingIndex);

    mDirtyDefaultAttribsMask.reset();
    return angle::Result::Continue;
}

angle::Result ContextMtl::handleDirtyDriverUniforms(const gl::Context *context,
                                                    GLint drawCallFirstVertex,
                                                    uint32_t verticesPerInstance)
{
    const gl::Rectangle &glViewport = mState.getViewport();

    float depthRangeNear = mState.getNearPlane();
    float depthRangeFar  = mState.getFarPlane();
    float depthRangeDiff = depthRangeFar - depthRangeNear;

    mDriverUniforms.viewport[0] = glViewport.x;
    mDriverUniforms.viewport[1] = glViewport.y;
    mDriverUniforms.viewport[2] = glViewport.width;
    mDriverUniforms.viewport[3] = glViewport.height;

    mDriverUniforms.halfRenderArea[0] =
        static_cast<float>(mDrawFramebuffer->getState().getDimensions().width) * 0.5f;
    mDriverUniforms.halfRenderArea[1] =
        static_cast<float>(mDrawFramebuffer->getState().getDimensions().height) * 0.5f;
    mDriverUniforms.flipXY[0]    = 1.0f;
    mDriverUniforms.flipXY[1]    = mDrawFramebuffer->flipY() ? -1.0f : 1.0f;
    mDriverUniforms.negFlipXY[0] = mDriverUniforms.flipXY[0];
    mDriverUniforms.negFlipXY[1] = -mDriverUniforms.flipXY[1];

    // gl_ClipDistance
    mDriverUniforms.enabledClipDistances = mState.getEnabledClipDistances().bits();

    mDriverUniforms.depthRange[0] = depthRangeNear;
    mDriverUniforms.depthRange[1] = depthRangeFar;
    mDriverUniforms.depthRange[2] = depthRangeDiff;
    mDriverUniforms.depthRange[3] = NeedToInvertDepthRange(depthRangeNear, depthRangeFar) ? -1 : 1;

    // NOTE(hqle): preRotation & fragRotation are unused.

    // Sample coverage mask
    uint32_t sampleBitCount = mDrawFramebuffer->getSamples();
    uint32_t coverageSampleBitCount =
        static_cast<uint32_t>(std::round(mState.getSampleCoverageValue() * sampleBitCount));
    ASSERT(sampleBitCount < 32);
    uint32_t coverageMask = (1u << coverageSampleBitCount) - 1;
    uint32_t sampleMask   = (1u << sampleBitCount) - 1;
    if (mState.getSampleCoverageInvert())
    {
        coverageMask = sampleMask & (~coverageMask);
    }
    mDriverUniforms.coverageMask = coverageMask;

    ANGLE_TRY(
        fillDriverXFBUniforms(drawCallFirstVertex, verticesPerInstance, /** skippedInstances */ 0));

    ASSERT(mRenderEncoder.valid());
    mRenderEncoder.setFragmentData(mDriverUniforms, mtl::kDriverUniformsBindingIndex);
    mRenderEncoder.setVertexData(mDriverUniforms, mtl::kDriverUniformsBindingIndex);

    return angle::Result::Continue;
}

angle::Result ContextMtl::fillDriverXFBUniforms(GLint drawCallFirstVertex,
                                                uint32_t verticesPerInstance,
                                                uint32_t skippedInstances)
{
    gl::TransformFeedback *transformFeedback = getState().getCurrentTransformFeedback();

    mDriverUniforms.xfbActiveUnpaused = getState().isTransformFeedbackActiveUnpaused();
    if (!transformFeedback || !mDriverUniforms.xfbActiveUnpaused)
    {
        return angle::Result::Continue;
    }

    mDriverUniforms.xfbVerticesPerDraw = verticesPerInstance;

    TransformFeedbackMtl *transformFeedbackMtl = mtl::GetImpl(transformFeedback);

    return transformFeedbackMtl->getBufferOffsets(this, drawCallFirstVertex,
                                                  verticesPerInstance * skippedInstances,
                                                  mDriverUniforms.xfbBufferOffsets);
}

angle::Result ContextMtl::handleDirtyDepthStencilState(const gl::Context *context)
{
    ASSERT(mRenderEncoder.valid());

    // Need to handle the case when render pass doesn't have depth/stencil attachment.
    mtl::DepthStencilDesc dsDesc              = mDepthStencilDesc;
    const mtl::RenderPassDesc &renderPassDesc = mRenderEncoder.renderPassDesc();

    if (!renderPassDesc.depthAttachment.texture)
    {
        dsDesc.depthWriteEnabled    = false;
        dsDesc.depthCompareFunction = MTLCompareFunctionAlways;
    }

    if (!renderPassDesc.stencilAttachment.texture)
    {
        dsDesc.frontFaceStencil.reset();
        dsDesc.backFaceStencil.reset();
    }

    // Apply depth stencil state
    mRenderEncoder.setDepthStencilState(getDisplay()->getDepthStencilState(dsDesc));

    return angle::Result::Continue;
}

angle::Result ContextMtl::handleDirtyDepthBias(const gl::Context *context)
{
    const gl::RasterizerState &raserState = mState.getRasterizerState();
    ASSERT(mRenderEncoder.valid());
    if (!mState.isPolygonOffsetFillEnabled())
    {
        mRenderEncoder.setDepthBias(0, 0, 0);
    }
    else
    {
        mRenderEncoder.setDepthBias(raserState.polygonOffsetUnits, raserState.polygonOffsetFactor,
                                    0);
    }

    return angle::Result::Continue;
}

angle::Result ContextMtl::checkIfPipelineChanged(const gl::Context *context,
                                                 gl::PrimitiveMode primitiveMode,
                                                 bool xfbPass,
                                                 bool *isPipelineDescChanged)
{
    ASSERT(mRenderEncoder.valid());
    mtl::PrimitiveTopologyClass topologyClass = mtl::GetPrimitiveTopologyClass(primitiveMode);

    bool rppChange = mDirtyBits.test(DIRTY_BIT_RENDER_PIPELINE) ||
                     topologyClass != mRenderPipelineDesc.inputPrimitiveTopology;

    // Obtain RenderPipelineDesc's vertex array descriptor.
    ANGLE_TRY(mVertexArray->setupDraw(context, &mRenderEncoder, &rppChange,
                                      &mRenderPipelineDesc.vertexDescriptor));

    if (rppChange)
    {
        const mtl::RenderPassDesc &renderPassDesc = mRenderEncoder.renderPassDesc();
        // Obtain RenderPipelineDesc's output descriptor.
        renderPassDesc.populateRenderPipelineOutputDesc(mBlendDesc,
                                                        &mRenderPipelineDesc.outputDescriptor);

        if (xfbPass)
        {
            // In XFB pass, we disable fragment shader.
            mRenderPipelineDesc.rasterizationType = mtl::RenderPipelineRasterization::Disabled;
        }
        else if (mState.isRasterizerDiscardEnabled())
        {
            // If XFB is not active and rasterizer discard is enabled, we need to emulate the
            // discard. Because in this case, vertex shader might write to stage output values and
            // Metal doesn't allow rasterization to be disabled.
            mRenderPipelineDesc.rasterizationType =
                mtl::RenderPipelineRasterization::EmulatedDiscard;
        }
        else
        {
            mRenderPipelineDesc.rasterizationType = mtl::RenderPipelineRasterization::Enabled;
        }
        mRenderPipelineDesc.inputPrimitiveTopology = topologyClass;
        mRenderPipelineDesc.alphaToCoverageEnabled = mState.isSampleAlphaToCoverageEnabled();
        mRenderPipelineDesc.emulateCoverageMask    = mState.isSampleCoverageEnabled();

        mRenderPipelineDesc.outputDescriptor.updateEnabledDrawBuffers(
            mDrawFramebuffer->getState().getEnabledDrawBuffers());
    }

    *isPipelineDescChanged = rppChange;

    return angle::Result::Continue;
}
}
