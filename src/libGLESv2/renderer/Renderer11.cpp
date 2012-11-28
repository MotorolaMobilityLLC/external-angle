//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Renderer11.cpp: Implements a back-end specific class for the D3D11 renderer.

#include "common/debug.h"
#include "libGLESv2/utilities.h"
#include "libGLESv2/renderer/Renderer11.h"

#include "libEGL/Config.h"
#include "libEGL/Display.h"

namespace rx
{

Renderer11::Renderer11(egl::Display *display, HDC hDc) : Renderer(display), mDc(hDc)
{
    mD3d11Module = NULL;
    mDxgiModule = NULL;

    mD3d11 = NULL;
    mDeviceContext = NULL;
}

Renderer11::~Renderer11()
{
    releaseDeviceResources();

    if (mDeviceContext)
    {
        mDeviceContext->Release();
        mDeviceContext = NULL;
    }

    if (mD3d11)
    {
        mD3d11->Release();
        mD3d11 = NULL;
    }

    if (mD3d11Module)
    {
        mD3d11Module = NULL;
    }

    if (mDxgiModule)
    {
        mDxgiModule = NULL;
    }

}

EGLint Renderer11::initialize()
{

    mDxgiModule = GetModuleHandle(TEXT("dxgi.dll"));
    mD3d11Module = GetModuleHandle(TEXT("d3d11.dll"));

    if (mD3d11Module == NULL || mDxgiModule == NULL)
    {
        ERR("No D3D11 or DXGI module found - aborting!\n");
        return EGL_NOT_INITIALIZED;
    }

    // TODO: device creation, any one-time setup.
    UNIMPLEMENTED();

    initializeDevice();

    return EGL_SUCCESS;
}

// do any one-time device initialization
// NOTE: this is also needed after a device lost/reset
// to reset the scene status and ensure the default states are reset.
void Renderer11::initializeDevice()
{
    // Permanent non-default states
    // TODO
    UNIMPLEMENTED();
}


int Renderer11::generateConfigs(ConfigDesc **configDescList)
{
    // TODO
    UNIMPLEMENTED();
    return 0;
}

void Renderer11::deleteConfigs(ConfigDesc *configDescList)
{
    delete [] (configDescList);
}

void Renderer11::startScene()
{
    // TODO: nop in d3d11?
}

void Renderer11::endScene()
{
    // TODO: nop in d3d11?
}

void Renderer11::sync(bool block)
{
    // TODO
    UNIMPLEMENTED();
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


void Renderer11::releaseDeviceResources()
{
    // TODO
    UNIMPLEMENTED();
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
    UNIMPLEMENTED();

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
    // TODO
    UNIMPLEMENTED();
    return 0;
}

const char *Renderer11::getAdapterDescription() const
{
    // TODO
    UNIMPLEMENTED();
    return "UNIMPLEMENTED";
}

GUID Renderer11::getAdapterIdentifier() const
{
    // TODO
    UNIMPLEMENTED();
    GUID foo = {};
    return foo;
}

bool Renderer11::getDXT1TextureSupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDXT3TextureSupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDXT5TextureSupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getDepthTextureSupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getFloat32TextureSupport(bool *filtering, bool *renderable)
{
    // TODO
    UNIMPLEMENTED();

    *filtering = false;
    *renderable = false;
    return false;
}

bool Renderer11::getFloat16TextureSupport(bool *filtering, bool *renderable)
{
    // TODO
    UNIMPLEMENTED();

    *filtering = false;
    *renderable = false;
    return false;
}

bool Renderer11::getLuminanceTextureSupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getLuminanceAlphaTextureSupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getTextureFilterAnisotropySupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

float Renderer11::getTextureMaxAnisotropy() const
{
    // TODO
    UNIMPLEMENTED();
    return 1.0f;
}

bool Renderer11::getEventQuerySupport()
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getVertexTextureSupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getNonPower2TextureSupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getOcclusionQuerySupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getInstancingSupport() const
{
    // TODO
    UNIMPLEMENTED();
    return false;
}

bool Renderer11::getShareHandleSupport() const
{
    // TODO
    UNIMPLEMENTED();

    // PIX doesn't seem to support using share handles, so disable them.
    return false && !gl::perfActive();
}

bool Renderer11::getShaderModel3Support() const
{
    // TODO
    UNIMPLEMENTED();
    return true;
}

float Renderer11::getMaxPointSize() const
{
    // TODO
    UNIMPLEMENTED();
    return 1.0f;
}

int Renderer11::getMaxTextureWidth() const
{
    // TODO
    UNIMPLEMENTED();
    return 1024;
}

int Renderer11::getMaxTextureHeight() const
{
    // TODO
    UNIMPLEMENTED();
    return 1024;
}

bool Renderer11::get32BitIndexSupport() const
{
    // TODO
    UNIMPLEMENTED();
    return true;
}

int Renderer11::getMinSwapInterval() const
{
    // TODO
    UNIMPLEMENTED();
    return 1;
}

int Renderer11::getMaxSwapInterval() const
{
    // TODO
    UNIMPLEMENTED();
    return 1;
}

int Renderer11::getMaxSupportedSamples() const
{
    // TODO
    UNIMPLEMENTED();
    return 1;
}

}