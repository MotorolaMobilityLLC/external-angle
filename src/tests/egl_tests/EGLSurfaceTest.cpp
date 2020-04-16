//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// EGLSurfaceTest:
//   Tests pertaining to egl::Surface.
//

#include <gtest/gtest.h>

#include <vector>

#include "common/Color.h"
#include "common/platform.h"
#include "test_utils/ANGLETest.h"
#include "util/EGLWindow.h"
#include "util/OSWindow.h"
#include "util/Timer.h"

#if defined(ANGLE_ENABLE_D3D11)
#    define INITGUID
#    include <guiddef.h>

#    include <d3d11.h>
#    include <dcomp.h>
#endif

using namespace angle;

namespace
{

class EGLSurfaceTest : public ANGLETest
{
  protected:
    EGLSurfaceTest()
        : mDisplay(EGL_NO_DISPLAY),
          mWindowSurface(EGL_NO_SURFACE),
          mPbufferSurface(EGL_NO_SURFACE),
          mContext(EGL_NO_CONTEXT),
          mSecondContext(EGL_NO_CONTEXT),
          mOSWindow(nullptr)
    {}

    void testSetUp() override
    {
        mOSWindow = OSWindow::New();
        mOSWindow->initialize("EGLSurfaceTest", 64, 64);
    }

    // Release any resources created in the test body
    void testTearDown() override
    {
        if (mDisplay != EGL_NO_DISPLAY)
        {
            eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

            if (mWindowSurface != EGL_NO_SURFACE)
            {
                eglDestroySurface(mDisplay, mWindowSurface);
                mWindowSurface = EGL_NO_SURFACE;
            }

            if (mPbufferSurface != EGL_NO_SURFACE)
            {
                eglDestroySurface(mDisplay, mPbufferSurface);
                mPbufferSurface = EGL_NO_SURFACE;
            }

            if (mContext != EGL_NO_CONTEXT)
            {
                eglDestroyContext(mDisplay, mContext);
                mContext = EGL_NO_CONTEXT;
            }

            if (mSecondContext != EGL_NO_CONTEXT)
            {
                eglDestroyContext(mDisplay, mSecondContext);
                mSecondContext = EGL_NO_CONTEXT;
            }

            eglTerminate(mDisplay);
            mDisplay = EGL_NO_DISPLAY;
        }

        mOSWindow->destroy();
        OSWindow::Delete(&mOSWindow);

        ASSERT_TRUE(mWindowSurface == EGL_NO_SURFACE && mContext == EGL_NO_CONTEXT);
    }

    void initializeDisplay()
    {
        GLenum platformType = GetParam().getRenderer();
        GLenum deviceType   = GetParam().getDeviceType();

        std::vector<EGLint> displayAttributes;
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_TYPE_ANGLE);
        displayAttributes.push_back(platformType);
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE);
        displayAttributes.push_back(EGL_DONT_CARE);
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE);
        displayAttributes.push_back(EGL_DONT_CARE);
        displayAttributes.push_back(EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE);
        displayAttributes.push_back(deviceType);
        displayAttributes.push_back(EGL_NONE);

        mDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE,
                                            reinterpret_cast<void *>(mOSWindow->getNativeDisplay()),
                                            displayAttributes.data());
        ASSERT_TRUE(mDisplay != EGL_NO_DISPLAY);

        EGLint majorVersion, minorVersion;
        ASSERT_TRUE(eglInitialize(mDisplay, &majorVersion, &minorVersion) == EGL_TRUE);

        eglBindAPI(EGL_OPENGL_ES_API);
        ASSERT_EGL_SUCCESS();
    }

    void initializeContext()
    {
        EGLint contextAttibutes[] = {EGL_CONTEXT_CLIENT_VERSION, GetParam().majorVersion, EGL_NONE};

        mContext = eglCreateContext(mDisplay, mConfig, nullptr, contextAttibutes);
        ASSERT_EGL_SUCCESS();

        mSecondContext = eglCreateContext(mDisplay, mConfig, nullptr, contextAttibutes);
        ASSERT_EGL_SUCCESS();
    }

    void initializeSurface(EGLConfig config)
    {
        mConfig = config;

        EGLint surfaceType = EGL_NONE;
        eglGetConfigAttrib(mDisplay, mConfig, EGL_SURFACE_TYPE, &surfaceType);

        std::vector<EGLint> windowAttributes;
        windowAttributes.push_back(EGL_NONE);

        if (surfaceType & EGL_WINDOW_BIT)
        {
            // Create first window surface
            mWindowSurface = eglCreateWindowSurface(mDisplay, mConfig, mOSWindow->getNativeWindow(),
                                                    windowAttributes.data());
            ASSERT_EGL_SUCCESS();
        }

        if (surfaceType & EGL_PBUFFER_BIT)
        {
            // Give pbuffer non-zero dimensions.
            std::vector<EGLint> pbufferAttributes;
            pbufferAttributes.push_back(EGL_WIDTH);
            pbufferAttributes.push_back(64);
            pbufferAttributes.push_back(EGL_HEIGHT);
            pbufferAttributes.push_back(64);
            pbufferAttributes.push_back(EGL_NONE);

            mPbufferSurface = eglCreatePbufferSurface(mDisplay, mConfig, pbufferAttributes.data());
            ASSERT_EGL_SUCCESS();
        }

        initializeContext();
    }

    void initializeSurfaceWithDefaultConfig()
    {
        const EGLint configAttributes[] = {EGL_RED_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_GREEN_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_BLUE_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_ALPHA_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_DEPTH_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_STENCIL_SIZE,
                                           EGL_DONT_CARE,
                                           EGL_SAMPLE_BUFFERS,
                                           0,
                                           EGL_NONE};

        EGLint configCount;
        EGLConfig config;
        ASSERT_TRUE(eglChooseConfig(mDisplay, configAttributes, &config, 1, &configCount) ||
                    (configCount != 1) == EGL_TRUE);

        initializeSurface(config);
    }

    GLuint createProgram()
    {
        return CompileProgram(angle::essl1_shaders::vs::Simple(), angle::essl1_shaders::fs::Red());
    }

    void drawWithProgram(GLuint program)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        GLint positionLocation =
            glGetAttribLocation(program, angle::essl1_shaders::PositionAttrib());

        glUseProgram(program);

        const GLfloat vertices[] = {
            -1.0f, 1.0f, 0.5f, -1.0f, -1.0f, 0.5f, 1.0f, -1.0f, 0.5f,

            -1.0f, 1.0f, 0.5f, 1.0f,  -1.0f, 0.5f, 1.0f, 1.0f,  0.5f,
        };

        glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(positionLocation);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(positionLocation);
        glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

        EXPECT_PIXEL_EQ(mOSWindow->getWidth() / 2, mOSWindow->getHeight() / 2, 255, 0, 0, 255);
    }

    void runMessageLoopTest(EGLSurface secondSurface, EGLContext secondContext)
    {
        eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
        ASSERT_EGL_SUCCESS();

        // Make a second context current
        eglMakeCurrent(mDisplay, secondSurface, secondSurface, secondContext);
        eglDestroySurface(mDisplay, mWindowSurface);

        // Create second window surface
        std::vector<EGLint> surfaceAttributes;
        surfaceAttributes.push_back(EGL_NONE);
        surfaceAttributes.push_back(EGL_NONE);

        mWindowSurface = eglCreateWindowSurface(mDisplay, mConfig, mOSWindow->getNativeWindow(),
                                                &surfaceAttributes[0]);
        ASSERT_EGL_SUCCESS();

        eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
        ASSERT_EGL_SUCCESS();

        mOSWindow->signalTestEvent();
        mOSWindow->messageLoop();
        ASSERT_TRUE(mOSWindow->didTestEventFire());

        // Simple operation to test the FBO is set appropriately
        glClear(GL_COLOR_BUFFER_BIT);
    }

    EGLDisplay mDisplay;
    EGLSurface mWindowSurface;
    EGLSurface mPbufferSurface;
    EGLContext mContext;
    EGLContext mSecondContext;
    EGLConfig mConfig;
    OSWindow *mOSWindow;
};

