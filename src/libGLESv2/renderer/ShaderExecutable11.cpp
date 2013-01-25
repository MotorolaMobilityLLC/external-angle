//
// Copyright (c) 2012-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// ShaderExecutable11.cpp: Implements a D3D11-specific class to contain shader
// executable implementation details.

#include "libGLESv2/renderer/ShaderExecutable11.h"

#include "common/debug.h"

namespace rx
{

ShaderExecutable11::ShaderExecutable11(const void *function, size_t length, ID3D11PixelShader *executable)
    : ShaderExecutable(function, length)
{
    mPixelExecutable = executable;
    mVertexExecutable = NULL;

    mConstantBuffer = NULL;
}

ShaderExecutable11::ShaderExecutable11(const void *function, size_t length, ID3D11VertexShader *executable)
    : ShaderExecutable(function, length)
{
    mVertexExecutable = executable;
    mPixelExecutable = NULL;

    mConstantBuffer = NULL;
}

ShaderExecutable11::~ShaderExecutable11()
{
    if (mVertexExecutable)
    {
        mVertexExecutable->Release();
    }
    if (mPixelExecutable)
    {
        mPixelExecutable->Release();
    }
    
    if (mConstantBuffer)
    {
        mConstantBuffer->Release();
    }
}

ShaderExecutable11 *ShaderExecutable11::makeShaderExecutable11(ShaderExecutable *executable)
{
    ASSERT(dynamic_cast<ShaderExecutable11*>(executable) != NULL);
    return static_cast<ShaderExecutable11*>(executable);
}

ID3D11VertexShader *ShaderExecutable11::getVertexShader() const
{
    return mVertexExecutable;
}

ID3D11PixelShader *ShaderExecutable11::getPixelShader() const
{
    return mPixelExecutable;
}

ID3D11Buffer *ShaderExecutable11::getConstantBuffer()
{
    return mConstantBuffer;
}

}