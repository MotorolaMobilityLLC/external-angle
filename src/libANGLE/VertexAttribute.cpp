//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Implementation of the state classes for mananging GLES 3.1 Vertex Array Objects.
//

#include "libANGLE/VertexAttribute.h"

namespace gl
{

// [OpenGL ES 3.1] (November 3, 2016) Section 20 Page 361
// Table 20.2: Vertex Array Object State
VertexBinding::VertexBinding() : VertexBinding(0) {}

VertexBinding::VertexBinding(GLuint boundAttribute) : mStride(16u), mDivisor(0), mOffset(0)
{
    mBoundAttributesMask.set(boundAttribute);
}

VertexBinding::VertexBinding(VertexBinding &&binding)
{
    *this = std::move(binding);
}

VertexBinding::~VertexBinding() {}

VertexBinding &VertexBinding::operator=(VertexBinding &&binding)
{
    if (this != &binding)
    {
        mStride              = binding.mStride;
        mDivisor             = binding.mDivisor;
        mOffset              = binding.mOffset;
        mBoundAttributesMask = binding.mBoundAttributesMask;
        std::swap(binding.mBuffer, mBuffer);
    }
    return *this;
}

void VertexBinding::onContainerBindingChanged(const Context *context, int incr) const
{
    if (mBuffer.get())
        mBuffer->onNonTFBindingChanged(incr);
}

VertexAttribute::VertexAttribute(GLuint bindingIndex)
    : enabled(false),
      type(VertexAttribType::Float),
      size(4u),
      normalized(false),
      pureInteger(false),
      pointer(nullptr),
      relativeOffset(0),
      vertexAttribArrayStride(0),
      bindingIndex(bindingIndex),
      mCachedElementLimit(0)
{}

VertexAttribute::VertexAttribute(VertexAttribute &&attrib)
    : enabled(attrib.enabled),
      type(attrib.type),
      size(attrib.size),
      normalized(attrib.normalized),
      pureInteger(attrib.pureInteger),
      pointer(attrib.pointer),
      relativeOffset(attrib.relativeOffset),
      vertexAttribArrayStride(attrib.vertexAttribArrayStride),
      bindingIndex(attrib.bindingIndex),
      mCachedElementLimit(attrib.mCachedElementLimit)
{}

VertexAttribute &VertexAttribute::operator=(VertexAttribute &&attrib)
{
    if (this != &attrib)
    {
        enabled                 = attrib.enabled;
        type                    = attrib.type;
        size                    = attrib.size;
        normalized              = attrib.normalized;
        pureInteger             = attrib.pureInteger;
        pointer                 = attrib.pointer;
        relativeOffset          = attrib.relativeOffset;
        vertexAttribArrayStride = attrib.vertexAttribArrayStride;
        bindingIndex            = attrib.bindingIndex;
        mCachedElementLimit     = attrib.mCachedElementLimit;
    }
    return *this;
}

void VertexAttribute::updateCachedElementLimit(const VertexBinding &binding)
{
    Buffer *buffer = binding.getBuffer().get();
    if (!buffer)
    {
        mCachedElementLimit = 0;
        return;
    }

    angle::CheckedNumeric<GLint64> bufferSize(buffer->getSize());
    angle::CheckedNumeric<GLint64> bufferOffset(binding.getOffset());
    angle::CheckedNumeric<GLint64> attribOffset(relativeOffset);
    angle::CheckedNumeric<GLint64> attribSize(ComputeVertexAttributeTypeSize(*this));

    // (buffer.size - buffer.offset - attrib.relativeOffset - attrib.size) / binding.stride
    angle::CheckedNumeric<GLint64> elementLimit =
        (bufferSize - bufferOffset - attribOffset - attribSize);

    // Use the special integer overflow value if there was a math error.
    if (!elementLimit.IsValid())
    {
        static_assert(kIntegerOverflow < 0, "Unexpected value");
        mCachedElementLimit = kIntegerOverflow;
        return;
    }

    mCachedElementLimit = elementLimit.ValueOrDie();
    if (mCachedElementLimit < 0)
    {
        return;
    }

    if (binding.getStride() == 0)
    {
        // Special case for a zero stride. If we can fit one vertex we can fit infinite vertices.
        mCachedElementLimit = std::numeric_limits<GLint64>::max();
        return;
    }

    angle::CheckedNumeric<GLint64> bindingStride(binding.getStride());
    elementLimit /= bindingStride;

    if (binding.getDivisor() > 0)
    {
        // For instanced draws, the element count is floor(instanceCount - 1) / binding.divisor.
        angle::CheckedNumeric<GLint64> bindingDivisor(binding.getDivisor());
        elementLimit *= bindingDivisor;

        // We account for the floor() part rounding by adding a rounding constant.
        elementLimit += bindingDivisor - 1;
    }

    mCachedElementLimit = elementLimit.ValueOrDefault(kIntegerOverflow);
}

size_t ComputeVertexAttributeTypeSize(const VertexAttribute &attrib)
{
    switch (attrib.type)
    {
        case VertexAttribType::Byte:
            return attrib.size * sizeof(GLbyte);
        case VertexAttribType::UnsignedByte:
            return attrib.size * sizeof(GLubyte);
        case VertexAttribType::Short:
            return attrib.size * sizeof(GLshort);
        case VertexAttribType::UnsignedShort:
            return attrib.size * sizeof(GLushort);
        case VertexAttribType::Int:
            return attrib.size * sizeof(GLint);
        case VertexAttribType::UnsignedInt:
            return attrib.size * sizeof(GLuint);
        case VertexAttribType::Float:
            return attrib.size * sizeof(GLfloat);
        case VertexAttribType::HalfFloat:
            return attrib.size * sizeof(GLhalf);
        case VertexAttribType::Fixed:
            return attrib.size * sizeof(GLfixed);
        case VertexAttribType::Int2101010:
            // Packed attribute types don't scale by their component size.
            return 4;
        case VertexAttribType::UnsignedInt2101010:
            // Packed attribute types don't scale by their component size.
            return 4;
        default:
            UNREACHABLE();
            return 0;
    }
}

size_t ComputeVertexAttributeStride(const VertexAttribute &attrib, const VertexBinding &binding)
{
    // In ES 3.1, VertexAttribPointer will store the type size in the binding stride.
    // Hence, rendering always uses the binding's stride.
    return attrib.enabled ? binding.getStride() : 16u;
}

// Warning: you should ensure binding really matches attrib.bindingIndex before using this function.
GLintptr ComputeVertexAttributeOffset(const VertexAttribute &attrib, const VertexBinding &binding)
{
    return attrib.relativeOffset + binding.getOffset();
}

size_t ComputeVertexBindingElementCount(GLuint divisor, size_t drawCount, size_t instanceCount)
{
    // For instanced rendering, we draw "instanceDrawCount" sets of "vertexDrawCount" vertices.
    //
    // A vertex attribute with a positive divisor loads one instanced vertex for every set of
    // non-instanced vertices, and the instanced vertex index advances once every "mDivisor"
    // instances.
    if (instanceCount > 0 && divisor > 0)
    {
        // When instanceDrawCount is not a multiple attrib.divisor, the division must round up.
        // For instance, with 5 non-instanced vertices and a divisor equal to 3, we need 2 instanced
        // vertices.
        return (instanceCount + divisor - 1u) / divisor;
    }

    return drawCount;
}

}  // namespace gl
