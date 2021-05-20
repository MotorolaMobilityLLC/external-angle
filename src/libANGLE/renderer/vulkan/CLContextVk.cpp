//
// Copyright 2021 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// CLContextVk.cpp: Implements the class methods for CLContextVk.

#include "libANGLE/renderer/vulkan/CLContextVk.h"

#include "libANGLE/renderer/vulkan/CLPlatformVk.h"

namespace rx
{

CLContextVk::CLContextVk(CLPlatformVk &platform, CLDeviceImpl::List &&devices)
    : CLContextImpl(platform, std::move(devices))
{}

CLContextVk::~CLContextVk() = default;

}  // namespace rx
