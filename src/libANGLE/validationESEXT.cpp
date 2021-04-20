//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationESEXT.cpp: Validation functions for OpenGL ES extension entry points.

#include "libANGLE/validationESEXT_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/ErrorStrings.h"
#include "libANGLE/MemoryObject.h"
#include "libANGLE/validationES.h"
#include "libANGLE/validationES2.h"
#include "libANGLE/validationES3.h"
#include "libANGLE/validationES31.h"
#include "libANGLE/validationES32.h"

namespace gl
{
using namespace err;

namespace
{
template <typename ObjectT>
bool ValidateGetImageFormatAndType(const Context *context, ObjectT *obj, GLenum format, GLenum type)
{
    GLenum implFormat = obj->getImplementationColorReadFormat(context);
    if (!ValidES3Format(format) && (format != implFormat || format == GL_NONE))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidFormat);
        return false;
    }

    GLenum implType = obj->getImplementationColorReadType(context);
    if (!ValidES3Type(type) && (type != implType || type == GL_NONE))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidType);
        return false;
    }

    // Format/type combinations are not yet validated.

    return true;
}

bool IsValidImageLayout(ImageLayout layout)
{
    switch (layout)
    {
        case ImageLayout::Undefined:
        case ImageLayout::General:
        case ImageLayout::ColorAttachment:
        case ImageLayout::DepthStencilAttachment:
        case ImageLayout::DepthStencilReadOnlyAttachment:
        case ImageLayout::ShaderReadOnly:
        case ImageLayout::TransferSrc:
        case ImageLayout::TransferDst:
        case ImageLayout::DepthReadOnlyStencilAttachment:
        case ImageLayout::DepthAttachmentStencilReadOnly:
            return true;

        default:
            return false;
    }
}

bool IsValidMemoryObjectParamater(const Context *context, GLenum pname)
{
    switch (pname)
    {
        case GL_DEDICATED_MEMORY_OBJECT_EXT:
            return true;

        default:
            return false;
    }
}

bool ValidateObjectIdentifierAndName(const Context *context, GLenum identifier, GLuint name)
{
    bool isGLES11 = context->getClientVersion() == Version(1, 1);
    bool isGLES3  = context->getClientMajorVersion() >= 3;
    bool isGLES31 = context->getClientVersion() >= Version(3, 1);
    switch (identifier)
    {
        case GL_BUFFER_OBJECT_EXT:
            if (context->getBuffer({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidBufferName);
                return false;
            }
            return true;

        case GL_SHADER_OBJECT_EXT:
            if (isGLES11)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getShader({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidShaderName);
                return false;
            }
            return true;

        case GL_PROGRAM_OBJECT_EXT:
            if (isGLES11)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getProgramNoResolveLink({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidProgramName);
                return false;
            }
            return true;

        case GL_VERTEX_ARRAY_OBJECT_EXT:
            if (!isGLES3 && !context->getExtensions().vertexArrayObjectOES)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getVertexArray({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidVertexArrayName);
                return false;
            }
            return true;

        case GL_QUERY_OBJECT_EXT:
            if (!isGLES3 && !context->getExtensions().occlusionQueryBoolean)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getQuery({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidQueryName);
                return false;
            }
            return true;

        case GL_TRANSFORM_FEEDBACK:
            if (!isGLES3)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getTransformFeedback({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidTransformFeedbackName);
                return false;
            }
            return true;

        case GL_SAMPLER:
            if (!isGLES3)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getSampler({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidSamplerName);
                return false;
            }
            return true;

        case GL_TEXTURE:
            if (context->getTexture({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidTextureName);
                return false;
            }
            return true;

        case GL_RENDERBUFFER:
            if (!context->isRenderbuffer({name}))
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidRenderbufferName);
                return false;
            }
            return true;

        case GL_FRAMEBUFFER:
            if (context->getFramebuffer({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidFramebufferName);
                return false;
            }
            return true;

        case GL_PROGRAM_PIPELINE_OBJECT_EXT:
            if (!isGLES31 && !context->getExtensions().separateShaderObjects)
            {
                context->validationError(GL_INVALID_ENUM, kInvalidType);
                return false;
            }
            if (context->getProgramPipeline({name}) == nullptr)
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidProgramPipelineName);
                return false;
            }
            return true;

        default:
            context->validationError(GL_INVALID_ENUM, kInvalidIndentifier);
            return false;
    }
}
}  // namespace

bool ValidateGetTexImageANGLE(const Context *context,
                              TextureTarget target,
                              GLint level,
                              GLenum format,
                              GLenum type,
                              const void *pixels)
{
    if (!context->getExtensions().getImageANGLE)
    {
        context->validationError(GL_INVALID_OPERATION, kGetImageExtensionNotEnabled);
        return false;
    }

    if (!ValidTexture2DDestinationTarget(context, target) &&
        !ValidTexture3DDestinationTarget(context, target))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidTextureTarget);
        return false;
    }

    if (level < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeLevel);
        return false;
    }

    TextureType textureType = TextureTargetToType(target);
    if (!ValidMipLevel(context, textureType, level))
    {
        context->validationError(GL_INVALID_VALUE, kInvalidMipLevel);
        return false;
    }

    Texture *texture = context->getTextureByTarget(target);

    if (!ValidateGetImageFormatAndType(context, texture, format, type))
    {
        return false;
    }

    GLsizei width  = static_cast<GLsizei>(texture->getWidth(target, level));
    GLsizei height = static_cast<GLsizei>(texture->getHeight(target, level));
    if (!ValidatePixelPack(context, format, type, 0, 0, width, height, -1, nullptr, pixels))
    {
        return false;
    }

    return true;
}

