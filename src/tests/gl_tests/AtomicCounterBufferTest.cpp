//
// Copyright 2017 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// AtomicCounterBufferTest:
//   Various tests related for atomic counter buffers.
//

#include "test_utils/ANGLETest.h"
#include "test_utils/gl_raii.h"

using namespace angle;

namespace
{

class AtomicCounterBufferTest : public ANGLETest
{
  protected:
    AtomicCounterBufferTest()
    {
        setWindowWidth(128);
        setWindowHeight(128);
        setConfigRedBits(8);
        setConfigGreenBits(8);
        setConfigBlueBits(8);
        setConfigAlphaBits(8);
    }
};

// Test GL_ATOMIC_COUNTER_BUFFER is not supported with version lower than ES31.
TEST_P(AtomicCounterBufferTest, AtomicCounterBufferBindings)
{
    ASSERT_EQ(3, getClientMajorVersion());
    GLBuffer atomicCounterBuffer;
    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicCounterBuffer.get());
    if (getClientMinorVersion() < 1)
    {
        EXPECT_GL_ERROR(GL_INVALID_ENUM);
    }
    else
    {
        EXPECT_GL_NO_ERROR();
    }
}

class AtomicCounterBufferTest31 : public AtomicCounterBufferTest
{};

// Linking should fail if counters in vertex shader exceed gl_MaxVertexAtomicCounters.
TEST_P(AtomicCounterBufferTest31, ExceedMaxVertexAtomicCounters)
{
    const std::string &vertexShaderSource =
        "#version 310 es\n"
        "layout(binding = 0) uniform atomic_uint foo[gl_MaxVertexAtomicCounters + 1];\n"
        "void main()\n"
        "{\n"
        "    atomicCounterIncrement(foo[0]);\n"
        "}\n";
    const std::string &fragmentShaderSource =
        "#version 310 es\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(vertexShaderSource, fragmentShaderSource);
    EXPECT_EQ(0u, program);
}

// Counters matching across shader stages should fail if offsets aren't all specified.
// GLSL ES Spec 3.10.4, section 9.2.1.
TEST_P(AtomicCounterBufferTest31, OffsetNotAllSpecified)
{
    const std::string &vertexShaderSource =
        "#version 310 es\n"
        "layout(binding = 0, offset = 4) uniform atomic_uint foo;\n"
        "void main()\n"
        "{\n"
        "    atomicCounterIncrement(foo);\n"
        "}\n";
    const std::string &fragmentShaderSource =
        "#version 310 es\n"
        "layout(binding = 0) uniform atomic_uint foo;\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(vertexShaderSource, fragmentShaderSource);
    EXPECT_EQ(0u, program);
}

// Counters matching across shader stages should fail if offsets aren't all specified with same
// value.
TEST_P(AtomicCounterBufferTest31, OffsetNotAllSpecifiedWithSameValue)
{
    const std::string &vertexShaderSource =
        "#version 310 es\n"
        "layout(binding = 0, offset = 4) uniform atomic_uint foo;\n"
        "void main()\n"
        "{\n"
        "    atomicCounterIncrement(foo);\n"
        "}\n";
    const std::string &fragmentShaderSource =
        "#version 310 es\n"
        "layout(binding = 0, offset = 8) uniform atomic_uint foo;\n"
        "void main()\n"
        "{\n"
        "}\n";

    GLuint program = CompileProgram(vertexShaderSource, fragmentShaderSource);
    EXPECT_EQ(0u, program);
}

