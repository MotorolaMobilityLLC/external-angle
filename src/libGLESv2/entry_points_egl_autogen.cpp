// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from egl.xml.
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_egl_autogen.cpp:
//   Defines the EGL entry points.

#include "libGLESv2/entry_points_egl_autogen.h"

#include "libANGLE/entry_points_utils.h"
#include "libANGLE/validationEGL_autogen.h"
#include "libGLESv2/egl_stubs_autogen.h"
#include "libGLESv2/global_state.h"

using namespace egl;

extern "C" {

// EGL 1.0
EGLBoolean EGLAPIENTRY EGL_ChooseConfig(EGLDisplay dpy,
                                        const EGLint *attrib_list,
                                        EGLConfig *configs,
                                        EGLint config_size,
                                        EGLint *num_config)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(ChooseConfig,
              "dpy = 0x%016" PRIxPTR ", attrib_list = 0x%016" PRIxPTR ", configs = 0x%016" PRIxPTR
              ", config_size = %d, num_config = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)attrib_list, (uintptr_t)configs, config_size,
              (uintptr_t)num_config);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, ChooseConfig, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       attrib_listPacked, configs, config_size, num_config);

    return ChooseConfig(thread, dpyPacked, attrib_listPacked, configs, config_size, num_config);
}

EGLBoolean EGLAPIENTRY EGL_CopyBuffers(EGLDisplay dpy,
                                       EGLSurface surface,
                                       EGLNativePixmapType target)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CopyBuffers,
              "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR ", target = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)surface, (uintptr_t)target);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, CopyBuffers, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked, target);

    return CopyBuffers(thread, dpyPacked, surfacePacked, target);
}

EGLContext EGLAPIENTRY EGL_CreateContext(EGLDisplay dpy,
                                         EGLConfig config,
                                         EGLContext share_context,
                                         const EGLint *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreateContext,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", share_context = 0x%016" PRIxPTR
              ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)share_context, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    gl::Context *share_contextPacked      = PackParam<gl::Context *>(share_context);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreateContext, GetDisplayIfValid(dpyPacked), EGLContext, dpyPacked,
                       configPacked, share_contextPacked, attrib_listPacked);

    return CreateContext(thread, dpyPacked, configPacked, share_contextPacked, attrib_listPacked);
}

EGLSurface EGLAPIENTRY EGL_CreatePbufferSurface(EGLDisplay dpy,
                                                EGLConfig config,
                                                const EGLint *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreatePbufferSurface,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", attrib_list = 0x%016" PRIxPTR
              "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreatePbufferSurface, GetDisplayIfValid(dpyPacked), EGLSurface,
                       dpyPacked, configPacked, attrib_listPacked);

    return CreatePbufferSurface(thread, dpyPacked, configPacked, attrib_listPacked);
}

EGLSurface EGLAPIENTRY EGL_CreatePixmapSurface(EGLDisplay dpy,
                                               EGLConfig config,
                                               EGLNativePixmapType pixmap,
                                               const EGLint *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreatePixmapSurface,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", pixmap = 0x%016" PRIxPTR
              ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)pixmap, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreatePixmapSurface, GetDisplayIfValid(dpyPacked), EGLSurface,
                       dpyPacked, configPacked, pixmap, attrib_listPacked);

    return CreatePixmapSurface(thread, dpyPacked, configPacked, pixmap, attrib_listPacked);
}

EGLSurface EGLAPIENTRY EGL_CreateWindowSurface(EGLDisplay dpy,
                                               EGLConfig config,
                                               EGLNativeWindowType win,
                                               const EGLint *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreateWindowSurface,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", win = 0x%016" PRIxPTR
              ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)win, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreateWindowSurface, GetDisplayIfValid(dpyPacked), EGLSurface,
                       dpyPacked, configPacked, win, attrib_listPacked);

    return CreateWindowSurface(thread, dpyPacked, configPacked, win, attrib_listPacked);
}

EGLBoolean EGLAPIENTRY EGL_DestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(DestroyContext, "dpy = 0x%016" PRIxPTR ", ctx = 0x%016" PRIxPTR "", (uintptr_t)dpy,
              (uintptr_t)ctx);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    gl::Context *ctxPacked  = PackParam<gl::Context *>(ctx);

    ANGLE_EGL_VALIDATE(thread, DestroyContext, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       ctxPacked);

    return DestroyContext(thread, dpyPacked, ctxPacked);
}

