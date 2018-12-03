//
// Copyright 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// ShaderStorageBufferTest:
//   Various tests related for shader storage buffers.
//

#include "test_utils/ANGLETest.h"
#include "test_utils/gl_raii.h"

using namespace angle;

namespace
{

struct MatrixCase
{
    MatrixCase(unsigned cols,
               unsigned rows,
               unsigned matrixStride,
               const char *computeShaderSource,
               const float *inputData)
        : mColumns(cols),
          mRows(rows),
          mMatrixStride(matrixStride),
          mComputeShaderSource(computeShaderSource),
          mInputdata(inputData)
    {}
    unsigned int mColumns;
    unsigned int mRows;
    unsigned int mMatrixStride;
    const char *mComputeShaderSource;
    const float *mInputdata;
    const unsigned int kBytesPerComponent = sizeof(float);
};

struct VectorCase
{
    VectorCase(unsigned components,
               const char *computeShaderSource,
               const GLuint *inputData,
               const GLuint *expectedData)
        : mComponents(components),
          mComputeShaderSource(computeShaderSource),
          mInputdata(inputData),
          mExpectedData(expectedData)
    {}
    unsigned int mComponents;
    const char *mComputeShaderSource;
    const GLuint *mInputdata;
    const GLuint *mExpectedData;
    const unsigned int kBytesPerComponent = sizeof(GLuint);
};

class ShaderStorageBufferTest31 : public ANGLETest
{
  protected:
    ShaderStorageBufferTest31()
    {
        setWindowWidth(128);
        setWindowHeight(128);
        setConfigRedBits(8);
        setConfigGreenBits(8);
        setConfigBlueBits(8);
        setConfigAlphaBits(8);
    }

    void runMatrixTest(const MatrixCase &matrixCase)
    {
        ANGLE_GL_COMPUTE_PROGRAM(program, matrixCase.mComputeShaderSource);
        glUseProgram(program);

        // Create shader storage buffer
        GLBuffer shaderStorageBuffer[2];
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, matrixCase.mRows * matrixCase.mMatrixStride,
                     matrixCase.mInputdata, GL_STATIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
        glBufferData(GL_SHADER_STORAGE_BUFFER, matrixCase.mRows * matrixCase.mMatrixStride, nullptr,
                     GL_STATIC_DRAW);

        // Bind shader storage buffer
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

        glDispatchCompute(1, 1, 1);
        glFinish();

        // Read back shader storage buffer
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
        const GLfloat *ptr = reinterpret_cast<const GLfloat *>(
            glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0,
                             matrixCase.mRows * matrixCase.mMatrixStride, GL_MAP_READ_BIT));
        for (unsigned int idx = 0; idx < matrixCase.mRows; idx++)
        {
            for (unsigned int idy = 0; idy < matrixCase.mColumns; idy++)
            {
                EXPECT_EQ(matrixCase.mInputdata[idx * (matrixCase.mMatrixStride /
                                                       matrixCase.kBytesPerComponent) +
                                                idy],
                          *(ptr + idx * (matrixCase.mMatrixStride / matrixCase.kBytesPerComponent) +
                            idy));
            }
        }

        EXPECT_GL_NO_ERROR();
    }

    void runVectorTest(const VectorCase &vectorCase)
    {
        ANGLE_GL_COMPUTE_PROGRAM(program, vectorCase.mComputeShaderSource);
        glUseProgram(program);

        // Create shader storage buffer
        GLBuffer shaderStorageBuffer[2];
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     vectorCase.mComponents * vectorCase.kBytesPerComponent, vectorCase.mInputdata,
                     GL_STATIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     vectorCase.mComponents * vectorCase.kBytesPerComponent, nullptr,
                     GL_STATIC_DRAW);

        // Bind shader storage buffer
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

        glDispatchCompute(1, 1, 1);
        glFinish();

        // Read back shader storage buffer
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
        const GLuint *ptr = reinterpret_cast<const GLuint *>(glMapBufferRange(
            GL_SHADER_STORAGE_BUFFER, 0, vectorCase.mComponents * vectorCase.kBytesPerComponent,
            GL_MAP_READ_BIT));
        for (unsigned int idx = 0; idx < vectorCase.mComponents; idx++)
        {
            EXPECT_EQ(vectorCase.mExpectedData[idx], *(ptr + idx));
        }

        EXPECT_GL_NO_ERROR();
    }
};

// Matched block names within a shader interface must match in terms of having the same number of
// declarations with the same sequence of types.
TEST_P(ShaderStorageBufferTest31, MatchedBlockNameWithDifferentMemberType)
{
    constexpr char kVS[] =
        "#version 310 es\n"
        "buffer blockName {\n"
        "    float data;\n"
        "};\n"
        "void main()\n"
        "{\n"
        "}\n";
    constexpr char kFS[] =
        "#version 310 es\n"
        "buffer blockName {\n"
        "    uint data;\n"
        "};\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(kVS, kFS);
    EXPECT_EQ(0u, program);
}

// Linking should fail if blocks in vertex shader exceed GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS.
TEST_P(ShaderStorageBufferTest31, ExceedMaxVertexShaderStorageBlocks)
{
    std::ostringstream instanceCount;
    GLint maxVertexShaderStorageBlocks = 0;
    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &maxVertexShaderStorageBlocks);
    EXPECT_GL_NO_ERROR();
    instanceCount << maxVertexShaderStorageBlocks;

    const std::string &vertexShaderSource =
        "#version 310 es\n"
        "layout(shared) buffer blockName {\n"
        "    uint data;\n"
        "} instance[" +
        instanceCount.str() +
        " + 1];\n"
        "void main()\n"
        "{\n"
        "}\n";
    constexpr char kFS[] =
        "#version 310 es\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(vertexShaderSource.c_str(), kFS);
    EXPECT_EQ(0u, program);
}

