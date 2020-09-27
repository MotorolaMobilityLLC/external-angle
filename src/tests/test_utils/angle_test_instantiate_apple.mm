//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// This file includes APIs to detect whether certain Apple renderer is availabe for testing.
//

#include "test_utils/angle_test_instantiate_apple.h"

#include "common/apple_platform_utils.h"
#include "test_utils/angle_test_instantiate.h"

namespace angle
{

bool IsMetalRendererAvailable()
{
    // NOTE(hqle): This code is currently duplicated with rx::IsMetalDisplayAvailable().
    // Consider move it to a common source code accessible to both libANGLE and test apps.
    if (ANGLE_APPLE_AVAILABLE_XCI(10.13, 13.0, 11))
    {
        return true;
    }
    return false;
}

bool IsMetalTextureSwizzleAvailable()
{
    // NOTE(hqle): This might not be accurate, since the capabilities also depend on underlying
    // hardwares, however, it is OK for testing.
    if (ANGLE_APPLE_AVAILABLE_XCI(10.15, 13.0, 13))
    {
        // Intel doesn't support swizzle because it is GPU family 1. We don't have a way to detect
        // Metal family here, so skip on Intel.
        return !IsIntel();
    }
    return false;
}

}  // namespace angle