class EGLFloatSurfaceTest : public EGLSurfaceTest
{
  protected:
    EGLFloatSurfaceTest() : EGLSurfaceTest()
    {
        setWindowWidth(512);
        setWindowHeight(512);
    }

    void testSetUp() override
    {
        mOSWindow = OSWindow::New();
        mOSWindow->initialize("EGLFloatSurfaceTest", 64, 64);
    }

    void testTearDown() override
    {
        EGLSurfaceTest::testTearDown();
        glDeleteProgram(mProgram);
    }

    GLuint createProgram()
    {
        constexpr char kFS[] =
            "precision highp float;\n"
            "void main()\n"
            "{\n"
            "   gl_FragColor = vec4(1.0, 2.0, 3.0, 4.0);\n"
            "}\n";
        return CompileProgram(angle::essl1_shaders::vs::Simple(), kFS);
    }

    bool initializeSurfaceWithFloatConfig()
    {
        const EGLint configAttributes[] = {EGL_RED_SIZE,
                                           16,
                                           EGL_GREEN_SIZE,
                                           16,
                                           EGL_BLUE_SIZE,
                                           16,
                                           EGL_ALPHA_SIZE,
                                           16,
                                           EGL_COLOR_COMPONENT_TYPE_EXT,
                                           EGL_COLOR_COMPONENT_TYPE_FLOAT_EXT,
                                           EGL_NONE,
                                           EGL_NONE};

        initializeDisplay();
        EGLConfig config;
        if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
        {
            std::cout << "EGLConfig for a float surface is not supported, skipping test"
                      << std::endl;
            return false;
        }

        initializeSurface(config);

        eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
        mProgram = createProgram();
        return true;
    }

    GLuint mProgram;
};

// Test clearing and checking the color is correct
TEST_P(EGLFloatSurfaceTest, Clearing)
{
    ANGLE_SKIP_TEST_IF(!initializeSurfaceWithFloatConfig());

    ASSERT_NE(0u, mProgram) << "shader compilation failed.";
    ASSERT_GL_NO_ERROR();

    GLColor32F clearColor(0.0f, 1.0f, 2.0f, 3.0f);
    glClearColor(clearColor.R, clearColor.G, clearColor.B, clearColor.A);
    glClear(GL_COLOR_BUFFER_BIT);
    ASSERT_GL_NO_ERROR();

    EXPECT_PIXEL_COLOR32F_EQ(0, 0, clearColor);
}

// Test drawing and checking the color is correct
TEST_P(EGLFloatSurfaceTest, Drawing)
{
    ANGLE_SKIP_TEST_IF(!initializeSurfaceWithFloatConfig());

    ASSERT_NE(0u, mProgram) << "shader compilation failed.";
    ASSERT_GL_NO_ERROR();

    glUseProgram(mProgram);
    drawQuad(mProgram, essl1_shaders::PositionAttrib(), 0.5f);

    EXPECT_PIXEL_32F_EQ(0, 0, 1.0f, 2.0f, 3.0f, 4.0f);
}

class EGLSurfaceTest3 : public EGLSurfaceTest
{};

// Test a surface bug where we could have two Window surfaces active
// at one time, blocking message loops. See http://crbug.com/475085
TEST_P(EGLSurfaceTest, MessageLoopBug)
{
    // TODO(syoussefi): http://anglebug.com/3123
    ANGLE_SKIP_TEST_IF(IsAndroid());

    // http://anglebug.com/3138
    ANGLE_SKIP_TEST_IF(IsOzone());

    initializeDisplay();
    initializeSurfaceWithDefaultConfig();

    runMessageLoopTest(EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

// Tests the message loop bug, but with setting a second context
// instead of null.
TEST_P(EGLSurfaceTest, MessageLoopBugContext)
{
    // TODO(syoussefi): http://anglebug.com/3123
    ANGLE_SKIP_TEST_IF(IsAndroid());

    // http://anglebug.com/3138
    ANGLE_SKIP_TEST_IF(IsOzone());

    initializeDisplay();
    initializeSurfaceWithDefaultConfig();

    ANGLE_SKIP_TEST_IF(!mPbufferSurface);
    runMessageLoopTest(mPbufferSurface, mSecondContext);
}

// Test a bug where calling makeCurrent twice would release the surface
TEST_P(EGLSurfaceTest, MakeCurrentTwice)
{
    initializeDisplay();
    initializeSurfaceWithDefaultConfig();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // Simple operation to test the FBO is set appropriately
    glClear(GL_COLOR_BUFFER_BIT);
}

// Test that the window surface is correctly resized after calling swapBuffers
TEST_P(EGLSurfaceTest, ResizeWindow)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());
    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    // Necessary for a window resizing test if there is no per-frame window size query
    setWindowVisible(mOSWindow, true);

    GLenum platform               = GetParam().getRenderer();
    bool platformSupportsZeroSize = platform == EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE ||
                                    platform == EGL_PLATFORM_ANGLE_TYPE_D3D9_ANGLE;
    int minSize = platformSupportsZeroSize ? 0 : 1;

    initializeDisplay();
    initializeSurfaceWithDefaultConfig();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    EGLint height;
    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    ASSERT_EGL_SUCCESS();
    ASSERT_EQ(64, height);  // initial size

    // set window's height to 0 (if possible) or 1
    mOSWindow->resize(64, minSize);

    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    // TODO(syoussefi): the GLX implementation still reads the window size as 64x64 through
    // XGetGeometry.  http://anglebug.com/3122
    ANGLE_SKIP_TEST_IF(IsLinux() && IsOpenGL());

    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    ASSERT_EGL_SUCCESS();
    ASSERT_EQ(minSize, height);

    // restore window's height
    mOSWindow->resize(64, 64);

    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    ASSERT_EGL_SUCCESS();
    ASSERT_EQ(64, height);
}