// Linking should fail if the sum of the number of active shader storage blocks exceeds
// MAX_COMBINED_SHADER_STORAGE_BLOCKS.
TEST_P(ShaderStorageBufferTest31, ExceedMaxCombinedShaderStorageBlocks)
{
    std::ostringstream vertexInstanceCount;
    GLint maxVertexShaderStorageBlocks = 0;
    glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &maxVertexShaderStorageBlocks);
    vertexInstanceCount << maxVertexShaderStorageBlocks;

    GLint maxFragmentShaderStorageBlocks = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, &maxFragmentShaderStorageBlocks);

    GLint maxCombinedShaderStorageBlocks = 0;
    glGetIntegerv(GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, &maxCombinedShaderStorageBlocks);
    EXPECT_GL_NO_ERROR();

    ASSERT_GE(maxCombinedShaderStorageBlocks, maxVertexShaderStorageBlocks);
    ASSERT_GE(maxCombinedShaderStorageBlocks, maxFragmentShaderStorageBlocks);

    // As SPEC allows MAX_VERTEX_SHADER_STORAGE_BLOCKS and MAX_FRAGMENT_SHADER_STORAGE_BLOCKS to be
    // 0, in this situation we should skip this test to prevent these unexpected compile errors.
    ANGLE_SKIP_TEST_IF(maxVertexShaderStorageBlocks == 0 || maxFragmentShaderStorageBlocks == 0);

    GLint fragmentShaderStorageBlocks =
        maxCombinedShaderStorageBlocks - maxVertexShaderStorageBlocks + 1;
    ANGLE_SKIP_TEST_IF(fragmentShaderStorageBlocks > maxFragmentShaderStorageBlocks);

    std::ostringstream fragmentInstanceCount;
    fragmentInstanceCount << fragmentShaderStorageBlocks;

    const std::string &vertexShaderSource =
        "#version 310 es\n"
        "layout(shared) buffer blockName0 {\n"
        "    uint data;\n"
        "} instance0[" +
        vertexInstanceCount.str() +
        "];\n"
        "void main()\n"
        "{\n"
        "}\n";
    const std::string &fragmentShaderSource =
        "#version 310 es\n"
        "layout(shared) buffer blockName1 {\n"
        "    uint data;\n"
        "} instance1[" +
        fragmentInstanceCount.str() +
        "];\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
    EXPECT_EQ(0u, program);
}

// Test shader storage buffer read write.
TEST_P(ShaderStorageBufferTest31, ShaderStorageBufferReadWrite)
{
    constexpr char kCS[] =
        "#version 310 es\n"
        "layout(local_size_x=1, local_size_y=1, local_size_z=1) in;\n"
        "layout(std140, binding = 1) buffer blockName {\n"
        "    uint data[2];\n"
        "} instanceName;\n"
        "void main()\n"
        "{\n"
        "    instanceName.data[0] = 3u;\n"
        "    instanceName.data[1] = 4u;\n"
        "}\n";

    ANGLE_GL_COMPUTE_PROGRAM(program, kCS);

    glUseProgram(program.get());

    constexpr unsigned int kElementCount = 2;
    // The array stride are rounded up to the base alignment of a vec4 for std140 layout.
    constexpr unsigned int kArrayStride = 16;
    // Create shader storage buffer
    GLBuffer shaderStorageBuffer;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kElementCount * kArrayStride, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer);

    // Dispath compute
    glDispatchCompute(1, 1, 1);

    glFinish();

    // Read back shader storage buffer
    constexpr unsigned int kExpectedValues[2] = {3u, 4u};
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    void *ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kElementCount * kArrayStride,
                                 GL_MAP_READ_BIT);
    for (unsigned int idx = 0; idx < kElementCount; idx++)
    {
        EXPECT_EQ(kExpectedValues[idx],
                  *(reinterpret_cast<const GLuint *>(reinterpret_cast<const GLbyte *>(ptr) +
                                                     idx * kArrayStride)));
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    EXPECT_GL_NO_ERROR();
}

// Test that access/write to vector data in shader storage buffer.
TEST_P(ShaderStorageBufferTest31, ShaderStorageBufferVector)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std140, binding = 0) buffer blockIn {
     uvec2 data;
 } instanceIn;
 layout(std140, binding = 1) buffer blockOut {
     uvec2 data;
 } instanceOut;
 void main()
 {
     instanceOut.data[0] = instanceIn.data[0];
     instanceOut.data[1] = instanceIn.data[1];
 }
 )";

    constexpr unsigned int kComponentCount         = 2;
    constexpr GLuint kInputValues[kComponentCount] = {3u, 4u};

    VectorCase vectorCase(kComponentCount, kComputeShaderSource, kInputValues, kInputValues);
    runVectorTest(vectorCase);
}

// Test that access/write to swizzle scalar data in shader storage block.
TEST_P(ShaderStorageBufferTest31, ScalarSwizzleTest)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std140, binding = 0) buffer blockIn {
     uvec2 data;
 } instanceIn;
 layout(std140, binding = 1) buffer blockOut {
     uvec2 data;
 } instanceOut;
 void main()
 {
     instanceOut.data.x = instanceIn.data.y;
     instanceOut.data.y = instanceIn.data.x;
 }
 )";

    constexpr unsigned int kComponentCount            = 2;
    constexpr GLuint kInputValues[kComponentCount]    = {3u, 4u};
    constexpr GLuint kExpectedValues[kComponentCount] = {4u, 3u};

    VectorCase vectorCase(kComponentCount, kComputeShaderSource, kInputValues, kExpectedValues);
    runVectorTest(vectorCase);
}

// Test that access/write to swizzle vector data in shader storage block.
TEST_P(ShaderStorageBufferTest31, VectorSwizzleTest)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std140, binding = 0) buffer blockIn {
     uvec2 data;
 } instanceIn;
 layout(std140, binding = 1) buffer blockOut {
     uvec2 data;
 } instanceOut;
 void main()
 {
     instanceOut.data.yx = instanceIn.data.xy;
 }
 )";

    constexpr unsigned int kComponentCount            = 2;
    constexpr GLuint kInputValues[kComponentCount]    = {3u, 4u};
    constexpr GLuint kExpectedValues[kComponentCount] = {4u, 3u};

    VectorCase vectorCase(kComponentCount, kComputeShaderSource, kInputValues, kExpectedValues);
    runVectorTest(vectorCase);
}

