#include "precompiled.h"
//
// Copyright (c) 2002-2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Shader.cpp: Implements the gl::Shader class and its  derived classes
// VertexShader and FragmentShader. Implements GL shader objects and related
// functionality. [OpenGL ES 2.0.24] section 2.10 page 24 and section 3.8 page 84.

#include "libGLESv2/Shader.h"

#include "GLSLANG/ShaderLang.h"
#include "common/utilities.h"
#include "libGLESv2/renderer/Renderer.h"
#include "libGLESv2/renderer/ShaderImpl.h"
#include "libGLESv2/Constants.h"
#include "libGLESv2/ResourceManager.h"

namespace gl
{

Shader::Shader(ResourceManager *manager, rx::ShaderImpl *impl, GLenum type, GLuint handle)
    : mShader(impl),
      mType(type),
      mHandle(handle),
      mResourceManager(manager),
      mRefCount(0),
      mDeleteStatus(false),
      mCompiled(false)
{
}

Shader::~Shader()
{
}

GLuint Shader::getHandle() const
{
    return mHandle;
}

void Shader::setSource(GLsizei count, const char *const *string, const GLint *length)
{
    std::ostringstream stream;

    for (int i = 0; i < count; i++)
    {
        stream << string[i];
    }

    mSource = stream.str();
}

int Shader::getInfoLogLength() const
{
    return  mShader->getInfoLog().empty() ? 0 : (mShader->getInfoLog().length() + 1);
}

void Shader::getInfoLog(GLsizei bufSize, GLsizei *length, char *infoLog) const
{
    int index = 0;

    if (bufSize > 0)
    {
        index = std::min(bufSize - 1, static_cast<GLsizei>(mShader->getInfoLog().length()));
        memcpy(infoLog, mShader->getInfoLog().c_str(), index);

        infoLog[index] = '\0';
    }

    if (length)
    {
        *length = index;
    }
}

int Shader::getSourceLength() const
{
    return mSource.empty() ? 0 : (mSource.length() + 1);
}

int Shader::getTranslatedSourceLength() const
{
    return mShader->getTranslatedSource().empty() ? 0 : (mShader->getTranslatedSource().length() + 1);
}

void Shader::getSourceImpl(const std::string &source, GLsizei bufSize, GLsizei *length, char *buffer)
{
    int index = 0;

    if (bufSize > 0)
    {
        index = std::min(bufSize - 1, static_cast<GLsizei>(source.length()));
        memcpy(buffer, source.c_str(), index);

        buffer[index] = '\0';
    }

    if (length)
    {
        *length = index;
    }
}

void Shader::getSource(GLsizei bufSize, GLsizei *length, char *buffer) const
{
    getSourceImpl(mSource, bufSize, length, buffer);
}

void Shader::getTranslatedSource(GLsizei bufSize, GLsizei *length, char *buffer) const
{
    getSourceImpl(mShader->getTranslatedSource(), bufSize, length, buffer);
}

void Shader::compile()
{
    mCompiled = mShader->compile(mSource);
}

void Shader::addRef()
{
    mRefCount++;
}

void Shader::release()
{
    mRefCount--;

    if (mRefCount == 0 && mDeleteStatus)
    {
        mResourceManager->deleteShader(mHandle);
    }
}

unsigned int Shader::getRefCount() const
{
    return mRefCount;
}

bool Shader::isFlaggedForDeletion() const
{
    return mDeleteStatus;
}

void Shader::flagForDeletion()
{
    mDeleteStatus = true;
}

VertexShader::VertexShader(ResourceManager *manager, rx::ShaderImpl *impl, GLuint handle)
    : Shader(manager, impl, GL_VERTEX_SHADER, handle)
{
}

VertexShader::~VertexShader()
{
}

FragmentShader::FragmentShader(ResourceManager *manager, rx::ShaderImpl *impl, GLuint handle)
    : Shader(manager, impl, GL_FRAGMENT_SHADER, handle)
{
}

FragmentShader::~FragmentShader()
{
}

}