bool ValidateGetRenderbufferImageANGLE(const Context *context,
                                       GLenum target,
                                       GLenum format,
                                       GLenum type,
                                       const void *pixels)
{
    if (!context->getExtensions().getImageANGLE)
    {
        context->validationError(GL_INVALID_OPERATION, kGetImageExtensionNotEnabled);
        return false;
    }

    if (target != GL_RENDERBUFFER)
    {
        context->validationError(GL_INVALID_ENUM, kInvalidRenderbufferTarget);
        return false;
    }

    Renderbuffer *renderbuffer = context->getState().getCurrentRenderbuffer();

    if (!ValidateGetImageFormatAndType(context, renderbuffer, format, type))
    {
        return false;
    }

    GLsizei width  = renderbuffer->getWidth();
    GLsizei height = renderbuffer->getHeight();
    if (!ValidatePixelPack(context, format, type, 0, 0, width, height, -1, nullptr, pixels))
    {
        return false;
    }

    return true;
}

bool ValidateDrawElementsBaseVertexEXT(const Context *context,
                                       PrimitiveMode mode,
                                       GLsizei count,
                                       DrawElementsType type,
                                       const void *indices,
                                       GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDrawElementsCommon(context, mode, count, type, indices, 1);
}

bool ValidateDrawElementsInstancedBaseVertexEXT(const Context *context,
                                                PrimitiveMode mode,
                                                GLsizei count,
                                                DrawElementsType type,
                                                const void *indices,
                                                GLsizei instancecount,
                                                GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDrawElementsInstancedBase(context, mode, count, type, indices, instancecount);
}

bool ValidateDrawRangeElementsBaseVertexEXT(const Context *context,
                                            PrimitiveMode mode,
                                            GLuint start,
                                            GLuint end,
                                            GLsizei count,
                                            DrawElementsType type,
                                            const void *indices,
                                            GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (end < start)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidElementRange);
        return false;
    }

    if (!ValidateDrawElementsCommon(context, mode, count, type, indices, 0))
    {
        return false;
    }

    // Skip range checks for no-op calls.
    if (count <= 0)
    {
        return true;
    }

    // Note that resolving the index range is a bit slow. We should probably optimize this.
    IndexRange indexRange;
    ANGLE_VALIDATION_TRY(context->getState().getVertexArray()->getIndexRange(context, type, count,
                                                                             indices, &indexRange));

    if (indexRange.end > end || indexRange.start < start)
    {
        // GL spec says that behavior in this case is undefined - generating an error is fine.
        context->validationError(GL_INVALID_OPERATION, kExceedsElementRange);
        return false;
    }
    return true;
}

bool ValidateMultiDrawElementsBaseVertexEXT(const Context *context,
                                            PrimitiveMode mode,
                                            const GLsizei *count,
                                            DrawElementsType type,
                                            const void *const *indices,
                                            GLsizei drawcount,
                                            const GLint *basevertex)
{
    return true;
}

bool ValidateDrawElementsBaseVertexOES(const Context *context,
                                       PrimitiveMode mode,
                                       GLsizei count,
                                       DrawElementsType type,
                                       const void *indices,
                                       GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDrawElementsCommon(context, mode, count, type, indices, 1);
}

bool ValidateDrawElementsInstancedBaseVertexOES(const Context *context,
                                                PrimitiveMode mode,
                                                GLsizei count,
                                                DrawElementsType type,
                                                const void *indices,
                                                GLsizei instancecount,
                                                GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDrawElementsInstancedBase(context, mode, count, type, indices, instancecount);
}

bool ValidateDrawRangeElementsBaseVertexOES(const Context *context,
                                            PrimitiveMode mode,
                                            GLuint start,
                                            GLuint end,
                                            GLsizei count,
                                            DrawElementsType type,
                                            const void *indices,
                                            GLint basevertex)
{
    if (!context->getExtensions().drawElementsBaseVertexAny())
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (end < start)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidElementRange);
        return false;
    }

    if (!ValidateDrawElementsCommon(context, mode, count, type, indices, 0))
    {
        return false;
    }

    // Skip range checks for no-op calls.
    if (count <= 0)
    {
        return true;
    }

    // Note that resolving the index range is a bit slow. We should probably optimize this.
    IndexRange indexRange;
    ANGLE_VALIDATION_TRY(context->getState().getVertexArray()->getIndexRange(context, type, count,
                                                                             indices, &indexRange));

    if (indexRange.end > end || indexRange.start < start)
    {
        // GL spec says that behavior in this case is undefined - generating an error is fine.
        context->validationError(GL_INVALID_OPERATION, kExceedsElementRange);
        return false;
    }
    return true;
}

