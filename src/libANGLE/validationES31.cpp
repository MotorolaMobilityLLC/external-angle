//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// validationES31.cpp: Validation functions for OpenGL ES 3.1 entry point parameters

#include "libANGLE/validationES31_autogen.h"

#include "libANGLE/Context.h"
#include "libANGLE/ErrorStrings.h"
#include "libANGLE/Framebuffer.h"
#include "libANGLE/ProgramExecutable.h"
#include "libANGLE/VertexArray.h"
#include "libANGLE/validationES.h"
#include "libANGLE/validationES2_autogen.h"
#include "libANGLE/validationES31.h"
#include "libANGLE/validationES3_autogen.h"

#include "common/utilities.h"

using namespace angle;

namespace gl
{
using namespace err;

namespace
{

bool ValidateNamedProgramInterface(GLenum programInterface)
{
    switch (programInterface)
    {
        case GL_UNIFORM:
        case GL_UNIFORM_BLOCK:
        case GL_PROGRAM_INPUT:
        case GL_PROGRAM_OUTPUT:
        case GL_TRANSFORM_FEEDBACK_VARYING:
        case GL_BUFFER_VARIABLE:
        case GL_SHADER_STORAGE_BLOCK:
            return true;
        default:
            return false;
    }
}

bool ValidateLocationProgramInterface(GLenum programInterface)
{
    switch (programInterface)
    {
        case GL_UNIFORM:
        case GL_PROGRAM_INPUT:
        case GL_PROGRAM_OUTPUT:
            return true;
        default:
            return false;
    }
}

bool ValidateProgramInterface(GLenum programInterface)
{
    return (programInterface == GL_ATOMIC_COUNTER_BUFFER ||
            ValidateNamedProgramInterface(programInterface));
}

bool ValidateProgramResourceProperty(const Context *context, GLenum prop)
{
    ASSERT(context);
    switch (prop)
    {
        case GL_ACTIVE_VARIABLES:
        case GL_BUFFER_BINDING:
        case GL_NUM_ACTIVE_VARIABLES:

        case GL_ARRAY_SIZE:

        case GL_ARRAY_STRIDE:
        case GL_BLOCK_INDEX:
        case GL_IS_ROW_MAJOR:
        case GL_MATRIX_STRIDE:

        case GL_ATOMIC_COUNTER_BUFFER_INDEX:

        case GL_BUFFER_DATA_SIZE:

        case GL_LOCATION:

        case GL_NAME_LENGTH:

        case GL_OFFSET:

        case GL_REFERENCED_BY_VERTEX_SHADER:
        case GL_REFERENCED_BY_FRAGMENT_SHADER:
        case GL_REFERENCED_BY_COMPUTE_SHADER:

        case GL_TOP_LEVEL_ARRAY_SIZE:
        case GL_TOP_LEVEL_ARRAY_STRIDE:

        case GL_TYPE:
            return true;

        case GL_REFERENCED_BY_GEOMETRY_SHADER_EXT:
            return context->getExtensions().geometryShader;

        case GL_LOCATION_INDEX_EXT:
            return context->getExtensions().blendFuncExtended;

        default:
            return false;
    }
}

// GLES 3.10 spec: Page 82 -- Table 7.2
bool ValidateProgramResourcePropertyByInterface(GLenum prop, GLenum programInterface)
{
    switch (prop)
    {
        case GL_ACTIVE_VARIABLES:
        case GL_BUFFER_BINDING:
        case GL_NUM_ACTIVE_VARIABLES:
        {
            switch (programInterface)
            {
                case GL_ATOMIC_COUNTER_BUFFER:
                case GL_SHADER_STORAGE_BLOCK:
                case GL_UNIFORM_BLOCK:
                    return true;
                default:
                    return false;
            }
        }

        case GL_ARRAY_SIZE:
        {
            switch (programInterface)
            {
                case GL_BUFFER_VARIABLE:
                case GL_PROGRAM_INPUT:
                case GL_PROGRAM_OUTPUT:
                case GL_TRANSFORM_FEEDBACK_VARYING:
                case GL_UNIFORM:
                    return true;
                default:
                    return false;
            }
        }

        case GL_ARRAY_STRIDE:
        case GL_BLOCK_INDEX:
        case GL_IS_ROW_MAJOR:
        case GL_MATRIX_STRIDE:
        {
            switch (programInterface)
            {
                case GL_BUFFER_VARIABLE:
                case GL_UNIFORM:
                    return true;
                default:
                    return false;
            }
        }

        case GL_ATOMIC_COUNTER_BUFFER_INDEX:
        {
            if (programInterface == GL_UNIFORM)
            {
                return true;
            }
            return false;
        }

        case GL_BUFFER_DATA_SIZE:
        {
            switch (programInterface)
            {
                case GL_ATOMIC_COUNTER_BUFFER:
                case GL_SHADER_STORAGE_BLOCK:
                case GL_UNIFORM_BLOCK:
                    return true;
                default:
                    return false;
            }
        }

        case GL_LOCATION:
        {
            return ValidateLocationProgramInterface(programInterface);
        }

        case GL_LOCATION_INDEX_EXT:
        {
            // EXT_blend_func_extended
            return (programInterface == GL_PROGRAM_OUTPUT);
        }

        case GL_NAME_LENGTH:
        {
            return ValidateNamedProgramInterface(programInterface);
        }

        case GL_OFFSET:
        {
            switch (programInterface)
            {
                case GL_BUFFER_VARIABLE:
                case GL_UNIFORM:
                    return true;
                default:
                    return false;
            }
        }

        case GL_REFERENCED_BY_VERTEX_SHADER:
        case GL_REFERENCED_BY_FRAGMENT_SHADER:
        case GL_REFERENCED_BY_COMPUTE_SHADER:
        case GL_REFERENCED_BY_GEOMETRY_SHADER_EXT:
        {
            switch (programInterface)
            {
                case GL_ATOMIC_COUNTER_BUFFER:
                case GL_BUFFER_VARIABLE:
                case GL_PROGRAM_INPUT:
                case GL_PROGRAM_OUTPUT:
                case GL_SHADER_STORAGE_BLOCK:
                case GL_UNIFORM:
                case GL_UNIFORM_BLOCK:
                    return true;
                default:
                    return false;
            }
        }

        case GL_TOP_LEVEL_ARRAY_SIZE:
        case GL_TOP_LEVEL_ARRAY_STRIDE:
        {
            if (programInterface == GL_BUFFER_VARIABLE)
            {
                return true;
            }
            return false;
        }

        case GL_TYPE:
        {
            switch (programInterface)
            {
                case GL_BUFFER_VARIABLE:
                case GL_PROGRAM_INPUT:
                case GL_PROGRAM_OUTPUT:
                case GL_TRANSFORM_FEEDBACK_VARYING:
                case GL_UNIFORM:
                    return true;
                default:
                    return false;
            }
        }

        default:
            return false;
    }
}

bool ValidateProgramResourceIndex(const Program *programObject,
                                  GLenum programInterface,
                                  GLuint index)
{
    switch (programInterface)
    {
        case GL_PROGRAM_INPUT:
            return (index <
                    static_cast<GLuint>(programObject->getState().getProgramInputs().size()));

        case GL_PROGRAM_OUTPUT:
            return (index < static_cast<GLuint>(programObject->getOutputResourceCount()));

        case GL_UNIFORM:
            return (index < static_cast<GLuint>(programObject->getActiveUniformCount()));

        case GL_BUFFER_VARIABLE:
            return (index < static_cast<GLuint>(programObject->getActiveBufferVariableCount()));

        case GL_SHADER_STORAGE_BLOCK:
            return (index < static_cast<GLuint>(programObject->getActiveShaderStorageBlockCount()));

        case GL_UNIFORM_BLOCK:
            return (index < programObject->getActiveUniformBlockCount());

        case GL_ATOMIC_COUNTER_BUFFER:
            return (index < programObject->getActiveAtomicCounterBufferCount());

        case GL_TRANSFORM_FEEDBACK_VARYING:
            return (index < static_cast<GLuint>(programObject->getTransformFeedbackVaryingCount()));

        default:
            UNREACHABLE();
            return false;
    }
}

bool ValidateProgramUniform(const Context *context,
                            GLenum valueType,
                            ShaderProgramID program,
                            UniformLocation location,
                            GLsizei count)
{
    // Check for ES31 program uniform entry points
    if (context->getClientVersion() < Version(3, 1))
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const LinkedUniform *uniform = nullptr;
    Program *programObject       = GetValidProgram(context, program);
    return ValidateUniformCommonBase(context, programObject, location, count, &uniform) &&
           ValidateUniformValue(context, valueType, uniform->type);
}

bool ValidateProgramUniformMatrix(const Context *context,
                                  GLenum valueType,
                                  ShaderProgramID program,
                                  UniformLocation location,
                                  GLsizei count,
                                  GLboolean transpose)
{
    // Check for ES31 program uniform entry points
    if (context->getClientVersion() < Version(3, 1))
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const LinkedUniform *uniform = nullptr;
    Program *programObject       = GetValidProgram(context, program);
    return ValidateUniformCommonBase(context, programObject, location, count, &uniform) &&
           ValidateUniformMatrixValue(context, valueType, uniform->type);
}

bool ValidateVertexAttribFormatCommon(const Context *context, GLuint relativeOffset)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const Caps &caps = context->getCaps();
    if (relativeOffset > static_cast<GLuint>(caps.maxVertexAttribRelativeOffset))
    {
        context->validationError(GL_INVALID_VALUE, kRelativeOffsetTooLarge);
        return false;
    }