// Test that the backbuffer is correctly resized after calling swapBuffers
TEST_P(EGLSurfaceTest, ResizeWindowWithDraw)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());

    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    // Necessary for a window resizing test if there is no per-frame window size query
    setWindowVisible(mOSWindow, true);

    initializeDisplay();
    initializeSurfaceWithDefaultConfig();
    initializeContext();

    int size      = 64;
    EGLint height = 0;
    EGLint width  = 0;

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    // Clear to red
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    eglQuerySurface(mDisplay, mWindowSurface, EGL_WIDTH, &width);
    ASSERT_EGL_SUCCESS();

    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(size - 1, 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(size - 1, size - 1, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(0, size - 1, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(-1, -1, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, 0, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(0, size, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, size, GLColor::transparentBlack);

    // set window's size small
    size = 1;
    mOSWindow->resize(size, size);

    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    // Clear to green
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    eglQuerySurface(mDisplay, mWindowSurface, EGL_WIDTH, &width);
    ASSERT_EGL_SUCCESS();

    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(size - 1, 0, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(size - 1, size - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(0, size - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(-1, -1, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, 0, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(0, size, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, size, GLColor::transparentBlack);

    // set window's height large
    size = 128;
    mOSWindow->resize(size, size);

    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    // Clear to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &height);
    eglQuerySurface(mDisplay, mWindowSurface, EGL_WIDTH, &width);
    ASSERT_EGL_SUCCESS();

    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::blue);
    EXPECT_PIXEL_COLOR_EQ(size - 1, 0, GLColor::blue);
    EXPECT_PIXEL_COLOR_EQ(size - 1, size - 1, GLColor::blue);
    EXPECT_PIXEL_COLOR_EQ(0, size - 1, GLColor::blue);
    EXPECT_PIXEL_COLOR_EQ(-1, -1, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, 0, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(0, size, GLColor::transparentBlack);
    EXPECT_PIXEL_COLOR_EQ(size, size, GLColor::transparentBlack);
}

// A slight variation of EGLSurfaceTest, where the initial window size is 256x256.  This allows
// each pixel to have a unique and predictable value, which will help in testing pre-rotation.
// The red channel will increment with the x axis, and the green channel will increment with the y
// axis.  The four corners will have the following values:
//
// Where                 GLES Render &  ReadPixels coords       Color    (in Hex)
// Lower-left,  which is (-1.0,-1.0) & (  0,   0) in GLES will be black  (0x00, 0x00, 0x00, 0xFF)
// Lower-right, which is ( 1.0,-1.0) & (256,   0) in GLES will be red    (0xFF, 0x00, 0x00, 0xFF)
// Upper-left,  which is (-1.0, 1.0) & (  0, 256) in GLES will be green  (0x00, 0xFF, 0x00, 0xFF)
// Upper-right, which is ( 1.0, 1.0) & (256, 256) in GLES will be yellow (0xFF, 0xFF, 0x00, 0xFF)
class EGLPreRotationSurfaceTest : public EGLSurfaceTest
{
  protected:
    EGLPreRotationSurfaceTest() : mSize(256) {}

    void testSetUp() override
    {
        mOSWindow = OSWindow::New();
        mOSWindow->initialize("EGLSurfaceTest", mSize, mSize);
    }

    void initializeSurfaceWithRGBA8888Config()
    {
        const EGLint configAttributes[] = {
            EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

        EGLint configCount;
        EGLConfig config;
        ASSERT_TRUE(eglChooseConfig(mDisplay, configAttributes, &config, 1, &configCount) ||
                    (configCount != 1) == EGL_TRUE);

        initializeSurface(config);
    }

    void testDrawingAndReadPixels()
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
        EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::black);
        EXPECT_PIXEL_COLOR_EQ(0, mSize - 1, GLColor::green);
        EXPECT_PIXEL_COLOR_EQ(mSize - 1, 0, GLColor::red);
        EXPECT_PIXEL_COLOR_EQ(mSize - 1, mSize - 1, GLColor::yellow);
        ASSERT_GL_NO_ERROR();

        eglSwapBuffers(mDisplay, mWindowSurface);
        ASSERT_EGL_SUCCESS();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
        EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::black);
        EXPECT_PIXEL_COLOR_EQ(0, mSize - 1, GLColor::green);
        EXPECT_PIXEL_COLOR_EQ(mSize - 1, 0, GLColor::red);
        EXPECT_PIXEL_COLOR_EQ(mSize - 1, mSize - 1, GLColor::yellow);
        ASSERT_GL_NO_ERROR();

        {
            // Now, test a 4x4 area in the center of the window, which should tell us if a non-1x1
            // ReadPixels is oriented correctly for the device's orientation:
            GLint xOffset  = 126;
            GLint yOffset  = 126;
            GLsizei width  = 4;
            GLsizei height = 4;
            std::vector<GLColor> pixels(width * height);
            glReadPixels(xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
            EXPECT_GL_NO_ERROR();
            // Expect that all red values equate to x and green values equate to y
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int index = (y * width) + x;
                    GLColor expectedPixel(xOffset + x, yOffset + y, 0, 255);
                    GLColor actualPixel = pixels[index];
                    EXPECT_EQ(expectedPixel, actualPixel);
                }
            }
        }

        {
            // Now, test a 8x4 area off-the-center of the window, just to make sure that works too:
            GLint xOffset  = 13;
            GLint yOffset  = 26;
            GLsizei width  = 8;
            GLsizei height = 4;
            std::vector<GLColor> pixels2(width * height);
            glReadPixels(xOffset, yOffset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &pixels2[0]);
            EXPECT_GL_NO_ERROR();
            // Expect that all red values equate to x and green values equate to y
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    int index = (y * width) + x;
                    GLColor expectedPixel(xOffset + x, yOffset + y, 0, 255);
                    GLColor actualPixel = pixels2[index];
                    EXPECT_EQ(expectedPixel, actualPixel);
                }
            }
        }

        eglSwapBuffers(mDisplay, mWindowSurface);
        ASSERT_EGL_SUCCESS();
    }

    int mSize;
};

// Provide a predictable pattern for testing pre-rotation
TEST_P(EGLPreRotationSurfaceTest, OrientedWindowWithDraw)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());

    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    // To aid in debugging, we want this window visible
    setWindowVisible(mOSWindow, true);

    initializeDisplay();
    initializeSurfaceWithRGBA8888Config();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // Init program
    constexpr char kVS[] =
        "attribute vec2 position;\n"
        "attribute vec2 redGreen;\n"
        "varying vec2 v_data;\n"
        "void main() {\n"
        "  gl_Position = vec4(position, 0, 1);\n"
        "  v_data = redGreen;\n"
        "}";

    constexpr char kFS[] =
        "varying highp vec2 v_data;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(v_data, 0, 1);\n"
        "}";

    GLuint program = CompileProgram(kVS, kFS);
    ASSERT_NE(0u, program);
    glUseProgram(program);

    GLint positionLocation = glGetAttribLocation(program, "position");
    ASSERT_NE(-1, positionLocation);

    GLint redGreenLocation = glGetAttribLocation(program, "redGreen");
    ASSERT_NE(-1, redGreenLocation);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);

    std::vector<GLuint> vertexBuffers(2);
    glGenBuffers(2, &vertexBuffers[0]);

    glBindVertexArray(vertexArray);

    std::vector<GLushort> indices = {0, 1, 2, 2, 3, 0};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0],
                 GL_STATIC_DRAW);

    std::vector<GLfloat> positionData = {// quad vertices
                                         -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positionData.size(), &positionData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(positionLocation);

    std::vector<GLfloat> redGreenData = {// green(0,1), black(0,0), red(1,0), yellow(1,1)
                                         0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * redGreenData.size(), &redGreenData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(redGreenLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(redGreenLocation);

    ASSERT_GL_NO_ERROR();

    testDrawingAndReadPixels();
}

// Use dFdx() and dFdy() and still provide a predictable pattern for testing pre-rotation
// In this case, the color values will be the following: (dFdx(v_data.x), dFdy(v_data.y), 0, 1).
// To help make this meaningful for pre-rotation, the derivatives will vary in the four corners of
// the window:
//
//  +------------+------------+      +--------+--------+
//  | (  0, 219) | (239, 249) |      | Green  | Yellow |
//  +------------+------------+  OR  +--------+--------+
//  | (  0,   0) | (229,   0) |      | Black  |  Red   |
//  +------------+------------+      +--------+--------+
TEST_P(EGLPreRotationSurfaceTest, OrientedWindowWithDerivativeDraw)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());

    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    // To aid in debugging, we want this window visible
    setWindowVisible(mOSWindow, true);

    initializeDisplay();
    initializeSurfaceWithRGBA8888Config();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // Init program
    constexpr char kVS[] =
        "#version 300 es\n"
        "in highp vec2 position;\n"
        "in highp vec2 redGreen;\n"
        "out highp vec2 v_data;\n"
        "void main() {\n"
        "  gl_Position = vec4(position, 0, 1);\n"
        "  v_data = redGreen;\n"
        "}";

    constexpr char kFS[] =
        "#version 300 es\n"
        "in highp vec2 v_data;\n"
        "out highp vec4 FragColor;\n"
        "void main() {\n"
        "  FragColor = vec4(dFdx(v_data.x), dFdy(v_data.y), 0, 1);\n"
        "}";

    GLuint program = CompileProgram(kVS, kFS);
    ASSERT_NE(0u, program);
    glUseProgram(program);

    GLint positionLocation = glGetAttribLocation(program, "position");
    ASSERT_NE(-1, positionLocation);

    GLint redGreenLocation = glGetAttribLocation(program, "redGreen");
    ASSERT_NE(-1, redGreenLocation);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);

    std::vector<GLuint> vertexBuffers(2);
    glGenBuffers(2, &vertexBuffers[0]);

    glBindVertexArray(vertexArray);

    std::vector<GLushort> indices = {// 4 squares each made up of 6 vertices:
                                     // 1st square, in the upper-left part of window
                                     0, 1, 2, 2, 3, 0,
                                     // 2nd square, in the upper-right part of window
                                     4, 5, 6, 6, 7, 4,
                                     // 3rd square, in the lower-left part of window
                                     8, 9, 10, 10, 11, 8,
                                     // 4th square, in the lower-right part of window
                                     12, 13, 14, 14, 15, 12};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0],
                 GL_STATIC_DRAW);

    std::vector<GLfloat> positionData = {// 4 squares each made up of quad vertices
                                         // 1st square, in the upper-left part of window
                                         -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                         // 2nd square, in the upper-right part of window
                                         0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                                         // 3rd square, in the lower-left part of window
                                         -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                                         // 4th square, in the lower-right part of window
                                         0.0f, 0.0f, 0.0f, -1.0f, 1.0f, -1.0f, 1.0f, 0.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positionData.size(), &positionData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(positionLocation);

    std::vector<GLfloat> redGreenData = {// green(0,110), black(0,0), red(115,0), yellow(120,125)
                                         // 4 squares each made up of 4 pairs of half-color values:
                                         // 1st square, in the upper-left part of window
                                         0.0f, 110.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 110.0f,
                                         // 2nd square, in the upper-right part of window
                                         0.0f, 125.0f, 0.0f, 0.0f, 120.0f, 0.0f, 120.0f, 125.0f,
                                         // 3rd square, in the lower-left part of window
                                         0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                         // 4th square, in the lower-right part of window
                                         0.0f, 0.0f, 0.0f, 0.0f, 115.0f, 0.0f, 115.0f, 0.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * redGreenData.size(), &redGreenData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(redGreenLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(redGreenLocation);

    ASSERT_GL_NO_ERROR();

    // Draw and check the 4 corner pixels, to ensure we're getting the expected "colors"
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
    GLColor expectedPixelLowerLeft(0, 0, 0, 255);
    GLColor expectedPixelLowerRight(229, 0, 0, 255);
    GLColor expectedPixelUpperLeft(0, 219, 0, 255);
    GLColor expectedPixelUpperRight(239, 249, 0, 255);
    EXPECT_PIXEL_COLOR_EQ(0, 0, expectedPixelLowerLeft);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, 0, expectedPixelLowerRight);
    EXPECT_PIXEL_COLOR_EQ(0, mSize - 1, expectedPixelUpperLeft);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, mSize - 1, expectedPixelUpperRight);
    ASSERT_GL_NO_ERROR();

    // Make the image visible
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();

    // Draw again and check the 4 center pixels, to ensure we're getting the expected "colors"
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
    EXPECT_PIXEL_COLOR_EQ((mSize / 2) - 1, (mSize / 2) - 1, expectedPixelLowerLeft);
    EXPECT_PIXEL_COLOR_EQ((mSize / 2) - 1, (mSize / 2), expectedPixelUpperLeft);
    EXPECT_PIXEL_COLOR_EQ((mSize / 2), (mSize / 2) - 1, expectedPixelLowerRight);
    EXPECT_PIXEL_COLOR_EQ((mSize / 2), (mSize / 2), expectedPixelUpperRight);
    ASSERT_GL_NO_ERROR();
}