// Test that access/write to swizzle vector data in column_major matrix in shader storage block.
TEST_P(ShaderStorageBufferTest31, VectorSwizzleInColumnMajorMatrixTest)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std140, binding = 0) buffer blockIn {
     layout(column_major) mat2x3 data;
 } instanceIn;
 layout(std140, binding = 1) buffer blockOut {
     layout(column_major) mat2x3 data;
 } instanceOut;
 void main()
 {
     instanceOut.data[0].xyz = instanceIn.data[0].xyz;
     instanceOut.data[1].xyz = instanceIn.data[1].xyz;
 }
 )";

    constexpr unsigned int kColumns                                             = 2;
    constexpr unsigned int kRows                                                = 3;
    constexpr unsigned int kBytesPerComponent                                   = sizeof(float);
    constexpr unsigned int kMatrixStride                                        = 16;
    constexpr float kInputDada[kColumns * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.3, 0.0, 0.4, 0.5, 0.6, 0.0};
    MatrixCase matrixCase(kRows, kColumns, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to swizzle vector data in row_major matrix in shader storage block.
TEST_P(ShaderStorageBufferTest31, VectorSwizzleInRowMajorMatrixTest)
{
    ANGLE_SKIP_TEST_IF(IsAndroid());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std140, binding = 0) buffer blockIn {
     layout(row_major) mat2x3 data;
 } instanceIn;
 layout(std140, binding = 1) buffer blockOut {
     layout(row_major) mat2x3 data;
 } instanceOut;
 void main()
 {
     instanceOut.data[0].xyz = instanceIn.data[0].xyz;
     instanceOut.data[1].xyz = instanceIn.data[1].xyz;
 }
 )";

    constexpr unsigned int kColumns           = 2;
    constexpr unsigned int kRows              = 3;
    constexpr unsigned int kBytesPerComponent = sizeof(float);
    // std140 layout requires that base alignment and stride of arrays of scalars and vectors are
    // rounded up a multiple of the base alignment of a vec4.
    constexpr unsigned int kMatrixStride                                     = 16;
    constexpr float kInputDada[kRows * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.0, 0.0, 0.3, 0.4, 0.0, 0.0, 0.5, 0.6, 0.0, 0.0};
    MatrixCase matrixCase(kColumns, kRows, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to scalar data in matrix in shader storage block with row major.
TEST_P(ShaderStorageBufferTest31, ScalarDataInMatrixInSSBOWithRowMajorQualifier)
{
    // TODO(jiajia.qin@intel.com): Figure out why it fails on Intel Linux platform.
    // http://anglebug.com/1951
    ANGLE_SKIP_TEST_IF(IsIntel() && IsLinux());
    ANGLE_SKIP_TEST_IF(IsAndroid());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    layout(row_major) mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(row_major) mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data[0][0] = instanceIn.data[0][0];
    instanceOut.data[0][1] = instanceIn.data[0][1];
    instanceOut.data[0][2] = instanceIn.data[0][2];
    instanceOut.data[1][0] = instanceIn.data[1][0];
    instanceOut.data[1][1] = instanceIn.data[1][1];
    instanceOut.data[1][2] = instanceIn.data[1][2];
}
)";

    constexpr unsigned int kColumns           = 2;
    constexpr unsigned int kRows              = 3;
    constexpr unsigned int kBytesPerComponent = sizeof(float);
    // std140 layout requires that base alignment and stride of arrays of scalars and vectors are
    // rounded up a multiple of the base alignment of a vec4.
    constexpr unsigned int kMatrixStride                                     = 16;
    constexpr float kInputDada[kRows * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.0, 0.0, 0.3, 0.4, 0.0, 0.0, 0.5, 0.6, 0.0, 0.0};
    MatrixCase matrixCase(kColumns, kRows, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

TEST_P(ShaderStorageBufferTest31, VectorDataInMatrixInSSBOWithRowMajorQualifier)
{
    ANGLE_SKIP_TEST_IF(IsAndroid());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    layout(row_major) mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(row_major) mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data[0] = instanceIn.data[0];
    instanceOut.data[1] = instanceIn.data[1];
}
)";

    constexpr unsigned int kColumns           = 2;
    constexpr unsigned int kRows              = 3;
    constexpr unsigned int kBytesPerComponent = sizeof(float);
    // std140 layout requires that base alignment and stride of arrays of scalars and vectors are
    // rounded up a multiple of the base alignment of a vec4.
    constexpr unsigned int kMatrixStride                                     = 16;
    constexpr float kInputDada[kRows * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.0, 0.0, 0.3, 0.4, 0.0, 0.0, 0.5, 0.6, 0.0, 0.0};
    MatrixCase matrixCase(kColumns, kRows, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

TEST_P(ShaderStorageBufferTest31, MatrixDataInSSBOWithRowMajorQualifier)
{
    ANGLE_SKIP_TEST_IF(IsAMD() && IsWindows() && IsOpenGL());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    layout(row_major) mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(row_major) mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data = instanceIn.data;
}
)";

    constexpr unsigned int kColumns           = 2;
    constexpr unsigned int kRows              = 3;
    constexpr unsigned int kBytesPerComponent = sizeof(float);
    // std140 layout requires that base alignment and stride of arrays of scalars and vectors are
    // rounded up a multiple of the base alignment of a vec4.
    constexpr unsigned int kMatrixStride                                     = 16;
    constexpr float kInputDada[kRows * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.0, 0.0, 0.3, 0.4, 0.0, 0.0, 0.5, 0.6, 0.0, 0.0};
    MatrixCase matrixCase(kColumns, kRows, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to scalar data in structure matrix in shader storage block with row major.
TEST_P(ShaderStorageBufferTest31, ScalarDataInMatrixInStructureInSSBOWithRowMajorQualifier)
{
    // TODO(jiajia.qin@intel.com): Figure out why it fails on Intel Linux platform.
    // http://anglebug.com/1951
    ANGLE_SKIP_TEST_IF(IsIntel() && IsLinux());
    ANGLE_SKIP_TEST_IF(IsAndroid());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
struct S
{
    mat2x3 data;
};
layout(std140, binding = 0) buffer blockIn {
    layout(row_major) S s;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(row_major) S s;
} instanceOut;
void main()
{
    instanceOut.s.data[0][0] = instanceIn.s.data[0][0];
    instanceOut.s.data[0][1] = instanceIn.s.data[0][1];
    instanceOut.s.data[0][2] = instanceIn.s.data[0][2];
    instanceOut.s.data[1][0] = instanceIn.s.data[1][0];
    instanceOut.s.data[1][1] = instanceIn.s.data[1][1];
    instanceOut.s.data[1][2] = instanceIn.s.data[1][2];
}
)";

    constexpr unsigned int kColumns           = 2;
    constexpr unsigned int kRows              = 3;
    constexpr unsigned int kBytesPerComponent = sizeof(float);
    // std140 layout requires that base alignment and stride of arrays of scalars and vectors are
    // rounded up a multiple of the base alignment of a vec4.
    constexpr unsigned int kMatrixStride                                     = 16;
    constexpr float kInputDada[kRows * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.0, 0.0, 0.3, 0.4, 0.0, 0.0, 0.5, 0.6, 0.0, 0.0};
    MatrixCase matrixCase(kColumns, kRows, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to column major matrix data in shader storage buffer.
TEST_P(ShaderStorageBufferTest31, ScalarDataInMatrixInSSBO)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data[0][0] = instanceIn.data[0][0];
    instanceOut.data[0][1] = instanceIn.data[0][1];
    instanceOut.data[0][2] = instanceIn.data[0][2];
    instanceOut.data[1][0] = instanceIn.data[1][0];
    instanceOut.data[1][1] = instanceIn.data[1][1];
    instanceOut.data[1][2] = instanceIn.data[1][2];
}
)";

    constexpr unsigned int kColumns                                             = 2;
    constexpr unsigned int kRows                                                = 3;
    constexpr unsigned int kBytesPerComponent                                   = sizeof(float);
    constexpr unsigned int kMatrixStride                                        = 16;
    constexpr float kInputDada[kColumns * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.3, 0.0, 0.4, 0.5, 0.6, 0.0};
    MatrixCase matrixCase(kRows, kColumns, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

TEST_P(ShaderStorageBufferTest31, VectorDataInMatrixInSSBOWithColumnMajorQualifier)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    layout(column_major) mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(column_major) mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data[0] = instanceIn.data[0];
    instanceOut.data[1] = instanceIn.data[1];
}
)";

    constexpr unsigned int kColumns                                             = 2;
    constexpr unsigned int kRows                                                = 3;
    constexpr unsigned int kBytesPerComponent                                   = sizeof(float);
    constexpr unsigned int kMatrixStride                                        = 16;
    constexpr float kInputDada[kColumns * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.3, 0.0, 0.4, 0.5, 0.6, 0.0};
    MatrixCase matrixCase(kRows, kColumns, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

TEST_P(ShaderStorageBufferTest31, MatrixDataInSSBOWithColumnMajorQualifier)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 0) buffer blockIn {
    layout(column_major) mat2x3 data;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    layout(column_major) mat2x3 data;
} instanceOut;
void main()
{
    instanceOut.data = instanceIn.data;
}
)";

    constexpr unsigned int kColumns                                             = 2;
    constexpr unsigned int kRows                                                = 3;
    constexpr unsigned int kBytesPerComponent                                   = sizeof(float);
    constexpr unsigned int kMatrixStride                                        = 16;
    constexpr float kInputDada[kColumns * (kMatrixStride / kBytesPerComponent)] = {
        0.1, 0.2, 0.3, 0.0, 0.4, 0.5, 0.6, 0.0};
    MatrixCase matrixCase(kRows, kColumns, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to structure data in shader storage buffer.
TEST_P(ShaderStorageBufferTest31, ShaderStorageBufferStructureArray)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
struct S
{
    uvec2 uvData;
    uint uiData[2];
};
layout(std140, binding = 0) buffer blockIn {
    S s[2];
    uint lastData;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    S s[2];
    uint lastData;
} instanceOut;
void main()
{
    instanceOut.s[0].uvData = instanceIn.s[0].uvData;
    instanceOut.s[0].uiData[0] = instanceIn.s[0].uiData[0];
    instanceOut.s[0].uiData[1] = instanceIn.s[0].uiData[1];
    instanceOut.s[1].uvData = instanceIn.s[1].uvData;
    instanceOut.s[1].uiData[0] = instanceIn.s[1].uiData[0];
    instanceOut.s[1].uiData[1] = instanceIn.s[1].uiData[1];
    instanceOut.lastData = instanceIn.lastData;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);

    glUseProgram(program);

    std::array<GLuint, 4> kUVData = {{
        1u,
        2u,
        0u,
        0u,
    }};
    std::array<GLuint, 8> kUIData = {{
        3u,
        0u,
        0u,
        0u,
        4u,
        0u,
        0u,
        0u,
    }};
    GLuint kLastData              = 5u;

    constexpr unsigned int kBytesPerComponent = sizeof(GLuint);
    constexpr unsigned int kStructureStride   = 48;
    constexpr unsigned int totalSize          = kStructureStride * 2 + sizeof(kLastData);

    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
    GLint offset = 0;
    // upload data to instanceIn.s[0]
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUVData.size() * kBytesPerComponent,
                    kUVData.data());
    offset += (kUVData.size() * kBytesPerComponent);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUIData.size() * kBytesPerComponent,
                    kUIData.data());
    offset += (kUIData.size() * kBytesPerComponent);
    // upload data to instanceIn.s[1]
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUVData.size() * kBytesPerComponent,
                    kUVData.data());
    offset += (kUVData.size() * kBytesPerComponent);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUIData.size() * kBytesPerComponent,
                    kUIData.data());
    offset += (kUIData.size() * kBytesPerComponent);
    // upload data to instanceIn.lastData
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(kLastData), &kLastData);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    constexpr float kExpectedValues[5] = {1u, 2u, 3u, 4u, 5u};
    const GLuint *ptr                  = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, totalSize, GL_MAP_READ_BIT));
    // instanceOut.s[0]
    EXPECT_EQ(kExpectedValues[0], *ptr);
    EXPECT_EQ(kExpectedValues[1], *(ptr + 1));
    EXPECT_EQ(kExpectedValues[2], *(ptr + 4));
    EXPECT_EQ(kExpectedValues[3], *(ptr + 8));
    // instanceOut.s[1]
    ptr += kStructureStride / kBytesPerComponent;
    EXPECT_EQ(kExpectedValues[0], *ptr);
    EXPECT_EQ(kExpectedValues[1], *(ptr + 1));
    EXPECT_EQ(kExpectedValues[2], *(ptr + 4));
    EXPECT_EQ(kExpectedValues[3], *(ptr + 8));
    // instanceOut.lastData
    ptr += kStructureStride / kBytesPerComponent;
    EXPECT_EQ(kExpectedValues[4], *(ptr));

    EXPECT_GL_NO_ERROR();
}