// GL_KHR_blend_equation_advanced
bool ValidateBlendBarrierKHR(const Context *context)
{
    context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
    return false;
}

bool ValidateBlendEquationSeparateiEXT(const Context *context,
                                       GLuint buf,
                                       GLenum modeRGB,
                                       GLenum modeAlpha)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendEquationSeparatei(context, buf, modeRGB, modeAlpha);
}

bool ValidateBlendEquationiEXT(const Context *context, GLuint buf, GLenum mode)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendEquationi(context, buf, mode);
}

bool ValidateBlendFuncSeparateiEXT(const Context *context,
                                   GLuint buf,
                                   GLenum srcRGB,
                                   GLenum dstRGB,
                                   GLenum srcAlpha,
                                   GLenum dstAlpha)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendFuncSeparatei(context, buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

bool ValidateBlendFunciEXT(const Context *context, GLuint buf, GLenum src, GLenum dst)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendFunci(context, buf, src, dst);
}

bool ValidateColorMaskiEXT(const Context *context,
                           GLuint index,
                           GLboolean r,
                           GLboolean g,
                           GLboolean b,
                           GLboolean a)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateColorMaski(context, index, r, g, b, a);
}

bool ValidateDisableiEXT(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDisablei(context, target, index);
}

bool ValidateEnableiEXT(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateEnablei(context, target, index);
}

bool ValidateIsEnablediEXT(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateIsEnabledi(context, target, index);
}

bool ValidateBlendEquationSeparateiOES(const Context *context,
                                       GLuint buf,
                                       GLenum modeRGB,
                                       GLenum modeAlpha)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendEquationSeparatei(context, buf, modeRGB, modeAlpha);
}

bool ValidateBlendEquationiOES(const Context *context, GLuint buf, GLenum mode)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendEquationi(context, buf, mode);
}

bool ValidateBlendFuncSeparateiOES(const Context *context,
                                   GLuint buf,
                                   GLenum srcRGB,
                                   GLenum dstRGB,
                                   GLenum srcAlpha,
                                   GLenum dstAlpha)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendFuncSeparatei(context, buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

bool ValidateBlendFunciOES(const Context *context, GLuint buf, GLenum src, GLenum dst)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBlendFunci(context, buf, src, dst);
}

bool ValidateColorMaskiOES(const Context *context,
                           GLuint index,
                           GLboolean r,
                           GLboolean g,
                           GLboolean b,
                           GLboolean a)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateColorMaski(context, index, r, g, b, a);
}

bool ValidateDisableiOES(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDisablei(context, target, index);
}

bool ValidateEnableiOES(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateEnablei(context, target, index);
}

bool ValidateIsEnablediOES(const Context *context, GLenum target, GLuint index)
{
    if (!context->getExtensions().drawBuffersIndexedOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateIsEnabledi(context, target, index);
}

bool ValidateGetInteger64vEXT(const Context *context, GLenum pname, const GLint64 *data)
{
    if (!context->getExtensions().disjointTimerQuery)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    GLenum nativeType      = GL_NONE;
    unsigned int numParams = 0;
    if (!ValidateStateQuery(context, pname, &nativeType, &numParams))
    {
        return false;
    }

    return true;
}

bool ValidateCopyImageSubDataEXT(const Context *context,
                                 GLuint srcName,
                                 GLenum srcTarget,
                                 GLint srcLevel,
                                 GLint srcX,
                                 GLint srcY,
                                 GLint srcZ,
                                 GLuint dstName,
                                 GLenum dstTarget,
                                 GLint dstLevel,
                                 GLint dstX,
                                 GLint dstY,
                                 GLint dstZ,
                                 GLsizei srcWidth,
                                 GLsizei srcHeight,
                                 GLsizei srcDepth)
{
    if (!context->getExtensions().copyImageEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateCopyImageSubDataBase(context, srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
                                        dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth,
                                        srcHeight, srcDepth);
}

bool ValidateCopyImageSubDataOES(const Context *context,
                                 GLuint srcName,
                                 GLenum srcTarget,
                                 GLint srcLevel,
                                 GLint srcX,
                                 GLint srcY,
                                 GLint srcZ,
                                 GLuint dstName,
                                 GLenum dstTarget,
                                 GLint dstLevel,
                                 GLint dstX,
                                 GLint dstY,
                                 GLint dstZ,
                                 GLsizei srcWidth,
                                 GLsizei srcHeight,
                                 GLsizei srcDepth)
{
    if (!context->getExtensions().copyImageEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateCopyImageSubDataBase(context, srcName, srcTarget, srcLevel, srcX, srcY, srcZ,
                                        dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth,
                                        srcHeight, srcDepth);
}

bool ValidateBufferStorageMemEXT(const Context *context,
                                 TextureType target,
                                 GLsizeiptr size,
                                 MemoryObjectID memory,
                                 GLuint64 offset)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateCreateMemoryObjectsEXT(const Context *context,
                                    GLsizei n,
                                    const MemoryObjectID *memoryObjects)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGenOrDelete(context, n);
}

bool ValidateDeleteMemoryObjectsEXT(const Context *context,
                                    GLsizei n,
                                    const MemoryObjectID *memoryObjects)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGenOrDelete(context, n);
}

bool ValidateGetMemoryObjectParameterivEXT(const Context *context,
                                           MemoryObjectID memoryObject,
                                           GLenum pname,
                                           const GLint *params)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    const MemoryObject *memory = context->getMemoryObject(memoryObject);
    if (memory == nullptr)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidMemoryObject);
    }

    if (!IsValidMemoryObjectParamater(context, pname))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidMemoryObjectParameter);
        return false;
    }

    return true;
}