// A slight variation of EGLPreRotationSurfaceTest, where the initial window size is 400x300, yet
// the drawing is still 256x256.  In addition, gl_FragCoord is used in a "clever" way, as the color
// of the 256x256 drawing area, which reproduces an interesting pre-rotation case from the
// following dEQP tests:
//
// - dEQP.GLES31/functional_texture_multisample_samples_*_sample_position
//
// This will test the rotation of gl_FragCoord, as well as the viewport, scissor, and rendering
// area calculations, especially when the Android device is rotated.
class EGLPreRotationLargeSurfaceTest : public EGLPreRotationSurfaceTest
{
  protected:
    EGLPreRotationLargeSurfaceTest() : mSize(256) {}

    void testSetUp() override
    {
        mOSWindow = OSWindow::New();
        mOSWindow->initialize("EGLSurfaceTest", 400, 300);
    }

    int mSize;
};

// Provide a predictable pattern for testing pre-rotation
TEST_P(EGLPreRotationLargeSurfaceTest, OrientedWindowWithDraw)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());

    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    // To aid in debugging, we want this window visible
    setWindowVisible(mOSWindow, true);

    initializeDisplay();
    initializeSurfaceWithRGBA8888Config();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // Init program
    constexpr char kVS[] =
        "attribute vec2 position;\n"
        "void main() {\n"
        "  gl_Position = vec4(position, 0, 1);\n"
        "}";

    constexpr char kFS[] =
        "void main() {\n"
        "  gl_FragColor = vec4(gl_FragCoord.x / 256.0, gl_FragCoord.y / 256.0, 0.0, 1.0);\n"
        "}";

    GLuint program = CompileProgram(kVS, kFS);
    ASSERT_NE(0u, program);
    glUseProgram(program);

    GLint positionLocation = glGetAttribLocation(program, "position");
    ASSERT_NE(-1, positionLocation);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);

    std::vector<GLushort> indices = {0, 1, 2, 2, 3, 0};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0],
                 GL_STATIC_DRAW);

    std::vector<GLfloat> positionData = {// quad vertices
                                         -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positionData.size(), &positionData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(positionLocation);

    ASSERT_GL_NO_ERROR();

    glViewport(0, 0, mSize, mSize);

    testDrawingAndReadPixels();
}