// Test that access/write to array of array structure data in shader storage buffer.
TEST_P(ShaderStorageBufferTest31, ShaderStorageBufferStructureArrayOfArray)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
struct S
{
    uvec2 uvData;
    uint uiData[2];
};
layout(std140, binding = 0) buffer blockIn {
    S s[3][2];
    uint lastData;
} instanceIn;
layout(std140, binding = 1) buffer blockOut {
    S s[3][2];
    uint lastData;
} instanceOut;
void main()
{
    instanceOut.s[1][0].uvData = instanceIn.s[1][0].uvData;
    instanceOut.s[1][0].uiData[0] = instanceIn.s[1][0].uiData[0];
    instanceOut.s[1][0].uiData[1] = instanceIn.s[1][0].uiData[1];
    instanceOut.s[1][1].uvData = instanceIn.s[1][1].uvData;
    instanceOut.s[1][1].uiData[0] = instanceIn.s[1][1].uiData[0];
    instanceOut.s[1][1].uiData[1] = instanceIn.s[1][1].uiData[1];

    instanceOut.lastData = instanceIn.lastData;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);

    glUseProgram(program);

    std::array<GLuint, 4> kUVData = {{
        1u,
        2u,
        0u,
        0u,
    }};
    std::array<GLuint, 8> kUIData = {{
        3u,
        0u,
        0u,
        0u,
        4u,
        0u,
        0u,
        0u,
    }};
    GLuint kLastData              = 5u;

    constexpr unsigned int kBytesPerComponent        = sizeof(GLuint);
    constexpr unsigned int kStructureStride          = 48;
    constexpr unsigned int kStructureArrayDimension0 = 3;
    constexpr unsigned int kStructureArrayDimension1 = 2;
    constexpr unsigned int kLastDataOffset =
        kStructureStride * kStructureArrayDimension0 * kStructureArrayDimension1;
    constexpr unsigned int totalSize = kLastDataOffset + sizeof(kLastData);

    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
    // offset of instanceIn.s[1][0]
    GLint offset      = kStructureStride * (kStructureArrayDimension1 * 1 + 0);
    GLuint uintOffset = offset / kBytesPerComponent;
    // upload data to instanceIn.s[1][0]
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUVData.size() * kBytesPerComponent,
                    kUVData.data());
    offset += (kUVData.size() * kBytesPerComponent);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUIData.size() * kBytesPerComponent,
                    kUIData.data());
    offset += (kUIData.size() * kBytesPerComponent);
    // upload data to instanceIn.s[1][1]
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUVData.size() * kBytesPerComponent,
                    kUVData.data());
    offset += (kUVData.size() * kBytesPerComponent);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kUIData.size() * kBytesPerComponent,
                    kUIData.data());
    // upload data to instanceIn.lastData
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kLastDataOffset, sizeof(kLastData), &kLastData);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    constexpr float kExpectedValues[5] = {1u, 2u, 3u, 4u, 5u};
    const GLuint *ptr                  = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, totalSize, GL_MAP_READ_BIT));

    // instanceOut.s[0][0]
    EXPECT_EQ(kExpectedValues[0], *(ptr + uintOffset));
    EXPECT_EQ(kExpectedValues[1], *(ptr + uintOffset + 1));
    EXPECT_EQ(kExpectedValues[2], *(ptr + uintOffset + 4));
    EXPECT_EQ(kExpectedValues[3], *(ptr + uintOffset + 8));

    // instanceOut.s[0][1]
    EXPECT_EQ(kExpectedValues[0], *(ptr + uintOffset + 12));
    EXPECT_EQ(kExpectedValues[1], *(ptr + uintOffset + 13));
    EXPECT_EQ(kExpectedValues[2], *(ptr + uintOffset + 16));
    EXPECT_EQ(kExpectedValues[3], *(ptr + uintOffset + 20));

    // instanceOut.lastData
    EXPECT_EQ(kExpectedValues[4], *(ptr + (kLastDataOffset / kBytesPerComponent)));

    EXPECT_GL_NO_ERROR();
}

