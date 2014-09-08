//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#ifndef SAMPLE_UTIL_WINDOW_H
#define SAMPLE_UTIL_WINDOW_H

#include "Event.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <list>

class OSWindow
{
  public:
    OSWindow();
    virtual ~OSWindow();

    virtual bool initialize(const std::string &name, size_t width, size_t height) = 0;
    virtual void destroy() = 0;

    int getWidth() const;
    int getHeight() const;

    virtual EGLNativeWindowType getNativeWindow() const = 0;
    virtual EGLNativeDisplayType getNativeDisplay() const = 0;

    virtual void messageLoop() = 0;

    bool popEvent(Event *event);
    virtual void pushEvent(Event event);

    virtual void setMousePosition(int x, int y) = 0;
    virtual bool resize(int width, int height) = 0;
    virtual bool setVisible(bool isVisible) = 0;

  protected:
    int mWidth;
    int mHeight;

    std::list<Event> mEvents;
};

OSWindow *CreateOSWindow();

#endif // SAMPLE_UTIL_WINDOW_H