    // [OpenGL ES 3.1] Section 10.3.1 page 243:
    // An INVALID_OPERATION error is generated if the default vertex array object is bound.
    if (context->getState().getVertexArrayId().value == 0)
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultVertexArray);
        return false;
    }

    return true;
}

}  // anonymous namespace

bool ValidateGetBooleani_v(const Context *context,
                           GLenum target,
                           GLuint index,
                           const GLboolean *data)
{
    if (context->getClientVersion() < ES_3_1 && !context->getExtensions().drawBuffersIndexedAny())
    {
        context->validationError(GL_INVALID_OPERATION,
                                 kES31OrDrawBuffersIndexedExtensionNotAvailable);
        return false;
    }

    if (!ValidateIndexedStateQuery(context, target, index, nullptr))
    {
        return false;
    }

    return true;
}

bool ValidateGetBooleani_vRobustANGLE(const Context *context,
                                      GLenum target,
                                      GLuint index,
                                      GLsizei bufSize,
                                      const GLsizei *length,
                                      const GLboolean *data)
{
    if (context->getClientVersion() < ES_3_1 && !context->getExtensions().drawBuffersIndexedAny())
    {
        context->validationError(GL_INVALID_OPERATION,
                                 kES31OrDrawBuffersIndexedExtensionNotAvailable);
        return false;
    }

    if (!ValidateRobustEntryPoint(context, bufSize))
    {
        return false;
    }

    GLsizei numParams = 0;

    if (!ValidateIndexedStateQuery(context, target, index, &numParams))
    {
        return false;
    }

    if (!ValidateRobustBufferSize(context, bufSize, numParams))
    {
        return false;
    }

    SetRobustLengthParam(length, numParams);
    return true;
}

bool ValidateDrawIndirectBase(const Context *context, PrimitiveMode mode, const void *indirect)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    // Here the third parameter 1 is only to pass the count validation.
    if (!ValidateDrawBase(context, mode))
    {
        return false;
    }

    const State &state = context->getState();

    // An INVALID_OPERATION error is generated if zero is bound to VERTEX_ARRAY_BINDING,
    // DRAW_INDIRECT_BUFFER or to any enabled vertex array.
    if (state.getVertexArrayId().value == 0)
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultVertexArray);
        return false;
    }

    if (context->getStateCache().hasAnyActiveClientAttrib())
    {
        context->validationError(GL_INVALID_OPERATION, kClientDataInVertexArray);
        return false;
    }

    Buffer *drawIndirectBuffer = state.getTargetBuffer(BufferBinding::DrawIndirect);
    if (!drawIndirectBuffer)
    {
        context->validationError(GL_INVALID_OPERATION, kDrawIndirectBufferNotBound);
        return false;
    }

    // An INVALID_VALUE error is generated if indirect is not a multiple of the size, in basic
    // machine units, of uint.
    GLint64 offset = reinterpret_cast<GLint64>(indirect);
    if ((static_cast<GLuint>(offset) % sizeof(GLuint)) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidIndirectOffset);
        return false;
    }

    return true;
}

bool ValidateDrawArraysIndirect(const Context *context, PrimitiveMode mode, const void *indirect)
{
    const State &state                      = context->getState();
    TransformFeedback *curTransformFeedback = state.getCurrentTransformFeedback();
    if (curTransformFeedback && curTransformFeedback->isActive() &&
        !curTransformFeedback->isPaused())
    {
        // EXT_geometry_shader allows transform feedback to work with all draw commands.
        // [EXT_geometry_shader] Section 12.1, "Transform Feedback"
        if (context->getExtensions().geometryShader)
        {
            if (!ValidateTransformFeedbackPrimitiveMode(
                    context, curTransformFeedback->getPrimitiveMode(), mode))
            {
                context->validationError(GL_INVALID_OPERATION, kInvalidDrawModeTransformFeedback);
                return false;
            }
        }
        else
        {
            // An INVALID_OPERATION error is generated if transform feedback is active and not
            // paused.
            context->validationError(GL_INVALID_OPERATION,
                                     kUnsupportedDrawModeForTransformFeedback);
            return false;
        }
    }

    if (!ValidateDrawIndirectBase(context, mode, indirect))
        return false;

    Buffer *drawIndirectBuffer = state.getTargetBuffer(BufferBinding::DrawIndirect);
    CheckedNumeric<size_t> checkedOffset(reinterpret_cast<size_t>(indirect));
    // In OpenGL ES3.1 spec, session 10.5, it defines the struct of DrawArraysIndirectCommand
    // which's size is 4 * sizeof(uint).
    auto checkedSum = checkedOffset + 4 * sizeof(GLuint);
    if (!checkedSum.IsValid() ||
        checkedSum.ValueOrDie() > static_cast<size_t>(drawIndirectBuffer->getSize()))
    {
        context->validationError(GL_INVALID_OPERATION, kParamOverflow);
        return false;
    }

    return true;
}