// Test that access/write to vector data in std430 shader storage block.
TEST_P(ShaderStorageBufferTest31, VectorArrayInSSBOWithStd430Qualifier)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std430, binding = 0) buffer blockIn {
    uvec2 data[2];
} instanceIn;
layout(std430, binding = 1) buffer blockOut {
    uvec2 data[2];
} instanceOut;
void main()
{
    instanceOut.data[0] = instanceIn.data[0];
    instanceOut.data[1] = instanceIn.data[1];
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);

    glUseProgram(program);

    constexpr unsigned int kElementCount      = 2;
    constexpr unsigned int kBytesPerComponent = sizeof(unsigned int);
    constexpr unsigned int kArrayStride       = 8;
    constexpr unsigned int kComponentCount    = kArrayStride / kBytesPerComponent;
    constexpr unsigned int kExpectedValues[kElementCount][kComponentCount] = {{1u, 2u}, {3u, 4u}};
    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kElementCount * kArrayStride, kExpectedValues,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kElementCount * kArrayStride, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);

    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(glMapBufferRange(
        GL_SHADER_STORAGE_BUFFER, 0, kElementCount * kArrayStride, GL_MAP_READ_BIT));
    for (unsigned int idx = 0; idx < kElementCount; idx++)
    {
        for (unsigned int idy = 0; idy < kComponentCount; idy++)
        {
            EXPECT_EQ(kExpectedValues[idx][idy], *(ptr + idx * kComponentCount + idy));
        }
    }

    EXPECT_GL_NO_ERROR();
}

// Test that access/write to matrix data in std430 shader storage block.
TEST_P(ShaderStorageBufferTest31, MatrixInSSBOWithStd430Qualifier)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std430, binding = 0) buffer blockIn {
    mat2 data;
} instanceIn;
layout(std430, binding = 1) buffer blockOut {
    mat2 data;
} instanceOut;
void main()
{
    instanceOut.data = instanceIn.data;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);

    glUseProgram(program);

    constexpr unsigned int kColumns              = 2;
    constexpr unsigned int kRows                 = 2;
    constexpr unsigned int kBytesPerComponent    = sizeof(float);
    constexpr unsigned int kMatrixStride         = kRows * kBytesPerComponent;
    constexpr float kInputDada[kColumns * kRows] = {0.1, 0.2, 0.4, 0.5};
    MatrixCase matrixCase(kRows, kColumns, kMatrixStride, kComputeShaderSource, kInputDada);
    runMatrixTest(matrixCase);
}

// Test that access/write to structure data in std430 shader storage block.
TEST_P(ShaderStorageBufferTest31, StructureInSSBOWithStd430Qualifier)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
struct S
{
    uvec2 u;
};
layout(std430, binding = 0) buffer blockIn {
    uint i1;
    S s;
    uint i2;
} instanceIn;
layout(std430, binding = 1) buffer blockOut {
    uint i1;
    S s;
    uint i2;
} instanceOut;
void main()
{
    instanceOut.i1 = instanceIn.i1;
    instanceOut.s.u = instanceIn.s.u;
    instanceOut.i2 = instanceIn.i2;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    GLuint kI1Data               = 1u;
    std::array<GLuint, 2> kUData = {{
        2u,
        3u,
    }};
    GLuint kI2Data               = 4u;

    constexpr unsigned int kBytesPerComponent    = sizeof(GLuint);
    constexpr unsigned int kStructureStartOffset = 8;
    constexpr unsigned int kStructureSize        = 8;
    constexpr unsigned int kTotalSize = kStructureStartOffset + kStructureSize + kBytesPerComponent;

    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);
    // upload data to instanceIn.i1
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, kBytesPerComponent, &kI1Data);
    // upload data to instanceIn.s.u
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kStructureStartOffset, kStructureSize, kUData.data());
    // upload data to instanceIn.i2
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kStructureStartOffset + kStructureSize,
                    kBytesPerComponent, &kI2Data);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    GLuint kExpectedValues[4] = {1u, 2u, 3u, 4u};
    const GLuint *ptr         = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kTotalSize, GL_MAP_READ_BIT));
    EXPECT_EQ(kExpectedValues[0], *ptr);
    ptr += (kStructureStartOffset / kBytesPerComponent);
    EXPECT_EQ(kExpectedValues[1], *ptr);
    EXPECT_EQ(kExpectedValues[2], *(ptr + 1));
    ptr += (kStructureSize / kBytesPerComponent);
    EXPECT_EQ(kExpectedValues[3], *ptr);

    EXPECT_GL_NO_ERROR();
}