bool ValidateGetUnsignedBytevEXT(const Context *context, GLenum pname, const GLubyte *data)
{
    if (!context->getExtensions().memoryObject && !context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateGetUnsignedBytei_vEXT(const Context *context,
                                   GLenum target,
                                   GLuint index,
                                   const GLubyte *data)
{
    if (!context->getExtensions().memoryObject && !context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateIsMemoryObjectEXT(const Context *context, MemoryObjectID memoryObject)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return true;
}

bool ValidateMemoryObjectParameterivEXT(const Context *context,
                                        MemoryObjectID memoryObject,
                                        GLenum pname,
                                        const GLint *params)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    const MemoryObject *memory = context->getMemoryObject(memoryObject);
    if (memory == nullptr)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidMemoryObject);
        return false;
    }

    if (memory->isImmutable())
    {
        context->validationError(GL_INVALID_OPERATION, kImmutableMemoryObject);
        return false;
    }

    if (!IsValidMemoryObjectParamater(context, pname))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidMemoryObjectParameter);
        return false;
    }

    return true;
}

bool ValidateTexStorageMem2DEXT(const Context *context,
                                TextureType target,
                                GLsizei levels,
                                GLenum internalFormat,
                                GLsizei width,
                                GLsizei height,
                                MemoryObjectID memory,
                                GLuint64 offset)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (context->getClientMajorVersion() < 3)
    {
        return ValidateES2TexStorageParametersBase(context, target, levels, internalFormat, width,
                                                   height);
    }

    ASSERT(context->getClientMajorVersion() >= 3);
    return ValidateES3TexStorage2DParameters(context, target, levels, internalFormat, width, height,
                                             1);
}

bool ValidateTexStorageMem3DEXT(const Context *context,
                                TextureType target,
                                GLsizei levels,
                                GLenum internalFormat,
                                GLsizei width,
                                GLsizei height,
                                GLsizei depth,
                                MemoryObjectID memory,
                                GLuint64 offset)
{
    if (!context->getExtensions().memoryObject)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateImportMemoryFdEXT(const Context *context,
                               MemoryObjectID memory,
                               GLuint64 size,
                               HandleType handleType,
                               GLint fd)
{
    if (!context->getExtensions().memoryObjectFd)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    switch (handleType)
    {
        case HandleType::OpaqueFd:
            break;
        default:
            context->validationError(GL_INVALID_ENUM, kInvalidHandleType);
            return false;
    }

    return true;
}

bool ValidateImportMemoryZirconHandleANGLE(const Context *context,
                                           MemoryObjectID memory,
                                           GLuint64 size,
                                           HandleType handleType,
                                           GLuint handle)
{
    if (!context->getExtensions().memoryObjectFuchsiaANGLE)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    switch (handleType)
    {
        case HandleType::ZirconVmo:
            break;
        default:
            context->validationError(GL_INVALID_ENUM, kInvalidHandleType);
            return false;
    }

    return true;
}

bool ValidateDeleteSemaphoresEXT(const Context *context, GLsizei n, const SemaphoreID *semaphores)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGenOrDelete(context, n);
}

bool ValidateGenSemaphoresEXT(const Context *context, GLsizei n, const SemaphoreID *semaphores)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGenOrDelete(context, n);
}

bool ValidateGetSemaphoreParameterui64vEXT(const Context *context,
                                           SemaphoreID semaphore,
                                           GLenum pname,
                                           const GLuint64 *params)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateIsSemaphoreEXT(const Context *context, SemaphoreID semaphore)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return true;
}

bool ValidateSemaphoreParameterui64vEXT(const Context *context,
                                        SemaphoreID semaphore,
                                        GLenum pname,
                                        const GLuint64 *params)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    UNIMPLEMENTED();
    return false;
}

bool ValidateSignalSemaphoreEXT(const Context *context,
                                SemaphoreID semaphore,
                                GLuint numBufferBarriers,
                                const BufferID *buffers,
                                GLuint numTextureBarriers,
                                const TextureID *textures,
                                const GLenum *dstLayouts)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    for (GLuint i = 0; i < numTextureBarriers; ++i)
    {
        if (!IsValidImageLayout(FromGLenum<ImageLayout>(dstLayouts[i])))
        {
            context->validationError(GL_INVALID_ENUM, kInvalidImageLayout);
            return false;
        }
    }

    return true;
}

