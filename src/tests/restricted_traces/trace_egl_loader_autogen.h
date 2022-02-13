// GENERATED FILE - DO NOT EDIT.
// Generated by generate_loader.py using data from egl.xml and egl_angle_ext.xml.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// egl_loader_autogen.h:
//   Simple EGL function loader.

#ifndef ANGLE_RESTRICTED_TRACES_EGL_LOADER_AUTOGEN_H_
#define ANGLE_RESTRICTED_TRACES_EGL_LOADER_AUTOGEN_H_

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "restricted_traces_export.h"

#define eglChooseConfig t_eglChooseConfig
#define eglCopyBuffers t_eglCopyBuffers
#define eglCreateContext t_eglCreateContext
#define eglCreatePbufferSurface t_eglCreatePbufferSurface
#define eglCreatePixmapSurface t_eglCreatePixmapSurface
#define eglCreateWindowSurface t_eglCreateWindowSurface
#define eglDestroyContext t_eglDestroyContext
#define eglDestroySurface t_eglDestroySurface
#define eglGetConfigAttrib t_eglGetConfigAttrib
#define eglGetConfigs t_eglGetConfigs
#define eglGetCurrentDisplay t_eglGetCurrentDisplay
#define eglGetCurrentSurface t_eglGetCurrentSurface
#define eglGetDisplay t_eglGetDisplay
#define eglGetError t_eglGetError
#define eglGetProcAddress t_eglGetProcAddress
#define eglInitialize t_eglInitialize
#define eglMakeCurrent t_eglMakeCurrent
#define eglQueryContext t_eglQueryContext
#define eglQueryString t_eglQueryString
#define eglQuerySurface t_eglQuerySurface
#define eglSwapBuffers t_eglSwapBuffers
#define eglTerminate t_eglTerminate
#define eglWaitGL t_eglWaitGL
#define eglWaitNative t_eglWaitNative
#define eglBindTexImage t_eglBindTexImage
#define eglReleaseTexImage t_eglReleaseTexImage
#define eglSurfaceAttrib t_eglSurfaceAttrib
#define eglSwapInterval t_eglSwapInterval
#define eglBindAPI t_eglBindAPI
#define eglQueryAPI t_eglQueryAPI
#define eglCreatePbufferFromClientBuffer t_eglCreatePbufferFromClientBuffer
#define eglReleaseThread t_eglReleaseThread
#define eglWaitClient t_eglWaitClient
#define eglGetCurrentContext t_eglGetCurrentContext
#define eglCreateSync t_eglCreateSync
#define eglDestroySync t_eglDestroySync
#define eglClientWaitSync t_eglClientWaitSync
#define eglGetSyncAttrib t_eglGetSyncAttrib
#define eglCreateImage t_eglCreateImage
#define eglDestroyImage t_eglDestroyImage
#define eglGetPlatformDisplay t_eglGetPlatformDisplay
#define eglCreatePlatformWindowSurface t_eglCreatePlatformWindowSurface
#define eglCreatePlatformPixmapSurface t_eglCreatePlatformPixmapSurface
#define eglWaitSync t_eglWaitSync
#define eglSetBlobCacheFuncsANDROID t_eglSetBlobCacheFuncsANDROID
#define eglCreateNativeClientBufferANDROID t_eglCreateNativeClientBufferANDROID
#define eglGetCompositorTimingANDROID t_eglGetCompositorTimingANDROID
#define eglGetCompositorTimingSupportedANDROID t_eglGetCompositorTimingSupportedANDROID
#define eglGetFrameTimestampSupportedANDROID t_eglGetFrameTimestampSupportedANDROID
#define eglGetFrameTimestampsANDROID t_eglGetFrameTimestampsANDROID
#define eglGetNextFrameIdANDROID t_eglGetNextFrameIdANDROID
#define eglGetNativeClientBufferANDROID t_eglGetNativeClientBufferANDROID
#define eglDupNativeFenceFDANDROID t_eglDupNativeFenceFDANDROID
#define eglPresentationTimeANDROID t_eglPresentationTimeANDROID
#define eglCreateDeviceANGLE t_eglCreateDeviceANGLE
#define eglReleaseDeviceANGLE t_eglReleaseDeviceANGLE
#define eglQueryDisplayAttribANGLE t_eglQueryDisplayAttribANGLE
#define eglQueryStringiANGLE t_eglQueryStringiANGLE
#define eglHandleGPUSwitchANGLE t_eglHandleGPUSwitchANGLE
#define eglReacquireHighPowerGPUANGLE t_eglReacquireHighPowerGPUANGLE
#define eglReleaseHighPowerGPUANGLE t_eglReleaseHighPowerGPUANGLE
#define eglPrepareSwapBuffersANGLE t_eglPrepareSwapBuffersANGLE
#define eglProgramCacheGetAttribANGLE t_eglProgramCacheGetAttribANGLE
#define eglProgramCachePopulateANGLE t_eglProgramCachePopulateANGLE
#define eglProgramCacheQueryANGLE t_eglProgramCacheQueryANGLE
#define eglProgramCacheResizeANGLE t_eglProgramCacheResizeANGLE
#define eglQuerySurfacePointerANGLE t_eglQuerySurfacePointerANGLE
#define eglCreateStreamProducerD3DTextureANGLE t_eglCreateStreamProducerD3DTextureANGLE
#define eglStreamPostD3DTextureANGLE t_eglStreamPostD3DTextureANGLE
#define eglSwapBuffersWithFrameTokenANGLE t_eglSwapBuffersWithFrameTokenANGLE
#define eglGetMscRateANGLE t_eglGetMscRateANGLE
#define eglExportVkImageANGLE t_eglExportVkImageANGLE
#define eglGetSyncValuesCHROMIUM t_eglGetSyncValuesCHROMIUM
#define eglQueryDeviceAttribEXT t_eglQueryDeviceAttribEXT
#define eglQueryDeviceStringEXT t_eglQueryDeviceStringEXT
#define eglQueryDisplayAttribEXT t_eglQueryDisplayAttribEXT
#define eglCreatePlatformPixmapSurfaceEXT t_eglCreatePlatformPixmapSurfaceEXT
#define eglCreatePlatformWindowSurfaceEXT t_eglCreatePlatformWindowSurfaceEXT
#define eglGetPlatformDisplayEXT t_eglGetPlatformDisplayEXT
#define eglDebugMessageControlKHR t_eglDebugMessageControlKHR
#define eglLabelObjectKHR t_eglLabelObjectKHR
#define eglQueryDebugKHR t_eglQueryDebugKHR
#define eglClientWaitSyncKHR t_eglClientWaitSyncKHR
#define eglCreateSyncKHR t_eglCreateSyncKHR
#define eglDestroySyncKHR t_eglDestroySyncKHR
#define eglGetSyncAttribKHR t_eglGetSyncAttribKHR
#define eglCreateImageKHR t_eglCreateImageKHR
#define eglDestroyImageKHR t_eglDestroyImageKHR
#define eglLockSurfaceKHR t_eglLockSurfaceKHR
#define eglQuerySurface64KHR t_eglQuerySurface64KHR
#define eglUnlockSurfaceKHR t_eglUnlockSurfaceKHR
#define eglSetDamageRegionKHR t_eglSetDamageRegionKHR
#define eglSignalSyncKHR t_eglSignalSyncKHR
#define eglCreateStreamKHR t_eglCreateStreamKHR
#define eglDestroyStreamKHR t_eglDestroyStreamKHR
#define eglQueryStreamKHR t_eglQueryStreamKHR
#define eglQueryStreamu64KHR t_eglQueryStreamu64KHR
#define eglStreamAttribKHR t_eglStreamAttribKHR
#define eglStreamConsumerAcquireKHR t_eglStreamConsumerAcquireKHR
#define eglStreamConsumerGLTextureExternalKHR t_eglStreamConsumerGLTextureExternalKHR
#define eglStreamConsumerReleaseKHR t_eglStreamConsumerReleaseKHR
#define eglSwapBuffersWithDamageKHR t_eglSwapBuffersWithDamageKHR
#define eglWaitSyncKHR t_eglWaitSyncKHR
#define eglPostSubBufferNV t_eglPostSubBufferNV
#define eglStreamConsumerGLTextureExternalAttribsNV t_eglStreamConsumerGLTextureExternalAttribsNV
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCHOOSECONFIGPROC t_eglChooseConfig;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCOPYBUFFERSPROC t_eglCopyBuffers;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATECONTEXTPROC t_eglCreateContext;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPBUFFERSURFACEPROC t_eglCreatePbufferSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPIXMAPSURFACEPROC t_eglCreatePixmapSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEWINDOWSURFACEPROC t_eglCreateWindowSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYCONTEXTPROC t_eglDestroyContext;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYSURFACEPROC t_eglDestroySurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCONFIGATTRIBPROC t_eglGetConfigAttrib;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCONFIGSPROC t_eglGetConfigs;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCURRENTDISPLAYPROC t_eglGetCurrentDisplay;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCURRENTSURFACEPROC t_eglGetCurrentSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETDISPLAYPROC t_eglGetDisplay;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETERRORPROC t_eglGetError;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETPROCADDRESSPROC t_eglGetProcAddress;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLINITIALIZEPROC t_eglInitialize;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLMAKECURRENTPROC t_eglMakeCurrent;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYCONTEXTPROC t_eglQueryContext;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSTRINGPROC t_eglQueryString;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSURFACEPROC t_eglQuerySurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSWAPBUFFERSPROC t_eglSwapBuffers;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLTERMINATEPROC t_eglTerminate;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLWAITGLPROC t_eglWaitGL;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLWAITNATIVEPROC t_eglWaitNative;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLBINDTEXIMAGEPROC t_eglBindTexImage;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLRELEASETEXIMAGEPROC t_eglReleaseTexImage;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSURFACEATTRIBPROC t_eglSurfaceAttrib;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSWAPINTERVALPROC t_eglSwapInterval;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLBINDAPIPROC t_eglBindAPI;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYAPIPROC t_eglQueryAPI;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC
    t_eglCreatePbufferFromClientBuffer;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLRELEASETHREADPROC t_eglReleaseThread;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLWAITCLIENTPROC t_eglWaitClient;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCURRENTCONTEXTPROC t_eglGetCurrentContext;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATESYNCPROC t_eglCreateSync;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYSYNCPROC t_eglDestroySync;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCLIENTWAITSYNCPROC t_eglClientWaitSync;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETSYNCATTRIBPROC t_eglGetSyncAttrib;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEIMAGEPROC t_eglCreateImage;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYIMAGEPROC t_eglDestroyImage;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETPLATFORMDISPLAYPROC t_eglGetPlatformDisplay;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPLATFORMWINDOWSURFACEPROC
    t_eglCreatePlatformWindowSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC
    t_eglCreatePlatformPixmapSurface;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLWAITSYNCPROC t_eglWaitSync;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSETBLOBCACHEFUNCSANDROIDPROC t_eglSetBlobCacheFuncsANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC
    t_eglCreateNativeClientBufferANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCOMPOSITORTIMINGANDROIDPROC
    t_eglGetCompositorTimingANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC
    t_eglGetCompositorTimingSupportedANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC
    t_eglGetFrameTimestampSupportedANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETFRAMETIMESTAMPSANDROIDPROC t_eglGetFrameTimestampsANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETNEXTFRAMEIDANDROIDPROC t_eglGetNextFrameIdANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC
    t_eglGetNativeClientBufferANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDUPNATIVEFENCEFDANDROIDPROC t_eglDupNativeFenceFDANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPRESENTATIONTIMEANDROIDPROC t_eglPresentationTimeANDROID;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEDEVICEANGLEPROC t_eglCreateDeviceANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLRELEASEDEVICEANGLEPROC t_eglReleaseDeviceANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYDISPLAYATTRIBANGLEPROC t_eglQueryDisplayAttribANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSTRINGIANGLEPROC t_eglQueryStringiANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLHANDLEGPUSWITCHANGLEPROC t_eglHandleGPUSwitchANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLREACQUIREHIGHPOWERGPUANGLEPROC
    t_eglReacquireHighPowerGPUANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLRELEASEHIGHPOWERGPUANGLEPROC t_eglReleaseHighPowerGPUANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPREPARESWAPBUFFERSANGLEPROC t_eglPrepareSwapBuffersANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPROGRAMCACHEGETATTRIBANGLEPROC
    t_eglProgramCacheGetAttribANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPROGRAMCACHEPOPULATEANGLEPROC t_eglProgramCachePopulateANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPROGRAMCACHEQUERYANGLEPROC t_eglProgramCacheQueryANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPROGRAMCACHERESIZEANGLEPROC t_eglProgramCacheResizeANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSURFACEPOINTERANGLEPROC t_eglQuerySurfacePointerANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATESTREAMPRODUCERD3DTEXTUREANGLEPROC
    t_eglCreateStreamProducerD3DTextureANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMPOSTD3DTEXTUREANGLEPROC t_eglStreamPostD3DTextureANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSWAPBUFFERSWITHFRAMETOKENANGLEPROC
    t_eglSwapBuffersWithFrameTokenANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETMSCRATEANGLEPROC t_eglGetMscRateANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLEXPORTVKIMAGEANGLEPROC t_eglExportVkImageANGLE;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETSYNCVALUESCHROMIUMPROC t_eglGetSyncValuesCHROMIUM;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYDEVICEATTRIBEXTPROC t_eglQueryDeviceAttribEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYDEVICESTRINGEXTPROC t_eglQueryDeviceStringEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYDISPLAYATTRIBEXTPROC t_eglQueryDisplayAttribEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC
    t_eglCreatePlatformPixmapSurfaceEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC
    t_eglCreatePlatformWindowSurfaceEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETPLATFORMDISPLAYEXTPROC t_eglGetPlatformDisplayEXT;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDEBUGMESSAGECONTROLKHRPROC t_eglDebugMessageControlKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLLABELOBJECTKHRPROC t_eglLabelObjectKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYDEBUGKHRPROC t_eglQueryDebugKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCLIENTWAITSYNCKHRPROC t_eglClientWaitSyncKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATESYNCKHRPROC t_eglCreateSyncKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYSYNCKHRPROC t_eglDestroySyncKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLGETSYNCATTRIBKHRPROC t_eglGetSyncAttribKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATEIMAGEKHRPROC t_eglCreateImageKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYIMAGEKHRPROC t_eglDestroyImageKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLLOCKSURFACEKHRPROC t_eglLockSurfaceKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSURFACE64KHRPROC t_eglQuerySurface64KHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLUNLOCKSURFACEKHRPROC t_eglUnlockSurfaceKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSETDAMAGEREGIONKHRPROC t_eglSetDamageRegionKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSIGNALSYNCKHRPROC t_eglSignalSyncKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLCREATESTREAMKHRPROC t_eglCreateStreamKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLDESTROYSTREAMKHRPROC t_eglDestroyStreamKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSTREAMKHRPROC t_eglQueryStreamKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLQUERYSTREAMU64KHRPROC t_eglQueryStreamu64KHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMATTRIBKHRPROC t_eglStreamAttribKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMCONSUMERACQUIREKHRPROC t_eglStreamConsumerAcquireKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC
    t_eglStreamConsumerGLTextureExternalKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMCONSUMERRELEASEKHRPROC t_eglStreamConsumerReleaseKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC t_eglSwapBuffersWithDamageKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLWAITSYNCKHRPROC t_eglWaitSyncKHR;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLPOSTSUBBUFFERNVPROC t_eglPostSubBufferNV;
ANGLE_TRACE_LOADER_EXPORT extern PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC
    t_eglStreamConsumerGLTextureExternalAttribsNV;

namespace trace_angle
{
using GenericProc = void (*)();
using LoadProc    = GenericProc(KHRONOS_APIENTRY *)(const char *);
ANGLE_TRACE_LOADER_EXPORT void LoadEGL(LoadProc loadProc);
}  // namespace trace_angle

#endif  // ANGLE_RESTRICTED_TRACES_EGL_LOADER_AUTOGEN_H_
