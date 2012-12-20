//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Buffer.cpp: Implements the gl::Buffer class, representing storage of vertex and/or
// index data. Implements GL buffer objects and related functionality.
// [OpenGL ES 2.0.24] section 2.9 page 21.

#include "libGLESv2/Buffer.h"

#include "libGLESv2/main.h"

namespace gl
{

Buffer::Buffer(rx::Renderer *renderer, GLuint id) : RefCountObject(id)
{
    ASSERT(dynamic_cast<rx::Renderer9*>(renderer) != NULL); // D3D9_REPLACE
    mRenderer = static_cast<rx::Renderer9*>(renderer);
    mContents = NULL;
    mSize = 0;
    mUsage = GL_DYNAMIC_DRAW;

    mStaticVertexBuffer = NULL;
    mStaticIndexBuffer = NULL;
    mUnmodifiedDataUse = 0;
}

Buffer::~Buffer()
{
    delete[] mContents;
    delete mStaticVertexBuffer;
    delete mStaticIndexBuffer;
}

void Buffer::bufferData(const void *data, GLsizeiptr size, GLenum usage)
{
    if (size == 0)
    {
        delete[] mContents;
        mContents = NULL;
    }
    else if (size != mSize)
    {
        delete[] mContents;
        mContents = new GLubyte[size];
        memset(mContents, 0, size);
    }

    if (data != NULL && size > 0)
    {
        memcpy(mContents, data, size);
    }

    mSize = size;
    mUsage = usage;

    invalidateStaticData();

    if (usage == GL_STATIC_DRAW)
    {
        mStaticVertexBuffer = new rx::StaticVertexBufferInterface(mRenderer);
        mStaticIndexBuffer = new rx::StaticIndexBufferInterface(mRenderer);
    }
}

void Buffer::bufferSubData(const void *data, GLsizeiptr size, GLintptr offset)
{
    memcpy(mContents + offset, data, size);
    
    if ((mStaticVertexBuffer && mStaticVertexBuffer->getBufferSize() != 0) || (mStaticIndexBuffer && mStaticIndexBuffer->size() != 0))
    {
        invalidateStaticData();
    }

    mUnmodifiedDataUse = 0;
}

rx::StaticVertexBufferInterface *Buffer::getStaticVertexBuffer()
{
    return mStaticVertexBuffer;
}

rx::StaticIndexBufferInterface *Buffer::getStaticIndexBuffer()
{
    return mStaticIndexBuffer;
}

void Buffer::invalidateStaticData()
{
    delete mStaticVertexBuffer;
    mStaticVertexBuffer = NULL;

    delete mStaticIndexBuffer;
    mStaticIndexBuffer = NULL;

    mUnmodifiedDataUse = 0;
}

// Creates static buffers if sufficient used data has been left unmodified
void Buffer::promoteStaticUsage(int dataSize)
{
    if (!mStaticVertexBuffer && !mStaticIndexBuffer)
    {
        mUnmodifiedDataUse += dataSize;

        if (mUnmodifiedDataUse > 3 * mSize)
        {
            mStaticVertexBuffer = new rx::StaticVertexBufferInterface(mRenderer);
            mStaticIndexBuffer = new rx::StaticIndexBufferInterface(mRenderer);
        }
    }
}

}