bool ValidateWaitSemaphoreEXT(const Context *context,
                              SemaphoreID semaphore,
                              GLuint numBufferBarriers,
                              const BufferID *buffers,
                              GLuint numTextureBarriers,
                              const TextureID *textures,
                              const GLenum *srcLayouts)
{
    if (!context->getExtensions().semaphore)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    for (GLuint i = 0; i < numTextureBarriers; ++i)
    {
        if (!IsValidImageLayout(FromGLenum<ImageLayout>(srcLayouts[i])))
        {
            context->validationError(GL_INVALID_ENUM, kInvalidImageLayout);
            return false;
        }
    }

    return true;
}

bool ValidateImportSemaphoreFdEXT(const Context *context,
                                  SemaphoreID semaphore,
                                  HandleType handleType,
                                  GLint fd)
{
    if (!context->getExtensions().semaphoreFd)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    switch (handleType)
    {
        case HandleType::OpaqueFd:
            break;
        default:
            context->validationError(GL_INVALID_ENUM, kInvalidHandleType);
            return false;
    }

    return true;
}

bool ValidateGetSamplerParameterIivEXT(const Context *context,
                                       SamplerID samplerPacked,
                                       GLenum pname,
                                       const GLint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateGetSamplerParameterBase(context, samplerPacked, pname, nullptr);
}

bool ValidateGetSamplerParameterIuivEXT(const Context *context,
                                        SamplerID samplerPacked,
                                        GLenum pname,
                                        const GLuint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateGetSamplerParameterBase(context, samplerPacked, pname, nullptr);
}

bool ValidateGetTexParameterIivEXT(const Context *context,
                                   TextureType targetPacked,
                                   GLenum pname,
                                   const GLint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateGetTexParameterBase(context, targetPacked, pname, nullptr);
}

bool ValidateGetTexParameterIuivEXT(const Context *context,
                                    TextureType targetPacked,
                                    GLenum pname,
                                    const GLuint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateGetTexParameterBase(context, targetPacked, pname, nullptr);
}

bool ValidateSamplerParameterIivEXT(const Context *context,
                                    SamplerID samplerPacked,
                                    GLenum pname,
                                    const GLint *param)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateSamplerParameterBase(context, samplerPacked, pname, -1, true, param);
}

bool ValidateSamplerParameterIuivEXT(const Context *context,
                                     SamplerID samplerPacked,
                                     GLenum pname,
                                     const GLuint *param)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateSamplerParameterBase(context, samplerPacked, pname, -1, true, param);
}

bool ValidateTexParameterIivEXT(const Context *context,
                                TextureType targetPacked,
                                GLenum pname,
                                const GLint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateTexParameterBase(context, targetPacked, pname, -1, true, params);
}

bool ValidateTexParameterIuivEXT(const Context *context,
                                 TextureType targetPacked,
                                 GLenum pname,
                                 const GLuint *params)
{
    if (context->getClientMajorVersion() < 3)
    {
        context->validationError(GL_INVALID_OPERATION, kES3Required);
        return false;
    }
    return ValidateTexParameterBase(context, targetPacked, pname, -1, true, params);
}

bool ValidateImportSemaphoreZirconHandleANGLE(const Context *context,
                                              SemaphoreID semaphore,
                                              HandleType handleType,
                                              GLuint handle)
{
    if (!context->getExtensions().semaphoreFuchsiaANGLE)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    switch (handleType)
    {
        case HandleType::ZirconEvent:
            break;
        default:
            context->validationError(GL_INVALID_ENUM, kInvalidHandleType);
            return false;
    }

    return true;
}

bool ValidateFramebufferFetchBarrierEXT(const Context *context)
{
    return true;
}

bool ValidatePatchParameteriEXT(const Context *context, GLenum pname, GLint value)
{
    if (!context->getExtensions().tessellationShaderEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kTessellationShaderExtensionNotEnabled);
        return false;
    }

    if (pname != GL_PATCH_VERTICES)
    {
        context->validationError(GL_INVALID_ENUM, kInvalidPname);
        return false;
    }

    if (value <= 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidValueNonPositive);
        return false;
    }

    if (value > context->getCaps().maxPatchVertices)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidValueExceedsMaxPatchSize);
        return false;
    }

    return true;
}

