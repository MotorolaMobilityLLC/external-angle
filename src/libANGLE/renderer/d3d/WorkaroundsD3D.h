//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// WorkaroundsD3D.h: Workarounds for D3D driver bugs and other issues.

#ifndef LIBANGLE_RENDERER_D3D_WORKAROUNDSD3D_H_
#define LIBANGLE_RENDERER_D3D_WORKAROUNDSD3D_H_

// TODO(jmadill,zmo,geofflang): make a workarounds library that can operate
// independent of ANGLE's renderer. Workarounds should also be accessible
// outside of the Renderer.

namespace rx
{
struct D3DCompilerWorkarounds
{
    bool skipOptimization   = false;
    bool useMaxOptimization = false;

    // IEEE strictness needs to be enabled for NANs to work.
    bool enableIEEEStrictness = false;
};

struct WorkaroundsD3D
{
    // On some systems, having extra rendertargets than necessary slows down the shader.
    // We can fix this by optimizing those out of the shader. At the same time, we can
    // work around a bug on some nVidia drivers that they ignore "null" render targets
    // in D3D11, by compacting the active color attachments list to omit null entries.
    bool mrtPerfWorkaround = false;

    bool setDataFasterThanImageUpload = false;

    // Some renderers can't disable mipmaps on a mipmapped texture (i.e. solely sample from level
    // zero, and ignore the other levels). D3D11 Feature Level 10+ does this by setting MaxLOD to
    // 0.0f in the Sampler state. D3D9 sets D3DSAMP_MIPFILTER to D3DTEXF_NONE. There is no
    // equivalent to this in D3D11 Feature Level 9_3. This causes problems when (for example) an
    // application creates a mipmapped texture2D, but sets GL_TEXTURE_MIN_FILTER to GL_NEAREST
    // (i.e disables mipmaps). To work around this, D3D11 FL9_3 has to create two copies of the
    // texture. The textures' level zeros are identical, but only one texture has mips.
    bool zeroMaxLodWorkaround = false;

    // Some renderers do not support Geometry Shaders so the Geometry Shader-based PointSprite
    // emulation will not work. To work around this, D3D11 FL9_3 has to use a different pointsprite
    // emulation that is implemented using instanced quads.
    bool useInstancedPointSpriteEmulation = false;

    // A bug fixed in NVIDIA driver version 347.88 < x <= 368.81 triggers a TDR when using
    // CopySubresourceRegion from a staging texture to a depth/stencil in D3D11. The workaround
    // is to use UpdateSubresource to trigger an extra copy. We disable this workaround on newer
    // NVIDIA driver versions because of a second driver bug present with the workaround enabled.
    // (See: http://anglebug.com/1452)
    bool depthStencilBlitExtraCopy = false;

    // The HLSL optimizer has a bug with optimizing "pow" in certain integer-valued expressions.
    // We can work around this by expanding the pow into a series of multiplies if we're running
    // under the affected compiler.
    bool expandIntegerPowExpressions = false;

    // NVIDIA drivers sometimes write out-of-order results to StreamOut buffers when transform
    // feedback is used to repeatedly write to the same buffer positions.
    bool flushAfterEndingTransformFeedback = false;

    // Some drivers (NVIDIA) do not take into account the base level of the texture in the results
    // of the HLSL GetDimensions builtin.
    bool getDimensionsIgnoresBaseLevel = false;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_D3D_WORKAROUNDSD3D_H_
