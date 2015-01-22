//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// DisplayGL.h: Defines the class interface for DisplayGL.

#ifndef LIBANGLE_RENDERER_GL_DISPLAYGL_H_
#define LIBANGLE_RENDERER_GL_DISPLAYGL_H_

#include "libANGLE/renderer/DisplayImpl.h"

namespace rx
{

class RendererGL;

class DisplayGL : public DisplayImpl
{
  public:
    DisplayGL();
    ~DisplayGL() override;

    egl::Error initialize(egl::Display *display) override;
    void terminate() override;

    egl::Error createContext(const egl::Config *config, const gl::Context *shareContext, const egl::AttributeMap &attribs,
                             gl::Context **outContext) override;

  private:
    DISALLOW_COPY_AND_ASSIGN(DisplayGL);

    RendererGL *mRenderer;
};

}

#endif // LIBANGLE_RENDERER_GL_DISPLAYGL_H_