// Test that access/write to structure of structure data in std430 shader storage block.
TEST_P(ShaderStorageBufferTest31, StructureOfStructureInSSBOWithStd430Qualifier)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
struct S2
{
    uvec3 u2;
};
struct S1
{
    uvec2 u1;
    S2 s2;
};
layout(std430, binding = 0) buffer blockIn {
    uint i1;
    S1 s1;
    uint i2;
} instanceIn;
layout(std430, binding = 1) buffer blockOut {
    uint i1;
    S1 s1;
    uint i2;
} instanceOut;
void main()
{
    instanceOut.i1 = instanceIn.i1;
    instanceOut.s1.u1 = instanceIn.s1.u1;
    instanceOut.s1.s2.u2 = instanceIn.s1.s2.u2;
    instanceOut.i2 = instanceIn.i2;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kBytesPerComponent      = sizeof(GLuint);
    constexpr unsigned int kStructureS1StartOffset = 16;
    constexpr unsigned int kStructureS2StartOffset = 32;
    constexpr unsigned int kStructureS1Size        = 32;
    constexpr unsigned int kTotalSize =
        kStructureS1StartOffset + kStructureS1Size + kBytesPerComponent;

    GLuint kI1Data                = 1u;
    std::array<GLuint, 2> kU1Data = {{2u, 3u}};
    std::array<GLuint, 3> kU2Data = {{4u, 5u, 6u}};
    GLuint kI2Data                = 7u;

    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);
    // upload data to instanceIn.i1
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, kBytesPerComponent, &kI1Data);
    // upload data to instanceIn.s1.u1
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kStructureS1StartOffset,
                    kU1Data.size() * kBytesPerComponent, kU1Data.data());
    // upload data to instanceIn.s1.s2.u2
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kStructureS2StartOffset,
                    kU2Data.size() * kBytesPerComponent, kU2Data.data());
    // upload data to instanceIn.i2
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, kStructureS1StartOffset + kStructureS1Size,
                    kBytesPerComponent, &kI2Data);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    GLuint kExpectedValues[7] = {1u, 2u, 3u, 4u, 5u, 6u, 7u};
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kTotalSize, GL_MAP_READ_BIT));
    EXPECT_EQ(kExpectedValues[0], *ptr);
    ptr += (kStructureS1StartOffset / kBytesPerComponent);
    EXPECT_EQ(kExpectedValues[1], *ptr);
    EXPECT_EQ(kExpectedValues[2], *(ptr + 1));
    ptr += ((kStructureS2StartOffset - kStructureS1StartOffset) / kBytesPerComponent);
    EXPECT_EQ(kExpectedValues[3], *ptr);
    EXPECT_EQ(kExpectedValues[4], *(ptr + 1));
    EXPECT_EQ(kExpectedValues[5], *(ptr + 2));
    ptr += ((kStructureS1Size - kStructureS2StartOffset) / kBytesPerComponent);
    EXPECT_EQ(kExpectedValues[6], *(ptr + 4));

    EXPECT_GL_NO_ERROR();
}

// Test atomic memory functions.
TEST_P(ShaderStorageBufferTest31, AtomicMemoryFunctions)
{
    // TODO(jiajia.qin@intel.com): Don't skip this test once atomic memory functions for SSBO is
    // supported on d3d backend. http://anglebug.com/1951

    ANGLE_SKIP_TEST_IF(IsD3D11());
    constexpr char kCS[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(std140, binding = 1) buffer blockName {
    uint data[2];
} instanceName;

void main()
{
    instanceName.data[0] = 0u;
    instanceName.data[1] = 0u;
    atomicAdd(instanceName.data[0], 5u);
    atomicMax(instanceName.data[1], 7u);
})";

    ANGLE_GL_COMPUTE_PROGRAM(program, kCS);

    glUseProgram(program.get());

    constexpr unsigned int kElementCount = 2;
    // The array stride are rounded up to the base alignment of a vec4 for std140 layout.
    constexpr unsigned int kArrayStride = 16;
    // Create shader storage buffer
    GLBuffer shaderStorageBuffer;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kElementCount * kArrayStride, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer);

    // Dispath compute
    glDispatchCompute(1, 1, 1);

    glFinish();

    // Read back shader storage buffer
    constexpr unsigned int kExpectedValues[2] = {5u, 7u};
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    void *ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kElementCount * kArrayStride,
                                 GL_MAP_READ_BIT);
    for (unsigned int idx = 0; idx < kElementCount; idx++)
    {
        EXPECT_EQ(kExpectedValues[idx],
                  *(reinterpret_cast<const GLuint *>(reinterpret_cast<const GLbyte *>(ptr) +
                                                     idx * kArrayStride)));
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    EXPECT_GL_NO_ERROR();
}

// Test multiple storage buffers work correctly when program switching. In angle, storage buffer
// bindings are updated accord to current program. If switch program, need to update storage buffer
// bindings again.
TEST_P(ShaderStorageBufferTest31, MultiStorageBuffersForMultiPrograms)
{
    constexpr char kCS1[] = R"(#version 310 es
layout(local_size_x=3, local_size_y=1, local_size_z=1) in;
layout(binding = 1) buffer Output {
    uint result1[];
} sb_out1;
void main()
{
    highp uint offset = gl_LocalInvocationID.x;
    sb_out1.result1[gl_LocalInvocationIndex] = gl_LocalInvocationIndex + 1u;
})";

    constexpr char kCS2[] = R"(#version 310 es
layout(local_size_x=3, local_size_y=1, local_size_z=1) in;
layout(binding = 2) buffer Output {
    uint result2[];
} sb_out2;
void main()
{
    highp uint offset = gl_LocalInvocationID.x;
    sb_out2.result2[gl_LocalInvocationIndex] = gl_LocalInvocationIndex + 2u;
})";

    constexpr unsigned int numInvocations = 3;
    int arrayStride1 = 0, arrayStride2 = 0;
    GLenum props[] = {GL_ARRAY_STRIDE};
    GLBuffer shaderStorageBuffer1, shaderStorageBuffer2;

    ANGLE_GL_COMPUTE_PROGRAM(program1, kCS1);
    ANGLE_GL_COMPUTE_PROGRAM(program2, kCS2);
    EXPECT_GL_NO_ERROR();

    unsigned int outVarIndex1 =
        glGetProgramResourceIndex(program1.get(), GL_BUFFER_VARIABLE, "Output.result1");
    glGetProgramResourceiv(program1.get(), GL_BUFFER_VARIABLE, outVarIndex1, 1, props, 1, 0,
                           &arrayStride1);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer1);
    glBufferData(GL_SHADER_STORAGE_BUFFER, numInvocations * arrayStride1, nullptr, GL_STREAM_READ);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer1);
    EXPECT_GL_NO_ERROR();

    unsigned int outVarIndex2 =
        glGetProgramResourceIndex(program2.get(), GL_BUFFER_VARIABLE, "Output.result2");
    glGetProgramResourceiv(program2.get(), GL_BUFFER_VARIABLE, outVarIndex2, 1, props, 1, 0,
                           &arrayStride2);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer2);
    glBufferData(GL_SHADER_STORAGE_BUFFER, numInvocations * arrayStride2, nullptr, GL_STREAM_READ);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, shaderStorageBuffer2);
    EXPECT_GL_NO_ERROR();

    glUseProgram(program1.get());
    glDispatchCompute(1, 1, 1);
    EXPECT_GL_NO_ERROR();
    glUseProgram(program2.get());
    glDispatchCompute(1, 1, 1);
    EXPECT_GL_NO_ERROR();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer1);
    const void *ptr1 =
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * arrayStride1, GL_MAP_READ_BIT);
    for (unsigned int idx = 0; idx < numInvocations; idx++)
    {
        EXPECT_EQ(idx + 1, *((const GLuint *)((const GLbyte *)ptr1 + idx * arrayStride1)));
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    EXPECT_GL_NO_ERROR();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer2);
    const void *ptr2 =
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * arrayStride2, GL_MAP_READ_BIT);
    EXPECT_GL_NO_ERROR();
    for (unsigned int idx = 0; idx < numInvocations; idx++)
    {
        EXPECT_EQ(idx + 2, *((const GLuint *)((const GLbyte *)ptr2 + idx * arrayStride2)));
    }
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    EXPECT_GL_NO_ERROR();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    EXPECT_GL_NO_ERROR();
}