bool ValidateTexStorageMemFlags2DANGLE(const Context *context,
                                       TextureType targetPacked,
                                       GLsizei levels,
                                       GLenum internalFormat,
                                       GLsizei width,
                                       GLsizei height,
                                       MemoryObjectID memoryPacked,
                                       GLuint64 offset,
                                       GLbitfield createFlags,
                                       GLbitfield usageFlags)
{
    if (!context->getExtensions().memoryObjectFlagsANGLE)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (!ValidateTexStorageMem2DEXT(context, targetPacked, levels, internalFormat, width, height,
                                    memoryPacked, offset))
    {
        return false;
    }

    // |createFlags| and |usageFlags| must only have bits specified by the extension.
    constexpr GLbitfield kAllCreateFlags =
        GL_CREATE_SPARSE_BINDING_BIT_ANGLE | GL_CREATE_SPARSE_RESIDENCY_BIT_ANGLE |
        GL_CREATE_SPARSE_ALIASED_BIT_ANGLE | GL_CREATE_MUTABLE_FORMAT_BIT_ANGLE |
        GL_CREATE_CUBE_COMPATIBLE_BIT_ANGLE | GL_CREATE_ALIAS_BIT_ANGLE |
        GL_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_ANGLE | GL_CREATE_2D_ARRAY_COMPATIBLE_BIT_ANGLE |
        GL_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_ANGLE | GL_CREATE_EXTENDED_USAGE_BIT_ANGLE |
        GL_CREATE_PROTECTED_BIT_ANGLE | GL_CREATE_DISJOINT_BIT_ANGLE |
        GL_CREATE_CORNER_SAMPLED_BIT_ANGLE | GL_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_ANGLE |
        GL_CREATE_SUBSAMPLED_BIT_ANGLE;

    if ((createFlags & ~kAllCreateFlags) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidExternalCreateFlags);
        return false;
    }

    constexpr GLbitfield kAllUsageFlags =
        GL_USAGE_TRANSFER_SRC_BIT_ANGLE | GL_USAGE_TRANSFER_DST_BIT_ANGLE |
        GL_USAGE_SAMPLED_BIT_ANGLE | GL_USAGE_STORAGE_BIT_ANGLE |
        GL_USAGE_COLOR_ATTACHMENT_BIT_ANGLE | GL_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT_ANGLE |
        GL_USAGE_TRANSIENT_ATTACHMENT_BIT_ANGLE | GL_USAGE_INPUT_ATTACHMENT_BIT_ANGLE |
        GL_USAGE_SHADING_RATE_IMAGE_BIT_ANGLE | GL_USAGE_FRAGMENT_DENSITY_MAP_BIT_ANGLE;

    if ((usageFlags & ~kAllUsageFlags) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidExternalUsageFlags);
        return false;
    }

    return true;
}

bool ValidateTexStorageMemFlags2DMultisampleANGLE(const Context *context,
                                                  TextureType targetPacked,
                                                  GLsizei samples,
                                                  GLenum internalFormat,
                                                  GLsizei width,
                                                  GLsizei height,
                                                  GLboolean fixedSampleLocations,
                                                  MemoryObjectID memoryPacked,
                                                  GLuint64 offset,
                                                  GLbitfield createFlags,
                                                  GLbitfield usageFlags)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateTexStorageMemFlags3DANGLE(const Context *context,
                                       TextureType targetPacked,
                                       GLsizei levels,
                                       GLenum internalFormat,
                                       GLsizei width,
                                       GLsizei height,
                                       GLsizei depth,
                                       MemoryObjectID memoryPacked,
                                       GLuint64 offset,
                                       GLbitfield createFlags,
                                       GLbitfield usageFlags)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateTexStorageMemFlags3DMultisampleANGLE(const Context *context,
                                                  TextureType targetPacked,
                                                  GLsizei samples,
                                                  GLenum internalFormat,
                                                  GLsizei width,
                                                  GLsizei height,
                                                  GLsizei depth,
                                                  GLboolean fixedSampleLocations,
                                                  MemoryObjectID memoryPacked,
                                                  GLuint64 offset,
                                                  GLbitfield createFlags,
                                                  GLbitfield usageFlags)
{
    UNIMPLEMENTED();
    return false;
}

// GL_EXT_buffer_storage
bool ValidateBufferStorageEXT(const Context *context,
                              BufferBinding targetPacked,
                              GLsizeiptr size,
                              const void *data,
                              GLbitfield flags)
{
    if (!context->isValidBufferBinding(targetPacked))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidBufferTypes);
        return false;
    }

    if (size <= 0)
    {
        context->validationError(GL_INVALID_VALUE, kNonPositiveSize);
        return false;
    }

    constexpr GLbitfield kAllUsageFlags =
        (GL_DYNAMIC_STORAGE_BIT_EXT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT |
         GL_MAP_PERSISTENT_BIT_EXT | GL_MAP_COHERENT_BIT_EXT | GL_CLIENT_STORAGE_BIT_EXT);
    if ((flags & ~kAllUsageFlags) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidBufferUsageFlags);
        return false;
    }

    if (((flags & GL_MAP_PERSISTENT_BIT_EXT) != 0) &&
        ((flags & (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT)) == 0))
    {
        context->validationError(GL_INVALID_VALUE, kInvalidBufferUsageFlags);
        return false;
    }

    if (((flags & GL_MAP_COHERENT_BIT_EXT) != 0) && ((flags & GL_MAP_PERSISTENT_BIT_EXT) == 0))
    {
        context->validationError(GL_INVALID_VALUE, kInvalidBufferUsageFlags);
        return false;
    }

    Buffer *buffer = context->getState().getTargetBuffer(targetPacked);

    if (buffer == nullptr)
    {
        context->validationError(GL_INVALID_OPERATION, kBufferNotBound);
        return false;
    }

    if (buffer->isImmutable())
    {
        context->validationError(GL_INVALID_OPERATION, kBufferImmutable);
        return false;
    }

    return true;
}