// Tests atomic counter reads using compute shaders. Used as a sanity check for the translator.
TEST_P(AtomicCounterBufferTest31, AtomicCounterReadCompute)
{
    // Skipping due to a bug on the Adreno OpenGLES Android driver.
    // http://anglebug.com/2925
    ANGLE_SKIP_TEST_IF(IsAndroid() && IsAdreno() && IsOpenGLES());

    constexpr char kComputeShaderSource[] = R"(#version 310 es
layout(local_size_x=1, local_size_y=1, local_size_z=1) in;
layout(binding = 0, offset = 8) uniform atomic_uint ac[3];

void atomicCounterInFunction(in atomic_uint counter[3])
{
    atomicCounter(counter[0]);
}

void main()
{
    atomicCounterInFunction(ac);
    atomicCounter(ac[gl_LocalInvocationIndex + 1u]);
})";

    ANGLE_GL_COMPUTE_PROGRAM(program, kComputeShaderSource);
    EXPECT_GL_NO_ERROR();
}

// Test atomic counter read.
TEST_P(AtomicCounterBufferTest31, AtomicCounterRead)
{
    // Skipping test while we work on enabling atomic counter buffer support in th D3D renderer.
    // http://anglebug.com/1729
    ANGLE_SKIP_TEST_IF(IsD3D11());

    const std::string &fragShader =
        "#version 310 es\n"
        "precision highp float;\n"
        "layout(binding = 0, offset = 4) uniform atomic_uint ac;\n"
        "out highp vec4 my_color;\n"
        "void main()\n"
        "{\n"
        "    my_color = vec4(0.0);\n"
        "    uint a1 = atomicCounter(ac);\n"
        "    if (a1 == 3u) my_color = vec4(1.0);\n"
        "}\n";

    ANGLE_GL_PROGRAM(program, essl31_shaders::vs::Simple(), fragShader);

    glUseProgram(program.get());

    // The initial value of counter 'ac' is 3u.
    unsigned int bufferData[3] = {11u, 3u, 1u};
    GLBuffer atomicCounterBuffer;
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicCounterBuffer);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicCounterBuffer);

    drawQuad(program.get(), essl31_shaders::PositionAttrib(), 0.0f);
    ASSERT_GL_NO_ERROR();
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::white);
}

// Test atomic counter increment and decrement.
TEST_P(AtomicCounterBufferTest31, AtomicCounterIncrementAndDecrement)
{
    // Skipping test while we work on enabling atomic counter buffer support in th D3D renderer.
    // http://anglebug.com/1729
    ANGLE_SKIP_TEST_IF(IsD3D11());

    const std::string &csSource =
        "#version 310 es\n"
        "layout(local_size_x=1, local_size_y=1, local_size_z=1) in;\n"
        "layout(binding = 0, offset = 4) uniform atomic_uint ac[2];\n"
        "void main()\n"
        "{\n"
        "    atomicCounterIncrement(ac[0]);\n"
        "    atomicCounterDecrement(ac[1]);\n"
        "}\n";

    ANGLE_GL_COMPUTE_PROGRAM(program, csSource);

    glUseProgram(program.get());

    // The initial value of 'ac[0]' is 3u, 'ac[1]' is 1u.
    unsigned int bufferData[3] = {11u, 3u, 1u};
    GLBuffer atomicCounterBuffer;
    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicCounterBuffer);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(bufferData), bufferData, GL_STATIC_DRAW);

    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, atomicCounterBuffer);

    glDispatchCompute(1, 1, 1);
    EXPECT_GL_NO_ERROR();

    glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomicCounterBuffer);
    void *mappedBuffer =
        glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint) * 3, GL_MAP_READ_BIT);
    memcpy(bufferData, mappedBuffer, sizeof(bufferData));
    glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);

    EXPECT_EQ(11u, bufferData[0]);
    EXPECT_EQ(4u, bufferData[1]);
    EXPECT_EQ(0u, bufferData[2]);
}

ANGLE_INSTANTIATE_TEST(AtomicCounterBufferTest,
                       ES3_OPENGL(),
                       ES3_OPENGLES(),
                       ES31_OPENGL(),
                       ES31_OPENGLES(),
                       ES31_D3D11());
ANGLE_INSTANTIATE_TEST(AtomicCounterBufferTest31, ES31_OPENGL(), ES31_OPENGLES(), ES31_D3D11());

}  // namespace