bool ValidateDrawElementsIndirect(const Context *context,
                                  PrimitiveMode mode,
                                  DrawElementsType type,
                                  const void *indirect)
{
    if (!ValidateDrawElementsBase(context, mode, type))
    {
        return false;
    }

    const State &state         = context->getState();
    const VertexArray *vao     = state.getVertexArray();
    Buffer *elementArrayBuffer = vao->getElementArrayBuffer();
    if (!elementArrayBuffer)
    {
        context->validationError(GL_INVALID_OPERATION, kMustHaveElementArrayBinding);
        return false;
    }

    if (!ValidateDrawIndirectBase(context, mode, indirect))
        return false;

    Buffer *drawIndirectBuffer = state.getTargetBuffer(BufferBinding::DrawIndirect);
    CheckedNumeric<size_t> checkedOffset(reinterpret_cast<size_t>(indirect));
    // In OpenGL ES3.1 spec, session 10.5, it defines the struct of DrawElementsIndirectCommand
    // which's size is 5 * sizeof(uint).
    auto checkedSum = checkedOffset + 5 * sizeof(GLuint);
    if (!checkedSum.IsValid() ||
        checkedSum.ValueOrDie() > static_cast<size_t>(drawIndirectBuffer->getSize()))
    {
        context->validationError(GL_INVALID_OPERATION, kParamOverflow);
        return false;
    }

    return true;
}

bool ValidateProgramUniform1i(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLint v0)
{
    return ValidateProgramUniform1iv(context, program, location, 1, &v0);
}

bool ValidateProgramUniform2i(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLint v0,
                              GLint v1)
{
    GLint xy[2] = {v0, v1};
    return ValidateProgramUniform2iv(context, program, location, 1, xy);
}

bool ValidateProgramUniform3i(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLint v0,
                              GLint v1,
                              GLint v2)
{
    GLint xyz[3] = {v0, v1, v2};
    return ValidateProgramUniform3iv(context, program, location, 1, xyz);
}

bool ValidateProgramUniform4i(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLint v0,
                              GLint v1,
                              GLint v2,
                              GLint v3)
{
    GLint xyzw[4] = {v0, v1, v2, v3};
    return ValidateProgramUniform4iv(context, program, location, 1, xyzw);
}

bool ValidateProgramUniform1ui(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLuint v0)
{
    return ValidateProgramUniform1uiv(context, program, location, 1, &v0);
}

bool ValidateProgramUniform2ui(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLuint v0,
                               GLuint v1)
{
    GLuint xy[2] = {v0, v1};
    return ValidateProgramUniform2uiv(context, program, location, 1, xy);
}

bool ValidateProgramUniform3ui(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLuint v0,
                               GLuint v1,
                               GLuint v2)
{
    GLuint xyz[3] = {v0, v1, v2};
    return ValidateProgramUniform3uiv(context, program, location, 1, xyz);
}

bool ValidateProgramUniform4ui(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLuint v0,
                               GLuint v1,
                               GLuint v2,
                               GLuint v3)
{
    GLuint xyzw[4] = {v0, v1, v2, v3};
    return ValidateProgramUniform4uiv(context, program, location, 1, xyzw);
}

bool ValidateProgramUniform1f(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLfloat v0)
{
    return ValidateProgramUniform1fv(context, program, location, 1, &v0);
}

bool ValidateProgramUniform2f(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLfloat v0,
                              GLfloat v1)
{
    GLfloat xy[2] = {v0, v1};
    return ValidateProgramUniform2fv(context, program, location, 1, xy);
}

bool ValidateProgramUniform3f(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLfloat v0,
                              GLfloat v1,
                              GLfloat v2)
{
    GLfloat xyz[3] = {v0, v1, v2};
    return ValidateProgramUniform3fv(context, program, location, 1, xyz);
}

bool ValidateProgramUniform4f(const Context *context,
                              ShaderProgramID program,
                              UniformLocation location,
                              GLfloat v0,
                              GLfloat v1,
                              GLfloat v2,
                              GLfloat v3)
{
    GLfloat xyzw[4] = {v0, v1, v2, v3};
    return ValidateProgramUniform4fv(context, program, location, 1, xyzw);
}

bool ValidateProgramUniform1iv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLint *value)
{
    // Check for ES31 program uniform entry points
    if (context->getClientVersion() < Version(3, 1))
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const LinkedUniform *uniform = nullptr;
    Program *programObject       = GetValidProgram(context, program);
    return ValidateUniformCommonBase(context, programObject, location, count, &uniform) &&
           ValidateUniform1ivValue(context, uniform->type, count, value);
}

bool ValidateProgramUniform2iv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLint *value)
{
    return ValidateProgramUniform(context, GL_INT_VEC2, program, location, count);
}

bool ValidateProgramUniform3iv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLint *value)
{
    return ValidateProgramUniform(context, GL_INT_VEC3, program, location, count);
}

bool ValidateProgramUniform4iv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLint *value)
{
    return ValidateProgramUniform(context, GL_INT_VEC4, program, location, count);
}

bool ValidateProgramUniform1uiv(const Context *context,
                                ShaderProgramID program,
                                UniformLocation location,
                                GLsizei count,
                                const GLuint *value)
{
    return ValidateProgramUniform(context, GL_UNSIGNED_INT, program, location, count);
}

bool ValidateProgramUniform2uiv(const Context *context,
                                ShaderProgramID program,
                                UniformLocation location,
                                GLsizei count,
                                const GLuint *value)
{
    return ValidateProgramUniform(context, GL_UNSIGNED_INT_VEC2, program, location, count);
}

bool ValidateProgramUniform3uiv(const Context *context,
                                ShaderProgramID program,
                                UniformLocation location,
                                GLsizei count,
                                const GLuint *value)
{
    return ValidateProgramUniform(context, GL_UNSIGNED_INT_VEC3, program, location, count);
}

bool ValidateProgramUniform4uiv(const Context *context,
                                ShaderProgramID program,
                                UniformLocation location,
                                GLsizei count,
                                const GLuint *value)
{
    return ValidateProgramUniform(context, GL_UNSIGNED_INT_VEC4, program, location, count);
}

bool ValidateProgramUniform1fv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLfloat *value)
{
    return ValidateProgramUniform(context, GL_FLOAT, program, location, count);
}

bool ValidateProgramUniform2fv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLfloat *value)
{
    return ValidateProgramUniform(context, GL_FLOAT_VEC2, program, location, count);
}

bool ValidateProgramUniform3fv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLfloat *value)
{
    return ValidateProgramUniform(context, GL_FLOAT_VEC3, program, location, count);
}

bool ValidateProgramUniform4fv(const Context *context,
                               ShaderProgramID program,
                               UniformLocation location,
                               GLsizei count,
                               const GLfloat *value)
{
    return ValidateProgramUniform(context, GL_FLOAT_VEC4, program, location, count);
}