// Draw a predictable pattern (for testing pre-rotation) into an FBO, and then use glBlitFramebuffer
// to put that pattern into various places within the 400x300 window
TEST_P(EGLPreRotationLargeSurfaceTest, OrientedWindowWithBlitFramebuffer)
{
    // http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(isVulkanRenderer() && IsLinux() && IsIntel());

    // Flaky on Linux SwANGLE http://anglebug.com/4453
    ANGLE_SKIP_TEST_IF(IsLinux() && isSwiftshader());

    constexpr GLuint kCoordMidWayShort       = 127;
    constexpr GLuint kCoordMidWayLong        = 128;
    constexpr GLColor kColorMidWayShortShort = GLColor(127, 127, 0, 255);
    constexpr GLColor kColorMidWayShortLong  = GLColor(127, 128, 0, 255);
    constexpr GLColor kColorMidWayLongShort  = GLColor(128, 127, 0, 255);
    constexpr GLColor kColorMidWayLongLong   = GLColor(128, 128, 0, 255);
    // When scaling horizontally, the "black" and "green" colors have a 1 in the red component
    constexpr GLColor kColorScaleHorizBlack = GLColor(1, 0, 0, 255);
    constexpr GLColor kColorScaleHorizGreen = GLColor(1, 255, 0, 255);
    // When scaling vertically, the "black" and "red" colors have a 1 in the green component
    constexpr GLColor kColorScaleVertBlack = GLColor(0, 1, 0, 255);
    constexpr GLColor kColorScaleVertRed   = GLColor(255, 1, 0, 255);

    // To aid in debugging, we want this window visible
    setWindowVisible(mOSWindow, true);

    initializeDisplay();
    initializeSurfaceWithRGBA8888Config();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // Init program
    constexpr char kVS[] =
        "attribute vec2 position;\n"
        "attribute vec2 redGreen;\n"
        "varying vec2 v_data;\n"
        "void main() {\n"
        "  gl_Position = vec4(position, 0, 1);\n"
        "  v_data = redGreen;\n"
        "}";

    constexpr char kFS[] =
        "varying highp vec2 v_data;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(v_data, 0, 1);\n"
        "}";

    GLuint program = CompileProgram(kVS, kFS);
    ASSERT_NE(0u, program);
    glUseProgram(program);

    GLint positionLocation = glGetAttribLocation(program, "position");
    ASSERT_NE(-1, positionLocation);

    GLint redGreenLocation = glGetAttribLocation(program, "redGreen");
    ASSERT_NE(-1, redGreenLocation);

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);

    std::vector<GLuint> vertexBuffers(2);
    glGenBuffers(2, &vertexBuffers[0]);

    glBindVertexArray(vertexArray);

    std::vector<GLushort> indices = {0, 1, 2, 2, 3, 0};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0],
                 GL_STATIC_DRAW);

    std::vector<GLfloat> positionData = {// quad vertices
                                         -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positionData.size(), &positionData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(positionLocation);

    std::vector<GLfloat> redGreenData = {// green(0,1), black(0,0), red(1,0), yellow(1,1)
                                         0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * redGreenData.size(), &redGreenData[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(redGreenLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, nullptr);
    glEnableVertexAttribArray(redGreenLocation);

    ASSERT_GL_NO_ERROR();

    // Create a texture-backed FBO and render the predictable pattern to it
    GLuint framebuffer = 0;
    GLuint texture     = 0;
    glGenFramebuffers(1, &framebuffer);
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mSize, mSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    ASSERT_GL_NO_ERROR();

    glViewport(0, 0, mSize, mSize);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    // Ensure the predictable pattern seems correct in the FBO
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(0, mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayShort, kCoordMidWayShort, kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayShort, kCoordMidWayLong, kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayLong, kCoordMidWayShort, kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayLong, kCoordMidWayLong, kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    //
    // Test blitting the entire FBO image to a 256x256 part of the default framebuffer (no scaling)
    //

    // Blit from the FBO to the default framebuffer (i.e. the swapchain)
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize, 0, 0, mSize, mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    ASSERT_GL_NO_ERROR();

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize, 0, 0, mSize, mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(0, mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(mSize - 1, mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayShort, kCoordMidWayShort, kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayShort, kCoordMidWayLong, kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayLong, kCoordMidWayShort, kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(kCoordMidWayLong, kCoordMidWayLong, kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    // Clear to black and blit to a different part of the window
    glClear(GL_COLOR_BUFFER_BIT);
    GLint xOffset = 40;
    GLint yOffset = 30;
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + mSize, yOffset + mSize,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + mSize, yOffset + mSize,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayShort,
                          kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayLong,
                          kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayShort,
                          kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayLong,
                          kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    //
    // Test blitting half of the FBO image to a 128x256 or 256x128 part of the default framebuffer
    // (no scaling)
    //

    // 1st) Clear to black and blit the left and right halves of the texture to the left and right
    // halves of that different part of the window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize / 2, mSize, xOffset, yOffset, xOffset + (mSize / 2),
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(mSize / 2, 0, mSize, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize / 2, mSize, xOffset, yOffset, xOffset + (mSize / 2),
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(mSize / 2, 0, mSize, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayShort,
                          kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayLong,
                          kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayShort,
                          kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayLong,
                          kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    // 2nd) Clear to black and this time blit the left half of the source texture to the right half
    // of the destination window, and then blit the right half of the source texture to the left
    // half of the destination window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(mSize / 2, 0, mSize, mSize, xOffset, yOffset, xOffset + (mSize / 2),
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize / 2, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(mSize / 2, 0, mSize, mSize, xOffset, yOffset, xOffset + (mSize / 2),
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize / 2, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort + 1, yOffset + 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort + 1, yOffset + mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayShort, kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayLong, kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayShort, kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayLong, kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    // 3rd) Clear to black and blit the top and bottom halves of the texture to the top and bottom
    // halves of that different part of the window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize, mSize / 2, xOffset, yOffset, xOffset + mSize,
                      yOffset + (mSize / 2), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, mSize / 2, mSize, mSize, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize / 2, xOffset, yOffset, xOffset + mSize,
                      yOffset + (mSize / 2), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, mSize / 2, mSize, mSize, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + 0, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayShort,
                          kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + kCoordMidWayLong,
                          kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayShort,
                          kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + kCoordMidWayLong,
                          kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    // 4th) Clear to black and this time blit the top half of the source texture to the bottom half
    // of the destination window, and then blit the bottom half of the source texture to the top
    // half of the destination window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize, mSize / 2, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, mSize / 2, mSize, mSize, xOffset, yOffset, xOffset + mSize,
                      yOffset + (mSize / 2), GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize / 2, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, mSize / 2, mSize, mSize, xOffset, yOffset, xOffset + mSize,
                      yOffset + (mSize / 2), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayShort + 1, GLColor::black);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayShort, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayShort + 1, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayShort, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + mSize - 1, kColorMidWayShortShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + 0, kColorMidWayShortLong);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + mSize - 1, kColorMidWayLongShort);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + 0, kColorMidWayLongLong);
    ASSERT_GL_NO_ERROR();

    //
    // Test blitting the entire FBO image to a 128x256 or 256x128 part of the default framebuffer
    // (requires scaling)
    //

    // 1st) Clear to black and blit the FBO to the left and right halves of that different part of
    // the window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + (mSize / 2), yOffset + mSize,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + (mSize / 2), yOffset + mSize,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset + (mSize / 2), yOffset, xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + 0, kColorScaleHorizBlack);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + mSize - 1, kColorScaleHorizGreen);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayShort, yOffset + mSize - 1, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + 0, kColorScaleHorizBlack);
    EXPECT_PIXEL_COLOR_EQ(xOffset + kCoordMidWayLong, yOffset + mSize - 1, kColorScaleHorizGreen);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + 0, GLColor::red);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + mSize - 1, GLColor::yellow);

    // 2nd) Clear to black and blit the FBO to the top and bottom halves of that different part of
    // the window
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(xOffset, yOffset, mSize, mSize);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + mSize, yOffset + (mSize / 2),
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    // Swap buffers to put the image in the window (so the test can be visually checked)
    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_GL_NO_ERROR();

    // Blit again to check the colors in the back buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset, xOffset + mSize, yOffset + (mSize / 2),
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBlitFramebuffer(0, 0, mSize, mSize, xOffset, yOffset + (mSize / 2), xOffset + mSize,
                      yOffset + mSize, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + 0, kColorScaleVertBlack);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + 0, kColorScaleVertRed);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayShort, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayShort, GLColor::yellow);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + kCoordMidWayLong, kColorScaleVertBlack);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + kCoordMidWayLong, kColorScaleVertRed);
    EXPECT_PIXEL_COLOR_EQ(xOffset + 0, yOffset + mSize - 1, GLColor::green);
    EXPECT_PIXEL_COLOR_EQ(xOffset + mSize - 1, yOffset + mSize - 1, GLColor::yellow);

    ASSERT_EGL_SUCCESS();
}