// Test that function calling is supported in SSBO access chain.
TEST_P(ShaderStorageBufferTest31, FunctionCallInSSBOAccessChain)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout (local_size_x=4) in;
highp uint getIndex (in highp uvec2 localID, uint element)
{
    return localID.x + element;
}
layout(binding=0, std430) buffer Storage
{
    highp uint values[];
} sb_store;

void main()
{
    sb_store.values[getIndex(gl_LocalInvocationID.xy, 0u)] = gl_LocalInvocationIndex;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    EXPECT_GL_NO_ERROR();
}

// Test that unary operator is supported in SSBO access chain.
TEST_P(ShaderStorageBufferTest31, UnaryOperatorInSSBOAccessChain)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout (local_size_x=4) in;
layout(binding=0, std430) buffer Storage
{
    highp uint values[];
} sb_store;

void main()
{
    uint invocationNdx = gl_LocalInvocationIndex;
    sb_store.values[++invocationNdx] = invocationNdx;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    EXPECT_GL_NO_ERROR();
}

// Test that ternary operator is supported in SSBO access chain.
TEST_P(ShaderStorageBufferTest31, TernaryOperatorInSSBOAccessChain)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout (local_size_x=4) in;
layout(binding=0, std430) buffer Storage
{
    highp uint values[];
} sb_store;

void main()
{
    sb_store.values[gl_LocalInvocationIndex > 2u ? gl_NumWorkGroups.x : gl_NumWorkGroups.y]
            = gl_LocalInvocationIndex;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    EXPECT_GL_NO_ERROR();
}

TEST_P(ShaderStorageBufferTest31, LoadAndStoreBooleanValue)
{
    // TODO(jiajia.qin@intel.com): Figure out why it fails on Intel Linux platform.
    // http://anglebug.com/1951
    ANGLE_SKIP_TEST_IF(IsIntel() && IsLinux());

    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout (local_size_x=1) in;
layout(binding=0, std140) buffer Storage0
{
    bool b1;
    bvec2 b2;
} sb_load;
layout(binding=1, std140) buffer Storage1
{
    bool b1;
    bvec2 b2;
} sb_store;
void main()
{
   sb_store.b1 = sb_load.b1;
   sb_store.b2 = sb_load.b2;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    EXPECT_GL_NO_ERROR();

    glUseProgram(program);

    constexpr GLuint kB1Value                 = 1u;
    constexpr GLuint kB2Value[2]              = {0u, 1u};
    constexpr unsigned int kBytesPerComponent = sizeof(GLuint);
    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * kBytesPerComponent, nullptr, GL_STATIC_DRAW);
    GLint offset = 0;
    // upload data to sb_load.b1
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kBytesPerComponent, &kB1Value);
    offset += kBytesPerComponent;
    // upload data to sb_load.b2
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, 2 * kBytesPerComponent, kB2Value);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * kBytesPerComponent, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    const GLboolean *ptr = reinterpret_cast<const GLboolean *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 3 * kBytesPerComponent, GL_MAP_READ_BIT));
    EXPECT_EQ(GL_TRUE, *ptr);
    ptr += kBytesPerComponent;
    EXPECT_EQ(GL_FALSE, *ptr);
    ptr += kBytesPerComponent;
    EXPECT_EQ(GL_TRUE, *ptr);

    EXPECT_GL_NO_ERROR();
}

// Test that non-structure array of arrays is supported in SSBO.
TEST_P(ShaderStorageBufferTest31, SimpleArrayOfArrays)
{
    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout (local_size_x=1) in;
layout(binding=0, std140) buffer Storage0
{
    uint a[2][2][2];
    uint b;
} sb_load;
layout(binding=1, std140) buffer Storage1
{
    uint a[2][2][2];
    uint b;
} sb_store;
void main()
{
   sb_store.a[0][0][0] = sb_load.a[0][0][0];
   sb_store.a[0][0][1] = sb_load.a[0][0][1];
   sb_store.a[0][1][0] = sb_load.a[0][1][0];
   sb_store.a[0][1][1] = sb_load.a[0][1][1];
   sb_store.a[1][0][0] = sb_load.a[1][0][0];
   sb_store.a[1][0][1] = sb_load.a[1][0][1];
   sb_store.a[1][1][0] = sb_load.a[1][1][0];
   sb_store.a[1][1][1] = sb_load.a[1][1][1];
   sb_store.b = sb_load.b;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kBytesPerComponent = sizeof(GLuint);
    // The array stride are rounded up to the base alignment of a vec4 for std140 layout.
    constexpr unsigned int kArrayStride                 = 16;
    constexpr unsigned int kDimension0                  = 2;
    constexpr unsigned int kDimension1                  = 2;
    constexpr unsigned int kDimension2                  = 2;
    constexpr unsigned int kAElementCount               = kDimension0 * kDimension1 * kDimension2;
    constexpr unsigned int kAComponentCountPerDimension = kArrayStride / kBytesPerComponent;
    constexpr unsigned int kTotalSize = kArrayStride * kAElementCount + kBytesPerComponent;

    constexpr GLuint kInputADatas[kAElementCount * kAComponentCountPerDimension] = {
        1u, 0u, 0u, 0u, 2u, 0u, 0u, 0u, 3u, 0u, 0u, 0u, 4u, 0u, 0u, 0u,
        5u, 0u, 0u, 0u, 6u, 0u, 0u, 0u, 7u, 0u, 0u, 0u, 8u, 0u, 0u, 0u};
    constexpr GLuint kInputBData = 9u;

    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);
    GLint offset = 0;
    // upload data to sb_load.a
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kAElementCount * kArrayStride, kInputADatas);
    offset += (kAElementCount * kArrayStride);
    // upload data to sb_load.b
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, kBytesPerComponent, &kInputBData);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kTotalSize, nullptr, GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    constexpr GLuint kExpectedADatas[kAElementCount] = {1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u};
    const GLuint *ptr                                = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kTotalSize, GL_MAP_READ_BIT));
    for (unsigned i = 0u; i < kDimension0; i++)
    {
        for (unsigned j = 0u; j < kDimension1; j++)
        {
            for (unsigned k = 0u; k < kDimension2; k++)
            {
                unsigned index = i * (kDimension1 * kDimension2) + j * kDimension2 + k;
                EXPECT_EQ(kExpectedADatas[index],
                          *(ptr + index * (kArrayStride / kBytesPerComponent)));
            }
        }
    }

    ptr += (kAElementCount * (kArrayStride / kBytesPerComponent));
    EXPECT_EQ(kInputBData, *ptr);

    EXPECT_GL_NO_ERROR();
}