bool ValidateProgramUniformMatrix2fv(const Context *context,
                                     ShaderProgramID program,
                                     UniformLocation location,
                                     GLsizei count,
                                     GLboolean transpose,
                                     const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT2, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix3fv(const Context *context,
                                     ShaderProgramID program,
                                     UniformLocation location,
                                     GLsizei count,
                                     GLboolean transpose,
                                     const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT3, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix4fv(const Context *context,
                                     ShaderProgramID program,
                                     UniformLocation location,
                                     GLsizei count,
                                     GLboolean transpose,
                                     const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT4, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix2x3fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT2x3, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix3x2fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT3x2, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix2x4fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT2x4, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix4x2fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT4x2, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix3x4fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT3x4, program, location, count,
                                        transpose);
}

bool ValidateProgramUniformMatrix4x3fv(const Context *context,
                                       ShaderProgramID program,
                                       UniformLocation location,
                                       GLsizei count,
                                       GLboolean transpose,
                                       const GLfloat *value)
{
    return ValidateProgramUniformMatrix(context, GL_FLOAT_MAT4x3, program, location, count,
                                        transpose);
}

bool ValidateGetTexLevelParameterfv(const Context *context,
                                    TextureTarget target,
                                    GLint level,
                                    GLenum pname,
                                    const GLfloat *params)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateGetTexLevelParameterBase(context, target, level, pname, nullptr);
}

bool ValidateGetTexLevelParameterfvRobustANGLE(const Context *context,
                                               TextureTarget target,
                                               GLint level,
                                               GLenum pname,
                                               GLsizei bufSize,
                                               const GLsizei *length,
                                               const GLfloat *params)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateGetTexLevelParameteriv(const Context *context,
                                    TextureTarget target,
                                    GLint level,
                                    GLenum pname,
                                    const GLint *params)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateGetTexLevelParameterBase(context, target, level, pname, nullptr);
}

bool ValidateGetTexLevelParameterivRobustANGLE(const Context *context,
                                               TextureTarget target,
                                               GLint level,
                                               GLenum pname,
                                               GLsizei bufSize,
                                               const GLsizei *length,
                                               const GLint *params)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateTexStorage2DMultisample(const Context *context,
                                     TextureType target,
                                     GLsizei samples,
                                     GLenum internalFormat,
                                     GLsizei width,
                                     GLsizei height,
                                     GLboolean fixedSampleLocations)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateTexStorage2DMultisampleBase(context, target, samples, internalFormat, width,
                                               height);
}

bool ValidateTexStorageMem2DMultisampleEXT(const Context *context,
                                           TextureType target,
                                           GLsizei samples,
                                           GLenum internalFormat,
                                           GLsizei width,
                                           GLsizei height,
                                           GLboolean fixedSampleLocations,
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

bool ValidateGetMultisamplefv(const Context *context,
                              GLenum pname,
                              GLuint index,
                              const GLfloat *val)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateGetMultisamplefvBase(context, pname, index, val);
}

bool ValidateGetMultisamplefvRobustANGLE(const Context *context,
                                         GLenum pname,
                                         GLuint index,
                                         GLsizei bufSize,
                                         const GLsizei *length,
                                         const GLfloat *val)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateFramebufferParameteri(const Context *context, GLenum target, GLenum pname, GLint param)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (!ValidFramebufferTarget(context, target))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidFramebufferTarget);
        return false;
    }

    switch (pname)
    {
        case GL_FRAMEBUFFER_DEFAULT_WIDTH:
        {
            GLint maxWidth = context->getCaps().maxFramebufferWidth;
            if (param < 0 || param > maxWidth)
            {
                context->validationError(GL_INVALID_VALUE, kExceedsFramebufferWidth);
                return false;
            }
            break;
        }
        case GL_FRAMEBUFFER_DEFAULT_HEIGHT:
        {
            GLint maxHeight = context->getCaps().maxFramebufferHeight;
            if (param < 0 || param > maxHeight)
            {
                context->validationError(GL_INVALID_VALUE, kExceedsFramebufferHeight);
                return false;
            }
            break;
        }
        case GL_FRAMEBUFFER_DEFAULT_SAMPLES:
        {
            GLint maxSamples = context->getCaps().maxFramebufferSamples;
            if (param < 0 || param > maxSamples)
            {
                context->validationError(GL_INVALID_VALUE, kExceedsFramebufferSamples);
                return false;
            }
            break;
        }
        case GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS:
        {
            break;
        }
        case GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT:
        {
            if (!context->getExtensions().geometryShader)
            {
                context->validationError(GL_INVALID_ENUM, kGeometryShaderExtensionNotEnabled);
                return false;
            }
            GLint maxLayers = context->getCaps().maxFramebufferLayers;
            if (param < 0 || param > maxLayers)
            {
                context->validationError(GL_INVALID_VALUE, kInvalidFramebufferLayer);
                return false;
            }
            break;
        }
        default:
        {
            context->validationError(GL_INVALID_ENUM, kInvalidPname);
            return false;
        }
    }

    const Framebuffer *framebuffer = context->getState().getTargetFramebuffer(target);
    ASSERT(framebuffer);
    if (framebuffer->isDefault())
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultFramebuffer);
        return false;
    }
    return true;
}

bool ValidateGetFramebufferParameteriv(const Context *context,
                                       GLenum target,
                                       GLenum pname,
                                       const GLint *params)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (!ValidFramebufferTarget(context, target))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidFramebufferTarget);
        return false;
    }

    switch (pname)
    {
        case GL_FRAMEBUFFER_DEFAULT_WIDTH:
        case GL_FRAMEBUFFER_DEFAULT_HEIGHT:
        case GL_FRAMEBUFFER_DEFAULT_SAMPLES:
        case GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS:
            break;
        case GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT:
            if (!context->getExtensions().geometryShader)
            {
                context->validationError(GL_INVALID_ENUM, kGeometryShaderExtensionNotEnabled);
                return false;
            }
            break;
        default:
            context->validationError(GL_INVALID_ENUM, kInvalidPname);
            return false;
    }

    const Framebuffer *framebuffer = context->getState().getTargetFramebuffer(target);
    ASSERT(framebuffer);

    if (framebuffer->isDefault())
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultFramebuffer);
        return false;
    }
    return true;
}

bool ValidateGetFramebufferParameterivRobustANGLE(const Context *context,
                                                  GLenum target,
                                                  GLenum pname,
                                                  GLsizei bufSize,
                                                  const GLsizei *length,
                                                  const GLint *params)
{
    UNIMPLEMENTED();
    return false;
}

bool ValidateGetProgramResourceIndex(const Context *context,
                                     ShaderProgramID program,
                                     GLenum programInterface,
                                     const GLchar *name)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    Program *programObject = GetValidProgram(context, program);
    if (programObject == nullptr)
    {
        return false;
    }

    if (!ValidateNamedProgramInterface(programInterface))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidProgramInterface);
        return false;
    }

    return true;
}

bool ValidateBindVertexBuffer(const Context *context,
                              GLuint bindingIndex,
                              BufferID buffer,
                              GLintptr offset,
                              GLsizei stride)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (!context->isBufferGenerated(buffer))
    {
        context->validationError(GL_INVALID_OPERATION, kObjectNotGenerated);
        return false;
    }

    const Caps &caps = context->getCaps();
    if (bindingIndex >= static_cast<GLuint>(caps.maxVertexAttribBindings))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsMaxVertexAttribBindings);
        return false;
    }

    if (offset < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeOffset);
        return false;
    }

    if (stride < 0 || stride > caps.maxVertexAttribStride)
    {
        context->validationError(GL_INVALID_VALUE, kExceedsMaxVertexAttribStride);
        return false;
    }

    // [OpenGL ES 3.1] Section 10.3.1 page 244:
    // An INVALID_OPERATION error is generated if the default vertex array object is bound.
    if (context->getState().getVertexArrayId().value == 0)
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultVertexArray);
        return false;
    }

    return true;
}

