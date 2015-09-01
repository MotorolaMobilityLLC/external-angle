//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// ProgramGL.cpp: Implements the class methods for ProgramGL.

#include "libANGLE/renderer/gl/ProgramGL.h"

#include "common/debug.h"
#include "common/utilities.h"
#include "libANGLE/renderer/gl/FunctionsGL.h"
#include "libANGLE/renderer/gl/ShaderGL.h"
#include "libANGLE/renderer/gl/StateManagerGL.h"

namespace rx
{

ProgramGL::ProgramGL(const gl::Program::Data &data,
                     const FunctionsGL *functions,
                     StateManagerGL *stateManager)
    : ProgramImpl(data), mFunctions(functions), mStateManager(stateManager), mProgramID(0)
{
    ASSERT(mFunctions);
    ASSERT(mStateManager);

    mProgramID = mFunctions->createProgram();
}

ProgramGL::~ProgramGL()
{
    mFunctions->deleteProgram(mProgramID);
    mProgramID = 0;
}

int ProgramGL::getShaderVersion() const
{
    UNIMPLEMENTED();
    return int();
}

GLenum ProgramGL::getBinaryFormat()
{
    UNIMPLEMENTED();
    return GLenum();
}

LinkResult ProgramGL::load(gl::InfoLog &infoLog, gl::BinaryInputStream *stream)
{
    UNIMPLEMENTED();
    return LinkResult(false, gl::Error(GL_INVALID_OPERATION));
}

gl::Error ProgramGL::save(gl::BinaryOutputStream *stream)
{
    UNIMPLEMENTED();
    return gl::Error(GL_INVALID_OPERATION);
}

LinkResult ProgramGL::link(const gl::Data &data,
                           gl::InfoLog &infoLog,
                           gl::Shader *fragmentShader,
                           gl::Shader *vertexShader)
{
    // Reset the program state, delete the current program if one exists
    reset();

    const ShaderGL *vertexShaderGL   = GetImplAs<ShaderGL>(vertexShader);
    const ShaderGL *fragmentShaderGL = GetImplAs<ShaderGL>(fragmentShader);

    // Attach the shaders
    mFunctions->attachShader(mProgramID, vertexShaderGL->getShaderID());
    mFunctions->attachShader(mProgramID, fragmentShaderGL->getShaderID());

    // Bind attribute locations to match the GL layer.
    for (const sh::Attribute &attribute : mData.getAttributes())
    {
        if (!attribute.staticUse)
        {
            continue;
        }

        mFunctions->bindAttribLocation(mProgramID, attribute.location, attribute.name.c_str());
    }

    // Link and verify
    mFunctions->linkProgram(mProgramID);

    // Detach the shaders
    mFunctions->detachShader(mProgramID, vertexShaderGL->getShaderID());
    mFunctions->detachShader(mProgramID, fragmentShaderGL->getShaderID());

    // Verify the link
    GLint linkStatus = GL_FALSE;
    mFunctions->getProgramiv(mProgramID, GL_LINK_STATUS, &linkStatus);
    ASSERT(linkStatus == GL_TRUE);
    if (linkStatus == GL_FALSE)
    {
        // Linking failed, put the error into the info log
        GLint infoLogLength = 0;
        mFunctions->getProgramiv(mProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> buf(infoLogLength);
        mFunctions->getProgramInfoLog(mProgramID, infoLogLength, nullptr, &buf[0]);

        mFunctions->deleteProgram(mProgramID);
        mProgramID = 0;

        infoLog << &buf[0];
        TRACE("\n%s", &buf[0]);

        // TODO, return GL_OUT_OF_MEMORY or just fail the link? This is an unexpected case
        return LinkResult(false, gl::Error(GL_NO_ERROR));
    }

    // Query the uniform information
    // TODO: A lot of this logic should be done at the gl::Program level
    GLint activeUniformMaxLength = 0;
    mFunctions->getProgramiv(mProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &activeUniformMaxLength);

    std::vector<GLchar> uniformNameBuffer(activeUniformMaxLength);

    GLint uniformCount = 0;
    mFunctions->getProgramiv(mProgramID, GL_ACTIVE_UNIFORMS, &uniformCount);
    for (GLint i = 0; i < uniformCount; i++)
    {
        GLsizei uniformNameLength = 0;
        GLint uniformSize = 0;
        GLenum uniformType = GL_NONE;
        mFunctions->getActiveUniform(mProgramID, i, static_cast<GLsizei>(uniformNameBuffer.size()),
                                     &uniformNameLength, &uniformSize, &uniformType,
                                     &uniformNameBuffer[0]);

        size_t subscript = 0;
        std::string uniformName = gl::ParseUniformName(std::string(&uniformNameBuffer[0], uniformNameLength), &subscript);

        bool isArray = uniformSize > 1 || subscript != GL_INVALID_INDEX;

        for (size_t arrayIndex = 0; arrayIndex < static_cast<size_t>(uniformSize); arrayIndex++)
        {
            std::string locationName = uniformName;
            if (isArray)
            {
                locationName += "[" + Str(static_cast<int>(arrayIndex)) + "]";
            }

            GLint location = mFunctions->getUniformLocation(mProgramID, locationName.c_str());
            if (location >= 0)
            {
                mUniformIndex[location] =
                    gl::VariableLocation(uniformName, static_cast<unsigned int>(arrayIndex),
                                         static_cast<unsigned int>(mUniforms.size()));

                // If the uniform is a sampler, track it in the sampler bindings array
                if (gl::IsSamplerType(uniformType))
                {
                    SamplerLocation samplerLoc;
                    samplerLoc.samplerIndex = mSamplerBindings.size();
                    samplerLoc.arrayIndex = arrayIndex;
                    mSamplerUniformMap[location] = samplerLoc;
                }
            }
        }

        // ANGLE uses 0 to identify an non-array uniform.
        unsigned int arraySize = isArray ? static_cast<unsigned int>(uniformSize) : 0;

        // TODO: determine uniform precision
        mUniforms.push_back(new gl::LinkedUniform(uniformType, GL_NONE, uniformName, arraySize, -1, sh::BlockMemberInfo::getDefaultBlockInfo()));

        // If uniform is a sampler type, insert it into the mSamplerBindings array
        if (gl::IsSamplerType(uniformType))
        {
            SamplerBindingGL samplerBinding;
            samplerBinding.textureType = gl::SamplerTypeToTextureType(uniformType);
            samplerBinding.boundTextureUnits.resize(uniformSize, 0);
            mSamplerBindings.push_back(samplerBinding);
        }
    }

    return LinkResult(true, gl::Error(GL_NO_ERROR));
}

GLboolean ProgramGL::validate(const gl::Caps & /*caps*/, gl::InfoLog * /*infoLog*/)
{
    // TODO(jmadill): implement validate
    return true;
}

void ProgramGL::setUniform1fv(GLint location, GLsizei count, const GLfloat *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform1fv(location, count, v);
}

void ProgramGL::setUniform2fv(GLint location, GLsizei count, const GLfloat *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform2fv(location, count, v);
}

void ProgramGL::setUniform3fv(GLint location, GLsizei count, const GLfloat *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform3fv(location, count, v);
}

void ProgramGL::setUniform4fv(GLint location, GLsizei count, const GLfloat *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform4fv(location, count, v);
}

void ProgramGL::setUniform1iv(GLint location, GLsizei count, const GLint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform1iv(location, count, v);

    auto iter = mSamplerUniformMap.find(location);
    if (iter != mSamplerUniformMap.end())
    {
        const SamplerLocation &samplerLoc = iter->second;
        std::vector<GLuint> &boundTextureUnits = mSamplerBindings[samplerLoc.samplerIndex].boundTextureUnits;

        size_t copyCount = std::max<size_t>(count, boundTextureUnits.size() - samplerLoc.arrayIndex);
        std::copy(v, v + copyCount, boundTextureUnits.begin() + samplerLoc.arrayIndex);
    }
}

void ProgramGL::setUniform2iv(GLint location, GLsizei count, const GLint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform2iv(location, count, v);
}

void ProgramGL::setUniform3iv(GLint location, GLsizei count, const GLint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform3iv(location, count, v);
}

void ProgramGL::setUniform4iv(GLint location, GLsizei count, const GLint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform4iv(location, count, v);
}

void ProgramGL::setUniform1uiv(GLint location, GLsizei count, const GLuint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform1uiv(location, count, v);
}

void ProgramGL::setUniform2uiv(GLint location, GLsizei count, const GLuint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform2uiv(location, count, v);
}

void ProgramGL::setUniform3uiv(GLint location, GLsizei count, const GLuint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform3uiv(location, count, v);
}

void ProgramGL::setUniform4uiv(GLint location, GLsizei count, const GLuint *v)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniform4uiv(location, count, v);
}

void ProgramGL::setUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix2fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix3fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix4fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix2x3fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix3x2fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix2x4fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix4x2fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix3x4fv(location, count, transpose, value);
}

void ProgramGL::setUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    mStateManager->useProgram(mProgramID);
    mFunctions->uniformMatrix4x3fv(location, count, transpose, value);
}

void ProgramGL::getUniformfv(GLint location, GLfloat *params)
{
    mFunctions->getUniformfv(mProgramID, location, params);
}

void ProgramGL::getUniformiv(GLint location, GLint *params)
{
    mFunctions->getUniformiv(mProgramID, location, params);
}

void ProgramGL::getUniformuiv(GLint location, GLuint *params)
{
    mFunctions->getUniformuiv(mProgramID, location, params);
}

bool ProgramGL::validateSamplers(gl::InfoLog *infoLog, const gl::Caps &caps)
{
    //UNIMPLEMENTED();
    return true;
}

void ProgramGL::reset()
{
    ProgramImpl::reset();

    mSamplerUniformMap.clear();
    mSamplerBindings.clear();
}

GLuint ProgramGL::getProgramID() const
{
    return mProgramID;
}

const std::vector<SamplerBindingGL> &ProgramGL::getAppliedSamplerUniforms() const
{
    return mSamplerBindings;
}

}
