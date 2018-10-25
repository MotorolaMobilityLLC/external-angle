//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// VertexArray11:
//   Implementation of rx::VertexArray11.
//

#include "libANGLE/renderer/d3d/d3d11/VertexArray11.h"

#include "common/bitset_utils.h"
#include "libANGLE/Context.h"
#include "libANGLE/renderer/d3d/IndexBuffer.h"
#include "libANGLE/renderer/d3d/d3d11/Buffer11.h"
#include "libANGLE/renderer/d3d/d3d11/Context11.h"

using namespace angle;

namespace rx
{
VertexArray11::VertexArray11(const gl::VertexArrayState &data)
    : VertexArrayImpl(data),
      mAttributeStorageTypes(data.getMaxAttribs(), VertexStorageType::CURRENT_VALUE),
      mTranslatedAttribs(data.getMaxAttribs()),
      mAppliedNumViewsToDivisor(1),
      mCurrentElementArrayStorage(IndexStorageType::Invalid),
      mCachedDestinationIndexType(GL_NONE)
{
}

VertexArray11::~VertexArray11()
{
}

void VertexArray11::destroy(const gl::Context *context)
{
}

// As VertexAttribPointer can modify both attribute and binding, we should also set other attributes
// that are also using this binding dirty.
#define ANGLE_VERTEX_DIRTY_ATTRIB_FUNC(INDEX)                                             \
    case gl::VertexArray::DIRTY_BIT_ATTRIB_0 + INDEX:                                     \
        if (attribBits[INDEX][gl::VertexArray::DirtyAttribBitType::DIRTY_ATTRIB_POINTER]) \
        {                                                                                 \
            attributesToUpdate |= mState.getBindingToAttributesMask(INDEX);               \
        }                                                                                 \
        else                                                                              \
        {                                                                                 \
            attributesToUpdate.set(INDEX);                                                \
        }                                                                                 \
        invalidateVertexBuffer = true;                                                    \
        break;

#define ANGLE_VERTEX_DIRTY_BINDING_FUNC(INDEX)                          \
    case gl::VertexArray::DIRTY_BIT_BINDING_0 + INDEX:                  \
        attributesToUpdate |= mState.getBindingToAttributesMask(INDEX); \
        invalidateVertexBuffer = true;                                  \
        break;

#define ANGLE_VERTEX_DIRTY_BUFFER_DATA_FUNC(INDEX)                      \
    case gl::VertexArray::DIRTY_BIT_BUFFER_DATA_0 + INDEX:              \
        if (mAttributeStorageTypes[INDEX] == VertexStorageType::STATIC) \
        {                                                               \
            invalidateVertexBuffer = true;                              \
            mAttribsToTranslate.set(INDEX);                             \
        }                                                               \
        break;

angle::Result VertexArray11::syncState(const gl::Context *context,
                                       const gl::VertexArray::DirtyBits &dirtyBits,
                                       const gl::VertexArray::DirtyAttribBitsArray &attribBits,
                                       const gl::VertexArray::DirtyBindingBitsArray &bindingBits)
{
    ASSERT(dirtyBits.any());

    Renderer11 *renderer         = GetImplAs<Context11>(context)->getRenderer();
    StateManager11 *stateManager = renderer->getStateManager();

    // Generate a state serial. This serial is used in the program class to validate the cached
    // input layout, and skip recomputation in the fast path.
    mCurrentStateSerial = renderer->generateSerial();

    bool invalidateVertexBuffer = false;

    gl::AttributesMask attributesToUpdate;

    // Make sure we trigger re-translation for static index or vertex data.
    for (size_t dirtyBit : dirtyBits)
    {
        switch (dirtyBit)
        {
            case gl::VertexArray::DIRTY_BIT_ELEMENT_ARRAY_BUFFER:
            case gl::VertexArray::DIRTY_BIT_ELEMENT_ARRAY_BUFFER_DATA:
            {
                mLastDrawElementsType.reset();
                mLastDrawElementsIndices.reset();
                mLastPrimitiveRestartEnabled.reset();
                mCachedIndexInfo.reset();
                break;
            }

                ANGLE_VERTEX_INDEX_CASES(ANGLE_VERTEX_DIRTY_ATTRIB_FUNC);
                ANGLE_VERTEX_INDEX_CASES(ANGLE_VERTEX_DIRTY_BINDING_FUNC);
                ANGLE_VERTEX_INDEX_CASES(ANGLE_VERTEX_DIRTY_BUFFER_DATA_FUNC);

            default:
                UNREACHABLE();
                break;
        }
    }

    for (size_t attribIndex : attributesToUpdate)
    {
        updateVertexAttribStorage(context, stateManager, attribIndex);
    }

    if (invalidateVertexBuffer)
    {
        // TODO(jmadill): Individual attribute invalidation.
        stateManager->invalidateVertexBuffer();
    }

    return angle::Result::Continue();
}

angle::Result VertexArray11::syncStateForDraw(const gl::Context *context,
                                              GLint firstVertex,
                                              GLsizei vertexOrIndexCount,
                                              GLenum indexTypeOrNone,
                                              const void *indices,
                                              GLsizei instances,
                                              GLint baseVertex)
{
    Renderer11 *renderer         = GetImplAs<Context11>(context)->getRenderer();
    StateManager11 *stateManager = renderer->getStateManager();

    const gl::State &glState   = context->getGLState();
    const gl::Program *program = glState.getProgram();
    ASSERT(program);
    mAppliedNumViewsToDivisor = (program->usesMultiview() ? program->getNumViews() : 1);

    if (mAttribsToTranslate.any())
    {
        const gl::AttributesMask &activeLocations =
            glState.getProgram()->getActiveAttribLocationsMask();
        gl::AttributesMask activeDirtyAttribs = (mAttribsToTranslate & activeLocations);
        if (activeDirtyAttribs.any())
        {
            ANGLE_TRY(updateDirtyAttribs(context, activeDirtyAttribs));
            stateManager->invalidateInputLayout();
        }
    }

    if (mDynamicAttribsMask.any())
    {
        const gl::AttributesMask &activeLocations =
            glState.getProgram()->getActiveAttribLocationsMask();
        gl::AttributesMask activeDynamicAttribs = (mDynamicAttribsMask & activeLocations);

        if (activeDynamicAttribs.any())
        {
            ANGLE_TRY(updateDynamicAttribs(context, stateManager->getVertexDataManager(),
                                           firstVertex, vertexOrIndexCount, indexTypeOrNone,
                                           indices, instances, baseVertex, activeDynamicAttribs));
            stateManager->invalidateInputLayout();
        }
    }

    if (indexTypeOrNone != GL_NONE)
    {
        bool restartEnabled = context->getGLState().isPrimitiveRestartEnabled();
        if (!mLastDrawElementsType.valid() || mLastDrawElementsType.value() != indexTypeOrNone ||
            mLastDrawElementsIndices.value() != indices ||
            mLastPrimitiveRestartEnabled.value() != restartEnabled)
        {
            mLastDrawElementsType        = indexTypeOrNone;
            mLastDrawElementsIndices     = indices;
            mLastPrimitiveRestartEnabled = restartEnabled;

            ANGLE_TRY(updateElementArrayStorage(context, vertexOrIndexCount, indexTypeOrNone,
                                                indices, restartEnabled));
            stateManager->invalidateIndexBuffer();
        }
        else if (mCurrentElementArrayStorage == IndexStorageType::Dynamic)
        {
            stateManager->invalidateIndexBuffer();
        }
    }

    return angle::Result::Continue();
}

angle::Result VertexArray11::updateElementArrayStorage(const gl::Context *context,
                                                       GLsizei indexCount,
                                                       GLenum indexType,
                                                       const void *indices,
                                                       bool restartEnabled)
{
    bool usePrimitiveRestartWorkaround = UsePrimitiveRestartWorkaround(restartEnabled, indexType);

    ANGLE_TRY(GetIndexTranslationDestType(context, indexCount, indexType, indices,
                                          usePrimitiveRestartWorkaround,
                                          &mCachedDestinationIndexType));

    unsigned int offset = static_cast<unsigned int>(reinterpret_cast<uintptr_t>(indices));

    mCurrentElementArrayStorage =
        ClassifyIndexStorage(context->getGLState(), mState.getElementArrayBuffer(), indexType,
                             mCachedDestinationIndexType, offset);

    return angle::Result::Continue();
}

void VertexArray11::updateVertexAttribStorage(const gl::Context *context,
                                              StateManager11 *stateManager,
                                              size_t attribIndex)
{
    const gl::VertexAttribute &attrib = mState.getVertexAttribute(attribIndex);
    const gl::VertexBinding &binding  = mState.getBindingFromAttribIndex(attribIndex);

    VertexStorageType newStorageType = ClassifyAttributeStorage(context, attrib, binding);

    // Note: having an unchanged storage type doesn't mean the attribute is clean.
    mAttribsToTranslate.set(attribIndex, newStorageType != VertexStorageType::DYNAMIC);

    if (mAttributeStorageTypes[attribIndex] == newStorageType)
        return;

    mAttributeStorageTypes[attribIndex] = newStorageType;
    mDynamicAttribsMask.set(attribIndex, newStorageType == VertexStorageType::DYNAMIC);

    if (newStorageType == VertexStorageType::CURRENT_VALUE)
    {
        stateManager->invalidateCurrentValueAttrib(attribIndex);
    }
}

bool VertexArray11::hasActiveDynamicAttrib(const gl::Context *context)
{
    const auto &activeLocations =
        context->getGLState().getProgram()->getActiveAttribLocationsMask();
    gl::AttributesMask activeDynamicAttribs = (mDynamicAttribsMask & activeLocations);
    return activeDynamicAttribs.any();
}

angle::Result VertexArray11::updateDirtyAttribs(const gl::Context *context,
                                                const gl::AttributesMask &activeDirtyAttribs)
{
    const auto &glState  = context->getGLState();
    const auto &attribs  = mState.getVertexAttributes();
    const auto &bindings = mState.getVertexBindings();

    for (size_t dirtyAttribIndex : activeDirtyAttribs)
    {
        mAttribsToTranslate.reset(dirtyAttribIndex);

        auto *translatedAttrib   = &mTranslatedAttribs[dirtyAttribIndex];
        const auto &currentValue = glState.getVertexAttribCurrentValue(dirtyAttribIndex);

        // Record basic attrib info
        translatedAttrib->attribute        = &attribs[dirtyAttribIndex];
        translatedAttrib->binding          = &bindings[translatedAttrib->attribute->bindingIndex];
        translatedAttrib->currentValueType = currentValue.Type;
        translatedAttrib->divisor =
            translatedAttrib->binding->getDivisor() * mAppliedNumViewsToDivisor;

        switch (mAttributeStorageTypes[dirtyAttribIndex])
        {
            case VertexStorageType::DIRECT:
                VertexDataManager::StoreDirectAttrib(context, translatedAttrib);
                break;
            case VertexStorageType::STATIC:
            {
                ANGLE_TRY(VertexDataManager::StoreStaticAttrib(context, translatedAttrib));
                break;
            }
            case VertexStorageType::CURRENT_VALUE:
                // Current value attribs are managed by the StateManager11.
                break;
            default:
                UNREACHABLE();
                break;
        }
    }

    return angle::Result::Continue();
}

angle::Result VertexArray11::updateDynamicAttribs(const gl::Context *context,
                                                  VertexDataManager *vertexDataManager,
                                                  GLint firstVertex,
                                                  GLsizei vertexOrIndexCount,
                                                  GLenum indexTypeOrNone,
                                                  const void *indices,
                                                  GLsizei instances,
                                                  GLint baseVertex,
                                                  const gl::AttributesMask &activeDynamicAttribs)
{
    const auto &glState  = context->getGLState();
    const auto &attribs  = mState.getVertexAttributes();
    const auto &bindings = mState.getVertexBindings();

    GLint startVertex;
    size_t vertexCount;
    ANGLE_TRY(GetVertexRangeInfo(context, firstVertex, vertexOrIndexCount, indexTypeOrNone, indices,
                                 baseVertex, &startVertex, &vertexCount));

    for (size_t dynamicAttribIndex : activeDynamicAttribs)
    {
        auto *dynamicAttrib      = &mTranslatedAttribs[dynamicAttribIndex];
        const auto &currentValue = glState.getVertexAttribCurrentValue(dynamicAttribIndex);

        // Record basic attrib info
        dynamicAttrib->attribute        = &attribs[dynamicAttribIndex];
        dynamicAttrib->binding          = &bindings[dynamicAttrib->attribute->bindingIndex];
        dynamicAttrib->currentValueType = currentValue.Type;
        dynamicAttrib->divisor = dynamicAttrib->binding->getDivisor() * mAppliedNumViewsToDivisor;
    }

    ANGLE_TRY(vertexDataManager->storeDynamicAttribs(
        context, &mTranslatedAttribs, activeDynamicAttribs, startVertex, vertexCount, instances));

    VertexDataManager::PromoteDynamicAttribs(context, mTranslatedAttribs, activeDynamicAttribs,
                                             vertexCount);

    return angle::Result::Continue();
}

const std::vector<TranslatedAttribute> &VertexArray11::getTranslatedAttribs() const
{
    return mTranslatedAttribs;
}

void VertexArray11::markAllAttributeDivisorsForAdjustment(int numViews)
{
    if (mAppliedNumViewsToDivisor != numViews)
    {
        mAppliedNumViewsToDivisor = numViews;
        mAttribsToTranslate.set();
    }
}

const TranslatedIndexData &VertexArray11::getCachedIndexInfo() const
{
    ASSERT(mCachedIndexInfo.valid());
    return mCachedIndexInfo.value();
}

void VertexArray11::updateCachedIndexInfo(const TranslatedIndexData &indexInfo)
{
    mCachedIndexInfo = indexInfo;
}

bool VertexArray11::isCachedIndexInfoValid() const
{
    return mCachedIndexInfo.valid();
}

GLenum VertexArray11::getCachedDestinationIndexType() const
{
    return mCachedDestinationIndexType;
}

}  // namespace rx
