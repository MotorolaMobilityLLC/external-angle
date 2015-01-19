//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Display.h: Defines the egl::Display class, representing the abstract
// display on which graphics are drawn. Implements EGLDisplay.
// [EGL 1.4] section 2.1.2 page 3.

#ifndef LIBANGLE_DISPLAY_H_
#define LIBANGLE_DISPLAY_H_

#include <set>
#include <vector>

#include "libANGLE/Error.h"
#include "libANGLE/Caps.h"
#include "libANGLE/Config.h"
#include "libANGLE/AttributeMap.h"

namespace gl
{
class Context;
}

namespace rx
{
class DisplayImpl;
}

namespace egl
{
class Surface;

class Display final
{
  public:
    ~Display();

    Error initialize();
    void terminate();

    static egl::Display *getDisplay(EGLNativeDisplayType displayId, const AttributeMap &attribMap);

    static const ClientExtensions &getClientExtensions();
    static const std::string &getClientExtensionString();

    std::vector<const Config*> getConfigs(const egl::AttributeMap &attribs) const;
    bool getConfigAttrib(const Config *configuration, EGLint attribute, EGLint *value);

    Error createWindowSurface(const Config *configuration, EGLNativeWindowType window, const AttributeMap &attribs,
                              Surface **outSurface);
    Error createOffscreenSurface(const Config *configuration, EGLClientBuffer shareHandle, const AttributeMap &attribs,
                                 Surface **outSurface);
    Error createContext(const Config *configuration, gl::Context *shareContext, const AttributeMap &attribs,
                        gl::Context **outContext);

    Error makeCurrent(egl::Surface *drawSurface, egl::Surface *readSurface, gl::Context *context);

    void destroySurface(egl::Surface *surface);
    void destroyContext(gl::Context *context);

    bool isInitialized() const;
    bool isValidConfig(const Config *config) const;
    bool isValidContext(gl::Context *context) const;
    bool isValidSurface(egl::Surface *surface) const;
    bool hasExistingWindowSurface(EGLNativeWindowType window) const;
    bool isValidNativeWindow(EGLNativeWindowType window) const;
    bool isValidNativeDisplay(EGLNativeDisplayType display) const;

    bool isDeviceLost() const;
    bool testDeviceLost();
    void notifyDeviceLost();

    const Caps &getCaps() const;

    const DisplayExtensions &getExtensions() const;
    const std::string &getExtensionString() const;
    const std::string &getVendorString() const;

  private:
    DISALLOW_COPY_AND_ASSIGN(Display);

    Display(rx::DisplayImpl *impl, EGLNativeDisplayType displayId);

    void setAttributes(const AttributeMap &attribMap);

    Error restoreLostDevice();

    void initDisplayExtensions();
    void initVendorString();

    rx::DisplayImpl *mImplementation;

    EGLNativeDisplayType mDisplayId;
    AttributeMap mAttributeMap;

    ConfigSet mConfigSet;

    typedef std::set<gl::Context*> ContextSet;
    ContextSet mContextSet;

    bool mInitialized;

    Caps mCaps;

    DisplayExtensions mDisplayExtensions;
    std::string mDisplayExtensionString;

    std::string mVendorString;
};

}

#endif   // LIBANGLE_DISPLAY_H_