bool ValidateVertexBindingDivisor(const Context *context, GLuint bindingIndex, GLuint divisor)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const Caps &caps = context->getCaps();
    if (bindingIndex >= static_cast<GLuint>(caps.maxVertexAttribBindings))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsMaxVertexAttribBindings);
        return false;
    }

    // [OpenGL ES 3.1] Section 10.3.1 page 243:
    // An INVALID_OPERATION error is generated if the default vertex array object is bound.
    if (context->getState().getVertexArrayId().value == 0)
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultVertexArray);
        return false;
    }

    return true;
}

bool ValidateVertexAttribFormat(const Context *context,
                                GLuint attribindex,
                                GLint size,
                                VertexAttribType type,
                                GLboolean normalized,
                                GLuint relativeoffset)
{
    if (!ValidateVertexAttribFormatCommon(context, relativeoffset))
    {
        return false;
    }

    return ValidateFloatVertexFormat(context, attribindex, size, type);
}

bool ValidateVertexAttribIFormat(const Context *context,
                                 GLuint attribindex,
                                 GLint size,
                                 VertexAttribType type,
                                 GLuint relativeoffset)
{
    if (!ValidateVertexAttribFormatCommon(context, relativeoffset))
    {
        return false;
    }

    return ValidateIntegerVertexFormat(context, attribindex, size, type);
}

bool ValidateVertexAttribBinding(const Context *context, GLuint attribIndex, GLuint bindingIndex)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    // [OpenGL ES 3.1] Section 10.3.1 page 243:
    // An INVALID_OPERATION error is generated if the default vertex array object is bound.
    if (context->getState().getVertexArrayId().value == 0)
    {
        context->validationError(GL_INVALID_OPERATION, kDefaultVertexArray);
        return false;
    }

    const Caps &caps = context->getCaps();
    if (attribIndex >= static_cast<GLuint>(caps.maxVertexAttributes))
    {
        context->validationError(GL_INVALID_VALUE, kIndexExceedsMaxVertexAttribute);
        return false;
    }

    if (bindingIndex >= static_cast<GLuint>(caps.maxVertexAttribBindings))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsMaxVertexAttribBindings);
        return false;
    }

    return true;
}

bool ValidateGetProgramResourceName(const Context *context,
                                    ShaderProgramID program,
                                    GLenum programInterface,
                                    GLuint index,
                                    GLsizei bufSize,
                                    const GLsizei *length,
                                    const GLchar *name)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    Program *programObject = GetValidProgram(context, program);
    if (programObject == nullptr)
    {
        return false;
    }

    if (!ValidateNamedProgramInterface(programInterface))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidProgramInterface);
        return false;
    }

    if (!ValidateProgramResourceIndex(programObject, programInterface, index))
    {
        context->validationError(GL_INVALID_VALUE, kInvalidProgramResourceIndex);
        return false;
    }

    if (bufSize < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeBufferSize);
        return false;
    }

    return true;
}

bool ValidateDispatchCompute(const Context *context,
                             GLuint numGroupsX,
                             GLuint numGroupsY,
                             GLuint numGroupsZ)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const State &state                  = context->getState();
    const ProgramExecutable *executable = state.getProgramExecutable();

    if (executable == nullptr || !executable->hasLinkedShaderStage(ShaderType::Compute))
    {
        context->validationError(GL_INVALID_OPERATION, kNoActiveProgramWithComputeShader);
        return false;
    }

    const Caps &caps = context->getCaps();
    if (numGroupsX > static_cast<GLuint>(caps.maxComputeWorkGroupCount[0]))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsComputeWorkGroupCountX);
        return false;
    }
    if (numGroupsY > static_cast<GLuint>(caps.maxComputeWorkGroupCount[1]))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsComputeWorkGroupCountY);
        return false;
    }
    if (numGroupsZ > static_cast<GLuint>(caps.maxComputeWorkGroupCount[2]))
    {
        context->validationError(GL_INVALID_VALUE, kExceedsComputeWorkGroupCountZ);
        return false;
    }

    return true;
}

bool ValidateDispatchComputeIndirect(const Context *context, GLintptr indirect)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    const State &state                  = context->getState();
    const ProgramExecutable *executable = state.getProgramExecutable();

    if (executable == nullptr || !executable->hasLinkedShaderStage(ShaderType::Compute))
    {
        context->validationError(GL_INVALID_OPERATION, kNoActiveProgramWithComputeShader);
        return false;
    }

    if (indirect < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeOffset);
        return false;
    }

    if ((indirect & (sizeof(GLuint) - 1)) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kOffsetMustBeMultipleOfUint);
        return false;
    }

    Buffer *dispatchIndirectBuffer = state.getTargetBuffer(BufferBinding::DispatchIndirect);
    if (!dispatchIndirectBuffer)
    {
        context->validationError(GL_INVALID_OPERATION, kDispatchIndirectBufferNotBound);
        return false;
    }

    CheckedNumeric<GLuint64> checkedOffset(static_cast<GLuint64>(indirect));
    auto checkedSum = checkedOffset + static_cast<GLuint64>(3 * sizeof(GLuint));
    if (!checkedSum.IsValid() ||
        checkedSum.ValueOrDie() > static_cast<GLuint64>(dispatchIndirectBuffer->getSize()))
    {
        context->validationError(GL_INVALID_OPERATION, kInsufficientBufferSize);
        return false;
    }

    return true;
}

bool ValidateBindImageTexture(const Context *context,
                              GLuint unit,
                              TextureID texture,
                              GLint level,
                              GLboolean layered,
                              GLint layer,
                              GLenum access,
                              GLenum format)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    GLuint maxImageUnits = static_cast<GLuint>(context->getCaps().maxImageUnits);
    if (unit >= maxImageUnits)
    {
        context->validationError(GL_INVALID_VALUE, kExceedsMaxImageUnits);
        return false;
    }

    if (level < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeLevel);
        return false;
    }

    if (layer < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeLayer);
        return false;
    }

    if (access != GL_READ_ONLY && access != GL_WRITE_ONLY && access != GL_READ_WRITE)
    {
        context->validationError(GL_INVALID_ENUM, kInvalidImageAccess);
        return false;
    }

    switch (format)
    {
        case GL_RGBA32F:
        case GL_RGBA16F:
        case GL_R32F:
        case GL_RGBA32UI:
        case GL_RGBA16UI:
        case GL_RGBA8UI:
        case GL_R32UI:
        case GL_RGBA32I:
        case GL_RGBA16I:
        case GL_RGBA8I:
        case GL_R32I:
        case GL_RGBA8:
        case GL_RGBA8_SNORM:
            break;
        default:
            context->validationError(GL_INVALID_VALUE, kInvalidImageFormat);
            return false;
    }

    if (texture.value != 0)
    {
        Texture *tex = context->getTexture(texture);

        if (tex == nullptr)
        {
            context->validationError(GL_INVALID_VALUE, kMissingTextureName);
            return false;
        }

        if (!tex->getImmutableFormat())
        {
            context->validationError(GL_INVALID_OPERATION, kTextureIsNotImmutable);
            return false;
        }
    }

    return true;
}

