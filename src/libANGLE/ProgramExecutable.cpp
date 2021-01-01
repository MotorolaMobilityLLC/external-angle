//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ProgramExecutable.cpp: Collects the interfaces common to both Programs and
// ProgramPipelines in order to execute/draw with either.

#include "libANGLE/ProgramExecutable.h"

#include "libANGLE/Context.h"
#include "libANGLE/Program.h"
#include "libANGLE/ProgramPipeline.h"
#include "libANGLE/Shader.h"

namespace gl
{

ProgramExecutable::ProgramExecutable()
    : mMaxActiveAttribLocation(0),
      mAttributesTypeMask(0),
      mAttributesMask(0),
      mActiveSamplersMask(0),
      mActiveSamplerRefCounts{},
      mActiveImagesMask(0),
      mCanDrawWith(false),
      mYUVOutput(false),
      mTransformFeedbackBufferMode(GL_INTERLEAVED_ATTRIBS),
      mDefaultUniformRange(0, 0),
      mSamplerUniformRange(0, 0),
      mImageUniformRange(0, 0),
      mPipelineHasGraphicsUniformBuffers(false),
      mPipelineHasComputeUniformBuffers(false),
      mPipelineHasGraphicsStorageBuffers(false),
      mPipelineHasComputeStorageBuffers(false),
      mPipelineHasGraphicsAtomicCounterBuffers(false),
      mPipelineHasComputeAtomicCounterBuffers(false),
      mPipelineHasGraphicsDefaultUniforms(false),
      mPipelineHasComputeDefaultUniforms(false),
      mPipelineHasGraphicsTextures(false),
      mPipelineHasComputeTextures(false),
      mPipelineHasGraphicsImages(false),
      mPipelineHasComputeImages(false),
      mIsCompute(false),
      // [GL_EXT_geometry_shader] Table 20.22
      mGeometryShaderInputPrimitiveType(PrimitiveMode::Triangles),
      mGeometryShaderOutputPrimitiveType(PrimitiveMode::TriangleStrip),
      mGeometryShaderInvocations(1),
      mGeometryShaderMaxVertices(0)
{
    reset();
}

ProgramExecutable::ProgramExecutable(const ProgramExecutable &other)
    : mLinkedGraphicsShaderStages(other.mLinkedGraphicsShaderStages),
      mLinkedComputeShaderStages(other.mLinkedComputeShaderStages),
      mActiveAttribLocationsMask(other.mActiveAttribLocationsMask),
      mMaxActiveAttribLocation(other.mMaxActiveAttribLocation),
      mAttributesTypeMask(other.mAttributesTypeMask),
      mAttributesMask(other.mAttributesMask),
      mActiveSamplersMask(other.mActiveSamplersMask),
      mActiveSamplerRefCounts(other.mActiveSamplerRefCounts),
      mActiveSamplerTypes(other.mActiveSamplerTypes),
      mActiveSamplerYUV(other.mActiveSamplerYUV),
      mActiveSamplerFormats(other.mActiveSamplerFormats),
      mActiveSamplerShaderBits(other.mActiveSamplerShaderBits),
      mActiveImagesMask(other.mActiveImagesMask),
      mActiveImageShaderBits(other.mActiveImageShaderBits),
      mCanDrawWith(other.mCanDrawWith),
      mOutputVariables(other.mOutputVariables),
      mOutputLocations(other.mOutputLocations),
      mYUVOutput(other.mYUVOutput),
      mProgramInputs(other.mProgramInputs),
      mLinkedTransformFeedbackVaryings(other.mLinkedTransformFeedbackVaryings),
      mTransformFeedbackStrides(other.mTransformFeedbackStrides),
      mTransformFeedbackBufferMode(other.mTransformFeedbackBufferMode),
      mUniforms(other.mUniforms),
      mDefaultUniformRange(other.mDefaultUniformRange),
      mSamplerUniformRange(other.mSamplerUniformRange),
      mUniformBlocks(other.mUniformBlocks),
      mAtomicCounterBuffers(other.mAtomicCounterBuffers),
      mImageUniformRange(other.mImageUniformRange),
      mComputeShaderStorageBlocks(other.mComputeShaderStorageBlocks),
      mGraphicsShaderStorageBlocks(other.mGraphicsShaderStorageBlocks),
      mPipelineHasGraphicsUniformBuffers(other.mPipelineHasGraphicsUniformBuffers),
      mPipelineHasComputeUniformBuffers(other.mPipelineHasComputeUniformBuffers),
      mPipelineHasGraphicsStorageBuffers(other.mPipelineHasGraphicsStorageBuffers),
      mPipelineHasComputeStorageBuffers(other.mPipelineHasComputeStorageBuffers),
      mPipelineHasGraphicsAtomicCounterBuffers(other.mPipelineHasGraphicsAtomicCounterBuffers),
      mPipelineHasComputeAtomicCounterBuffers(other.mPipelineHasComputeAtomicCounterBuffers),
      mPipelineHasGraphicsDefaultUniforms(other.mPipelineHasGraphicsDefaultUniforms),
      mPipelineHasComputeDefaultUniforms(other.mPipelineHasComputeDefaultUniforms),
      mPipelineHasGraphicsTextures(other.mPipelineHasGraphicsTextures),
      mPipelineHasComputeTextures(other.mPipelineHasComputeTextures),
      mPipelineHasGraphicsImages(other.mPipelineHasGraphicsImages),
      mPipelineHasComputeImages(other.mPipelineHasComputeImages),
      mIsCompute(other.mIsCompute)
{
    reset();
}

ProgramExecutable::~ProgramExecutable() = default;

void ProgramExecutable::reset()
{
    resetInfoLog();
    mActiveAttribLocationsMask.reset();
    mAttributesTypeMask.reset();
    mAttributesMask.reset();
    mMaxActiveAttribLocation = 0;

    mActiveSamplersMask.reset();
    mActiveSamplerRefCounts = {};
    mActiveSamplerTypes.fill(TextureType::InvalidEnum);
    mActiveSamplerYUV.reset();
    mActiveSamplerFormats.fill(SamplerFormat::InvalidEnum);

    mActiveImagesMask.reset();

    mProgramInputs.clear();
    mLinkedTransformFeedbackVaryings.clear();
    mUniforms.clear();
    mUniformBlocks.clear();
    mComputeShaderStorageBlocks.clear();
    mGraphicsShaderStorageBlocks.clear();
    mAtomicCounterBuffers.clear();
    mOutputVariables.clear();
    mOutputLocations.clear();
    mYUVOutput = false;
    mSamplerBindings.clear();
    mComputeImageBindings.clear();
    mGraphicsImageBindings.clear();

    mPipelineHasGraphicsUniformBuffers       = false;
    mPipelineHasComputeUniformBuffers        = false;
    mPipelineHasGraphicsStorageBuffers       = false;
    mPipelineHasComputeStorageBuffers        = false;
    mPipelineHasGraphicsAtomicCounterBuffers = false;
    mPipelineHasComputeAtomicCounterBuffers  = false;
    mPipelineHasGraphicsDefaultUniforms      = false;
    mPipelineHasComputeDefaultUniforms       = false;
    mPipelineHasGraphicsTextures             = false;
    mPipelineHasComputeTextures              = false;

    mGeometryShaderInputPrimitiveType  = PrimitiveMode::Triangles;
    mGeometryShaderOutputPrimitiveType = PrimitiveMode::TriangleStrip;
    mGeometryShaderInvocations         = 1;
    mGeometryShaderMaxVertices         = 0;
}

void ProgramExecutable::load(gl::BinaryInputStream *stream)
{
    static_assert(MAX_VERTEX_ATTRIBS * 2 <= sizeof(uint32_t) * 8,
                  "Too many vertex attribs for mask: All bits of mAttributesTypeMask types and "
                  "mask fit into 32 bits each");
    mAttributesTypeMask        = gl::ComponentTypeMask(stream->readInt<uint32_t>());
    mAttributesMask            = gl::AttributesMask(stream->readInt<uint32_t>());
    mActiveAttribLocationsMask = gl::AttributesMask(stream->readInt<uint32_t>());
    mMaxActiveAttribLocation   = stream->readInt<unsigned int>();

    mLinkedGraphicsShaderStages = ShaderBitSet(stream->readInt<uint8_t>());
    mLinkedComputeShaderStages  = ShaderBitSet(stream->readInt<uint8_t>());
    mIsCompute                  = stream->readBool();

    mPipelineHasGraphicsUniformBuffers       = stream->readBool();
    mPipelineHasComputeUniformBuffers        = stream->readBool();
    mPipelineHasGraphicsStorageBuffers       = stream->readBool();
    mPipelineHasComputeStorageBuffers        = stream->readBool();
    mPipelineHasGraphicsAtomicCounterBuffers = stream->readBool();
    mPipelineHasComputeAtomicCounterBuffers  = stream->readBool();
    mPipelineHasGraphicsDefaultUniforms      = stream->readBool();
    mPipelineHasComputeDefaultUniforms       = stream->readBool();
    mPipelineHasGraphicsTextures             = stream->readBool();
    mPipelineHasComputeTextures              = stream->readBool();

    mGeometryShaderInputPrimitiveType  = stream->readEnum<PrimitiveMode>();
    mGeometryShaderOutputPrimitiveType = stream->readEnum<PrimitiveMode>();
    mGeometryShaderInvocations         = stream->readInt<int>();
    mGeometryShaderMaxVertices         = stream->readInt<int>();
}

void ProgramExecutable::save(gl::BinaryOutputStream *stream) const
{
    static_assert(MAX_VERTEX_ATTRIBS * 2 <= sizeof(uint32_t) * 8,
                  "All bits of mAttributesTypeMask types and mask fit into 32 bits each");
    stream->writeInt(static_cast<uint32_t>(mAttributesTypeMask.to_ulong()));
    stream->writeInt(static_cast<uint32_t>(mAttributesMask.to_ulong()));
    stream->writeInt(static_cast<uint32_t>(mActiveAttribLocationsMask.to_ulong()));
    stream->writeInt(mMaxActiveAttribLocation);

    stream->writeInt(mLinkedGraphicsShaderStages.bits());
    stream->writeInt(mLinkedComputeShaderStages.bits());
    stream->writeBool(mIsCompute);

    stream->writeBool(mPipelineHasGraphicsUniformBuffers);
    stream->writeBool(mPipelineHasComputeUniformBuffers);
    stream->writeBool(mPipelineHasGraphicsStorageBuffers);
    stream->writeBool(mPipelineHasComputeStorageBuffers);
    stream->writeBool(mPipelineHasGraphicsAtomicCounterBuffers);
    stream->writeBool(mPipelineHasComputeAtomicCounterBuffers);
    stream->writeBool(mPipelineHasGraphicsDefaultUniforms);
    stream->writeBool(mPipelineHasComputeDefaultUniforms);
    stream->writeBool(mPipelineHasGraphicsTextures);
    stream->writeBool(mPipelineHasComputeTextures);

    ASSERT(mGeometryShaderInvocations >= 1 && mGeometryShaderMaxVertices >= 0);
    stream->writeEnum(mGeometryShaderInputPrimitiveType);
    stream->writeEnum(mGeometryShaderOutputPrimitiveType);
    stream->writeInt(mGeometryShaderInvocations);
    stream->writeInt(mGeometryShaderMaxVertices);
}

int ProgramExecutable::getInfoLogLength() const
{
    return static_cast<int>(mInfoLog.getLength());
}

void ProgramExecutable::getInfoLog(GLsizei bufSize, GLsizei *length, char *infoLog) const
{
    return mInfoLog.getLog(bufSize, length, infoLog);
}

std::string ProgramExecutable::getInfoLogString() const
{
    return mInfoLog.str();
}

bool ProgramExecutable::isAttribLocationActive(size_t attribLocation) const
{
    // TODO(timvp): http://anglebug.com/3570: Enable this assert here somehow.
    //    ASSERT(!mLinkingState);
    ASSERT(attribLocation < mActiveAttribLocationsMask.size());
    return mActiveAttribLocationsMask[attribLocation];
}

AttributesMask ProgramExecutable::getAttributesMask() const
{
    // TODO(timvp): http://anglebug.com/3570: Enable this assert here somehow.
    //    ASSERT(!mLinkingState);
    return mAttributesMask;
}

bool ProgramExecutable::hasDefaultUniforms() const
{
    return !getDefaultUniformRange().empty() ||
           (isCompute() ? mPipelineHasComputeDefaultUniforms : mPipelineHasGraphicsDefaultUniforms);
}

bool ProgramExecutable::hasTextures() const
{
    return !getSamplerBindings().empty() ||
           (isCompute() ? mPipelineHasComputeTextures : mPipelineHasGraphicsTextures);
}

// TODO: http://anglebug.com/3570: Remove mHas*UniformBuffers once PPO's have valid data in
// mUniformBlocks
bool ProgramExecutable::hasUniformBuffers() const
{
    return !getUniformBlocks().empty() ||
           (isCompute() ? mPipelineHasComputeUniformBuffers : mPipelineHasGraphicsUniformBuffers);
}

bool ProgramExecutable::hasStorageBuffers() const
{
    return (isCompute() ? hasComputeStorageBuffers() : hasGraphicsStorageBuffers());
}

bool ProgramExecutable::hasGraphicsStorageBuffers() const
{
    return !mGraphicsShaderStorageBlocks.empty() || mPipelineHasGraphicsStorageBuffers;
}

bool ProgramExecutable::hasComputeStorageBuffers() const
{
    return !mComputeShaderStorageBlocks.empty() || mPipelineHasComputeStorageBuffers;
}

bool ProgramExecutable::hasAtomicCounterBuffers() const
{
    return !getAtomicCounterBuffers().empty() ||
           (isCompute() ? mPipelineHasComputeAtomicCounterBuffers
                        : mPipelineHasGraphicsAtomicCounterBuffers);
}

bool ProgramExecutable::hasImages() const
{
    return (isCompute() ? hasComputeImages() : hasGraphicsImages());
}

bool ProgramExecutable::hasGraphicsImages() const
{
    return !mGraphicsImageBindings.empty() || mPipelineHasGraphicsImages;
}

bool ProgramExecutable::hasComputeImages() const
{
    return !mComputeImageBindings.empty() || mPipelineHasComputeImages;
}

GLuint ProgramExecutable::getUniformIndexFromImageIndex(GLuint imageIndex) const
{
    ASSERT(imageIndex < mImageUniformRange.length());
    return imageIndex + mImageUniformRange.low();
}

void ProgramExecutable::updateActiveSamplers(const ProgramState &programState)
{
    const std::vector<SamplerBinding> &samplerBindings = programState.getSamplerBindings();

    for (uint32_t samplerIndex = 0; samplerIndex < samplerBindings.size(); ++samplerIndex)
    {
        const SamplerBinding &samplerBinding = samplerBindings[samplerIndex];
        uint32_t uniformIndex = programState.getUniformIndexFromSamplerIndex(samplerIndex);
        const gl::LinkedUniform &samplerUniform = programState.getUniforms()[uniformIndex];

        for (GLint textureUnit : samplerBinding.boundTextureUnits)
        {
            if (++mActiveSamplerRefCounts[textureUnit] == 1)
            {
                mActiveSamplerTypes[textureUnit]   = samplerBinding.textureType;
                mActiveSamplerYUV[textureUnit]     = IsSamplerYUVType(samplerBinding.samplerType);
                mActiveSamplerFormats[textureUnit] = samplerBinding.format;
                mActiveSamplerShaderBits[textureUnit] = samplerUniform.activeShaders();
            }
            else
            {
                if (mActiveSamplerTypes[textureUnit] != samplerBinding.textureType)
                {
                    mActiveSamplerTypes[textureUnit] = TextureType::InvalidEnum;
                }
                if (mActiveSamplerYUV.test(textureUnit) !=
                    IsSamplerYUVType(samplerBinding.samplerType))
                {
                    mActiveSamplerYUV[textureUnit] = false;
                }
                if (mActiveSamplerFormats[textureUnit] != samplerBinding.format)
                {
                    mActiveSamplerFormats[textureUnit] = SamplerFormat::InvalidEnum;
                }
            }
            mActiveSamplersMask.set(textureUnit);
        }
    }
}

void ProgramExecutable::updateActiveImages(const ProgramExecutable &executable)
{
    const std::vector<ImageBinding> *imageBindings = getImageBindings();
    for (uint32_t imageIndex = 0; imageIndex < imageBindings->size(); ++imageIndex)
    {
        const gl::ImageBinding &imageBinding = imageBindings->at(imageIndex);

        uint32_t uniformIndex = executable.getUniformIndexFromImageIndex(imageIndex);
        const gl::LinkedUniform &imageUniform = executable.getUniforms()[uniformIndex];
        const ShaderBitSet shaderBits         = imageUniform.activeShaders();
        for (GLint imageUnit : imageBinding.boundImageUnits)
        {
            mActiveImagesMask.set(imageUnit);
            if (isCompute())
            {
                mActiveImageShaderBits[imageUnit].set(gl::ShaderType::Compute);
            }
            else
            {
                mActiveImageShaderBits[imageUnit] = shaderBits;
            }
        }
    }
}

void ProgramExecutable::setSamplerUniformTextureTypeAndFormat(
    size_t textureUnitIndex,
    std::vector<SamplerBinding> &samplerBindings)
{
    bool foundBinding         = false;
    TextureType foundType     = TextureType::InvalidEnum;
    bool foundYUV             = false;
    SamplerFormat foundFormat = SamplerFormat::InvalidEnum;

    for (const SamplerBinding &binding : samplerBindings)
    {
        // A conflict exists if samplers of different types are sourced by the same texture unit.
        // We need to check all bound textures to detect this error case.
        for (GLuint textureUnit : binding.boundTextureUnits)
        {
            if (textureUnit == textureUnitIndex)
            {
                if (!foundBinding)
                {
                    foundBinding = true;
                    foundType    = binding.textureType;
                    foundYUV     = IsSamplerYUVType(binding.samplerType);
                    foundFormat  = binding.format;
                }
                else
                {
                    if (foundType != binding.textureType)
                    {
                        foundType = TextureType::InvalidEnum;
                    }
                    if (foundYUV != IsSamplerYUVType(binding.samplerType))
                    {
                        foundYUV = false;
                    }
                    if (foundFormat != binding.format)
                    {
                        foundFormat = SamplerFormat::InvalidEnum;
                    }
                }
            }
        }
    }

    mActiveSamplerTypes[textureUnitIndex]   = foundType;
    mActiveSamplerYUV[textureUnitIndex]     = foundYUV;
    mActiveSamplerFormats[textureUnitIndex] = foundFormat;
}

void ProgramExecutable::updateCanDrawWith()
{
    mCanDrawWith =
        (hasLinkedShaderStage(ShaderType::Vertex) && hasLinkedShaderStage(ShaderType::Fragment));
}

void ProgramExecutable::saveLinkedStateInfo(const ProgramState &state)
{
    for (ShaderType shaderType : getLinkedShaderStages())
    {
        Shader *shader = state.getAttachedShader(shaderType);
        ASSERT(shader);
        mLinkedOutputVaryings[shaderType] = shader->getOutputVaryings();
        mLinkedInputVaryings[shaderType]  = shader->getInputVaryings();
        mLinkedShaderVersions[shaderType] = shader->getShaderVersion();
    }
}

bool ProgramExecutable::isYUVOutput() const
{
    return !isCompute() && mYUVOutput;
}

ShaderType ProgramExecutable::getLinkedTransformFeedbackStage() const
{
    if (mLinkedGraphicsShaderStages[ShaderType::Geometry])
    {
        return ShaderType::Geometry;
    }
    if (mLinkedGraphicsShaderStages[ShaderType::TessEvaluation])
    {
        return ShaderType::TessEvaluation;
    }
    return ShaderType::Vertex;
}
}  // namespace gl
