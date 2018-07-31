//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Implementation of the state class for mananging GLES 3 Vertex Array Objects.
//

#include "libANGLE/VertexArray.h"
#include "libANGLE/Buffer.h"
#include "libANGLE/Context.h"
#include "libANGLE/renderer/BufferImpl.h"
#include "libANGLE/renderer/GLImplFactory.h"
#include "libANGLE/renderer/VertexArrayImpl.h"

namespace gl
{
// VertexArrayState implementation.
VertexArrayState::VertexArrayState(size_t maxAttribs, size_t maxAttribBindings)
    : mLabel(), mVertexBindings()
{
    ASSERT(maxAttribs <= maxAttribBindings);

    for (size_t i = 0; i < maxAttribs; i++)
    {
        mVertexAttributes.emplace_back(static_cast<GLuint>(i));
        mVertexBindings.emplace_back(static_cast<GLuint>(i));
    }

    // Initially all attributes start as "client" with no buffer bound.
    mClientMemoryAttribsMask.set();
}

VertexArrayState::~VertexArrayState()
{
}

bool VertexArrayState::hasEnabledNullPointerClientArray() const
{
    return (mNullPointerClientMemoryAttribsMask & mEnabledAttributesMask).any();
}

AttributesMask VertexArrayState::getBindingToAttributesMask(GLuint bindingIndex) const
{
    ASSERT(bindingIndex < MAX_VERTEX_ATTRIB_BINDINGS);
    return mVertexBindings[bindingIndex].getBoundAttributesMask();
}

// Set an attribute using a new binding.
void VertexArrayState::setAttribBinding(size_t attribIndex, GLuint newBindingIndex)
{
    ASSERT(attribIndex < MAX_VERTEX_ATTRIBS && newBindingIndex < MAX_VERTEX_ATTRIB_BINDINGS);

    // Update the binding-attribute map.
    const GLuint oldBindingIndex = mVertexAttributes[attribIndex].bindingIndex;
    ASSERT(oldBindingIndex != newBindingIndex);

    ASSERT(mVertexBindings[oldBindingIndex].getBoundAttributesMask().test(attribIndex) &&
           !mVertexBindings[newBindingIndex].getBoundAttributesMask().test(attribIndex));

    mVertexBindings[oldBindingIndex].resetBoundAttribute(attribIndex);
    mVertexBindings[newBindingIndex].setBoundAttribute(attribIndex);

    // Set the attribute using the new binding.
    mVertexAttributes[attribIndex].bindingIndex = newBindingIndex;
}

// VertexArray implementation.
VertexArray::VertexArray(rx::GLImplFactory *factory,
                         GLuint id,
                         size_t maxAttribs,
                         size_t maxAttribBindings)
    : mId(id),
      mState(maxAttribs, maxAttribBindings),
      mVertexArray(factory->createVertexArray(mState)),
      mElementArrayBufferObserverBinding(this, maxAttribBindings)
{
    for (size_t attribIndex = 0; attribIndex < maxAttribBindings; ++attribIndex)
    {
        mArrayBufferObserverBindings.emplace_back(this, attribIndex);
    }
}

void VertexArray::onDestroy(const Context *context)
{
    bool isBound = context->isCurrentVertexArray(this);
    for (VertexBinding &binding : mState.mVertexBindings)
    {
        binding.setBuffer(context, nullptr, isBound);
    }
    if (isBound && mState.mElementArrayBuffer.get())
        mState.mElementArrayBuffer->onBindingChanged(context, false, BufferBinding::ElementArray,
                                                     false);
    mState.mElementArrayBuffer.set(context, nullptr);
    mVertexArray->destroy(context);
    SafeDelete(mVertexArray);
    delete this;
}

VertexArray::~VertexArray()
{
    ASSERT(!mVertexArray);
}

GLuint VertexArray::id() const
{
    return mId;
}

void VertexArray::setLabel(const std::string &label)
{
    mState.mLabel = label;
}

const std::string &VertexArray::getLabel() const
{
    return mState.mLabel;
}

void VertexArray::detachBuffer(const Context *context, GLuint bufferName)
{
    bool isBound = context->isCurrentVertexArray(this);
    for (auto &binding : mState.mVertexBindings)
    {
        if (binding.getBuffer().id() == bufferName)
        {
            binding.setBuffer(context, nullptr, isBound);
        }
    }

    if (mState.mElementArrayBuffer.id() == bufferName)
    {
        if (isBound && mState.mElementArrayBuffer.get())
            mState.mElementArrayBuffer->onBindingChanged(context, false, BufferBinding::Array,
                                                         false);
        mState.mElementArrayBuffer.set(context, nullptr);
    }
}

const VertexAttribute &VertexArray::getVertexAttribute(size_t attribIndex) const
{
    ASSERT(attribIndex < getMaxAttribs());
    return mState.mVertexAttributes[attribIndex];
}

const VertexBinding &VertexArray::getVertexBinding(size_t bindingIndex) const
{
    ASSERT(bindingIndex < getMaxBindings());
    return mState.mVertexBindings[bindingIndex];
}

size_t VertexArray::GetVertexIndexFromDirtyBit(size_t dirtyBit)
{
    static_assert(gl::MAX_VERTEX_ATTRIBS == gl::MAX_VERTEX_ATTRIB_BINDINGS,
                  "The stride of vertex attributes should equal to that of vertex bindings.");
    ASSERT(dirtyBit > DIRTY_BIT_ELEMENT_ARRAY_BUFFER);
    return (dirtyBit - DIRTY_BIT_ATTRIB_0) % gl::MAX_VERTEX_ATTRIBS;
}

void VertexArray::setDirtyAttribBit(size_t attribIndex, DirtyAttribBitType dirtyAttribBit)
{
    mDirtyBits.set(DIRTY_BIT_ATTRIB_0 + attribIndex);
    mDirtyAttribBits[attribIndex].set(dirtyAttribBit);
}

void VertexArray::setDirtyBindingBit(size_t bindingIndex, DirtyBindingBitType dirtyBindingBit)
{
    mDirtyBits.set(DIRTY_BIT_BINDING_0 + bindingIndex);
    mDirtyBindingBits[bindingIndex].set(dirtyBindingBit);
}

void VertexArray::bindVertexBufferImpl(const Context *context,
                                       size_t bindingIndex,
                                       Buffer *boundBuffer,
                                       GLintptr offset,
                                       GLsizei stride)
{
    ASSERT(bindingIndex < getMaxBindings());
    bool isBound = context->isCurrentVertexArray(this);

    VertexBinding *binding = &mState.mVertexBindings[bindingIndex];

    binding->setBuffer(context, boundBuffer, isBound);
    binding->setOffset(offset);
    binding->setStride(stride);

    updateObserverBinding(bindingIndex);
    updateCachedBufferBindingSize(bindingIndex);
    updateCachedTransformFeedbackBindingValidation(bindingIndex, boundBuffer);

    // Update client memory attribute pointers. Affects all bound attributes.
    if (boundBuffer)
    {
        mState.mClientMemoryAttribsMask &= ~binding->getBoundAttributesMask();
    }
    else
    {
        mState.mClientMemoryAttribsMask |= binding->getBoundAttributesMask();
    }
}

void VertexArray::bindVertexBuffer(const Context *context,
                                   size_t bindingIndex,
                                   Buffer *boundBuffer,
                                   GLintptr offset,
                                   GLsizei stride)
{
    bindVertexBufferImpl(context, bindingIndex, boundBuffer, offset, stride);
    setDirtyBindingBit(bindingIndex, DIRTY_BINDING_BUFFER);
}

void VertexArray::setVertexAttribBinding(const Context *context,
                                         size_t attribIndex,
                                         GLuint bindingIndex)
{
    ASSERT(attribIndex < getMaxAttribs() && bindingIndex < getMaxBindings());

    if (mState.mVertexAttributes[attribIndex].bindingIndex != bindingIndex)
    {
        // In ES 3.0 contexts, the binding cannot change, hence the code below is unreachable.
        ASSERT(context->getClientVersion() >= ES_3_1);

        mState.setAttribBinding(attribIndex, bindingIndex);

        setDirtyAttribBit(attribIndex, DIRTY_ATTRIB_BINDING);

        // Update client attribs mask.
        bool hasBuffer = mState.mVertexBindings[bindingIndex].getBuffer().get() != nullptr;
        mState.mClientMemoryAttribsMask.set(attribIndex, !hasBuffer);
    }
}

void VertexArray::setVertexBindingDivisor(size_t bindingIndex, GLuint divisor)
{
    ASSERT(bindingIndex < getMaxBindings());

    mState.mVertexBindings[bindingIndex].setDivisor(divisor);
    setDirtyBindingBit(bindingIndex, DIRTY_BINDING_DIVISOR);
}

void VertexArray::setVertexAttribFormatImpl(size_t attribIndex,
                                            GLint size,
                                            GLenum type,
                                            bool normalized,
                                            bool pureInteger,
                                            GLuint relativeOffset)
{
    ASSERT(attribIndex < getMaxAttribs());

    VertexAttribute *attrib = &mState.mVertexAttributes[attribIndex];

    attrib->size           = size;
    attrib->type           = type;
    attrib->normalized     = normalized;
    attrib->pureInteger    = pureInteger;
    attrib->relativeOffset = relativeOffset;
    mState.mVertexAttributesTypeMask.setIndex(GetVertexAttributeBaseType(*attrib), attribIndex);
    attrib->updateCachedSizePlusRelativeOffset();
}

void VertexArray::setVertexAttribFormat(size_t attribIndex,
                                        GLint size,
                                        GLenum type,
                                        bool normalized,
                                        bool pureInteger,
                                        GLuint relativeOffset)
{
    setVertexAttribFormatImpl(attribIndex, size, type, normalized, pureInteger, relativeOffset);
    setDirtyAttribBit(attribIndex, DIRTY_ATTRIB_FORMAT);
}

void VertexArray::setVertexAttribDivisor(const Context *context, size_t attribIndex, GLuint divisor)
{
    ASSERT(attribIndex < getMaxAttribs());

    setVertexAttribBinding(context, attribIndex, static_cast<GLuint>(attribIndex));
    setVertexBindingDivisor(attribIndex, divisor);
}

void VertexArray::enableAttribute(size_t attribIndex, bool enabledState)
{
    ASSERT(attribIndex < getMaxAttribs());

    mState.mVertexAttributes[attribIndex].enabled = enabledState;
    mState.mVertexAttributesTypeMask.setIndex(
        GetVertexAttributeBaseType(mState.mVertexAttributes[attribIndex]), attribIndex);

    setDirtyAttribBit(attribIndex, DIRTY_ATTRIB_ENABLED);

    // Update state cache
    mState.mEnabledAttributesMask.set(attribIndex, enabledState);
}

void VertexArray::setVertexAttribPointer(const Context *context,
                                         size_t attribIndex,
                                         gl::Buffer *boundBuffer,
                                         GLint size,
                                         GLenum type,
                                         bool normalized,
                                         bool pureInteger,
                                         GLsizei stride,
                                         const void *pointer)
{
    ASSERT(attribIndex < getMaxAttribs());

    GLintptr offset = boundBuffer ? reinterpret_cast<GLintptr>(pointer) : 0;

    setVertexAttribFormatImpl(attribIndex, size, type, normalized, pureInteger, 0);
    setVertexAttribBinding(context, attribIndex, static_cast<GLuint>(attribIndex));

    VertexAttribute &attrib = mState.mVertexAttributes[attribIndex];

    GLsizei effectiveStride =
        stride != 0 ? stride : static_cast<GLsizei>(ComputeVertexAttributeTypeSize(attrib));
    attrib.pointer                 = pointer;
    attrib.vertexAttribArrayStride = stride;

    bindVertexBufferImpl(context, attribIndex, boundBuffer, offset, effectiveStride);

    setDirtyAttribBit(attribIndex, DIRTY_ATTRIB_POINTER);

    mState.mNullPointerClientMemoryAttribsMask.set(attribIndex,
                                                   boundBuffer == nullptr && pointer == nullptr);
}

void VertexArray::setElementArrayBuffer(const Context *context, Buffer *buffer)
{
    bool isBound = context->isCurrentVertexArray(this);
    if (isBound && mState.mElementArrayBuffer.get())
        mState.mElementArrayBuffer->onBindingChanged(context, false, BufferBinding::ElementArray,
                                                     false);
    mState.mElementArrayBuffer.set(context, buffer);
    if (isBound && mState.mElementArrayBuffer.get())
        mState.mElementArrayBuffer->onBindingChanged(context, true, BufferBinding::ElementArray,
                                                     false);
    mElementArrayBufferObserverBinding.bind(buffer ? buffer->getImplementation() : nullptr);
    mDirtyBits.set(DIRTY_BIT_ELEMENT_ARRAY_BUFFER);
}

gl::Error VertexArray::syncState(const Context *context)
{
    if (mDirtyBits.any())
    {
        mDirtyBitsGuard = mDirtyBits;
        ANGLE_TRY(
            mVertexArray->syncState(context, mDirtyBits, mDirtyAttribBits, mDirtyBindingBits));
        mDirtyBits.reset();
        mDirtyBitsGuard.reset();

        // This is a bit of an implementation hack - but since we know the implementation
        // details of the dirty bit class it should always have the same effect as iterating
        // individual attribs. We could also look into schemes where iterating the dirty
        // bit set also resets it as you pass through it.
        memset(&mDirtyAttribBits, 0, sizeof(mDirtyAttribBits));
        memset(&mDirtyBindingBits, 0, sizeof(mDirtyBindingBits));
    }
    return gl::NoError();
}

void VertexArray::onBindingChanged(const Context *context, bool bound)
{
    if (mState.mElementArrayBuffer.get())
        mState.mElementArrayBuffer->onBindingChanged(context, bound, BufferBinding::ElementArray,
                                                     false);
    for (auto &binding : mState.mVertexBindings)
    {
        binding.onContainerBindingChanged(context, bound);
    }
}

VertexArray::DirtyBitType VertexArray::getDirtyBitFromIndex(bool contentsChanged,
                                                            angle::SubjectIndex index) const
{
    if (index == mArrayBufferObserverBindings.size())
    {
        return contentsChanged ? DIRTY_BIT_ELEMENT_ARRAY_BUFFER_DATA
                               : DIRTY_BIT_ELEMENT_ARRAY_BUFFER;
    }
    else
    {
        // Note: this currently just gets the top-level dirty bit.
        ASSERT(index < mArrayBufferObserverBindings.size());
        return static_cast<DirtyBitType>(
            (contentsChanged ? DIRTY_BIT_BUFFER_DATA_0 : DIRTY_BIT_BINDING_0) + index);
    }
}

void VertexArray::onSubjectStateChange(const gl::Context *context,
                                       angle::SubjectIndex index,
                                       angle::SubjectMessage message)
{
    switch (message)
    {
        case angle::SubjectMessage::CONTENTS_CHANGED:
            setDependentDirtyBit(context, true, index);
            break;

        case angle::SubjectMessage::STORAGE_CHANGED:
            setDependentDirtyBit(context, false, index);
            if (index < mArrayBufferObserverBindings.size())
            {
                updateCachedBufferBindingSize(index);
            }
            break;

        case angle::SubjectMessage::BINDING_CHANGED:
            if (index < mArrayBufferObserverBindings.size())
            {
                const Buffer *buffer = mState.mVertexBindings[index].getBuffer().get();
                updateCachedTransformFeedbackBindingValidation(index, buffer);
            }
            break;

        default:
            UNREACHABLE();
            break;
    }
}

void VertexArray::setDependentDirtyBit(const gl::Context *context,
                                       bool contentsChanged,
                                       angle::SubjectIndex index)
{
    DirtyBitType dirtyBit = getDirtyBitFromIndex(contentsChanged, index);
    ASSERT(!mDirtyBitsGuard.valid() || mDirtyBitsGuard.value().test(dirtyBit));
    mDirtyBits.set(dirtyBit);
    context->getGLState().setVertexArrayDirty(this);
}

void VertexArray::updateObserverBinding(size_t bindingIndex)
{
    Buffer *boundBuffer = mState.mVertexBindings[bindingIndex].getBuffer().get();
    mArrayBufferObserverBindings[bindingIndex].bind(boundBuffer ? boundBuffer->getImplementation()
                                                                : nullptr);
}

void VertexArray::updateCachedVertexAttributeSize(size_t attribIndex)
{
    mState.mVertexAttributes[attribIndex].updateCachedSizePlusRelativeOffset();
}

void VertexArray::updateCachedBufferBindingSize(size_t bindingIndex)
{
    mState.mVertexBindings[bindingIndex].updateCachedBufferSizeMinusOffset();
}

void VertexArray::updateCachedTransformFeedbackBindingValidation(size_t bindingIndex,
                                                                 const Buffer *buffer)
{
    const bool hasConflict = buffer && buffer->isBoundForTransformFeedbackAndOtherUse();
    mCachedTransformFeedbackConflictedBindingsMask.set(bindingIndex, hasConflict);
}

bool VertexArray::hasTransformFeedbackBindingConflict(const gl::Context *context) const
{
    // Fast check first.
    if (!mCachedTransformFeedbackConflictedBindingsMask.any())
    {
        return false;
    }

    const AttributesMask &activeAttribues = context->getStateCache().getActiveBufferedAttribsMask();

    // Slow check. We must ensure that the conflicting attributes are enabled/active.
    for (size_t attribIndex : activeAttribues)
    {
        const VertexAttribute &attrib = mState.mVertexAttributes[attribIndex];
        if (mCachedTransformFeedbackConflictedBindingsMask[attrib.bindingIndex])
        {
            return true;
        }
    }

    return false;
}

}  // namespace gl