bool ValidateGetProgramResourceLocation(const Context *context,
                                        ShaderProgramID program,
                                        GLenum programInterface,
                                        const GLchar *name)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    Program *programObject = GetValidProgram(context, program);
    if (programObject == nullptr)
    {
        return false;
    }

    if (!programObject->isLinked())
    {
        context->validationError(GL_INVALID_OPERATION, kProgramNotLinked);
        return false;
    }

    if (!ValidateLocationProgramInterface(programInterface))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidProgramInterface);
        return false;
    }
    return true;
}

bool ValidateGetProgramResourceiv(const Context *context,
                                  ShaderProgramID program,
                                  GLenum programInterface,
                                  GLuint index,
                                  GLsizei propCount,
                                  const GLenum *props,
                                  GLsizei bufSize,
                                  const GLsizei *length,
                                  const GLint *params)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    Program *programObject = GetValidProgram(context, program);
    if (programObject == nullptr)
    {
        return false;
    }
    if (!ValidateProgramInterface(programInterface))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidProgramInterface);
        return false;
    }
    if (propCount <= 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidPropCount);
        return false;
    }
    if (bufSize < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeBufSize);
        return false;
    }
    if (!ValidateProgramResourceIndex(programObject, programInterface, index))
    {
        context->validationError(GL_INVALID_VALUE, kInvalidProgramResourceIndex);
        return false;
    }
    for (GLsizei i = 0; i < propCount; i++)
    {
        if (!ValidateProgramResourceProperty(context, props[i]))
        {
            context->validationError(GL_INVALID_ENUM, kInvalidProgramResourceProperty);
            return false;
        }
        if (!ValidateProgramResourcePropertyByInterface(props[i], programInterface))
        {
            context->validationError(GL_INVALID_OPERATION, kInvalidPropertyForProgramInterface);
            return false;
        }
    }
    return true;
}

bool ValidateGetProgramInterfaceiv(const Context *context,
                                   ShaderProgramID program,
                                   GLenum programInterface,
                                   GLenum pname,
                                   const GLint *params)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    Program *programObject = GetValidProgram(context, program);
    if (programObject == nullptr)
    {
        return false;
    }

    if (!ValidateProgramInterface(programInterface))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidProgramInterface);
        return false;
    }

    switch (pname)
    {
        case GL_ACTIVE_RESOURCES:
        case GL_MAX_NAME_LENGTH:
        case GL_MAX_NUM_ACTIVE_VARIABLES:
            break;

        default:
            context->validationError(GL_INVALID_ENUM, kInvalidPname);
            return false;
    }

    if (pname == GL_MAX_NAME_LENGTH && programInterface == GL_ATOMIC_COUNTER_BUFFER)
    {
        context->validationError(GL_INVALID_OPERATION, kAtomicCounterResourceName);
        return false;
    }

    if (pname == GL_MAX_NUM_ACTIVE_VARIABLES)
    {
        switch (programInterface)
        {
            case GL_ATOMIC_COUNTER_BUFFER:
            case GL_SHADER_STORAGE_BLOCK:
            case GL_UNIFORM_BLOCK:
                break;

            default:
                context->validationError(GL_INVALID_OPERATION, kMaxActiveVariablesInterface);
                return false;
        }
    }

    return true;
}

bool ValidateGetProgramInterfaceivRobustANGLE(const Context *context,
                                              ShaderProgramID program,
                                              GLenum programInterface,
                                              GLenum pname,
                                              GLsizei bufSize,
                                              const GLsizei *length,
                                              const GLint *params)
{
    UNIMPLEMENTED();
    return false;
}

static bool ValidateGenOrDeleteES31(const Context *context, GLint n)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateGenOrDelete(context, n);
}

bool ValidateGenProgramPipelines(const Context *context,
                                 GLsizei n,
                                 const ProgramPipelineID *pipelines)
{
    return ValidateGenOrDeleteES31(context, n);
}

bool ValidateDeleteProgramPipelines(const Context *context,
                                    GLsizei n,
                                    const ProgramPipelineID *pipelines)
{
    return ValidateGenOrDeleteES31(context, n);
}

bool ValidateBindProgramPipeline(const Context *context, ProgramPipelineID pipeline)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (!context->isProgramPipelineGenerated({pipeline}))
    {
        context->validationError(GL_INVALID_OPERATION, kObjectNotGenerated);
        return false;
    }

    return true;
}

bool ValidateIsProgramPipeline(const Context *context, ProgramPipelineID pipeline)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return true;
}

bool ValidateUseProgramStages(const Context *context,
                              ProgramPipelineID pipeline,
                              GLbitfield stages,
                              ShaderProgramID programId)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    // GL_INVALID_VALUE is generated if shaders contains set bits that are not recognized, and is
    // not the reserved value GL_ALL_SHADER_BITS.
    const GLbitfield knownShaderBits =
        GL_VERTEX_SHADER_BIT | GL_FRAGMENT_SHADER_BIT | GL_COMPUTE_SHADER_BIT;
    if ((stages & ~knownShaderBits) && (stages != GL_ALL_SHADER_BITS))
    {
        context->validationError(GL_INVALID_VALUE, kUnrecognizedShaderStageBit);
        return false;
    }

    // GL_INVALID_OPERATION is generated if pipeline is not a name previously returned from a call
    // to glGenProgramPipelines or if such a name has been deleted by a call to
    // glDeleteProgramPipelines.
    if (!context->isProgramPipelineGenerated({pipeline}))
    {
        context->validationError(GL_INVALID_OPERATION, kObjectNotGenerated);
        return false;
    }

    // If program is zero, or refers to a program object with no valid shader executable for a given
    // stage, it is as if the pipeline object has no programmable stage configured for the indicated
    // shader stages.
    if (programId.value == 0)
    {
        return true;
    }

    Program *program = context->getProgramNoResolveLink(programId);
    if (!program)
    {
        context->validationError(GL_INVALID_VALUE, kProgramDoesNotExist);
        return false;
    }

    // GL_INVALID_OPERATION is generated if program refers to a program object that was not linked
    // with its GL_PROGRAM_SEPARABLE status set.
    // resolveLink() may not have been called if glCreateShaderProgramv() was not used and
    // glDetachShader() was not called.
    program->resolveLink(context);
    if (!program->isSeparable())
    {
        context->validationError(GL_INVALID_OPERATION, kProgramNotSeparable);
        return false;
    }

    // GL_INVALID_OPERATION is generated if program refers to a program object that has not been
    // successfully linked.
    if (!program->isLinked())
    {
        context->validationError(GL_INVALID_OPERATION, kProgramNotLinked);
        return false;
    }

    return true;
}

