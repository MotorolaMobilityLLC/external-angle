//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Renderer11.cpp: Implements a back-end specific class for the D3D11 renderer.

#include "common/debug.h"
#include "libGLESv2/main.h"
#include "libGLESv2/utilities.h"
#include "libGLESv2/mathutil.h"
#include "libGLESv2/Buffer.h"
#include "libGLESv2/Program.h"
#include "libGLESv2/ProgramBinary.h"
#include "libGLESv2/Framebuffer.h"
#include "libGLESv2/renderer/Renderer11.h"
#include "libGLESv2/renderer/RenderTarget11.h"
#include "libGLESv2/renderer/renderer11_utils.h"
#include "libGLESv2/renderer/ShaderExecutable11.h"
#include "libGLESv2/renderer/SwapChain11.h"
#include "libGLESv2/renderer/Image11.h"
#include "libGLESv2/renderer/VertexBuffer11.h"
#include "libGLESv2/renderer/IndexBuffer11.h"

#include "libEGL/Config.h"
#include "libEGL/Display.h"

namespace rx
{
static const DXGI_FORMAT RenderTargetFormats[] =
    {
        DXGI_FORMAT_R8G8B8A8_UNORM
    };

static const DXGI_FORMAT DepthStencilFormats[] =
    {
        DXGI_FORMAT_D24_UNORM_S8_UINT
    };

Renderer11::Renderer11(egl::Display *display, HDC hDc) : Renderer(display), mDc(hDc)
{
    mD3d11Module = NULL;
    mDxgiModule = NULL;

    mDeviceLost = false;

    mDevice = NULL;
    mDeviceContext = NULL;
    mDxgiAdapter = NULL;
    mDxgiFactory = NULL;
}

Renderer11::~Renderer11()
{
    releaseDeviceResources();

    if (mDxgiFactory)
    {
        mDxgiFactory->Release();
        mDxgiFactory = NULL;
    }

    if (mDxgiAdapter)
    {
        mDxgiAdapter->Release();
        mDxgiAdapter = NULL;
    }

    if (mDeviceContext)
    {
        mDeviceContext->Release();
        mDeviceContext = NULL;
    }

    if (mDevice)
    {
        mDevice->Release();
        mDevice = NULL;
    }

    if (mD3d11Module)
    {
        FreeLibrary(mD3d11Module);
        mD3d11Module = NULL;
    }

    if (mDxgiModule)
    {
        FreeLibrary(mDxgiModule);
        mDxgiModule = NULL;
    }
}

Renderer11 *Renderer11::makeRenderer11(Renderer *renderer)
{
    ASSERT(dynamic_cast<rx::Renderer11*>(renderer) != NULL);
    return static_cast<rx::Renderer11*>(renderer);
}

EGLint Renderer11::initialize()
{
    if (!initializeCompiler())
    {
        return EGL_NOT_INITIALIZED;
    }

    mDxgiModule = LoadLibrary(TEXT("dxgi.dll"));
    mD3d11Module = LoadLibrary(TEXT("d3d11.dll"));

    if (mD3d11Module == NULL || mDxgiModule == NULL)
    {
        ERR("Could not load D3D11 or DXGI library - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }

    PFN_D3D11_CREATE_DEVICE D3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(mD3d11Module, "D3D11CreateDevice");

    if (D3D11CreateDevice == NULL)
    {
        ERR("Could not retrieve D3D11CreateDevice address - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }
    
    D3D_FEATURE_LEVEL featureLevel[] = 
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
        
    HRESULT result = D3D11CreateDevice(NULL,
                                       D3D_DRIVER_TYPE_HARDWARE,
                                       NULL,
                                       #if defined(_DEBUG)
                                       D3D11_CREATE_DEVICE_DEBUG,
                                       #else
                                       0,
                                       #endif
                                       featureLevel,
                                       sizeof(featureLevel)/sizeof(featureLevel[0]),
                                       D3D11_SDK_VERSION,
                                       &mDevice,
                                       &mFeatureLevel,
                                       &mDeviceContext);
    
    if (!mDevice || FAILED(result))
    {
        ERR("Could not create D3D11 device - aborting!\n");
        return EGL_NOT_INITIALIZED;   // Cleanup done by destructor through glDestroyRenderer
    }

    IDXGIDevice *dxgiDevice = NULL;
    result = mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    if (FAILED(result))
    {
        ERR("Could not query DXGI device - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }

    result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDxgiAdapter);

    if (FAILED(result))
    {
        ERR("Could not retrieve DXGI adapter - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }

    dxgiDevice->Release();

    mDxgiAdapter->GetDesc(&mAdapterDescription);
    memset(mDescription, 0, sizeof(mDescription));
    wcstombs(mDescription, mAdapterDescription.Description, sizeof(mDescription) - 1);

    result = mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDxgiFactory);

    if (!mDxgiFactory || FAILED(result))
    {
        ERR("Could not create DXGI factory - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }

    initializeDevice();

    return EGL_SUCCESS;
}

// do any one-time device initialization
// NOTE: this is also needed after a device lost/reset
// to reset the scene status and ensure the default states are reset.
void Renderer11::initializeDevice()
{
    mStateCache.initialize(mDevice);

    markAllStateDirty();

    // Permanent non-default states
    // TODO
    // UNIMPLEMENTED();
}

int Renderer11::generateConfigs(ConfigDesc **configDescList)
{
    unsigned int numRenderFormats = sizeof(RenderTargetFormats) / sizeof(RenderTargetFormats[0]);
    unsigned int numDepthFormats = sizeof(DepthStencilFormats) / sizeof(DepthStencilFormats[0]);
    (*configDescList) = new ConfigDesc[numRenderFormats * numDepthFormats];
    int numConfigs = 0;
    
    for (unsigned int formatIndex = 0; formatIndex < numRenderFormats; formatIndex++)
    {
        for (unsigned int depthStencilIndex = 0; depthStencilIndex < numDepthFormats; depthStencilIndex++)
        {
            DXGI_FORMAT renderTargetFormat = RenderTargetFormats[formatIndex];

            UINT formatSupport = 0;
            HRESULT result = mDevice->CheckFormatSupport(renderTargetFormat, &formatSupport);
            
            if (SUCCEEDED(result) && (formatSupport & D3D11_FORMAT_SUPPORT_RENDER_TARGET))
            {
                DXGI_FORMAT depthStencilFormat = DepthStencilFormats[depthStencilIndex];

                UINT formatSupport = 0;
                HRESULT result = mDevice->CheckFormatSupport(depthStencilFormat, &formatSupport);

                if (SUCCEEDED(result) && (formatSupport & D3D11_FORMAT_SUPPORT_DEPTH_STENCIL))
                {
                    ConfigDesc newConfig;
                    newConfig.renderTargetFormat = d3d11_gl::ConvertBackBufferFormat(renderTargetFormat);
                    newConfig.depthStencilFormat = d3d11_gl::ConvertDepthStencilFormat(depthStencilFormat);
                    newConfig.multiSample = 0;     // FIXME: enumerate multi-sampling
                    newConfig.fastConfig = true;   // Assume all DX11 format conversions to be fast

                    (*configDescList)[numConfigs++] = newConfig;
                }
            }
        }
    }

    return numConfigs;
}

void Renderer11::deleteConfigs(ConfigDesc *configDescList)
{
    delete [] (configDescList);
}

void Renderer11::sync(bool block)
{
    // TODO
    UNIMPLEMENTED();
}

SwapChain *Renderer11::createSwapChain(HWND window, HANDLE shareHandle, GLenum backBufferFormat, GLenum depthBufferFormat)
{
    return new rx::SwapChain11(this, window, shareHandle, backBufferFormat, depthBufferFormat);
}

void Renderer11::setSamplerState(gl::SamplerType type, int index, const gl::SamplerState &samplerState)
{
    // TODO
    UNIMPLEMENTED();
}

void Renderer11::setTexture(gl::SamplerType type, int index, gl::Texture *texture)
{
    // TODO
    UNIMPLEMENTED();
}

void Renderer11::setRasterizerState(const gl::RasterizerState &rasterState)
{
    if (mForceSetRasterState || memcmp(&rasterState, &mCurRasterState, sizeof(gl::RasterizerState)) != 0)
    {
        ID3D11RasterizerState *dxRasterState = mStateCache.getRasterizerState(rasterState, mScissorEnabled,
                                                                              mCurDepthSize);
        if (!dxRasterState)
        {
            ERR("NULL blend state returned by RenderStateCache::getRasterizerState, setting the default"
                "rasterizer state.");
        }

        mDeviceContext->RSSetState(dxRasterState);

        if (dxRasterState)
        {
            dxRasterState->Release();
        }
        mCurRasterState = rasterState;
    }

    mForceSetRasterState = false;
}

void Renderer11::setBlendState(const gl::BlendState &blendState, const gl::Color &blendColor,
                               unsigned int sampleMask)
{
    if (mForceSetBlendState ||
        memcmp(&blendState, &mCurBlendState, sizeof(gl::BlendState)) != 0 ||
        memcmp(&blendColor, &mCurBlendColor, sizeof(gl::Color)) != 0 ||
        sampleMask != mCurSampleMask)
    {
        ID3D11BlendState *dxBlendState = mStateCache.getBlendState(blendState);
        if (!dxBlendState)
        {
            ERR("NULL blend state returned by RenderStateCache::getBlendState, setting the default "
                "blend state.");
        }

        const float blendColors[] = { blendColor.red, blendColor.green, blendColor.blue, blendColor.alpha };
        mDeviceContext->OMSetBlendState(dxBlendState, blendColors, sampleMask);

        if (dxBlendState)
        {
            dxBlendState->Release();
        }
        mCurBlendState = blendState;
        mCurBlendColor = blendColor;
        mCurSampleMask = sampleMask;
    }

    mForceSetBlendState = false;
}

void Renderer11::setDepthStencilState(const gl::DepthStencilState &depthStencilState, int stencilRef,
                                      int stencilBackRef, bool frontFaceCCW)
{
    if (mForceSetDepthStencilState ||
        memcmp(&depthStencilState, &mCurDepthStencilState, sizeof(gl::DepthStencilState)) != 0 ||
        stencilRef != mCurStencilRef || stencilBackRef != mCurStencilBackRef)
    {
        if (depthStencilState.stencilWritemask != depthStencilState.stencilBackWritemask ||
            stencilRef != stencilBackRef ||
            depthStencilState.stencilMask != depthStencilState.stencilBackMask)
        {
            ERR("Separate front/back stencil writemasks, reference values, or stencil mask values are "
                "invalid under WebGL.");
            return error(GL_INVALID_OPERATION);
        }

        ID3D11DepthStencilState *dxDepthStencilState = mStateCache.getDepthStencilState(depthStencilState);
        if (!dxDepthStencilState)
        {
            ERR("NULL depth stencil state returned by RenderStateCache::getDepthStencilState, "
                "setting the default depth stencil state.");
        }

        mDeviceContext->OMSetDepthStencilState(dxDepthStencilState, static_cast<UINT>(stencilRef));

        if (dxDepthStencilState)
        {
            dxDepthStencilState->Release();
        }
        mCurDepthStencilState = depthStencilState;
        mCurStencilRef = stencilRef;
        mCurStencilBackRef = stencilBackRef;
    }

    mForceSetDepthStencilState = false;
}

void Renderer11::setScissorRectangle(const gl::Rectangle &scissor, bool enabled)
{
    if (mForceSetScissor || memcmp(&scissor, &mCurScissor, sizeof(gl::Rectangle)) != 0 ||
        enabled != mScissorEnabled)
    {
        if (enabled)
        {
            D3D11_RECT rect;
            rect.left = gl::clamp(scissor.x, 0, static_cast<int>(mRenderTargetDesc.width));
            rect.top = gl::clamp(scissor.y, 0, static_cast<int>(mRenderTargetDesc.height));
            rect.right = gl::clamp(scissor.x + scissor.width, 0, static_cast<int>(mRenderTargetDesc.width));
            rect.bottom = gl::clamp(scissor.y + scissor.height, 0, static_cast<int>(mRenderTargetDesc.height));

            mDeviceContext->RSSetScissorRects(1, &rect);
        }

        if (enabled != mScissorEnabled)
        {
            mForceSetRasterState = true;
        }

        mCurScissor = scissor;
        mScissorEnabled = enabled;
    }

    mForceSetScissor = false;
}

bool Renderer11::setViewport(const gl::Rectangle &viewport, float zNear, float zFar, GLenum drawMode, GLenum frontFace, 
                             bool ignoreViewport, gl::ProgramBinary *currentProgram, bool forceSetUniforms)
{
    gl::Rectangle actualViewport = viewport;
    float actualZNear = gl::clamp01(zNear);
    float actualZFar = gl::clamp01(zFar);
    if (ignoreViewport)
    {
        actualViewport.x = 0;
        actualViewport.y = 0;
        actualViewport.width = mRenderTargetDesc.width;
        actualViewport.height = mRenderTargetDesc.height;
        actualZNear = 0.0f;
        actualZFar = 1.0f;
    }

    D3D11_VIEWPORT dxViewport;
    dxViewport.TopLeftX = gl::clamp(actualViewport.x, 0, static_cast<int>(mRenderTargetDesc.width));
    dxViewport.TopLeftY = gl::clamp(actualViewport.y, 0, static_cast<int>(mRenderTargetDesc.height));
    dxViewport.Width = gl::clamp(actualViewport.width, 0, static_cast<int>(mRenderTargetDesc.width) - static_cast<int>(dxViewport.TopLeftX));
    dxViewport.Height = gl::clamp(actualViewport.height, 0, static_cast<int>(mRenderTargetDesc.height) - static_cast<int>(dxViewport.TopLeftY));
    dxViewport.MinDepth = actualZNear;
    dxViewport.MaxDepth = actualZFar;

    if (dxViewport.Width <= 0 || dxViewport.Height <= 0)
    {
        return false;   // Nothing to render
    }

    bool viewportChanged =  mForceSetViewport || memcmp(&actualViewport, &mCurViewport, sizeof(gl::Rectangle)) != 0 ||
                            actualZNear != mCurNear || actualZFar != mCurFar;

    if (viewportChanged)
    {
        mDeviceContext->RSSetViewports(1, &dxViewport);

        mCurViewport = actualViewport;
        mCurNear = actualZNear;
        mCurFar = actualZFar;
    }

    if (currentProgram && (viewportChanged || forceSetUniforms))
    {
        currentProgram->applyDxHalfPixelSize(0.0f, 0.0f);

        // These values are used for computing gl_FragCoord in Program::linkVaryings().
        currentProgram->applyDxCoord(actualViewport.width  * 0.5f,
                                     actualViewport.height * 0.5f,
                                     actualViewport.x + (actualViewport.width  * 0.5f),
                                     actualViewport.y + (actualViewport.height * 0.5f));

        GLfloat ccw = !gl::IsTriangleMode(drawMode) ? 0.0f : (frontFace == GL_CCW ? 1.0f : -1.0f);
        currentProgram->applyDxDepthFront((actualZFar - actualZNear) * 0.5f, (actualZNear + actualZFar) * 0.5f, ccw);

        currentProgram->applyDxDepthRange(actualZNear, actualZFar, actualZFar - actualZNear);
    }

    mForceSetViewport = false;
    return true;
}

bool Renderer11::applyPrimitiveType(GLenum mode, GLsizei count)
{
    D3D11_PRIMITIVE_TOPOLOGY primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

    switch (mode)
    {
      case GL_POINTS:         primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;   break;
      case GL_LINES:          primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;      break;
      case GL_LINE_LOOP:      UNIMPLEMENTED();   /* TODO */                              break;
      case GL_LINE_STRIP:     primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;     break;
      case GL_TRIANGLES:      primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;  break;
      case GL_TRIANGLE_STRIP: primitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
      case GL_TRIANGLE_FAN:   UNIMPLEMENTED();   /* TODO */                              break;
      default:
        return error(GL_INVALID_ENUM, false);
    }

    mDeviceContext->IASetPrimitiveTopology(primitiveTopology);

    return count > 0;
}

bool Renderer11::applyRenderTarget(gl::Framebuffer *framebuffer)
{
    // Get the color render buffer and serial
    gl::Renderbuffer *renderbufferObject = NULL;
    unsigned int renderTargetSerial = 0;
    if (framebuffer->getColorbufferType() != GL_NONE)
    {
        renderbufferObject = framebuffer->getColorbuffer();

        if (!renderbufferObject)
        {
            ERR("render target pointer unexpectedly null.");
            return false;
        }

        renderTargetSerial = renderbufferObject->getSerial();
    }

    // Get the depth stencil render buffer and serials
    gl::Renderbuffer *depthStencil = NULL;
    unsigned int depthbufferSerial = 0;
    unsigned int stencilbufferSerial = 0;
    if (framebuffer->getDepthbufferType() != GL_NONE)
    {
        depthStencil = framebuffer->getDepthbuffer();
        if (!depthStencil)
        {
            ERR("Depth stencil pointer unexpectedly null.");
            return false;
        }

        depthbufferSerial = depthStencil->getSerial();
    }
    else if (framebuffer->getStencilbufferType() != GL_NONE)
    {
        depthStencil = framebuffer->getStencilbuffer();
        if (!depthStencil)
        {
            ERR("Depth stencil pointer unexpectedly null.");
            return false;
        }

        stencilbufferSerial = depthStencil->getSerial();
    }

    // Extract the render target dimensions and view
    unsigned int renderTargetWidth = 0;
    unsigned int renderTargetHeight = 0;
    GLenum renderTargetFormat = 0;
    ID3D11RenderTargetView* framebufferRTV = NULL;
    if (renderbufferObject)
    {
        RenderTarget11 *renderTarget = RenderTarget11::makeRenderTarget11(renderbufferObject->getRenderTarget());
        if (!renderTarget)
        {
            ERR("render target pointer unexpectedly null.");
            return false;
        }

        framebufferRTV = renderTarget->getRenderTargetView();
        if (!framebufferRTV)
        {
            ERR("render target view pointer unexpectedly null.");
            return false;
        }

        renderTargetWidth = renderbufferObject->getWidth();
        renderTargetHeight = renderbufferObject->getHeight();
        renderTargetFormat = renderbufferObject->getActualFormat();
    }

    // Extract the depth stencil sizes and view
    unsigned int depthSize = 0;
    unsigned int stencilSize = 0;
    ID3D11DepthStencilView* framebufferDSV = NULL;
    if (depthStencil)
    {
        RenderTarget11 *depthStencilRenderTarget = RenderTarget11::makeRenderTarget11(depthStencil->getDepthStencil());
        if (!depthStencilRenderTarget)
        {
            ERR("render target pointer unexpectedly null.");
            if (framebufferRTV)
            {
                framebufferRTV->Release();
            }
            return false;
        }

        framebufferDSV = depthStencilRenderTarget->getDepthStencilView();
        if (!framebufferDSV)
        {
            ERR("depth stencil view pointer unexpectedly null.");
            if (framebufferRTV)
            {
                framebufferRTV->Release();
            }
            return false;
        }

        // If there is no render buffer, the width, height and format values come from
        // the depth stencil
        if (!renderbufferObject)
        {
            renderTargetWidth = depthStencil->getWidth();
            renderTargetHeight = depthStencil->getHeight();
            renderTargetFormat = depthStencil->getActualFormat();
        }

        depthSize = depthStencil->getDepthSize();
        stencilSize = depthStencil->getStencilSize();
    }

    // Apply the render target and depth stencil
    if (!mRenderTargetDescInitialized || !mDepthStencilInitialized ||
        renderTargetSerial != mAppliedRenderTargetSerial ||
        depthbufferSerial != mAppliedDepthbufferSerial ||
        stencilbufferSerial != mAppliedStencilbufferSerial)
    {
        mDeviceContext->OMSetRenderTargets(1, &framebufferRTV, framebufferDSV);

        mRenderTargetDesc.width = renderTargetWidth;
        mRenderTargetDesc.height = renderTargetHeight;
        mRenderTargetDesc.format = renderTargetFormat;
        mForceSetViewport = true; // TODO: It may not be required to clamp the viewport in D3D11
        mForceSetScissor = true; // TODO: It may not be required to clamp the scissor in D3D11

        if (!mDepthStencilInitialized || depthSize != mCurDepthSize)
        {
            mCurDepthSize = depthSize;
            mForceSetRasterState = true;
        }

        mCurStencilSize = stencilSize;

        mAppliedRenderTargetSerial = renderTargetSerial;
        mAppliedDepthbufferSerial = depthbufferSerial;
        mAppliedStencilbufferSerial = stencilbufferSerial;
        mRenderTargetDescInitialized = true;
        mDepthStencilInitialized = true;
    }

    if (framebufferRTV)
    {
        framebufferRTV->Release();
    }
    if (framebufferDSV)
    {
        framebufferDSV->Release();
    }

    return true;
}

GLenum Renderer11::applyVertexBuffer(gl::ProgramBinary *programBinary, gl::VertexAttribute vertexAttributes[], GLint first, GLsizei count, GLsizei instances)
{
    // TODO: Create/update vertex buffers for arbitrary GL attributes
    ASSERT(vertexAttributes[0].mBoundBuffer.get() == 0);   // UNIMPLEMENTED();

    UINT stride = vertexAttributes[0].mStride != 0 ? vertexAttributes[0].mStride : vertexAttributes[0].typeSize();
    UINT size = stride * count;

    D3D11_BUFFER_DESC vertexBufferDescription = {0};
    vertexBufferDescription.ByteWidth = size;
    vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDescription.MiscFlags = 0;
    vertexBufferDescription.StructureByteStride = 0;

    ID3D11Buffer *vertexBuffer = NULL;
    HRESULT result = mDevice->CreateBuffer(&vertexBufferDescription, NULL, &vertexBuffer);
    ASSERT(SUCCEEDED(result));

    D3D11_MAPPED_SUBRESOURCE map;
    result = mDeviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
    ASSERT(SUCCEEDED(result));
    memcpy(map.pData, vertexAttributes[0].mPointer, size);
    mDeviceContext->Unmap(vertexBuffer, 0);

    UINT offset = 0;
    mDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    vertexBuffer->Release();

    // TODO: Build the input layout from the (translated) attribute information
    D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[1] =
    {
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    ShaderExecutable *vertexExecutable = programBinary->getVertexExecutable();

    ID3D11InputLayout *inputLayout = NULL;
    result = mDevice->CreateInputLayout(inputElementDescriptions, 1, vertexExecutable->getFunction(), vertexExecutable->getLength(), &inputLayout);
    ASSERT(SUCCEEDED(result));
    
    mDeviceContext->IASetInputLayout(inputLayout);
    inputLayout->Release();   // TODO: Build a cache of input layouts

    return GL_NO_ERROR;
}

GLenum Renderer11::applyIndexBuffer(const GLvoid *indices, gl::Buffer *elementArrayBuffer, GLsizei count, GLenum mode, GLenum type, TranslatedIndexData *indexInfo)
{
    // TODO
    UNIMPLEMENTED();

    return GL_OUT_OF_MEMORY;
}

void Renderer11::drawArrays(GLenum mode, GLsizei count, GLsizei instances)
{
    mDeviceContext->Draw(count, 0);
}

void Renderer11::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, gl::Buffer *elementArrayBuffer, const TranslatedIndexData &indexInfo)
{
    // TODO
    UNIMPLEMENTED();
}

void Renderer11::applyShaders(gl::ProgramBinary *programBinary)
{
    unsigned int programBinarySerial = programBinary->getSerial();
    if (programBinarySerial != mAppliedProgramBinarySerial)
    {
        ShaderExecutable *vertexExe = programBinary->getVertexExecutable();
        ShaderExecutable *pixelExe = programBinary->getPixelExecutable();

        ID3D11VertexShader *vertexShader = NULL;
        if (vertexExe) vertexShader = ShaderExecutable11::makeShaderExecutable11(vertexExe)->getVertexShader();

        ID3D11PixelShader *pixelShader = NULL;
        if (pixelExe) pixelShader = ShaderExecutable11::makeShaderExecutable11(pixelExe)->getPixelShader();

        mDeviceContext->PSSetShader(pixelShader, NULL, 0);
        mDeviceContext->VSSetShader(vertexShader, NULL, 0);
        programBinary->dirtyAllUniforms();

        mAppliedProgramBinarySerial = programBinarySerial;
    }
}

void Renderer11::applyUniforms(const gl::UniformArray *uniformArray)
{
    // TODO
    if (uniformArray->size() != 0)
    {
        UNIMPLEMENTED();
    }
}

void Renderer11::clear(const gl::ClearParameters &clearParams, gl::Framebuffer *frameBuffer)
{
    if (clearParams.mask & GL_COLOR_BUFFER_BIT)
    {
        gl::Renderbuffer *renderbufferObject = frameBuffer->getColorbuffer();
        if (renderbufferObject)
        {
            RenderTarget11 *renderTarget = RenderTarget11::makeRenderTarget11(renderbufferObject->getRenderTarget());
            if (!renderTarget)
            {
                ERR("render target pointer unexpectedly null.");
                return;
            }

            ID3D11RenderTargetView *framebufferRTV = renderTarget->getRenderTargetView();
            if (!framebufferRTV)
            {
                ERR("render target view pointer unexpectedly null.");
                return;
            }

            if (mScissorEnabled && (mCurScissor.x > 0 || mCurScissor.y > 0 ||
                                    mCurScissor.x + mCurScissor.width < renderTarget->getWidth() ||
                                    mCurScissor.y + mCurScissor.height < renderTarget->getHeight()))
            {
                // TODO: clearing of subregion of render target
                UNIMPLEMENTED();
            }

            bool alphaUnmasked = (gl::GetAlphaSize(mRenderTargetDesc.format) == 0) || clearParams.colorMaskAlpha;
            const bool needMaskedColorClear = (clearParams.mask & GL_COLOR_BUFFER_BIT) &&
                                              !(clearParams.colorMaskRed && clearParams.colorMaskGreen &&
                                               clearParams.colorMaskBlue && alphaUnmasked);

            if (needMaskedColorClear)
            {
                // TODO: masked color clearing
                UNIMPLEMENTED();
            }
            else
            {
                const float clearValues[4] = { clearParams.colorClearValue.red,
                                               clearParams.colorClearValue.green,
                                               clearParams.colorClearValue.blue,
                                               clearParams.colorClearValue.alpha };
                mDeviceContext->ClearRenderTargetView(framebufferRTV, clearValues);
            }

            framebufferRTV->Release();
        }
    }
    if (clearParams.mask & GL_DEPTH_BUFFER_BIT || clearParams.mask & GL_STENCIL_BUFFER_BIT)
    {
        gl::Renderbuffer *renderbufferObject = frameBuffer->getDepthOrStencilbuffer();
        if (renderbufferObject)
        {
            RenderTarget11 *renderTarget = RenderTarget11::makeRenderTarget11(renderbufferObject->getRenderTarget());
            if (!renderTarget)
            {
                ERR("render target pointer unexpectedly null.");
                return;
            }

            ID3D11DepthStencilView *framebufferDSV = renderTarget->getDepthStencilView();
            if (!framebufferDSV)
            {
                ERR("depth stencil view pointer unexpectedly null.");
                return;
            }

            if (mScissorEnabled && (mCurScissor.x > 0 || mCurScissor.y > 0 ||
                                    mCurScissor.x + mCurScissor.width < renderTarget->getWidth() ||
                                    mCurScissor.y + mCurScissor.height < renderTarget->getHeight()))
            {
                // TODO: clearing of subregion of depth stencil view
                UNIMPLEMENTED();
            }

            unsigned int stencilUnmasked = 0x0;
            if ((clearParams.mask & GL_STENCIL_BUFFER_BIT) && frameBuffer->hasStencil())
            {
                unsigned int stencilSize = gl::GetStencilSize(frameBuffer->getStencilbuffer()->getActualFormat());
                stencilUnmasked = (0x1 << stencilSize) - 1;
            }

            const bool needMaskedStencilClear = (clearParams.mask & GL_STENCIL_BUFFER_BIT) &&
                                                (clearParams.stencilWriteMask & stencilUnmasked) != stencilUnmasked;

            if (needMaskedStencilClear)
            {
                // TODO: masked clearing of depth stencil
                UNIMPLEMENTED();
            }
            else
            {
                UINT clearFlags = 0;
                if (clearParams.mask & GL_DEPTH_BUFFER_BIT)
                {
                    clearFlags |= D3D11_CLEAR_DEPTH;
                }
                if (clearParams.mask & GL_STENCIL_BUFFER_BIT)
                {
                    clearFlags |= D3D11_CLEAR_STENCIL;
                }

                float depthClear = clearParams.depthClearValue;
                UINT8 stencilClear = clearParams.stencilClearValue & 0x000000FF;

                mDeviceContext->ClearDepthStencilView(framebufferDSV, clearFlags, depthClear, stencilClear);
            }

            framebufferDSV->Release();
        }
    }
}

void Renderer11::markAllStateDirty()
{
    mAppliedRenderTargetSerial = 0;
    mAppliedDepthbufferSerial = 0;
    mAppliedStencilbufferSerial = 0;
    mDepthStencilInitialized = false;
    mRenderTargetDescInitialized = false;

    mForceSetBlendState = true;
    mForceSetRasterState = true;
    mForceSetDepthStencilState = true;
    mForceSetScissor = true;
    mForceSetViewport = true;

    mAppliedProgramBinarySerial = 0;
}

void Renderer11::releaseDeviceResources()
{
    // TODO
    // UNIMPLEMENTED();
    mStateCache.clear();
}

void Renderer11::markDeviceLost()
{
    mDeviceLost = true;
}

bool Renderer11::isDeviceLost()
{
    return mDeviceLost;
}

// set notify to true to broadcast a message to all contexts of the device loss
bool Renderer11::testDeviceLost(bool notify)
{
    bool isLost = false;

    // TODO
    //UNIMPLEMENTED();

    if (isLost)
    {
        // ensure we note the device loss --
        // we'll probably get this done again by markDeviceLost
        // but best to remember it!
        // Note that we don't want to clear the device loss status here
        // -- this needs to be done by resetDevice
        mDeviceLost = true;
        if (notify)
        {
            mDisplay->notifyDeviceLost();
        }
    }

    return isLost;
}

bool Renderer11::testDeviceResettable()
{
    HRESULT status = D3D_OK;

    // TODO
    UNIMPLEMENTED();

    switch (status)
    {
      case D3DERR_DEVICENOTRESET:
      case D3DERR_DEVICEHUNG:
        return true;
      default:
        return false;
    }
}

bool Renderer11::resetDevice()
{
    releaseDeviceResources();

    // TODO
    UNIMPLEMENTED();

    // reset device defaults
    initializeDevice();
    mDeviceLost = false;

    return true;
}

DWORD Renderer11::getAdapterVendor() const
{
    return mAdapterDescription.VendorId;
}

const char *Renderer11::getAdapterDescription() const
{
    return mDescription;
}

GUID Renderer11::getAdapterIdentifier() const
{
    // TODO
    // UNIMPLEMENTED();
    GUID foo = {0};
    return foo;
}

bool Renderer11::getDXT1TextureSupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDXT3TextureSupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDXT5TextureSupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDepthTextureSupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getFloat32TextureSupport(bool *filtering, bool *renderable)
{
    // TODO
    // UNIMPLEMENTED();

    *filtering = false;
    *renderable = false;
    return false;
}

bool Renderer11::getFloat16TextureSupport(bool *filtering, bool *renderable)
{
    // TODO
    // UNIMPLEMENTED();

    *filtering = false;
    *renderable = false;
    return false;
}

bool Renderer11::getLuminanceTextureSupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getLuminanceAlphaTextureSupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getTextureFilterAnisotropySupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

float Renderer11::getTextureMaxAnisotropy() const
{
    // TODO
    // UNIMPLEMENTED();
    return 1.0f;
}

bool Renderer11::getEventQuerySupport()
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getVertexTextureSupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getNonPower2TextureSupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getOcclusionQuerySupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getInstancingSupport() const
{
    // TODO
    // UNIMPLEMENTED();
    return false;
}

bool Renderer11::getShareHandleSupport() const
{
    // TODO
    // UNIMPLEMENTED();

    // PIX doesn't seem to support using share handles, so disable them.
    return false && !gl::perfActive();
}

int Renderer11::getMajorShaderModel() const
{
    switch (mFeatureLevel)
    {
      case D3D_FEATURE_LEVEL_11_0: return D3D11_SHADER_MAJOR_VERSION;   // 5
      case D3D_FEATURE_LEVEL_10_1:
      case D3D_FEATURE_LEVEL_10_0: return D3D10_SHADER_MAJOR_VERSION;   // 4
      default: UNREACHABLE();      return 0;
    }
}

float Renderer11::getMaxPointSize() const
{
    // TODO
    // UNIMPLEMENTED();
    return 1.0f;
}

int Renderer11::getMaxTextureWidth() const
{
    switch (mFeatureLevel)
    {
      case D3D_FEATURE_LEVEL_11_0: return D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;   // 16384
      case D3D_FEATURE_LEVEL_10_1:
      case D3D_FEATURE_LEVEL_10_0: return D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION;   // 8192
      default: UNREACHABLE();      return 0;
    }
}

int Renderer11::getMaxTextureHeight() const
{
    switch (mFeatureLevel)
    {
      case D3D_FEATURE_LEVEL_11_0: return D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;   // 16384
      case D3D_FEATURE_LEVEL_10_1:
      case D3D_FEATURE_LEVEL_10_0: return D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION;   // 8192
      default: UNREACHABLE();      return 0;
    }
}

bool Renderer11::get32BitIndexSupport() const
{
    switch (mFeatureLevel)
    {
      case D3D_FEATURE_LEVEL_11_0: 
      case D3D_FEATURE_LEVEL_10_1:
      case D3D_FEATURE_LEVEL_10_0: return D3D10_REQ_DRAWINDEXED_INDEX_COUNT_2_TO_EXP >= 32;   // true
      default: UNREACHABLE();      return false;
    }
}

int Renderer11::getMinSwapInterval() const
{
    return 0;
}

int Renderer11::getMaxSwapInterval() const
{
    return 4;
}

int Renderer11::getMaxSupportedSamples() const
{
    // TODO
    // UNIMPLEMENTED();
    return 1;
}

bool Renderer11::copyToRenderTarget(TextureStorage2D *dest, TextureStorage2D *source)
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::copyToRenderTarget(TextureStorageCubeMap *dest, TextureStorageCubeMap *source)
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::copyImage(gl::Framebuffer *framebuffer, const RECT &sourceRect, GLenum destFormat,
                           GLint xoffset, GLint yoffset, TextureStorage2D *storage, GLint level)
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::copyImage(gl::Framebuffer *framebuffer, const RECT &sourceRect, GLenum destFormat,
                           GLint xoffset, GLint yoffset, TextureStorageCubeMap *storage, GLenum target, GLint level)
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

RenderTarget *Renderer11::createRenderTarget(SwapChain *swapChain, bool depth)
{
    SwapChain11 *swapChain11 = SwapChain11::makeSwapChain11(swapChain); 
    RenderTarget11 *renderTarget = NULL;
    if (depth)
    {
        renderTarget = new RenderTarget11(this, swapChain11->getDepthStencil(), swapChain11->getWidth(), swapChain11->getHeight());
    }
    else
    {
        renderTarget = new RenderTarget11(this, swapChain11->getRenderTarget(), swapChain11->getWidth(), swapChain11->getHeight());
    }
    return renderTarget;
}

RenderTarget *Renderer11::createRenderTarget(int width, int height, GLenum format, GLsizei samples, bool depth)
{
    // TODO
    UNIMPLEMENTED();
    return NULL;
}

ShaderExecutable *Renderer11::loadExecutable(const void *function, size_t length, GLenum type, void *data)
{
    ShaderExecutable11 *executable = NULL;

    switch (type)
    {
      case GL_VERTEX_SHADER:
        {
            ID3D11VertexShader *vshader = NULL;
            HRESULT result = mDevice->CreateVertexShader(function, length, NULL, &vshader);
            ASSERT(SUCCEEDED(result));

            if (vshader)
            {
                executable = new ShaderExecutable11(function, length, vshader);
            }
        }
        break;
      case GL_FRAGMENT_SHADER:
        {
            ID3D11PixelShader *pshader = NULL;
            HRESULT result = mDevice->CreatePixelShader(function, length, NULL, &pshader);
            ASSERT(SUCCEEDED(result));

            if (pshader)
            {
                executable = new ShaderExecutable11(function, length, pshader);
            }
        }
        break;
      default:
        UNREACHABLE();
        break;
    }

    return executable;
}

ShaderExecutable *Renderer11::compileToExecutable(gl::InfoLog &infoLog, const char *shaderHLSL, GLenum type)
{
    const char *profile = NULL;

    switch (type)
    {
      case GL_VERTEX_SHADER:
        profile = "vs_4_0";
        break;
      case GL_FRAGMENT_SHADER:
        profile = "ps_4_0";
        break;
      default:
        UNREACHABLE();
        return NULL;
    }

    ID3DBlob *binary = compileToBinary(infoLog, shaderHLSL, profile, false);
    if (!binary)
        return NULL;

    ShaderExecutable *executable = loadExecutable((DWORD *)binary->GetBufferPointer(), binary->GetBufferSize(), type, NULL);
    binary->Release();

    return executable;
}

VertexBuffer *Renderer11::createVertexBuffer()
{
    return new VertexBuffer11(this);
}

IndexBuffer *Renderer11::createIndexBuffer()
{
    return new IndexBuffer11(this);
}

bool Renderer11::blitRect(gl::Framebuffer *readTarget, gl::Rectangle *readRect, gl::Framebuffer *drawTarget, gl::Rectangle *drawRect,
                          bool blitRenderTarget, bool blitDepthStencil)
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

void Renderer11::readPixels(gl::Framebuffer *framebuffer, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type,
                            GLsizei outputPitch, bool packReverseRowOrder, GLint packAlignment, void* pixels)
{
    // TODO
    UNIMPLEMENTED();
    return;
}

Image *Renderer11::createImage()
{
    return new Image11();
}

void Renderer11::generateMipmap(Image *dest, Image *src)
{
    // TODO
    UNIMPLEMENTED();
    return;
}

}