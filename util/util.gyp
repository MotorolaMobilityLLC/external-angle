# Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

util_sources =
[
  "com_utils.h",
  "keyboard.h",
  "geometry_utils.cpp",
  "geometry_utils.h",
  "mouse.h",
  "random_utils.cpp",
  "random_utils.h",
  "shader_utils.cpp",
  "shader_utils.h",
  "system_utils.h",
  "Event.h",
  "EGLWindow.cpp",
  "EGLWindow.h",
  "Matrix.cpp",
  "Matrix.h",
  "OSPixmap.h",
  "OSWindow.cpp",
  "OSWindow.h",
  "Timer.h",
]
util_win32_sources =
[
  "windows/win32/Win32_system_utils.cpp",
  "windows/win32/Win32Pixmap.cpp",
  "windows/win32/Win32Pixmap.h",
  "windows/win32/Win32Window.cpp",
  "windows/win32/Win32Window.h",
  "windows/Windows_system_utils.cpp",
  "windows/WindowsTimer.cpp",
  "windows/WindowsTimer.h",
]
util_winrt_sources =
[
  "windows/winrt/WinRT_system_utils.cpp",
  "windows/winrt/WinRTPixmap.cpp",
  "windows/winrt/WinRTWindow.cpp",
  "windows/winrt/WinRTWindow.h",
  "windows/Windows_system_utils.cpp",
  "windows/WindowsTimer.cpp",
  "windows/WindowsTimer.h",
]
util_linux_sources =
[
  "linux/LinuxTimer.cpp",
  "linux/LinuxTimer.h",
  "posix/Posix_system_utils.cpp",
]
util_x11_sources =
[
  "x11/X11Pixmap.cpp",
  "x11/X11Pixmap.h",
  "x11/X11Window.cpp",
  "x11/X11Window.h",
]
util_ozone_sources =
[
  "ozone/OzonePixmap.cpp",
  "ozone/OzoneWindow.cpp",
  "ozone/OzoneWindow.h",
]
util_osx_sources =
[
  "osx/OSXTimer.cpp",
  "osx/OSXTimer.h",
  "osx/OSXPixmap.mm",
  "osx/OSXPixmap.h",
  "osx/OSXWindow.mm",
  "osx/OSXWindow.h",
  "posix/Posix_system_utils.cpp",
]
util_android_sources =
[
  "android/AndroidPixmap.cpp",
  "android/AndroidWindow.cpp",
  "android/AndroidWindow.h",
  "android/third_party/android_native_app_glue.c",
  "android/third_party/android_native_app_glue.h",
]
