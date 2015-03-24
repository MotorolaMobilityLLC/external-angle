//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// RenderbufferGL.h: Defines the class interface for RenderbufferGL.

#ifndef LIBANGLE_RENDERER_GL_RENDERBUFFERGL_H_
#define LIBANGLE_RENDERER_GL_RENDERBUFFERGL_H_

#include "libANGLE/renderer/RenderbufferImpl.h"

namespace rx
{

class RenderbufferGL : public RenderbufferImpl
{
  public:
    RenderbufferGL();
    ~RenderbufferGL() override;

    virtual gl::Error setStorage(GLenum internalformat, size_t width, size_t height) override;
    virtual gl::Error setStorageMultisample(size_t samples, GLenum internalformat, size_t width, size_t height) override;

  private:
    DISALLOW_COPY_AND_ASSIGN(RenderbufferGL);
};

}

#endif // LIBANGLE_RENDERER_GL_RENDERBUFFERGL_H_
