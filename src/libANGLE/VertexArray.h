//
// Copyright (c) 2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This class contains prototypes for representing GLES 3 Vertex Array Objects:
//
//   The buffer objects that are to be used by the vertex stage of the GL are collected
//   together to form a vertex array object. All state related to the definition of data used
//   by the vertex processor is encapsulated in a vertex array object.
//

#ifndef LIBANGLE_VERTEXARRAY_H_
#define LIBANGLE_VERTEXARRAY_H_

#include "libANGLE/RefCountObject.h"
#include "libANGLE/Constants.h"
#include "libANGLE/VertexAttribute.h"

#include <vector>

namespace rx
{
class ImplFactory;
class VertexArrayImpl;
}

namespace gl
{
class Buffer;

class VertexArray
{
  public:
    VertexArray(rx::ImplFactory *factory, GLuint id, size_t maxAttribs);
    ~VertexArray();

    GLuint id() const;

    const VertexAttribute &getVertexAttribute(size_t attributeIndex) const;

    void detachBuffer(GLuint bufferName);
    void setVertexAttribDivisor(size_t index, GLuint divisor);
    void enableAttribute(size_t attributeIndex, bool enabledState);
    void setAttributeState(size_t attributeIndex, gl::Buffer *boundBuffer, GLint size, GLenum type,
                           bool normalized, bool pureInteger, GLsizei stride, const void *pointer);

    void setElementArrayBuffer(Buffer *buffer);

    const BindingPointer<Buffer> &getElementArrayBuffer() const { return mData.getElementArrayBuffer(); }
    size_t getMaxAttribs() const { return mData.getVertexAttributes().size(); }
    const std::vector<VertexAttribute> &getVertexAttributes() const { return mData.getVertexAttributes(); }

    rx::VertexArrayImpl *getImplementation() { return mVertexArray; }
    const rx::VertexArrayImpl *getImplementation() const { return mVertexArray; }

    size_t getMaxEnabledAttribute() const { return mData.getMaxEnabledAttribute(); }

    class Data final : public angle::NonCopyable
    {
      public:
        explicit Data(size_t maxAttribs);
        ~Data();

        const BindingPointer<Buffer> &getElementArrayBuffer() const { return mElementArrayBuffer; }
        size_t getMaxAttribs() const { return mVertexAttributes.size(); }
        size_t getMaxEnabledAttribute() const { return mMaxEnabledAttribute; }
        const std::vector<VertexAttribute> &getVertexAttributes() const { return mVertexAttributes; }

      private:
        friend class VertexArray;
        std::vector<VertexAttribute> mVertexAttributes;
        BindingPointer<Buffer> mElementArrayBuffer;
        size_t mMaxEnabledAttribute;
    };

  private:
    GLuint mId;

    rx::VertexArrayImpl *mVertexArray;

    Data mData;
};

}

#endif // LIBANGLE_VERTEXARRAY_H_
