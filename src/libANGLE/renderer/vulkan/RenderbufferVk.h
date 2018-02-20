//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// RenderbufferVk.h:
//    Defines the class interface for RenderbufferVk, implementing RenderbufferImpl.
//

#ifndef LIBANGLE_RENDERER_VULKAN_RENDERBUFFERVK_H_
#define LIBANGLE_RENDERER_VULKAN_RENDERBUFFERVK_H_

#include "libANGLE/renderer/RenderbufferImpl.h"
#include "libANGLE/renderer/vulkan/RenderTargetVk.h"
#include "libANGLE/renderer/vulkan/vk_utils.h"

namespace rx
{

class RenderbufferVk : public RenderbufferImpl, public ResourceVk
{
  public:
    RenderbufferVk(const gl::RenderbufferState &state);
    ~RenderbufferVk() override;

    gl::Error onDestroy(const gl::Context *context) override;

    gl::Error setStorage(const gl::Context *context,
                         GLenum internalformat,
                         size_t width,
                         size_t height) override;
    gl::Error setStorageMultisample(const gl::Context *context,
                                    size_t samples,
                                    GLenum internalformat,
                                    size_t width,
                                    size_t height) override;
    gl::Error setStorageEGLImageTarget(const gl::Context *context, egl::Image *image) override;

    gl::Error getAttachmentRenderTarget(const gl::Context *context,
                                        GLenum binding,
                                        const gl::ImageIndex &imageIndex,
                                        FramebufferAttachmentRenderTarget **rtOut) override;

    gl::Error initializeContents(const gl::Context *context,
                                 const gl::ImageIndex &imageIndex) override;

  private:
    vk::Image mImage;
    vk::DeviceMemory mDeviceMemory;
    vk::ImageView mImageView;
    size_t mRequiredSize;
    RenderTargetVk mRenderTarget;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_VULKAN_RENDERBUFFERVK_H_