// Test that the length of unsized array is supported.
TEST_P(ShaderStorageBufferTest31, UnsizedArrayLength)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout (local_size_x=1) in;
layout(std430, binding = 0) buffer Storage0 {
  uint buf1[2];
  uint buf2[];
} sb_load;
layout(std430, binding = 1) buffer Storage1 {
  int unsizedArrayLength;
  uint buf1[2];
  uint buf2[];
} sb_store;

void main()
{
  sb_store.unsizedArrayLength = sb_store.buf2.length();
  for (int i = 0; i < sb_load.buf1.length(); i++) {
    sb_store.buf1[i] = sb_load.buf1[i];
  }
  for (int i = 0; i < sb_load.buf2.length(); i++) {
    sb_store.buf2[i] = sb_load.buf2[i];
  }
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kBytesPerComponent                       = sizeof(unsigned int);
    constexpr unsigned int kLoadBlockElementCount                   = 5;
    constexpr unsigned int kStoreBlockElementCount                  = 6;
    constexpr unsigned int kInputValues[kLoadBlockElementCount]     = {1u, 2u, 3u, 4u, 5u};
    constexpr unsigned int kExpectedValues[kStoreBlockElementCount] = {3u, 1u, 2u, 3u, 4u, 5u};
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kLoadBlockElementCount * kBytesPerComponent,
                 &kInputValues, GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kStoreBlockElementCount * kBytesPerComponent, nullptr,
                 GL_STATIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kStoreBlockElementCount * kBytesPerComponent,
                         GL_MAP_READ_BIT));
    for (unsigned int i = 0; i < kStoreBlockElementCount; i++)
    {
        EXPECT_EQ(kExpectedValues[i], *(ptr + i));
    }

    EXPECT_GL_NO_ERROR();
}

// Test that compond assignment operator for buffer variable is correctly handled.
TEST_P(ShaderStorageBufferTest31, CompoundAssignmentOperator)
{
    // http://anglebug.com/2990
    ANGLE_SKIP_TEST_IF(IsD3D11());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout (local_size_x=1) in;
layout(binding=0, std140) buffer Storage0
{
    uint b;
} sb_load;
layout(binding=1, std140) buffer Storage1
{
    uint b;
} sb_store;
void main()
{
    uint temp = 2u;
    temp += sb_load.b;
    sb_store.b += temp;
    sb_store.b += sb_load.b;
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kBytesPerComponent = sizeof(unsigned int);
    constexpr unsigned int kInputValue        = 1u;
    constexpr unsigned int kExpectedValue     = 5u;
    GLBuffer shaderStorageBuffer[2];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kBytesPerComponent, &kInputValue, GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kBytesPerComponent, &kInputValue, GL_STATIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, kBytesPerComponent, GL_MAP_READ_BIT));
    EXPECT_EQ(kExpectedValue, *ptr);

    EXPECT_GL_NO_ERROR();
}

// Test that readonly binary operator for buffer variable is correctly handled.
TEST_P(ShaderStorageBufferTest31, ReadonlyBinaryOperator)
{
    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
 layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
 layout(std430, binding = 0) buffer blockIn1 {
     uvec2 data1;
 };
 layout(std430, binding = 1) buffer blockIn2 {
     uvec2 data2;
 };
 layout(std430, binding = 2) buffer blockIn3 {
     uvec2 data;
 } instanceIn3;
 layout(std430, binding = 3) buffer blockOut {
     uvec2 data;
 } instanceOut;
 void main()
 {
     instanceOut.data = data1 + data2 + instanceIn3.data;
 }
 )";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kComponentCount                = 2;
    constexpr unsigned int kBytesPerComponent             = sizeof(unsigned int);
    constexpr unsigned int kInputValues1[kComponentCount] = {1u, 2u};
    constexpr unsigned int kInputValues2[kComponentCount] = {3u, 4u};
    constexpr unsigned int kInputValues3[kComponentCount] = {5u, 6u};
    // Create shader storage buffer
    GLBuffer shaderStorageBuffer[4];
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kComponentCount * kBytesPerComponent, kInputValues1,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kComponentCount * kBytesPerComponent, kInputValues2,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[2]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kComponentCount * kBytesPerComponent, kInputValues3,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[3]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, kComponentCount * kBytesPerComponent, nullptr,
                 GL_STATIC_DRAW);

    // Bind shader storage buffer
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer[0]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shaderStorageBuffer[1]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, shaderStorageBuffer[2]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, shaderStorageBuffer[3]);

    glDispatchCompute(1, 1, 1);
    glFinish();

    // Read back shader storage buffer
    constexpr unsigned int kExpectedValues[kComponentCount] = {9u, 12u};
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer[3]);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(glMapBufferRange(
        GL_SHADER_STORAGE_BUFFER, 0, kComponentCount * kBytesPerComponent, GL_MAP_READ_BIT));
    for (unsigned int idx = 0; idx < kComponentCount; idx++)
    {
        EXPECT_EQ(kExpectedValues[idx], *(ptr + idx));
    }

    EXPECT_GL_NO_ERROR();
}

// Test that ssbo as an argument of a function can be translated.
TEST_P(ShaderStorageBufferTest31, SSBOAsFunctionArgument)
{
    // http://anglebug.com/2990
    ANGLE_SKIP_TEST_IF(IsD3D11());

    constexpr char kComputeShaderSource[] =
        R"(#version 310 es
layout(local_size_x = 1) in;

layout(std430, binding = 0) buffer Block
{
    uint var1;
    uint var2;
};

bool compare(uint a, uint b)
{
    return a == b;
}

uint increase(inout uint a)
{
    a++;
    return a;
}

void main(void)
{
    bool isEqual = compare(var1, 2u);
    if (isEqual)
    {
        var2 += increase(var1);
    }
}
)";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    glUseProgram(program);

    constexpr unsigned int kBytesPerComponent = sizeof(unsigned int);
    constexpr unsigned int kInputValues[2]    = {2u, 2u};
    constexpr unsigned int kExpectedValues[2] = {3u, 5u};
    GLBuffer shaderStorageBuffer;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 2 * kBytesPerComponent, &kInputValues, GL_STATIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shaderStorageBuffer);

    glDispatchCompute(1, 1, 1);
    glFinish();

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, shaderStorageBuffer);
    const GLuint *ptr = reinterpret_cast<const GLuint *>(
        glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, 2 * kBytesPerComponent, GL_MAP_READ_BIT));
    EXPECT_EQ(kExpectedValues[0], *ptr);
    EXPECT_EQ(kExpectedValues[1], *(ptr + 1));

    EXPECT_GL_NO_ERROR();
}

ANGLE_INSTANTIATE_TEST(ShaderStorageBufferTest31, ES31_OPENGL(), ES31_OPENGLES(), ES31_D3D11());

}  // namespace