// Test that the window can be reset repeatedly before surface creation.
TEST_P(EGLSurfaceTest, ResetNativeWindow)
{
    setWindowVisible(mOSWindow, true);

    initializeDisplay();

    for (int i = 0; i < 10; ++i)
    {
        mOSWindow->resetNativeWindow();
    }

    initializeSurfaceWithDefaultConfig();
    initializeContext();

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);

    eglSwapBuffers(mDisplay, mWindowSurface);
    ASSERT_EGL_SUCCESS();
}

// Test creating a surface that supports a EGLConfig with 16bit
// support GL_RGB565
TEST_P(EGLSurfaceTest, CreateWithEGLConfig5650Support)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   5, EGL_GREEN_SIZE,   6, EGL_BLUE_SIZE,      5, EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    initializeDisplay();
    EGLConfig config;
    if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
    {
        std::cout << "EGLConfig for a GL_RGB565 surface is not supported, skipping test"
                  << std::endl;
        return;
    }

    initializeSurface(config);

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);
    drawWithProgram(program);
    EXPECT_GL_NO_ERROR();
    glDeleteProgram(program);
}

// Test creating a surface that supports a EGLConfig with 16bit
// support GL_RGBA4
TEST_P(EGLSurfaceTest, CreateWithEGLConfig4444Support)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   4, EGL_GREEN_SIZE,   4, EGL_BLUE_SIZE,      4, EGL_ALPHA_SIZE, 4,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    initializeDisplay();
    EGLConfig config;
    if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
    {
        std::cout << "EGLConfig for a GL_RGBA4 surface is not supported, skipping test"
                  << std::endl;
        return;
    }

    initializeSurface(config);

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);
    drawWithProgram(program);
    EXPECT_GL_NO_ERROR();
    glDeleteProgram(program);
}

// Test creating a surface that supports a EGLConfig with 16bit
// support GL_RGB5_A1
TEST_P(EGLSurfaceTest, CreateWithEGLConfig5551Support)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   5, EGL_GREEN_SIZE,   5, EGL_BLUE_SIZE,      5, EGL_ALPHA_SIZE, 1,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    initializeDisplay();
    EGLConfig config;
    if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
    {
        std::cout << "EGLConfig for a GL_RGB5_A1 surface is not supported, skipping test"
                  << std::endl;
        return;
    }

    initializeSurface(config);

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);
    drawWithProgram(program);
    EXPECT_GL_NO_ERROR();
    glDeleteProgram(program);
}

// Test creating a surface that supports a EGLConfig without alpha support
TEST_P(EGLSurfaceTest, CreateWithEGLConfig8880Support)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    initializeDisplay();
    EGLConfig config;
    if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
    {
        std::cout << "EGLConfig for a GL_RGB8_OES surface is not supported, skipping test"
                  << std::endl;
        return;
    }

    initializeSurface(config);

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);
    drawWithProgram(program);
    EXPECT_GL_NO_ERROR();
    glDeleteProgram(program);
}

TEST_P(EGLSurfaceTest, FixedSizeWindow)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    initializeDisplay();
    ANGLE_SKIP_TEST_IF(EGLWindow::FindEGLConfig(mDisplay, configAttributes, &mConfig) == EGL_FALSE);

    ANGLE_SKIP_TEST_IF(!IsEGLDisplayExtensionEnabled(mDisplay, "EGL_ANGLE_window_fixed_size"));

    constexpr EGLint kInitialSize = 64;
    constexpr EGLint kUpdateSize  = 32;

    EGLint surfaceAttributes[] = {
        EGL_FIXED_SIZE_ANGLE, EGL_TRUE, EGL_WIDTH, kInitialSize, EGL_HEIGHT, kInitialSize, EGL_NONE,
    };

    // Create first window surface
    mWindowSurface =
        eglCreateWindowSurface(mDisplay, mConfig, mOSWindow->getNativeWindow(), surfaceAttributes);
    ASSERT_EGL_SUCCESS();
    ASSERT_NE(EGL_NO_SURFACE, mWindowSurface);

    initializeContext();
    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext));
    ASSERT_EGL_SUCCESS();

    EGLint queryIsFixedSize = 0;
    EXPECT_EGL_TRUE(
        eglQuerySurface(mDisplay, mWindowSurface, EGL_FIXED_SIZE_ANGLE, &queryIsFixedSize));
    ASSERT_EGL_SUCCESS();
    EXPECT_EGL_TRUE(queryIsFixedSize);

    EGLint queryWidth = 0;
    EXPECT_EGL_TRUE(eglQuerySurface(mDisplay, mWindowSurface, EGL_WIDTH, &queryWidth));
    ASSERT_EGL_SUCCESS();
    EXPECT_EQ(kInitialSize, queryWidth);

    EGLint queryHeight = 0;
    EXPECT_EGL_TRUE(eglQuerySurface(mDisplay, mWindowSurface, EGL_HEIGHT, &queryHeight));
    ASSERT_EGL_SUCCESS();
    EXPECT_EQ(kInitialSize, queryHeight);

    // Update the size
    EXPECT_EGL_TRUE(eglSurfaceAttrib(mDisplay, mWindowSurface, EGL_WIDTH, kUpdateSize));
    ASSERT_EGL_SUCCESS();

    EXPECT_EGL_TRUE(eglWaitNative(EGL_CORE_NATIVE_ENGINE));
    ASSERT_EGL_SUCCESS();

    EGLint queryUpdatedWidth = 0;
    EXPECT_EGL_TRUE(eglQuerySurface(mDisplay, mWindowSurface, EGL_WIDTH, &queryUpdatedWidth));
    ASSERT_EGL_SUCCESS();
    EXPECT_EQ(kUpdateSize, queryUpdatedWidth);
}

TEST_P(EGLSurfaceTest3, MakeCurrentDifferentSurfaces)
{
    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};
    EGLSurface firstPbufferSurface;
    EGLSurface secondPbufferSurface;

    initializeDisplay();
    ANGLE_SKIP_TEST_IF(EGLWindow::FindEGLConfig(mDisplay, configAttributes, &mConfig) == EGL_FALSE);

    EGLint surfaceType = 0;
    eglGetConfigAttrib(mDisplay, mConfig, EGL_SURFACE_TYPE, &surfaceType);
    bool supportsPbuffers    = (surfaceType & EGL_PBUFFER_BIT) != 0;
    EGLint bindToTextureRGBA = 0;
    eglGetConfigAttrib(mDisplay, mConfig, EGL_BIND_TO_TEXTURE_RGBA, &bindToTextureRGBA);
    bool supportsBindTexImage = (bindToTextureRGBA == EGL_TRUE);

    const EGLint pBufferAttributes[] = {
        EGL_WIDTH,          64,
        EGL_HEIGHT,         64,
        EGL_TEXTURE_FORMAT, supportsPbuffers ? EGL_TEXTURE_RGBA : EGL_NO_TEXTURE,
        EGL_TEXTURE_TARGET, supportsBindTexImage ? EGL_TEXTURE_2D : EGL_NO_TEXTURE,
        EGL_NONE,           EGL_NONE,
    };

    // Create the surfaces
    firstPbufferSurface = eglCreatePbufferSurface(mDisplay, mConfig, pBufferAttributes);
    ASSERT_EGL_SUCCESS();
    ASSERT_NE(EGL_NO_SURFACE, firstPbufferSurface);
    secondPbufferSurface = eglCreatePbufferSurface(mDisplay, mConfig, pBufferAttributes);
    ASSERT_EGL_SUCCESS();
    ASSERT_NE(EGL_NO_SURFACE, secondPbufferSurface);

    initializeContext();

    // Use the same surface for both draw and read
    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, firstPbufferSurface, firstPbufferSurface, mContext));
    glClearColor(GLColor::red.R, GLColor::red.G, GLColor::red.B, GLColor::red.A);
    glClear(GL_COLOR_BUFFER_BIT);
    ASSERT_GL_NO_ERROR();
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::red);

    // Use different surfaces for draw and read, read should stay the same
    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, secondPbufferSurface, firstPbufferSurface, mContext));
    glClearColor(GLColor::blue.R, GLColor::blue.G, GLColor::blue.B, GLColor::blue.A);
    glClear(GL_COLOR_BUFFER_BIT);
    ASSERT_GL_NO_ERROR();
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::red);
    // Verify draw surface was cleared
    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, secondPbufferSurface, secondPbufferSurface, mContext));
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::blue);

    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, firstPbufferSurface, secondPbufferSurface, mContext));
    ASSERT_EGL_SUCCESS();

    // Blit the source surface to the destination surface
    glBlitFramebuffer(0, 0, 64, 64, 0, 0, 64, 64, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    ASSERT_GL_NO_ERROR();
    EXPECT_EGL_TRUE(eglMakeCurrent(mDisplay, firstPbufferSurface, firstPbufferSurface, mContext));
    EXPECT_PIXEL_COLOR_EQ(0, 0, GLColor::blue);
}