// GL_EXT_clip_control
bool ValidateClipControlEXT(const Context *context, GLenum origin, GLenum depth)
{
    if ((origin != GL_LOWER_LEFT_EXT) && (origin != GL_UPPER_LEFT_EXT))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidOriginEnum);
        return false;
    }

    if ((depth != GL_NEGATIVE_ONE_TO_ONE_EXT) && (depth != GL_ZERO_TO_ONE_EXT))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidDepthEnum);
        return false;
    }

    return true;
}

// GL_EXT_external_buffer
bool ValidateBufferStorageExternalEXT(const Context *context,
                                      BufferBinding targetPacked,
                                      GLintptr offset,
                                      GLsizeiptr size,
                                      GLeglClientBufferEXT clientBuffer,
                                      GLbitfield flags)
{
    if (!ValidateBufferStorageEXT(context, targetPacked, size, nullptr, flags))
    {
        return false;
    }

    if (offset != 0)
    {
        context->validationError(GL_INVALID_VALUE, kExternalBufferInvalidOffset);
        return false;
    }

    if (clientBuffer == nullptr && size > 0)
    {
        context->validationError(GL_INVALID_VALUE, kClientBufferInvalid);
        return false;
    }

    return true;
}

bool ValidateNamedBufferStorageExternalEXT(const Context *context,
                                           GLuint buffer,
                                           GLintptr offset,
                                           GLsizeiptr size,
                                           GLeglClientBufferEXT clientBuffer,
                                           GLbitfield flags)
{
    UNIMPLEMENTED();
    return false;
}

// GL_EXT_separate_shader_objects
bool ValidateActiveShaderProgramEXT(const Context *context,
                                    ProgramPipelineID pipelinePacked,
                                    ShaderProgramID programPacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateActiveShaderProgramBase(context, pipelinePacked, programPacked);
}

bool ValidateBindProgramPipelineEXT(const Context *context, ProgramPipelineID pipelinePacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateBindProgramPipelineBase(context, pipelinePacked);
}

bool ValidateCreateShaderProgramvEXT(const Context *context,
                                     ShaderType typePacked,
                                     GLsizei count,
                                     const GLchar **strings)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateCreateShaderProgramvBase(context, typePacked, count, strings);
}

bool ValidateDeleteProgramPipelinesEXT(const Context *context,
                                       GLsizei n,
                                       const ProgramPipelineID *pipelinesPacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateDeleteProgramPipelinesBase(context, n, pipelinesPacked);
}

bool ValidateGenProgramPipelinesEXT(const Context *context,
                                    GLsizei n,
                                    const ProgramPipelineID *pipelinesPacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGenProgramPipelinesBase(context, n, pipelinesPacked);
}

bool ValidateGetProgramPipelineInfoLogEXT(const Context *context,
                                          ProgramPipelineID pipelinePacked,
                                          GLsizei bufSize,
                                          const GLsizei *length,
                                          const GLchar *infoLog)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGetProgramPipelineInfoLogBase(context, pipelinePacked, bufSize, length, infoLog);
}

bool ValidateGetProgramPipelineivEXT(const Context *context,
                                     ProgramPipelineID pipelinePacked,
                                     GLenum pname,
                                     const GLint *params)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateGetProgramPipelineivBase(context, pipelinePacked, pname, params);
}

bool ValidateIsProgramPipelineEXT(const Context *context, ProgramPipelineID pipelinePacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateIsProgramPipelineBase(context, pipelinePacked);
}

bool ValidateProgramParameteriEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  GLenum pname,
                                  GLint value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramParameteriBase(context, programPacked, pname, value);
}

bool ValidateProgramUniform1fEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLfloat v0)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1fBase(context, programPacked, locationPacked, v0);
}

bool ValidateProgramUniform1fvEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1fvBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform1iEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLint v0)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1iBase(context, programPacked, locationPacked, v0);
}

bool ValidateProgramUniform1ivEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1ivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform1uiEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLuint v0)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1uiBase(context, programPacked, locationPacked, v0);
}

bool ValidateProgramUniform1uivEXT(const Context *context,
                                   ShaderProgramID programPacked,
                                   UniformLocation locationPacked,
                                   GLsizei count,
                                   const GLuint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform1uivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform2fEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLfloat v0,
                                 GLfloat v1)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2fBase(context, programPacked, locationPacked, v0, v1);
}

bool ValidateProgramUniform2fvEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2fvBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform2iEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLint v0,
                                 GLint v1)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2iBase(context, programPacked, locationPacked, v0, v1);
}

bool ValidateProgramUniform2ivEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2ivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform2uiEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLuint v0,
                                  GLuint v1)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2uiBase(context, programPacked, locationPacked, v0, v1);
}

