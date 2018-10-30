//
// Copyright (c) 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// LinkProgramPerfTest:
//   Performance tests compiling a lot of shaders.
//

#include "ANGLEPerfTest.h"

#include <array>

#include "common/vector_utils.h"
#include "shader_utils.h"

using namespace angle;

namespace
{

enum class LinkProgramOption
{
    CompileOnly,
    CompileAndLink,

    Unspecified
};

struct LinkProgramParams final : public RenderTestParams
{
    LinkProgramParams(LinkProgramOption optionIn)
    {
        iterationsPerStep = 1;

        majorVersion = 2;
        minorVersion = 0;
        windowWidth  = 256;
        windowHeight = 256;
        option       = optionIn;
    }

    std::string suffix() const override
    {
        std::stringstream strstr;
        strstr << RenderTestParams::suffix();

        if (option == LinkProgramOption::CompileOnly)
        {
            strstr << "_compile_only";
        }

        if (eglParameters.deviceType == EGL_PLATFORM_ANGLE_DEVICE_TYPE_NULL_ANGLE)
        {
            strstr << "_null";
        }

        return strstr.str();
    }

    LinkProgramOption option;
};

std::ostream &operator<<(std::ostream &os, const LinkProgramParams &params)
{
    os << params.suffix().substr(1);
    return os;
}

class LinkProgramBenchmark : public ANGLERenderTest,
                             public ::testing::WithParamInterface<LinkProgramParams>
{
  public:
    LinkProgramBenchmark();

    void initializeBenchmark() override;
    void destroyBenchmark() override;
    void drawBenchmark() override;

  protected:
    GLuint mVertexBuffer = 0;
};

LinkProgramBenchmark::LinkProgramBenchmark() : ANGLERenderTest("LinkProgram", GetParam())
{
}

void LinkProgramBenchmark::initializeBenchmark()
{
    std::array<Vector3, 6> vertices = {{Vector3(-1.0f, 1.0f, 0.5f), Vector3(-1.0f, -1.0f, 0.5f),
                                        Vector3(1.0f, -1.0f, 0.5f), Vector3(-1.0f, 1.0f, 0.5f),
                                        Vector3(1.0f, -1.0f, 0.5f), Vector3(1.0f, 1.0f, 0.5f)}};

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(),
                 GL_STATIC_DRAW);
};

void LinkProgramBenchmark::destroyBenchmark()
{
    glDeleteBuffers(1, &mVertexBuffer);
}

void LinkProgramBenchmark::drawBenchmark()
{
    static const char *vertexShader =
        "attribute vec2 position;\n"
        "void main() {\n"
        "    gl_Position = vec4(position, 0, 1);\n"
        "}";
    static const char *fragmentShader =
        "precision mediump float;\n"
        "void main() {\n"
        "    gl_FragColor = vec4(1, 0, 0, 1);\n"
        "}";
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    ASSERT_NE(0u, vs);
    ASSERT_NE(0u, fs);
    if (GetParam().option == LinkProgramOption::CompileOnly)
    {
        glDeleteShader(vs);
        glDeleteShader(fs);
        return;
    }

    GLuint program = glCreateProgram();
    ASSERT_NE(0u, program);

    glAttachShader(program, vs);
    glDeleteShader(vs);
    glAttachShader(program, fs);
    glDeleteShader(fs);
    glLinkProgram(program);
    glUseProgram(program);

    GLint positionLoc = glGetAttribLocation(program, "position");
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 8, nullptr);
    glEnableVertexAttribArray(positionLoc);

    // Draw with the program to ensure the shader gets compiled and used.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDeleteProgram(program);
}

using namespace egl_platform;

LinkProgramParams LinkProgramD3D11Params(LinkProgramOption option)
{
    LinkProgramParams params(option);
    params.eglParameters = D3D11();
    return params;
}

LinkProgramParams LinkProgramD3D9Params(LinkProgramOption option)
{
    LinkProgramParams params(option);
    params.eglParameters = D3D9();
    return params;
}

LinkProgramParams LinkProgramOpenGLOrGLESParams(LinkProgramOption option)
{
    LinkProgramParams params(option);
    params.eglParameters = OPENGL_OR_GLES(false);
    return params;
}

LinkProgramParams LinkProgramVulkanParams(LinkProgramOption option)
{
    LinkProgramParams params(option);
    params.eglParameters = VULKAN();
    return params;
}

TEST_P(LinkProgramBenchmark, Run)
{
    run();
}

ANGLE_INSTANTIATE_TEST(LinkProgramBenchmark,
                       LinkProgramD3D11Params(LinkProgramOption::CompileOnly),
                       LinkProgramD3D9Params(LinkProgramOption::CompileOnly),
                       LinkProgramOpenGLOrGLESParams(LinkProgramOption::CompileOnly),
                       LinkProgramVulkanParams(LinkProgramOption::CompileOnly),
                       LinkProgramD3D11Params(LinkProgramOption::CompileAndLink),
                       LinkProgramD3D9Params(LinkProgramOption::CompileAndLink),
                       LinkProgramOpenGLOrGLESParams(LinkProgramOption::CompileAndLink),
                       LinkProgramVulkanParams(LinkProgramOption::CompileAndLink));

}  // anonymous namespace