EGLBoolean EGLAPIENTRY EGL_DestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(DestroySurface, "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)surface);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, DestroySurface, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked);

    return DestroySurface(thread, dpyPacked, surfacePacked);
}

EGLBoolean EGLAPIENTRY EGL_GetConfigAttrib(EGLDisplay dpy,
                                           EGLConfig config,
                                           EGLint attribute,
                                           EGLint *value)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetConfigAttrib,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR
              ", attribute = %d, value = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, attribute, (uintptr_t)value);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Config *configPacked    = PackParam<Config *>(config);

    ANGLE_EGL_VALIDATE(thread, GetConfigAttrib, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       configPacked, attribute, value);

    return GetConfigAttrib(thread, dpyPacked, configPacked, attribute, value);
}

EGLBoolean EGLAPIENTRY EGL_GetConfigs(EGLDisplay dpy,
                                      EGLConfig *configs,
                                      EGLint config_size,
                                      EGLint *num_config)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetConfigs,
              "dpy = 0x%016" PRIxPTR ", configs = 0x%016" PRIxPTR
              ", config_size = %d, num_config = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)configs, config_size, (uintptr_t)num_config);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);

    ANGLE_EGL_VALIDATE(thread, GetConfigs, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       configs, config_size, num_config);

    return GetConfigs(thread, dpyPacked, configs, config_size, num_config);
}

EGLDisplay EGLAPIENTRY EGL_GetCurrentDisplay()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetCurrentDisplay, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetCurrentDisplay, nullptr, EGLDisplay);

    return GetCurrentDisplay(thread);
}

EGLSurface EGLAPIENTRY EGL_GetCurrentSurface(EGLint readdraw)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetCurrentSurface, "readdraw = %d", readdraw);

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetCurrentSurface, nullptr, EGLSurface, readdraw);

    return GetCurrentSurface(thread, readdraw);
}

EGLDisplay EGLAPIENTRY EGL_GetDisplay(EGLNativeDisplayType display_id)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetDisplay, "display_id = 0x%016" PRIxPTR "", (uintptr_t)display_id);

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetDisplay, nullptr, EGLDisplay, display_id);

    return GetDisplay(thread, display_id);
}

EGLint EGLAPIENTRY EGL_GetError()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetError, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetError, nullptr, EGLint);

    return GetError(thread);
}

__eglMustCastToProperFunctionPointerType EGLAPIENTRY EGL_GetProcAddress(const char *procname)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetProcAddress, "procname = 0x%016" PRIxPTR "", (uintptr_t)procname);

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetProcAddress, nullptr, __eglMustCastToProperFunctionPointerType,
                       procname);

    return GetProcAddress(thread, procname);
}

EGLBoolean EGLAPIENTRY EGL_Initialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(Initialize,
              "dpy = 0x%016" PRIxPTR ", major = 0x%016" PRIxPTR ", minor = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)major, (uintptr_t)minor);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);

    ANGLE_EGL_VALIDATE(thread, Initialize, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       major, minor);

    return Initialize(thread, dpyPacked, major, minor);
}

EGLBoolean EGLAPIENTRY EGL_MakeCurrent(EGLDisplay dpy,
                                       EGLSurface draw,
                                       EGLSurface read,
                                       EGLContext ctx)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(MakeCurrent,
              "dpy = 0x%016" PRIxPTR ", draw = 0x%016" PRIxPTR ", read = 0x%016" PRIxPTR
              ", ctx = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)draw, (uintptr_t)read, (uintptr_t)ctx);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *drawPacked     = PackParam<Surface *>(draw);
    Surface *readPacked     = PackParam<Surface *>(read);
    gl::Context *ctxPacked  = PackParam<gl::Context *>(ctx);

    ANGLE_EGL_VALIDATE(thread, MakeCurrent, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       drawPacked, readPacked, ctxPacked);

    return MakeCurrent(thread, dpyPacked, drawPacked, readPacked, ctxPacked);
}