bool ValidateActiveShaderProgram(const Context *context,
                                 ProgramPipelineID pipeline,
                                 ShaderProgramID programId)
{
    // An INVALID_OPERATION error is generated if pipeline is not a name returned from a previous
    // call to GenProgramPipelines or if such a name has since been deleted by
    // DeleteProgramPipelines.
    if (!context->isProgramPipelineGenerated({pipeline}))
    {
        context->validationError(GL_INVALID_OPERATION, kObjectNotGenerated);
        return false;
    }

    // An INVALID_VALUE error is generated if program is not zero and is not the name of either a
    // program or shader object.
    if ((programId.value != 0) && !context->isProgram(programId) && !context->isShader(programId))
    {
        context->validationError(GL_INVALID_VALUE, kProgramDoesNotExist);
        return false;
    }

    // An INVALID_OPERATION error is generated if program is the name of a shader object.
    if (context->isShader(programId))
    {
        context->validationError(GL_INVALID_OPERATION, kExpectedProgramName);
        return false;
    }

    // An INVALID_OPERATION error is generated if program is not zero and has not been linked, or
    // was last linked unsuccessfully. The active program is not modified.
    Program *program = context->getProgramNoResolveLink(programId);
    if ((programId.value != 0) && !program->isLinked())
    {
        context->validationError(GL_INVALID_OPERATION, kProgramNotLinked);
        return false;
    }

    return true;
}

bool ValidateCreateShaderProgramv(const Context *context,
                                  ShaderType type,
                                  GLsizei count,
                                  const GLchar *const *strings)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    // GL_INVALID_ENUM is generated if type is not an accepted shader type.
    if ((type != ShaderType::Vertex) && (type != ShaderType::Fragment) &&
        (type != ShaderType::Compute))
    {
        context->validationError(GL_INVALID_ENUM, kInvalidShaderType);
        return false;
    }

    // GL_INVALID_VALUE is generated if count is negative.
    if (count < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeCount);
        return false;
    }

    return true;
}

bool ValidateGetProgramPipelineiv(const Context *context,
                                  ProgramPipelineID pipeline,
                                  GLenum pname,
                                  const GLint *params)
{
    // An INVALID_OPERATION error is generated if pipeline is not a name returned from a previous
    // call to GenProgramPipelines or if such a name has since been deleted by
    // DeleteProgramPipelines.
    if ((pipeline.value == 0) || (!context->isProgramPipelineGenerated(pipeline)))
    {
        context->validationError(GL_INVALID_OPERATION, kProgramPipelineDoesNotExist);
        return false;
    }

    // An INVALID_ENUM error is generated if pname is not ACTIVE_PROGRAM,
    // INFO_LOG_LENGTH, VALIDATE_STATUS, or one of the type arguments in
    // table 7.1.
    switch (pname)
    {
        case GL_ACTIVE_PROGRAM:
        case GL_INFO_LOG_LENGTH:
        case GL_VALIDATE_STATUS:
        case GL_VERTEX_SHADER:
        case GL_FRAGMENT_SHADER:
        case GL_COMPUTE_SHADER:
            break;

        default:
            context->validationError(GL_INVALID_ENUM, kInvalidPname);
            return false;
    }

    return true;
}

bool ValidateValidateProgramPipeline(const Context *context, ProgramPipelineID pipeline)
{
    if (pipeline.value == 0)
    {
        return false;
    }

    if (!context->isProgramPipelineGenerated(pipeline))
    {
        context->validationError(GL_INVALID_OPERATION, kProgramPipelineDoesNotExist);
        return false;
    }

    return true;
}

bool ValidateGetProgramPipelineInfoLog(const Context *context,
                                       ProgramPipelineID pipeline,
                                       GLsizei bufSize,
                                       const GLsizei *length,
                                       const GLchar *infoLog)
{
    if (bufSize < 0)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeBufferSize);
        return false;
    }

    if (!context->isProgramPipelineGenerated(pipeline))
    {
        context->validationError(GL_INVALID_VALUE, kProgramPipelineDoesNotExist);
        return false;
    }

    return true;
}

bool ValidateMemoryBarrier(const Context *context, GLbitfield barriers)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (barriers == GL_ALL_BARRIER_BITS)
    {
        return true;
    }

    GLbitfield supported_barrier_bits =
        GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT | GL_ELEMENT_ARRAY_BARRIER_BIT | GL_UNIFORM_BARRIER_BIT |
        GL_TEXTURE_FETCH_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_COMMAND_BARRIER_BIT |
        GL_PIXEL_BUFFER_BARRIER_BIT | GL_TEXTURE_UPDATE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT |
        GL_FRAMEBUFFER_BARRIER_BIT | GL_TRANSFORM_FEEDBACK_BARRIER_BIT |
        GL_ATOMIC_COUNTER_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT;

    if (context->getExtensions().bufferStorageEXT)
    {
        supported_barrier_bits |= GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT_EXT;
    }

    if (barriers == 0 || (barriers & ~supported_barrier_bits) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidMemoryBarrierBit);
        return false;
    }

    return true;
}

bool ValidateMemoryBarrierByRegion(const Context *context, GLbitfield barriers)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    if (barriers == GL_ALL_BARRIER_BITS)
    {
        return true;
    }

    GLbitfield supported_barrier_bits = GL_ATOMIC_COUNTER_BARRIER_BIT | GL_FRAMEBUFFER_BARRIER_BIT |
                                        GL_SHADER_IMAGE_ACCESS_BARRIER_BIT |
                                        GL_SHADER_STORAGE_BARRIER_BIT |
                                        GL_TEXTURE_FETCH_BARRIER_BIT | GL_UNIFORM_BARRIER_BIT;
    if (barriers == 0 || (barriers & ~supported_barrier_bits) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kInvalidMemoryBarrierBit);
        return false;
    }

    return true;
}

bool ValidateSampleMaski(const Context *context, GLuint maskNumber, GLbitfield mask)
{
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }

    return ValidateSampleMaskiBase(context, maskNumber, mask);
}

bool ValidateMinSampleShadingOES(const Context *context, GLfloat value)
{
    if (!context->getExtensions().sampleShadingOES)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }

    return true;
}

bool ValidateFramebufferTextureEXT(const Context *context,
                                   GLenum target,
                                   GLenum attachment,
                                   TextureID texture,
                                   GLint level)
{
    if (!context->getExtensions().geometryShader)
    {
        context->validationError(GL_INVALID_OPERATION, kGeometryShaderExtensionNotEnabled);
        return false;
    }

    if (texture.value != 0)
    {
        Texture *tex = context->getTexture(texture);

        // [EXT_geometry_shader] Section 9.2.8 "Attaching Texture Images to a Framebuffer"
        // An INVALID_VALUE error is generated if <texture> is not the name of a texture object.
        // We put this validation before ValidateFramebufferTextureBase because it is an
        // INVALID_OPERATION error for both FramebufferTexture2D and FramebufferTextureLayer:
        // [OpenGL ES 3.1] Chapter 9.2.8 (FramebufferTexture2D)
        // An INVALID_OPERATION error is generated if texture is not zero, and does not name an
        // existing texture object of type matching textarget.
        // [OpenGL ES 3.1 Chapter 9.2.8 (FramebufferTextureLayer)
        // An INVALID_OPERATION error is generated if texture is non-zero and is not the name of a
        // three-dimensional or two-dimensional array texture.
        if (tex == nullptr)
        {
            context->validationError(GL_INVALID_VALUE, kInvalidTextureName);
            return false;
        }

        if (!ValidMipLevel(context, tex->getType(), level))
        {
            context->validationError(GL_INVALID_VALUE, kInvalidMipLevel);
            return false;
        }
    }

    if (!ValidateFramebufferTextureBase(context, target, attachment, texture, level))
    {
        return false;
    }

    return true;
}