#if defined(ANGLE_ENABLE_D3D11)
class EGLSurfaceTestD3D11 : public EGLSurfaceTest
{};

// Test that rendering to an IDCompositionSurface using a pbuffer works.
TEST_P(EGLSurfaceTestD3D11, CreateDirectCompositionSurface)
{
    ANGLE_SKIP_TEST_IF(!IsEGLClientExtensionEnabled("EGL_ANGLE_platform_angle_d3d"));
    initializeDisplay();

    EGLAttrib device       = 0;
    EGLAttrib newEglDevice = 0;
    ASSERT_EGL_TRUE(eglQueryDisplayAttribEXT(mDisplay, EGL_DEVICE_EXT, &newEglDevice));
    ASSERT_EGL_TRUE(eglQueryDeviceAttribEXT(reinterpret_cast<EGLDeviceEXT>(newEglDevice),
                                            EGL_D3D11_DEVICE_ANGLE, &device));
    angle::ComPtr<ID3D11Device> d3d11Device(reinterpret_cast<ID3D11Device *>(device));
    ASSERT_TRUE(!!d3d11Device);

    HMODULE dcompLibrary = LoadLibraryA("dcomp.dll");
    if (!dcompLibrary)
    {
        std::cout << "DirectComposition not supported" << std::endl;
        return;
    }
    typedef HRESULT(WINAPI * PFN_DCOMPOSITION_CREATE_DEVICE2)(IUnknown * dxgiDevice, REFIID iid,
                                                              void **dcompositionDevice);
    PFN_DCOMPOSITION_CREATE_DEVICE2 createDComp = reinterpret_cast<PFN_DCOMPOSITION_CREATE_DEVICE2>(
        GetProcAddress(dcompLibrary, "DCompositionCreateDevice2"));
    if (!createDComp)
    {
        std::cout << "DirectComposition2 not supported" << std::endl;
        FreeLibrary(dcompLibrary);
        return;
    }

    angle::ComPtr<IDCompositionDevice> dcompDevice;
    HRESULT hr = createDComp(d3d11Device.Get(), IID_PPV_ARGS(dcompDevice.GetAddressOf()));
    ASSERT_TRUE(SUCCEEDED(hr));

    angle::ComPtr<IDCompositionSurface> dcompSurface;
    hr = dcompDevice->CreateSurface(100, 100, DXGI_FORMAT_B8G8R8A8_UNORM,
                                    DXGI_ALPHA_MODE_PREMULTIPLIED, dcompSurface.GetAddressOf());
    ASSERT_TRUE(SUCCEEDED(hr));

    angle::ComPtr<ID3D11Texture2D> texture;
    POINT updateOffset;
    hr = dcompSurface->BeginDraw(nullptr, IID_PPV_ARGS(texture.GetAddressOf()), &updateOffset);
    ASSERT_TRUE(SUCCEEDED(hr));

    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    EGLConfig config;
    ASSERT_EGL_TRUE(EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config));

    const EGLint surfaceAttributes[] = {EGL_WIDTH,
                                        100,
                                        EGL_HEIGHT,
                                        100,
                                        EGL_FLEXIBLE_SURFACE_COMPATIBILITY_SUPPORTED_ANGLE,
                                        EGL_TRUE,
                                        EGL_TEXTURE_OFFSET_X_ANGLE,
                                        updateOffset.x,
                                        EGL_TEXTURE_OFFSET_Y_ANGLE,
                                        updateOffset.y,
                                        EGL_NONE};

    EGLClientBuffer buffer = reinterpret_cast<EGLClientBuffer>(texture.Get());
    mPbufferSurface = eglCreatePbufferFromClientBuffer(mDisplay, EGL_D3D_TEXTURE_ANGLE, buffer,
                                                       config, surfaceAttributes);
    ASSERT_EGL_SUCCESS();

    mConfig = config;
    initializeContext();

    eglMakeCurrent(mDisplay, mPbufferSurface, mPbufferSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);
    drawWithProgram(program);
    EXPECT_GL_NO_ERROR();
    glDeleteProgram(program);
}

