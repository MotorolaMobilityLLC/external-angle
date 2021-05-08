//
// Copyright 2021 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// CLPlatformVk.cpp: Implements the class methods for CLPlatformVk.

#include "libANGLE/renderer/vulkan/CLPlatformVk.h"

#include "libANGLE/renderer/vulkan/CLDeviceVk.h"

#include "anglebase/no_destructor.h"
#include "common/angle_version.h"

namespace rx
{

namespace
{
std::string CreateExtensionString(const NameVersionVector &extList)
{
    std::string extensions;
    for (const cl_name_version &ext : extList)
    {
        extensions += ext.name;
        extensions += ' ';
    }
    if (!extensions.empty())
    {
        extensions.pop_back();
    }
    return extensions;
}
}  // anonymous namespace

CLPlatformVk::~CLPlatformVk() = default;

CLDeviceImpl::InitList CLPlatformVk::getDevices()
{
    CLDeviceImpl::InitList initList;
    CLDeviceImpl::Info info = CLDeviceVk::GetInfo();
    if (info.isValid())
    {
        initList.emplace_back(new CLDeviceVk(), std::move(info));
    }
    return initList;
}

CLPlatformVk::InitList CLPlatformVk::GetPlatforms()
{
    NameVersionVector extList = {
        cl_name_version{CL_MAKE_VERSION(1, 0, 0), "cl_khr_icd"},
        cl_name_version{CL_MAKE_VERSION(1, 0, 0), "cl_khr_extended_versioning"}};

    Info info;
    info.mProfile.assign("FULL_PROFILE");
    info.mVersionStr.assign(GetVersionString());
    info.mVersion = GetVersion();
    info.mName.assign("ANGLE Vulkan");
    info.mExtensions.assign(CreateExtensionString(extList));
    info.mExtensionsWithVersion = std::move(extList);
    info.mHostTimerRes          = 0u;

    InitList initList;
    initList.emplace_back(new CLPlatformVk, std::move(info));
    return initList;
}

const std::string &CLPlatformVk::GetVersionString()
{
    static const angle::base::NoDestructor<const std::string> sVersion(
        "OpenCL " + std::to_string(CL_VERSION_MAJOR(GetVersion())) + "." +
        std::to_string(CL_VERSION_MINOR(GetVersion())) + " ANGLE " ANGLE_VERSION_STRING);
    return *sVersion;
}

CLPlatformVk::CLPlatformVk() = default;

}  // namespace rx