EGLBoolean EGLAPIENTRY EGL_QueryContext(EGLDisplay dpy,
                                        EGLContext ctx,
                                        EGLint attribute,
                                        EGLint *value)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(QueryContext,
              "dpy = 0x%016" PRIxPTR ", ctx = 0x%016" PRIxPTR
              ", attribute = %d, value = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)ctx, attribute, (uintptr_t)value);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    gl::Context *ctxPacked  = PackParam<gl::Context *>(ctx);

    ANGLE_EGL_VALIDATE(thread, QueryContext, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       ctxPacked, attribute, value);

    return QueryContext(thread, dpyPacked, ctxPacked, attribute, value);
}

const char *EGLAPIENTRY EGL_QueryString(EGLDisplay dpy, EGLint name)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(QueryString, "dpy = 0x%016" PRIxPTR ", name = %d", (uintptr_t)dpy, name);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);

    ANGLE_EGL_VALIDATE(thread, QueryString, GetDisplayIfValid(dpyPacked), const char *, dpyPacked,
                       name);

    return QueryString(thread, dpyPacked, name);
}

EGLBoolean EGLAPIENTRY EGL_QuerySurface(EGLDisplay dpy,
                                        EGLSurface surface,
                                        EGLint attribute,
                                        EGLint *value)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(QuerySurface,
              "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR
              ", attribute = %d, value = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)surface, attribute, (uintptr_t)value);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, QuerySurface, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked, attribute, value);

    return QuerySurface(thread, dpyPacked, surfacePacked, attribute, value);
}

EGLBoolean EGLAPIENTRY EGL_SwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(SwapBuffers, "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR "", (uintptr_t)dpy,
              (uintptr_t)surface);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, SwapBuffers, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked);

    return SwapBuffers(thread, dpyPacked, surfacePacked);
}

EGLBoolean EGLAPIENTRY EGL_Terminate(EGLDisplay dpy)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(Terminate, "dpy = 0x%016" PRIxPTR "", (uintptr_t)dpy);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);

    ANGLE_EGL_VALIDATE(thread, Terminate, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked);

    return Terminate(thread, dpyPacked);
}

EGLBoolean EGLAPIENTRY EGL_WaitGL()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(WaitGL, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, WaitGL, nullptr, EGLBoolean);

    return WaitGL(thread);
}

EGLBoolean EGLAPIENTRY EGL_WaitNative(EGLint engine)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(WaitNative, "engine = %d", engine);

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, WaitNative, nullptr, EGLBoolean, engine);

    return WaitNative(thread, engine);
}

// EGL 1.1
EGLBoolean EGLAPIENTRY EGL_BindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(BindTexImage, "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR ", buffer = %d",
              (uintptr_t)dpy, (uintptr_t)surface, buffer);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, BindTexImage, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked, buffer);

    return BindTexImage(thread, dpyPacked, surfacePacked, buffer);
}

EGLBoolean EGLAPIENTRY EGL_ReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(ReleaseTexImage, "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR ", buffer = %d",
              (uintptr_t)dpy, (uintptr_t)surface, buffer);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, ReleaseTexImage, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked, buffer);

    return ReleaseTexImage(thread, dpyPacked, surfacePacked, buffer);
}

EGLBoolean EGLAPIENTRY EGL_SurfaceAttrib(EGLDisplay dpy,
                                         EGLSurface surface,
                                         EGLint attribute,
                                         EGLint value)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(SurfaceAttrib,
              "dpy = 0x%016" PRIxPTR ", surface = 0x%016" PRIxPTR ", attribute = %d, value = %d",
              (uintptr_t)dpy, (uintptr_t)surface, attribute, value);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Surface *surfacePacked  = PackParam<Surface *>(surface);

    ANGLE_EGL_VALIDATE(thread, SurfaceAttrib, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       surfacePacked, attribute, value);

    return SurfaceAttrib(thread, dpyPacked, surfacePacked, attribute, value);
}

EGLBoolean EGLAPIENTRY EGL_SwapInterval(EGLDisplay dpy, EGLint interval)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(SwapInterval, "dpy = 0x%016" PRIxPTR ", interval = %d", (uintptr_t)dpy, interval);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);

    ANGLE_EGL_VALIDATE(thread, SwapInterval, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       interval);

    return SwapInterval(thread, dpyPacked, interval);
}

// EGL 1.2
EGLBoolean EGLAPIENTRY EGL_BindAPI(EGLenum api)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(BindAPI, "api = 0x%X", api);

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, BindAPI, nullptr, EGLBoolean, api);

    return BindAPI(thread, api);
}