TEST_P(EGLSurfaceTestD3D11, CreateSurfaceWithTextureOffset)
{
    ANGLE_SKIP_TEST_IF(!IsEGLClientExtensionEnabled("EGL_ANGLE_platform_angle_d3d"));
    initializeDisplay();

    const EGLint configAttributes[] = {
        EGL_RED_SIZE,   8, EGL_GREEN_SIZE,   8, EGL_BLUE_SIZE,      8, EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 0, EGL_STENCIL_SIZE, 0, EGL_SAMPLE_BUFFERS, 0, EGL_NONE};

    EGLConfig config;
    ASSERT_EGL_TRUE(EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config));

    mConfig = config;
    initializeContext();

    EGLAttrib device       = 0;
    EGLAttrib newEglDevice = 0;
    ASSERT_EGL_TRUE(eglQueryDisplayAttribEXT(mDisplay, EGL_DEVICE_EXT, &newEglDevice));
    ASSERT_EGL_TRUE(eglQueryDeviceAttribEXT(reinterpret_cast<EGLDeviceEXT>(newEglDevice),
                                            EGL_D3D11_DEVICE_ANGLE, &device));
    angle::ComPtr<ID3D11Device> d3d11Device(reinterpret_cast<ID3D11Device *>(device));
    ASSERT_TRUE(!!d3d11Device);

    constexpr UINT kTextureWidth  = 100;
    constexpr UINT kTextureHeight = 100;
    constexpr Color<uint8_t> kOpaqueBlack(0, 0, 0, 255);
    std::vector<Color<uint8_t>> textureData(kTextureWidth * kTextureHeight, kOpaqueBlack);

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem                = textureData.data();
    initialData.SysMemPitch            = kTextureWidth * sizeof(kOpaqueBlack);

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Format               = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.Width                = kTextureWidth;
    desc.Height               = kTextureHeight;
    desc.ArraySize            = 1;
    desc.MipLevels            = 1;
    desc.SampleDesc.Count     = 1;
    desc.Usage                = D3D11_USAGE_DEFAULT;
    desc.BindFlags            = D3D11_BIND_RENDER_TARGET;
    angle::ComPtr<ID3D11Texture2D> texture;
    HRESULT hr = d3d11Device->CreateTexture2D(&desc, &initialData, &texture);
    ASSERT_TRUE(SUCCEEDED(hr));

    angle::ComPtr<ID3D11DeviceContext> d3d11Context;
    d3d11Device->GetImmediateContext(&d3d11Context);

    // Specify a texture offset of (50, 50) when rendering to the pbuffer surface.
    const EGLint surfaceAttributes[] = {EGL_WIDTH,
                                        kTextureWidth,
                                        EGL_HEIGHT,
                                        kTextureHeight,
                                        EGL_FLEXIBLE_SURFACE_COMPATIBILITY_SUPPORTED_ANGLE,
                                        EGL_TRUE,
                                        EGL_TEXTURE_OFFSET_X_ANGLE,
                                        50,
                                        EGL_TEXTURE_OFFSET_Y_ANGLE,
                                        50,
                                        EGL_NONE};
    EGLClientBuffer buffer           = reinterpret_cast<EGLClientBuffer>(texture.Get());
    mPbufferSurface = eglCreatePbufferFromClientBuffer(mDisplay, EGL_D3D_TEXTURE_ANGLE, buffer,
                                                       config, surfaceAttributes);
    ASSERT_EGL_SUCCESS();

    eglMakeCurrent(mDisplay, mPbufferSurface, mPbufferSurface, mContext);
    ASSERT_EGL_SUCCESS();

    // glClear should only clear subrect at offset (50, 50) without explicit scissor.
    glClearColor(0, 0, 1, 1);  // Blue
    glClear(GL_COLOR_BUFFER_BIT);
    EXPECT_PIXEL_EQ(25, 25, 0, 0, 0, 255);
    EXPECT_PIXEL_EQ(75, 75, 0, 0, 255, 255);
    EXPECT_GL_NO_ERROR();

    // Drawing with a shader should also update the same subrect only without explicit viewport.
    GLuint program = createProgram();  // Red
    ASSERT_NE(0u, program);
    GLint positionLocation = glGetAttribLocation(program, angle::essl1_shaders::PositionAttrib());
    glUseProgram(program);
    const GLfloat vertices[] = {
        -1.0f, 1.0f, 0.5f, -1.0f, -1.0f, 0.5f, 1.0f, -1.0f, 0.5f,
        -1.0f, 1.0f, 0.5f, 1.0f,  -1.0f, 0.5f, 1.0f, 1.0f,  0.5f,
    };
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLocation);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    EXPECT_PIXEL_EQ(25, 25, 0, 0, 0, 255);
    EXPECT_PIXEL_EQ(75, 75, 255, 0, 0, 255);
    EXPECT_GL_NO_ERROR();

    glDeleteProgram(program);
    EXPECT_GL_NO_ERROR();

    // Blit framebuffer should also blit to the same subrect despite the dstX/Y arguments.
    GLuint renderBuffer = 0;
    glGenRenderbuffers(1u, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, 50, 50);
    EXPECT_GL_NO_ERROR();

    GLuint framebuffer = 0;
    glGenFramebuffers(1u, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuffer);
    EXPECT_GL_NO_ERROR();

    glClearColor(0, 1, 0, 1);  // Green
    glClear(GL_COLOR_BUFFER_BIT);
    EXPECT_PIXEL_EQ(25, 25, 0, 255, 0, 255);
    EXPECT_GL_NO_ERROR();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0u);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBlitFramebuffer(0, 0, 50, 50, 0, 0, 50, 50, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    EXPECT_GL_NO_ERROR();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0u);
    EXPECT_PIXEL_EQ(25, 25, 0, 0, 0, 255);
    EXPECT_PIXEL_EQ(75, 75, 0, 255, 0, 255);
    EXPECT_GL_NO_ERROR();

    glDeleteFramebuffers(1u, &framebuffer);
    glDeleteRenderbuffers(1u, &renderBuffer);
    EXPECT_GL_NO_ERROR();
}

TEST_P(EGLSurfaceTestD3D11, CreateSurfaceWithMSAA)
{
    ANGLE_SKIP_TEST_IF(!IsEGLClientExtensionEnabled("EGL_ANGLE_platform_angle_d3d"));

    // clang-format off
    const EGLint configAttributes[] =
    {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 0,
        EGL_DEPTH_SIZE, 0,
        EGL_STENCIL_SIZE, 0,
        EGL_SAMPLE_BUFFERS, 1,
        EGL_SAMPLES, 4,
        EGL_NONE
    };
    // clang-format on

    initializeDisplay();
    EGLConfig config;
    if (EGLWindow::FindEGLConfig(mDisplay, configAttributes, &config) == EGL_FALSE)
    {
        std::cout << "EGLConfig for 4xMSAA is not supported, skipping test" << std::endl;
        return;
    }

    initializeSurface(config);

    eglMakeCurrent(mDisplay, mWindowSurface, mWindowSurface, mContext);
    ASSERT_EGL_SUCCESS();

    GLuint program = createProgram();
    ASSERT_NE(0u, program);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    GLint positionLocation = glGetAttribLocation(program, angle::essl1_shaders::PositionAttrib());
    ASSERT_NE(-1, positionLocation);

    glUseProgram(program);

    const GLfloat halfPixelOffset = 0.5f * 2.0f / mOSWindow->getWidth();
    // clang-format off
    const GLfloat vertices[] =
    {
        -1.0f + halfPixelOffset,  1.0f, 0.5f,
        -1.0f + halfPixelOffset, -1.0f, 0.5f,
         1.0f,                   -1.0f, 0.5f
    };
    // clang-format on

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLocation);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    EXPECT_PIXEL_NEAR(0, 0, 127, 0, 0, 255, 10);
    EXPECT_GL_NO_ERROR();

    glDeleteProgram(program);
}

#endif  // ANGLE_ENABLE_D3D11

}  // anonymous namespace

ANGLE_INSTANTIATE_TEST(EGLSurfaceTest,
                       WithNoFixture(ES2_D3D9()),
                       WithNoFixture(ES2_D3D11()),
                       WithNoFixture(ES3_D3D11()),
                       WithNoFixture(ES2_OPENGL()),
                       WithNoFixture(ES3_OPENGL()),
                       WithNoFixture(ES2_OPENGLES()),
                       WithNoFixture(ES3_OPENGLES()),
                       WithNoFixture(ES2_VULKAN()),
                       WithNoFixture(ES3_VULKAN()),
                       WithNoFixture(ES2_VULKAN_SWIFTSHADER()),
                       WithNoFixture(ES3_VULKAN_SWIFTSHADER()));
ANGLE_INSTANTIATE_TEST(EGLPreRotationSurfaceTest,
                       WithNoFixture(ES2_VULKAN()),
                       WithNoFixture(ES3_VULKAN()));
ANGLE_INSTANTIATE_TEST(EGLPreRotationLargeSurfaceTest,
                       WithNoFixture(ES2_VULKAN()),
                       WithNoFixture(ES3_VULKAN()));
ANGLE_INSTANTIATE_TEST(EGLFloatSurfaceTest,
                       WithNoFixture(ES2_OPENGL()),
                       WithNoFixture(ES3_OPENGL()),
                       WithNoFixture(ES2_VULKAN()),
                       WithNoFixture(ES3_VULKAN()));
ANGLE_INSTANTIATE_TEST(EGLSurfaceTest3, WithNoFixture(ES3_VULKAN()));

#if defined(ANGLE_ENABLE_D3D11)
ANGLE_INSTANTIATE_TEST(EGLSurfaceTestD3D11, WithNoFixture(ES2_D3D11()), WithNoFixture(ES3_D3D11()));
#endif