// GL_OES_texture_storage_multisample_2d_array
bool ValidateTexStorage3DMultisampleOES(const Context *context,
                                        TextureType target,
                                        GLsizei samples,
                                        GLenum sizedinternalformat,
                                        GLsizei width,
                                        GLsizei height,
                                        GLsizei depth,
                                        GLboolean fixedsamplelocations)
{
    if (!context->getExtensions().textureStorageMultisample2DArrayOES)
    {
        context->validationError(GL_INVALID_ENUM, kMultisampleArrayExtensionRequired);
        return false;
    }

    if (target != TextureType::_2DMultisampleArray)
    {
        context->validationError(GL_INVALID_ENUM, kTargetMustBeTexture2DMultisampleArrayOES);
        return false;
    }

    if (width < 1 || height < 1 || depth < 1)
    {
        context->validationError(GL_INVALID_VALUE, kNegativeSize);
        return false;
    }

    if (depth > context->getCaps().maxArrayTextureLayers)
    {
        context->validationError(GL_INVALID_VALUE, kTextureDepthOutOfRange);
        return false;
    }

    return ValidateTexStorageMultisample(context, target, samples, sizedinternalformat, width,
                                         height);
}

bool ValidateTexStorageMem3DMultisampleEXT(const Context *context,
                                           TextureType target,
                                           GLsizei samples,
                                           GLenum internalFormat,
                                           GLsizei width,
                                           GLsizei height,
                                           GLsizei depth,
                                           GLboolean fixedSampleLocations,
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

bool ValidateGetProgramResourceLocationIndexEXT(const Context *context,
                                                ShaderProgramID program,
                                                GLenum programInterface,
                                                const char *name)
{
    if (!context->getExtensions().blendFuncExtended)
    {
        context->validationError(GL_INVALID_OPERATION, kExtensionNotEnabled);
        return false;
    }
    if (context->getClientVersion() < ES_3_1)
    {
        context->validationError(GL_INVALID_OPERATION, kES31Required);
        return false;
    }
    if (programInterface != GL_PROGRAM_OUTPUT)
    {
        context->validationError(GL_INVALID_ENUM, kProgramInterfaceMustBeProgramOutput);
        return false;
    }
    Program *programObject = GetValidProgram(context, program);
    if (!programObject)
    {
        return false;
    }
    if (!programObject->isLinked())
    {
        context->validationError(GL_INVALID_OPERATION, kProgramNotLinked);
        return false;
    }
    return true;
}

// GL_OES_texture_buffer
bool ValidateTexBufferOES(const Context *context,
                          TextureType target,
                          GLenum internalformat,
                          BufferID bufferPacked)
{
    if (!context->getExtensions().textureBufferOES)
    {
        context->validationError(GL_INVALID_OPERATION, kTextureBufferExtensionNotAvailable);
        return false;
    }

    return ValidateTexBufferBase(context, target, internalformat, bufferPacked);
}

bool ValidateTexBufferRangeOES(const Context *context,
                               TextureType target,
                               GLenum internalformat,
                               BufferID bufferPacked,
                               GLintptr offset,
                               GLsizeiptr size)
{
    if (!context->getExtensions().textureBufferOES)
    {
        context->validationError(GL_INVALID_OPERATION, kTextureBufferExtensionNotAvailable);
        return false;
    }

    return ValidateTexBufferRangeBase(context, target, internalformat, bufferPacked, offset, size);
}

// GL_EXT_texture_buffer
bool ValidateTexBufferEXT(const Context *context,
                          TextureType target,
                          GLenum internalformat,
                          BufferID bufferPacked)
{
    if (!context->getExtensions().textureBufferEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kTextureBufferExtensionNotAvailable);
        return false;
    }

    return ValidateTexBufferBase(context, target, internalformat, bufferPacked);
}

bool ValidateTexBufferRangeEXT(const Context *context,
                               TextureType target,
                               GLenum internalformat,
                               BufferID bufferPacked,
                               GLintptr offset,
                               GLsizeiptr size)
{
    if (!context->getExtensions().textureBufferEXT)
    {
        context->validationError(GL_INVALID_OPERATION, kTextureBufferExtensionNotAvailable);
        return false;
    }

    return ValidateTexBufferRangeBase(context, target, internalformat, bufferPacked, offset, size);
}

bool ValidateTexBufferBase(const Context *context,
                           TextureType target,
                           GLenum internalformat,
                           BufferID bufferPacked)
{
    if (target != TextureType::Buffer)
    {
        context->validationError(GL_INVALID_ENUM, kTextureBufferTarget);
        return false;
    }

    switch (internalformat)
    {
        case GL_R8:
        case GL_R16F:
        case GL_R32F:
        case GL_R8I:
        case GL_R16I:
        case GL_R32I:
        case GL_R8UI:
        case GL_R16UI:
        case GL_R32UI:
        case GL_RG8:
        case GL_RG16F:
        case GL_RG32F:
        case GL_RG8I:
        case GL_RG16I:
        case GL_RG32I:
        case GL_RG8UI:
        case GL_RG16UI:
        case GL_RG32UI:
        case GL_RGB32F:
        case GL_RGB32I:
        case GL_RGB32UI:
        case GL_RGBA8:
        case GL_RGBA16F:
        case GL_RGBA32F:
        case GL_RGBA8I:
        case GL_RGBA16I:
        case GL_RGBA32I:
        case GL_RGBA8UI:
        case GL_RGBA16UI:
        case GL_RGBA32UI:
            break;

        default:
            context->validationError(GL_INVALID_ENUM, kTextureBufferInternalFormat);
            return false;
    }

    if (bufferPacked.value != 0)
    {
        if (!context->isBufferGenerated(bufferPacked))
        {
            context->validationError(GL_INVALID_OPERATION, kTextureBufferInvalidBuffer);
            return false;
        }
    }

    return true;
}

bool ValidateTexBufferRangeBase(const Context *context,
                                TextureType target,
                                GLenum internalformat,
                                BufferID bufferPacked,
                                GLintptr offset,
                                GLsizeiptr size)
{
    const Caps &caps = context->getCaps();

    if (offset < 0 || (offset % caps.textureBufferOffsetAlignment) != 0)
    {
        context->validationError(GL_INVALID_VALUE, kTextureBufferOffsetAlignment);
        return false;
    }
    if (size <= 0)
    {
        context->validationError(GL_INVALID_VALUE, kTextureBufferSize);
        return false;
    }
    const Buffer *buffer = context->getBuffer(bufferPacked);

    if (!buffer)
    {
        context->validationError(GL_INVALID_OPERATION, kBufferNotBound);
        return false;
    }

    if (offset + size > buffer->getSize())
    {
        context->validationError(GL_INVALID_VALUE, kTextureBufferSizeOffset);
        return false;
    }

    return ValidateTexBufferBase(context, target, internalformat, bufferPacked);
}

}  // namespace gl