EGLSurface EGLAPIENTRY EGL_CreatePbufferFromClientBuffer(EGLDisplay dpy,
                                                         EGLenum buftype,
                                                         EGLClientBuffer buffer,
                                                         EGLConfig config,
                                                         const EGLint *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreatePbufferFromClientBuffer,
              "dpy = 0x%016" PRIxPTR ", buftype = 0x%X, buffer = 0x%016" PRIxPTR
              ", config = 0x%016" PRIxPTR ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, buftype, (uintptr_t)buffer, (uintptr_t)config,
              (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreatePbufferFromClientBuffer, GetDisplayIfValid(dpyPacked),
                       EGLSurface, dpyPacked, buftype, buffer, configPacked, attrib_listPacked);

    return CreatePbufferFromClientBuffer(thread, dpyPacked, buftype, buffer, configPacked,
                                         attrib_listPacked);
}

EGLenum EGLAPIENTRY EGL_QueryAPI()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(QueryAPI, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, QueryAPI, nullptr, EGLenum);

    return QueryAPI(thread);
}

EGLBoolean EGLAPIENTRY EGL_ReleaseThread()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(ReleaseThread, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, ReleaseThread, nullptr, EGLBoolean);

    return ReleaseThread(thread);
}

EGLBoolean EGLAPIENTRY EGL_WaitClient()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(WaitClient, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, WaitClient, nullptr, EGLBoolean);

    return WaitClient(thread);
}

// EGL 1.4
EGLContext EGLAPIENTRY EGL_GetCurrentContext()
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetCurrentContext, "");

    Thread *thread = egl::GetCurrentThread();

    ANGLE_EGL_VALIDATE(thread, GetCurrentContext, nullptr, EGLContext);

    return GetCurrentContext(thread);
}

// EGL 1.5
EGLint EGLAPIENTRY EGL_ClientWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(ClientWaitSync,
              "dpy = 0x%016" PRIxPTR ", sync = 0x%016" PRIxPTR ", flags = %d, timeout = %llu",
              (uintptr_t)dpy, (uintptr_t)sync, flags, static_cast<unsigned long long>(timeout));

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Sync *syncPacked        = PackParam<Sync *>(sync);

    ANGLE_EGL_VALIDATE(thread, ClientWaitSync, GetDisplayIfValid(dpyPacked), EGLint, dpyPacked,
                       syncPacked, flags, timeout);

    return ClientWaitSync(thread, dpyPacked, syncPacked, flags, timeout);
}

EGLImage EGLAPIENTRY EGL_CreateImage(EGLDisplay dpy,
                                     EGLContext ctx,
                                     EGLenum target,
                                     EGLClientBuffer buffer,
                                     const EGLAttrib *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreateImage,
              "dpy = 0x%016" PRIxPTR ", ctx = 0x%016" PRIxPTR
              ", target = 0x%X, buffer = 0x%016" PRIxPTR ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)ctx, target, (uintptr_t)buffer, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    gl::Context *ctxPacked                = PackParam<gl::Context *>(ctx);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreateImage, GetDisplayIfValid(dpyPacked), EGLImage, dpyPacked,
                       ctxPacked, target, buffer, attrib_listPacked);

    return CreateImage(thread, dpyPacked, ctxPacked, target, buffer, attrib_listPacked);
}

EGLSurface EGLAPIENTRY EGL_CreatePlatformPixmapSurface(EGLDisplay dpy,
                                                       EGLConfig config,
                                                       void *native_pixmap,
                                                       const EGLAttrib *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreatePlatformPixmapSurface,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", native_pixmap = 0x%016" PRIxPTR
              ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)native_pixmap, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreatePlatformPixmapSurface, GetDisplayIfValid(dpyPacked),
                       EGLSurface, dpyPacked, configPacked, native_pixmap, attrib_listPacked);

    return CreatePlatformPixmapSurface(thread, dpyPacked, configPacked, native_pixmap,
                                       attrib_listPacked);
}

EGLSurface EGLAPIENTRY EGL_CreatePlatformWindowSurface(EGLDisplay dpy,
                                                       EGLConfig config,
                                                       void *native_window,
                                                       const EGLAttrib *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreatePlatformWindowSurface,
              "dpy = 0x%016" PRIxPTR ", config = 0x%016" PRIxPTR ", native_window = 0x%016" PRIxPTR
              ", attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)config, (uintptr_t)native_window, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    Config *configPacked                  = PackParam<Config *>(config);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreatePlatformWindowSurface, GetDisplayIfValid(dpyPacked),
                       EGLSurface, dpyPacked, configPacked, native_window, attrib_listPacked);

    return CreatePlatformWindowSurface(thread, dpyPacked, configPacked, native_window,
                                       attrib_listPacked);
}

