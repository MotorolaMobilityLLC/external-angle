//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// RenderBufferMtl.mm:
//    Implements the class methods for RenderBufferMtl.
//

#include "libANGLE/renderer/metal/RenderBufferMtl.h"

#include "libANGLE/renderer/metal/ContextMtl.h"
#include "libANGLE/renderer/metal/mtl_format_utils.h"
#include "libANGLE/renderer/metal/mtl_utils.h"

namespace rx
{

RenderbufferMtl::RenderbufferMtl(const gl::RenderbufferState &state) : RenderbufferImpl(state) {}

RenderbufferMtl::~RenderbufferMtl() {}

void RenderbufferMtl::onDestroy(const gl::Context *context)
{
    releaseTexture();
}

void RenderbufferMtl::releaseTexture()
{
    mTexture = nullptr;
}

angle::Result RenderbufferMtl::setStorageImpl(const gl::Context *context,
                                              GLsizei samples,
                                              GLenum internalformat,
                                              GLsizei width,
                                              GLsizei height)
{
    ContextMtl *contextMtl = mtl::GetImpl(context);

    // NOTE(hqle): Support MSAA
    ANGLE_CHECK(contextMtl, samples == 1, "Multisample is not supported atm.", GL_INVALID_VALUE);

    if (mTexture != nullptr && mTexture->valid())
    {
        // Check against the state if we need to recreate the storage.
        if (internalformat != mState.getFormat().info->internalFormat ||
            width != mState.getWidth() || height != mState.getHeight())
        {
            releaseTexture();
        }
    }

    const gl::InternalFormat &internalFormat = gl::GetSizedInternalFormatInfo(internalformat);
    angle::FormatID angleFormatId =
        angle::Format::InternalFormatToID(internalFormat.sizedInternalFormat);
    mFormat = contextMtl->getPixelFormat(angleFormatId);

    if ((mTexture == nullptr || !mTexture->valid()) && (width != 0 && height != 0))
    {
        ANGLE_TRY(mtl::Texture::Make2DTexture(contextMtl, mFormat, width, height, 1, false,
                                              mFormat.hasDepthAndStencilBits(), &mTexture));

        mRenderTarget.set(mTexture, mtl::kZeroNativeMipLevel, 0, mFormat);

        // For emulated channels that GL texture intends to not have,
        // we need to initialize their content.
        bool emulatedChannels = mtl::IsFormatEmulated(mFormat);
        if (emulatedChannels)
        {
            auto index = mtl::ImageNativeIndex::FromBaseZeroGLIndex(gl::ImageIndex::Make2D(0));

            ANGLE_TRY(mtl::InitializeTextureContents(context, mTexture, mFormat, index));
        }
    }

    return angle::Result::Continue;
}

angle::Result RenderbufferMtl::setStorage(const gl::Context *context,
                                          GLenum internalformat,
                                          GLsizei width,
                                          GLsizei height)
{
    return setStorageImpl(context, 1, internalformat, width, height);
}

angle::Result RenderbufferMtl::setStorageMultisample(const gl::Context *context,
                                                     GLsizei samples,
                                                     GLenum internalformat,
                                                     GLsizei width,
                                                     GLsizei height,
                                                     gl::MultisamplingMode mode)
{
    // NOTE(hqle): Support MSAA
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result RenderbufferMtl::setStorageEGLImageTarget(const gl::Context *context,
                                                        egl::Image *image)
{
    // NOTE(hqle): Support EGLimage
    UNIMPLEMENTED();
    return angle::Result::Stop;
}

angle::Result RenderbufferMtl::getAttachmentRenderTarget(const gl::Context *context,
                                                         GLenum binding,
                                                         const gl::ImageIndex &imageIndex,
                                                         GLsizei samples,
                                                         FramebufferAttachmentRenderTarget **rtOut)
{
    // NOTE(hqle): Support MSAA.
    ASSERT(mTexture && mTexture->valid());
    *rtOut = &mRenderTarget;
    return angle::Result::Continue;
}

angle::Result RenderbufferMtl::initializeContents(const gl::Context *context,
                                                  const gl::ImageIndex &imageIndex)
{
    return mtl::InitializeTextureContents(context, mTexture, mFormat,
                                          mtl::ImageNativeIndex::FromBaseZeroGLIndex(imageIndex));
}
}