bool ValidateProgramUniform2uivEXT(const Context *context,
                                   ShaderProgramID programPacked,
                                   UniformLocation locationPacked,
                                   GLsizei count,
                                   const GLuint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform2uivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform3fEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLfloat v0,
                                 GLfloat v1,
                                 GLfloat v2)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3fBase(context, programPacked, locationPacked, v0, v1, v2);
}

bool ValidateProgramUniform3fvEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3fvBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform3iEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLint v0,
                                 GLint v1,
                                 GLint v2)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3iBase(context, programPacked, locationPacked, v0, v1, v2);
}

bool ValidateProgramUniform3ivEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3ivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform3uiEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLuint v0,
                                  GLuint v1,
                                  GLuint v2)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3uiBase(context, programPacked, locationPacked, v0, v1, v2);
}

bool ValidateProgramUniform3uivEXT(const Context *context,
                                   ShaderProgramID programPacked,
                                   UniformLocation locationPacked,
                                   GLsizei count,
                                   const GLuint *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform3uivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform4fEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLfloat v0,
                                 GLfloat v1,
                                 GLfloat v2,
                                 GLfloat v3)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform4fBase(context, programPacked, locationPacked, v0, v1, v2, v3);
}

bool ValidateProgramUniform4fvEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform4fvBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform4iEXT(const Context *context,
                                 ShaderProgramID programPacked,
                                 UniformLocation locationPacked,
                                 GLint v0,
                                 GLint v1,
                                 GLint v2,
                                 GLint v3)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform4iBase(context, programPacked, locationPacked, v0, v1, v2, v3);
}

bool ValidateProgramUniform4ivEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLsizei count,
                                  const GLint *value)
{
    return ValidateProgramUniform4ivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniform4uiEXT(const Context *context,
                                  ShaderProgramID programPacked,
                                  UniformLocation locationPacked,
                                  GLuint v0,
                                  GLuint v1,
                                  GLuint v2,
                                  GLuint v3)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniform4uiBase(context, programPacked, locationPacked, v0, v1, v2, v3);
}

bool ValidateProgramUniform4uivEXT(const Context *context,
                                   ShaderProgramID programPacked,
                                   UniformLocation locationPacked,
                                   GLsizei count,
                                   const GLuint *value)
{
    return ValidateProgramUniform4uivBase(context, programPacked, locationPacked, count, value);
}

bool ValidateProgramUniformMatrix2fvEXT(const Context *context,
                                        ShaderProgramID programPacked,
                                        UniformLocation locationPacked,
                                        GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix2fvBase(context, programPacked, locationPacked, count,
                                               transpose, value);
}

bool ValidateProgramUniformMatrix2x3fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix2x3fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateProgramUniformMatrix2x4fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix2x4fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateProgramUniformMatrix3fvEXT(const Context *context,
                                        ShaderProgramID programPacked,
                                        UniformLocation locationPacked,
                                        GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix3fvBase(context, programPacked, locationPacked, count,
                                               transpose, value);
}

bool ValidateProgramUniformMatrix3x2fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix3x2fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateProgramUniformMatrix3x4fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix3x4fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateProgramUniformMatrix4fvEXT(const Context *context,
                                        ShaderProgramID programPacked,
                                        UniformLocation locationPacked,
                                        GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix4fvBase(context, programPacked, locationPacked, count,
                                               transpose, value);
}

bool ValidateProgramUniformMatrix4x2fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix4x2fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateProgramUniformMatrix4x3fvEXT(const Context *context,
                                          ShaderProgramID programPacked,
                                          UniformLocation locationPacked,
                                          GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateProgramUniformMatrix4x3fvBase(context, programPacked, locationPacked, count,
                                                 transpose, value);
}

bool ValidateUseProgramStagesEXT(const Context *context,
                                 ProgramPipelineID pipelinePacked,
                                 GLbitfield stages,
                                 ShaderProgramID programPacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateUseProgramStagesBase(context, pipelinePacked, stages, programPacked);
}

bool ValidateValidateProgramPipelineEXT(const Context *context, ProgramPipelineID pipelinePacked)
{
    if (!context->getExtensions().separateShaderObjects)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return ValidateValidateProgramPipelineBase(context, pipelinePacked);
}

// GL_EXT_debug_label
bool ValidateGetObjectLabelEXT(const Context *context,
                               GLenum type,
                               GLuint object,
                               GLsizei bufSize,
                               const GLsizei *length,
                               const GLchar *label)
{
    if (!context->getExtensions().debugLabel)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (bufSize < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeBufferSize);
        return false;
    }

    return ValidateObjectIdentifierAndName(context, type, object);
}

bool ValidateLabelObjectEXT(const Context *context,
                            GLenum type,
                            GLuint object,
                            GLsizei length,
                            const GLchar *label)
{
    if (!context->getExtensions().debugLabel)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    if (length < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeLength);
        return false;
    }

    return ValidateObjectIdentifierAndName(context, type, object);
}
}  // namespace gl