EGLSync EGLAPIENTRY EGL_CreateSync(EGLDisplay dpy, EGLenum type, const EGLAttrib *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(CreateSync, "dpy = 0x%016" PRIxPTR ", type = 0x%X, attrib_list = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, type, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked               = PackParam<egl::Display *>(dpy);
    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, CreateSync, GetDisplayIfValid(dpyPacked), EGLSync, dpyPacked, type,
                       attrib_listPacked);

    return CreateSync(thread, dpyPacked, type, attrib_listPacked);
}

EGLBoolean EGLAPIENTRY EGL_DestroyImage(EGLDisplay dpy, EGLImage image)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(DestroyImage, "dpy = 0x%016" PRIxPTR ", image = 0x%016" PRIxPTR "", (uintptr_t)dpy,
              (uintptr_t)image);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Image *imagePacked      = PackParam<Image *>(image);

    ANGLE_EGL_VALIDATE(thread, DestroyImage, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       imagePacked);

    return DestroyImage(thread, dpyPacked, imagePacked);
}

EGLBoolean EGLAPIENTRY EGL_DestroySync(EGLDisplay dpy, EGLSync sync)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(DestroySync, "dpy = 0x%016" PRIxPTR ", sync = 0x%016" PRIxPTR "", (uintptr_t)dpy,
              (uintptr_t)sync);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Sync *syncPacked        = PackParam<Sync *>(sync);

    ANGLE_EGL_VALIDATE(thread, DestroySync, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       syncPacked);

    return DestroySync(thread, dpyPacked, syncPacked);
}

EGLDisplay EGLAPIENTRY EGL_GetPlatformDisplay(EGLenum platform,
                                              void *native_display,
                                              const EGLAttrib *attrib_list)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetPlatformDisplay,
              "platform = 0x%X, native_display = 0x%016" PRIxPTR ", attrib_list = 0x%016" PRIxPTR
              "",
              platform, (uintptr_t)native_display, (uintptr_t)attrib_list);

    Thread *thread = egl::GetCurrentThread();

    const AttributeMap &attrib_listPacked = PackParam<const AttributeMap &>(attrib_list);

    ANGLE_EGL_VALIDATE(thread, GetPlatformDisplay, nullptr, EGLDisplay, platform, native_display,
                       attrib_listPacked);

    return GetPlatformDisplay(thread, platform, native_display, attrib_listPacked);
}

EGLBoolean EGLAPIENTRY EGL_GetSyncAttrib(EGLDisplay dpy,
                                         EGLSync sync,
                                         EGLint attribute,
                                         EGLAttrib *value)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(GetSyncAttrib,
              "dpy = 0x%016" PRIxPTR ", sync = 0x%016" PRIxPTR
              ", attribute = %d, value = 0x%016" PRIxPTR "",
              (uintptr_t)dpy, (uintptr_t)sync, attribute, (uintptr_t)value);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Sync *syncPacked        = PackParam<Sync *>(sync);

    ANGLE_EGL_VALIDATE(thread, GetSyncAttrib, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       syncPacked, attribute, value);

    return GetSyncAttrib(thread, dpyPacked, syncPacked, attribute, value);
}

EGLBoolean EGLAPIENTRY EGL_WaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags)
{
    ANGLE_SCOPED_GLOBAL_LOCK();
    EGL_EVENT(WaitSync, "dpy = 0x%016" PRIxPTR ", sync = 0x%016" PRIxPTR ", flags = %d",
              (uintptr_t)dpy, (uintptr_t)sync, flags);

    Thread *thread = egl::GetCurrentThread();

    egl::Display *dpyPacked = PackParam<egl::Display *>(dpy);
    Sync *syncPacked        = PackParam<Sync *>(sync);

    ANGLE_EGL_VALIDATE(thread, WaitSync, GetDisplayIfValid(dpyPacked), EGLBoolean, dpyPacked,
                       syncPacked, flags);

    return WaitSync(thread, dpyPacked, syncPacked, flags);
}
}  // extern "C"
