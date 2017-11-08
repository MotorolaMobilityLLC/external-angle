//
// Copyright (c) 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// UniformLinker.cpp: implements link-time checks for default block uniforms, and generates uniform
// locations. Populates data structures related to uniforms so that they can be stored in program
// state.

#include "libANGLE/ProgramLinkedResources.h"

#include "common/string_utils.h"
#include "common/utilities.h"
#include "libANGLE/Caps.h"
#include "libANGLE/Context.h"
#include "libANGLE/Shader.h"
#include "libANGLE/features.h"

namespace gl
{

namespace
{

LinkedUniform *FindUniform(std::vector<LinkedUniform> &list, const std::string &name)
{
    for (LinkedUniform &uniform : list)
    {
        if (uniform.name == name)
            return &uniform;
    }

    return nullptr;
}

int GetUniformLocationBinding(const Program::Bindings &uniformLocationBindings,
                              const sh::Uniform &uniform)
{
    int binding = uniformLocationBindings.getBinding(uniform.name);
    if (uniform.isArray() && binding == -1)
    {
        // Bindings for array uniforms can be set either with or without [0] in the end.
        ASSERT(angle::EndsWith(uniform.name, "[0]"));
        std::string nameWithoutIndex = uniform.name.substr(0u, uniform.name.length() - 3u);
        return uniformLocationBindings.getBinding(nameWithoutIndex);
    }
    return binding;
}

}  // anonymous namespace

UniformLinker::UniformLinker(const ProgramState &state) : mState(state)
{
}

void UniformLinker::getResults(std::vector<LinkedUniform> *uniforms,
                               std::vector<VariableLocation> *uniformLocations)
{
    uniforms->swap(mUniforms);
    uniformLocations->swap(mUniformLocations);
}

bool UniformLinker::link(const Context *context,
                         InfoLog &infoLog,
                         const Program::Bindings &uniformLocationBindings)
{
    if (mState.getAttachedVertexShader() && mState.getAttachedFragmentShader())
    {
        ASSERT(mState.getAttachedComputeShader() == nullptr);
        if (!validateVertexAndFragmentUniforms(context, infoLog))
        {
            return false;
        }
    }

    // Flatten the uniforms list (nested fields) into a simple list (no nesting).
    // Also check the maximum uniform vector and sampler counts.
    if (!flattenUniformsAndCheckCaps(context, infoLog))
    {
        return false;
    }

    if (!checkMaxCombinedAtomicCounters(context->getCaps(), infoLog))
    {
        return false;
    }

    if (!indexUniforms(infoLog, uniformLocationBindings))
    {
        return false;
    }

    return true;
}

bool UniformLinker::validateVertexAndFragmentUniforms(const Context *context,
                                                      InfoLog &infoLog) const
{
    // Check that uniforms defined in the vertex and fragment shaders are identical
    std::map<std::string, LinkedUniform> linkedUniforms;
    const std::vector<sh::Uniform> &vertexUniforms =
        mState.getAttachedVertexShader()->getUniforms(context);
    const std::vector<sh::Uniform> &fragmentUniforms =
        mState.getAttachedFragmentShader()->getUniforms(context);

    for (const sh::Uniform &vertexUniform : vertexUniforms)
    {
        linkedUniforms[vertexUniform.name] = LinkedUniform(vertexUniform);
    }

    for (const sh::Uniform &fragmentUniform : fragmentUniforms)
    {
        auto entry = linkedUniforms.find(fragmentUniform.name);
        if (entry != linkedUniforms.end())
        {
            LinkedUniform *linkedUniform   = &entry->second;
            const std::string &uniformName = "uniform '" + linkedUniform->name + "'";
            if (!linkValidateUniforms(infoLog, uniformName, *linkedUniform, fragmentUniform))
            {
                return false;
            }
        }
    }
    return true;
}

// GLSL ES Spec 3.00.3, section 4.3.5.
bool UniformLinker::linkValidateUniforms(InfoLog &infoLog,
                                         const std::string &uniformName,
                                         const sh::Uniform &vertexUniform,
                                         const sh::Uniform &fragmentUniform)
{
#if ANGLE_PROGRAM_LINK_VALIDATE_UNIFORM_PRECISION == ANGLE_ENABLED
    const bool validatePrecision = true;
#else
    const bool validatePrecision = false;
#endif

    if (!Program::linkValidateVariablesBase(infoLog, uniformName, vertexUniform, fragmentUniform,
                                            validatePrecision))
    {
        return false;
    }

    // GLSL ES Spec 3.10.4, section 4.4.5.
    if (vertexUniform.binding != -1 && fragmentUniform.binding != -1 &&
        vertexUniform.binding != fragmentUniform.binding)
    {
        infoLog << "Binding layout qualifiers for " << uniformName
                << " differ between vertex and fragment shaders.";
        return false;
    }

    // GLSL ES Spec 3.10.4, section 9.2.1.
    if (vertexUniform.location != -1 && fragmentUniform.location != -1 &&
        vertexUniform.location != fragmentUniform.location)
    {
        infoLog << "Location layout qualifiers for " << uniformName
                << " differ between vertex and fragment shaders.";
        return false;
    }
    if (vertexUniform.offset != fragmentUniform.offset)
    {
        infoLog << "Offset layout qualifiers for " << uniformName
                << " differ between vertex and fragment shaders.";
        return false;
    }

    return true;
}

bool UniformLinker::indexUniforms(InfoLog &infoLog,
                                  const Program::Bindings &uniformLocationBindings)
{
    // All the locations where another uniform can't be located.
    std::set<GLuint> reservedLocations;
    // Locations which have been allocated for an unused uniform.
    std::set<GLuint> ignoredLocations;

    int maxUniformLocation = -1;

    // Gather uniform locations that have been set either using the bindUniformLocation API or by
    // using a location layout qualifier and check conflicts between them.
    if (!gatherUniformLocationsAndCheckConflicts(infoLog, uniformLocationBindings,
                                                 &reservedLocations, &ignoredLocations,
                                                 &maxUniformLocation))
    {
        return false;
    }

    // Conflicts have been checked, now we can prune non-statically used uniforms. Code further down
    // the line relies on only having statically used uniforms in mUniforms.
    pruneUnusedUniforms();

    // Gather uniforms that have their location pre-set and uniforms that don't yet have a location.
    std::vector<VariableLocation> unlocatedUniforms;
    std::map<GLuint, VariableLocation> preLocatedUniforms;

    for (size_t uniformIndex = 0; uniformIndex < mUniforms.size(); uniformIndex++)
    {
        const LinkedUniform &uniform = mUniforms[uniformIndex];

        if (uniform.isBuiltIn() || IsAtomicCounterType(uniform.type))
        {
            continue;
        }

        int preSetLocation = GetUniformLocationBinding(uniformLocationBindings, uniform);
        int shaderLocation = uniform.location;

        if (shaderLocation != -1)
        {
            preSetLocation = shaderLocation;
        }

        for (unsigned int arrayIndex = 0; arrayIndex < uniform.elementCount(); arrayIndex++)
        {
            VariableLocation location(arrayIndex, static_cast<unsigned int>(uniformIndex));

            if ((arrayIndex == 0 && preSetLocation != -1) || shaderLocation != -1)
            {
                int elementLocation                 = preSetLocation + arrayIndex;
                preLocatedUniforms[elementLocation] = location;
            }
            else
            {
                unlocatedUniforms.push_back(location);
            }
        }
    }

    // Make enough space for all uniforms, with pre-set locations or not.
    mUniformLocations.resize(
        std::max(unlocatedUniforms.size() + preLocatedUniforms.size() + ignoredLocations.size(),
                 static_cast<size_t>(maxUniformLocation + 1)));

    // Assign uniforms with pre-set locations
    for (const auto &uniform : preLocatedUniforms)
    {
        mUniformLocations[uniform.first] = uniform.second;
    }

    // Assign ignored uniforms
    for (const auto &ignoredLocation : ignoredLocations)
    {
        mUniformLocations[ignoredLocation].markIgnored();
    }

    // Automatically assign locations for the rest of the uniforms
    size_t nextUniformLocation = 0;
    for (const auto &unlocatedUniform : unlocatedUniforms)
    {
        while (mUniformLocations[nextUniformLocation].used() ||
               mUniformLocations[nextUniformLocation].ignored)
        {
            nextUniformLocation++;
        }

        ASSERT(nextUniformLocation < mUniformLocations.size());
        mUniformLocations[nextUniformLocation] = unlocatedUniform;
        nextUniformLocation++;
    }

    return true;
}

bool UniformLinker::gatherUniformLocationsAndCheckConflicts(
    InfoLog &infoLog,
    const Program::Bindings &uniformLocationBindings,
    std::set<GLuint> *reservedLocations,
    std::set<GLuint> *ignoredLocations,
    int *maxUniformLocation)
{
    for (const LinkedUniform &uniform : mUniforms)
    {
        if (uniform.isBuiltIn())
        {
            continue;
        }

        int apiBoundLocation = GetUniformLocationBinding(uniformLocationBindings, uniform);
        int shaderLocation   = uniform.location;

        if (shaderLocation != -1)
        {
            for (unsigned int arrayIndex = 0; arrayIndex < uniform.elementCount(); arrayIndex++)
            {
                // GLSL ES 3.10 section 4.4.3
                int elementLocation = shaderLocation + arrayIndex;
                *maxUniformLocation = std::max(*maxUniformLocation, elementLocation);
                if (reservedLocations->find(elementLocation) != reservedLocations->end())
                {
                    infoLog << "Multiple uniforms bound to location " << elementLocation << ".";
                    return false;
                }
                reservedLocations->insert(elementLocation);
                if (!uniform.staticUse)
                {
                    ignoredLocations->insert(elementLocation);
                }
            }
        }
        else if (apiBoundLocation != -1 && uniform.staticUse)
        {
            // Only the first location is reserved even if the uniform is an array.
            *maxUniformLocation = std::max(*maxUniformLocation, apiBoundLocation);
            if (reservedLocations->find(apiBoundLocation) != reservedLocations->end())
            {
                infoLog << "Multiple uniforms bound to location " << apiBoundLocation << ".";
                return false;
            }
            reservedLocations->insert(apiBoundLocation);
        }
    }

    // Record the uniform locations that were bound using the API for uniforms that were not found
    // from the shader. Other uniforms should not be assigned to those locations.
    for (const auto &locationBinding : uniformLocationBindings)
    {
        GLuint location = locationBinding.second;
        if (reservedLocations->find(location) == reservedLocations->end())
        {
            ignoredLocations->insert(location);
            *maxUniformLocation = std::max(*maxUniformLocation, static_cast<int>(location));
        }
    }

    return true;
}

void UniformLinker::pruneUnusedUniforms()
{
    auto uniformIter = mUniforms.begin();
    while (uniformIter != mUniforms.end())
    {
        if (uniformIter->staticUse)
        {
            ++uniformIter;
        }
        else
        {
            uniformIter = mUniforms.erase(uniformIter);
        }
    }
}

bool UniformLinker::flattenUniformsAndCheckCapsForShader(
    const Context *context,
    Shader *shader,
    GLuint maxUniformComponents,
    GLuint maxTextureImageUnits,
    GLuint maxImageUnits,
    GLuint maxAtomicCounters,
    const std::string &componentsErrorMessage,
    const std::string &samplerErrorMessage,
    const std::string &imageErrorMessage,
    const std::string &atomicCounterErrorMessage,
    std::vector<LinkedUniform> &samplerUniforms,
    std::vector<LinkedUniform> &imageUniforms,
    std::vector<LinkedUniform> &atomicCounterUniforms,
    InfoLog &infoLog)
{
    ShaderUniformCount shaderUniformCount;
    for (const sh::Uniform &uniform : shader->getUniforms(context))
    {
        shaderUniformCount += flattenUniform(uniform, &samplerUniforms, &imageUniforms,
                                             &atomicCounterUniforms, shader->getType());
    }

    if (shaderUniformCount.vectorCount > maxUniformComponents)
    {
        infoLog << componentsErrorMessage << maxUniformComponents << ").";
        return false;
    }

    if (shaderUniformCount.samplerCount > maxTextureImageUnits)
    {
        infoLog << samplerErrorMessage << maxTextureImageUnits << ").";
        return false;
    }

    if (shaderUniformCount.imageCount > maxImageUnits)
    {
        infoLog << imageErrorMessage << maxImageUnits << ").";
        return false;
    }

    if (shaderUniformCount.atomicCounterCount > maxAtomicCounters)
    {
        infoLog << atomicCounterErrorMessage << maxAtomicCounters << ").";
        return false;
    }

    return true;
}

bool UniformLinker::flattenUniformsAndCheckCaps(const Context *context, InfoLog &infoLog)
{
    std::vector<LinkedUniform> samplerUniforms;
    std::vector<LinkedUniform> imageUniforms;
    std::vector<LinkedUniform> atomicCounterUniforms;

    const Caps &caps = context->getCaps();

    if (mState.getAttachedComputeShader())
    {
        Shader *computeShader = mState.getAttachedComputeShader();

        // TODO (mradev): check whether we need finer-grained component counting
        if (!flattenUniformsAndCheckCapsForShader(
                context, computeShader, caps.maxComputeUniformComponents / 4,
                caps.maxComputeTextureImageUnits, caps.maxComputeImageUniforms,
                caps.maxComputeAtomicCounters,
                "Compute shader active uniforms exceed MAX_COMPUTE_UNIFORM_COMPONENTS (",
                "Compute shader sampler count exceeds MAX_COMPUTE_TEXTURE_IMAGE_UNITS (",
                "Compute shader image count exceeds MAX_COMPUTE_IMAGE_UNIFORMS (",
                "Compute shader atomic counter count exceeds MAX_COMPUTE_ATOMIC_COUNTERS (",
                samplerUniforms, imageUniforms, atomicCounterUniforms, infoLog))
        {
            return false;
        }
    }
    else
    {
        Shader *vertexShader = mState.getAttachedVertexShader();

        if (!flattenUniformsAndCheckCapsForShader(
                context, vertexShader, caps.maxVertexUniformVectors,
                caps.maxVertexTextureImageUnits, caps.maxVertexImageUniforms,
                caps.maxVertexAtomicCounters,
                "Vertex shader active uniforms exceed MAX_VERTEX_UNIFORM_VECTORS (",
                "Vertex shader sampler count exceeds MAX_VERTEX_TEXTURE_IMAGE_UNITS (",
                "Vertex shader image count exceeds MAX_VERTEX_IMAGE_UNIFORMS (",
                "Vertex shader atomic counter count exceeds MAX_VERTEX_ATOMIC_COUNTERS (",
                samplerUniforms, imageUniforms, atomicCounterUniforms, infoLog))
        {
            return false;
        }

        Shader *fragmentShader = mState.getAttachedFragmentShader();

        if (!flattenUniformsAndCheckCapsForShader(
                context, fragmentShader, caps.maxFragmentUniformVectors, caps.maxTextureImageUnits,
                caps.maxFragmentImageUniforms, caps.maxFragmentAtomicCounters,
                "Fragment shader active uniforms exceed MAX_FRAGMENT_UNIFORM_VECTORS (",
                "Fragment shader sampler count exceeds MAX_TEXTURE_IMAGE_UNITS (",
                "Fragment shader image count exceeds MAX_FRAGMENT_IMAGE_UNIFORMS (",
                "Fragment shader atomic counter count exceeds MAX_FRAGMENT_ATOMIC_COUNTERS (",
                samplerUniforms, imageUniforms, atomicCounterUniforms, infoLog))
        {
            return false;
        }
    }

    mUniforms.insert(mUniforms.end(), samplerUniforms.begin(), samplerUniforms.end());
    mUniforms.insert(mUniforms.end(), imageUniforms.begin(), imageUniforms.end());
    mUniforms.insert(mUniforms.end(), atomicCounterUniforms.begin(), atomicCounterUniforms.end());
    return true;
}

UniformLinker::ShaderUniformCount UniformLinker::flattenUniform(
    const sh::Uniform &uniform,
    std::vector<LinkedUniform> *samplerUniforms,
    std::vector<LinkedUniform> *imageUniforms,
    std::vector<LinkedUniform> *atomicCounterUniforms,
    GLenum shaderType)
{
    int location = uniform.location;
    ShaderUniformCount shaderUniformCount =
        flattenUniformImpl(uniform, uniform.name, uniform.mappedName, samplerUniforms,
                           imageUniforms, atomicCounterUniforms, shaderType, uniform.staticUse,
                           uniform.binding, uniform.offset, &location);
    if (uniform.staticUse)
    {
        return shaderUniformCount;
    }
    return ShaderUniformCount();
}

UniformLinker::ShaderUniformCount UniformLinker::flattenUniformImpl(
    const sh::ShaderVariable &uniform,
    const std::string &fullName,
    const std::string &fullMappedName,
    std::vector<LinkedUniform> *samplerUniforms,
    std::vector<LinkedUniform> *imageUniforms,
    std::vector<LinkedUniform> *atomicCounterUniforms,
    GLenum shaderType,
    bool markStaticUse,
    int binding,
    int offset,
    int *location)
{
    ASSERT(location);
    ShaderUniformCount shaderUniformCount;

    if (uniform.isStruct())
    {
        for (unsigned int elementIndex = 0; elementIndex < uniform.elementCount(); elementIndex++)
        {
            const std::string &elementString = (uniform.isArray() ? ArrayString(elementIndex) : "");

            for (size_t fieldIndex = 0; fieldIndex < uniform.fields.size(); fieldIndex++)
            {
                const sh::ShaderVariable &field  = uniform.fields[fieldIndex];
                const std::string &fieldFullName = (fullName + elementString + "." + field.name);
                const std::string &fieldFullMappedName =
                    (fullMappedName + elementString + "." + field.mappedName);

                shaderUniformCount += flattenUniformImpl(
                    field, fieldFullName, fieldFullMappedName, samplerUniforms, imageUniforms,
                    atomicCounterUniforms, shaderType, markStaticUse, -1, -1, location);
            }
        }

        return shaderUniformCount;
    }

    // Not a struct
    bool isSampler                              = IsSamplerType(uniform.type);
    bool isImage                                = IsImageType(uniform.type);
    bool isAtomicCounter                        = IsAtomicCounterType(uniform.type);
    std::vector<gl::LinkedUniform> *uniformList = &mUniforms;
    if (isSampler)
    {
        uniformList = samplerUniforms;
    }
    else if (isImage)
    {
        uniformList = imageUniforms;
    }
    else if (isAtomicCounter)
    {
        uniformList = atomicCounterUniforms;
    }

    std::string fullNameWithArrayIndex(fullName);
    std::string fullMappedNameWithArrayIndex(fullMappedName);

    if (uniform.isArray())
    {
        // We're following the GLES 3.1 November 2016 spec section 7.3.1.1 Naming Active Resources
        // and including [0] at the end of array variable names.
        fullNameWithArrayIndex += "[0]";
        fullMappedNameWithArrayIndex += "[0]";
    }

    LinkedUniform *existingUniform = FindUniform(*uniformList, fullNameWithArrayIndex);
    if (existingUniform)
    {
        if (binding != -1)
        {
            existingUniform->binding = binding;
        }
        if (offset != -1)
        {
            existingUniform->offset = offset;
        }
        if (*location != -1)
        {
            existingUniform->location = *location;
        }
        if (markStaticUse)
        {
            existingUniform->staticUse = true;
            existingUniform->setStaticUse(shaderType, true);
        }
    }
    else
    {
        LinkedUniform linkedUniform(uniform.type, uniform.precision, fullNameWithArrayIndex,
                                    uniform.arraySize, binding, offset, *location, -1,
                                    sh::BlockMemberInfo::getDefaultBlockInfo());
        linkedUniform.mappedName = fullMappedNameWithArrayIndex;
        linkedUniform.staticUse  = markStaticUse;
        if (markStaticUse)
        {
            linkedUniform.setStaticUse(shaderType, true);
        }

        uniformList->push_back(linkedUniform);
    }

    unsigned int elementCount = uniform.elementCount();

    // Samplers and images aren't "real" uniforms, so they don't count towards register usage.
    // Likewise, don't count "real" uniforms towards opaque count.
    shaderUniformCount.vectorCount =
        (IsOpaqueType(uniform.type) ? 0 : (VariableRegisterCount(uniform.type) * elementCount));
    shaderUniformCount.samplerCount       = (isSampler ? elementCount : 0);
    shaderUniformCount.imageCount         = (isImage ? elementCount : 0);
    shaderUniformCount.atomicCounterCount = (isAtomicCounter ? elementCount : 0);

    if (*location != -1)
    {
        *location += elementCount;
    }

    return shaderUniformCount;
}

bool UniformLinker::checkMaxCombinedAtomicCounters(const Caps &caps, InfoLog &infoLog)
{
    unsigned int atomicCounterCount = 0;
    for (const auto &uniform : mUniforms)
    {
        if (IsAtomicCounterType(uniform.type) && uniform.staticUse)
        {
            atomicCounterCount += uniform.elementCount();
            if (atomicCounterCount > caps.maxCombinedAtomicCounters)
            {
                infoLog << "atomic counter count exceeds MAX_COMBINED_ATOMIC_COUNTERS"
                        << caps.maxCombinedAtomicCounters << ").";
                return false;
            }
        }
    }
    return true;
}

// InterfaceBlockLinker implementation.
InterfaceBlockLinker::InterfaceBlockLinker(std::vector<InterfaceBlock> *blocksOut)
    : mBlocksOut(blocksOut)
{
}

InterfaceBlockLinker::~InterfaceBlockLinker()
{
}

void InterfaceBlockLinker::addShaderBlocks(GLenum shader,
                                           const std::vector<sh::InterfaceBlock> *blocks)
{
    mShaderBlocks.push_back(std::make_pair(shader, blocks));
}

void InterfaceBlockLinker::linkBlocks(const GetBlockSize &getBlockSize,
                                      const GetBlockMemberInfo &getMemberInfo) const
{
    ASSERT(mBlocksOut->empty());

    std::set<std::string> visitedList;

    for (const auto &shaderBlocks : mShaderBlocks)
    {
        const GLenum shaderType = shaderBlocks.first;

        for (const auto &block : *shaderBlocks.second)
        {
            // Only 'packed' blocks are allowed to be considered inactive.
            if (!block.staticUse && block.layout == sh::BLOCKLAYOUT_PACKED)
                continue;

            if (visitedList.count(block.name) > 0)
            {
                if (block.staticUse)
                {
                    for (InterfaceBlock &priorBlock : *mBlocksOut)
                    {
                        if (block.name == priorBlock.name)
                        {
                            priorBlock.setStaticUse(shaderType, true);
                        }
                    }
                }
            }
            else
            {
                defineInterfaceBlock(getBlockSize, getMemberInfo, block, shaderType);
                visitedList.insert(block.name);
            }
        }
    }
}

template <typename VarT>
void InterfaceBlockLinker::defineBlockMembers(const GetBlockMemberInfo &getMemberInfo,
                                              const std::vector<VarT> &fields,
                                              const std::string &prefix,
                                              const std::string &mappedPrefix,
                                              int blockIndex) const
{
    for (const VarT &field : fields)
    {
        std::string fullName = (prefix.empty() ? field.name : prefix + "." + field.name);

        std::string fullMappedName =
            (mappedPrefix.empty() ? field.mappedName : mappedPrefix + "." + field.mappedName);

        if (field.isStruct())
        {
            for (unsigned int arrayElement = 0; arrayElement < field.elementCount(); arrayElement++)
            {
                const std::string elementName =
                    fullName + (field.isArray() ? ArrayString(arrayElement) : "");
                const std::string elementMappedName =
                    fullMappedName + (field.isArray() ? ArrayString(arrayElement) : "");
                defineBlockMembers(getMemberInfo, field.fields, elementName, elementMappedName,
                                   blockIndex);
            }
        }
        else
        {
            // If getBlockMemberInfo returns false, the variable is optimized out.
            sh::BlockMemberInfo memberInfo;
            if (!getMemberInfo(fullName, fullMappedName, &memberInfo))
            {
                continue;
            }

            if (field.isArray())
            {
                fullName += "[0]";
                fullMappedName += "[0]";
            }

            defineBlockMember(field, fullName, fullMappedName, blockIndex, memberInfo);
        }
    }
}

void InterfaceBlockLinker::defineInterfaceBlock(const GetBlockSize &getBlockSize,
                                                const GetBlockMemberInfo &getMemberInfo,
                                                const sh::InterfaceBlock &interfaceBlock,
                                                GLenum shaderType) const
{
    size_t blockSize = 0;
    std::vector<unsigned int> blockIndexes;

    int blockIndex = static_cast<int>(mBlocksOut->size());
    // Track the first and last uniform index to determine the range of active uniforms in the
    // block.
    size_t firstBlockMemberIndex = getCurrentBlockMemberIndex();
    defineBlockMembers(getMemberInfo, interfaceBlock.fields, interfaceBlock.fieldPrefix(),
                       interfaceBlock.fieldMappedPrefix(), blockIndex);
    size_t lastBlockMemberIndex = getCurrentBlockMemberIndex();

    for (size_t blockMemberIndex = firstBlockMemberIndex; blockMemberIndex < lastBlockMemberIndex;
         ++blockMemberIndex)
    {
        blockIndexes.push_back(static_cast<unsigned int>(blockMemberIndex));
    }

    // ESSL 3.10 section 4.4.4 page 58:
    // Any uniform or shader storage block declared without a binding qualifier is initially
    // assigned to block binding point zero.
    int blockBinding = (interfaceBlock.binding == -1 ? 0 : interfaceBlock.binding);
    for (unsigned int arrayElement = 0; arrayElement < interfaceBlock.elementCount();
         ++arrayElement)
    {
        // We don't currently have the getBlockSize implemented for SSBOs.
        // TODO(jiajia.qin@intel.com): Remove the if when we have getBlockSize for SSBOs.
        if (interfaceBlock.blockType == sh::BlockType::BLOCK_UNIFORM)
        {
            std::string blockArrayName       = interfaceBlock.name;
            std::string blockMappedArrayName = interfaceBlock.mappedName;
            if (interfaceBlock.isArray())
            {
                blockArrayName += ArrayString(arrayElement);
                blockMappedArrayName += ArrayString(arrayElement);
            }

            // Don't define this block at all if it's not active in the implementation.
            if (!getBlockSize(blockArrayName, blockMappedArrayName, &blockSize))
            {
                continue;
            }
        }

        InterfaceBlock block(interfaceBlock.name, interfaceBlock.mappedName,
                             interfaceBlock.isArray(), arrayElement, blockBinding + arrayElement);
        block.memberIndexes = blockIndexes;
        block.setStaticUse(shaderType, interfaceBlock.staticUse);

        // Since all block elements in an array share the same active interface blocks, they
        // will all be active once any block member is used. So, since interfaceBlock.name[0]
        // was active, here we will add every block element in the array.
        block.dataSize = static_cast<unsigned int>(blockSize);
        mBlocksOut->push_back(block);
    }
}

// UniformBlockLinker implementation.
UniformBlockLinker::UniformBlockLinker(std::vector<InterfaceBlock> *blocksOut,
                                       std::vector<LinkedUniform> *uniformsOut)
    : InterfaceBlockLinker(blocksOut), mUniformsOut(uniformsOut)
{
}

UniformBlockLinker::~UniformBlockLinker()
{
}

void UniformBlockLinker::defineBlockMember(const sh::ShaderVariable &field,
                                           const std::string &fullName,
                                           const std::string &fullMappedName,
                                           int blockIndex,
                                           const sh::BlockMemberInfo &memberInfo) const
{
    LinkedUniform newUniform(field.type, field.precision, fullName, field.arraySize, -1, -1, -1,
                             blockIndex, memberInfo);
    newUniform.mappedName = fullMappedName;

    // Since block uniforms have no location, we don't need to store them in the uniform locations
    // list.
    mUniformsOut->push_back(newUniform);
}

size_t UniformBlockLinker::getCurrentBlockMemberIndex() const
{
    return mUniformsOut->size();
}

// ShaderStorageBlockLinker implementation.
ShaderStorageBlockLinker::ShaderStorageBlockLinker(std::vector<InterfaceBlock> *blocksOut)
    : InterfaceBlockLinker(blocksOut)
{
}

ShaderStorageBlockLinker::~ShaderStorageBlockLinker()
{
}

void ShaderStorageBlockLinker::defineBlockMember(const sh::ShaderVariable &field,
                                                 const std::string &fullName,
                                                 const std::string &fullMappedName,
                                                 int blockIndex,
                                                 const sh::BlockMemberInfo &memberInfo) const
{
    // TODO(jiajia.qin@intel.com): Add buffer variables support.
}

size_t ShaderStorageBlockLinker::getCurrentBlockMemberIndex() const
{
    // TODO(jiajia.qin@intel.com): Add buffer variables support.
    return 0;
}

}  // namespace gl
