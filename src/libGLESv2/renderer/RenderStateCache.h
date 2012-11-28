//
// Copyright (c) 2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// RenderStateCache.h: Defines rx::RenderStateCache, a cache of Direct3D render
// state objects.

#ifndef LIBGLESV2_RENDERER_RENDERSTATECACHE_H_
#define LIBGLESV2_RENDERER_RENDERSTATECACHE_H_

#include "libGLESv2/angletypes.h"
#include "common/angleutils.h"

#include <D3D11.h>
#include <unordered_map>

namespace rx
{

class RenderStateCache
{
  public:
    RenderStateCache();
    virtual ~RenderStateCache();

    void initialize(ID3D11Device* device);
    void clear();

    // Increments refcount on the returned blend state, Release() must be called.
    ID3D11BlendState *getBlendState(const gl::BlendState &blendState);
    ID3D11RasterizerState *getRasterizerState(const gl::RasterizerState &rasterState,
                                              unsigned int depthSize);

  private:
    DISALLOW_COPY_AND_ASSIGN(RenderStateCache);

    unsigned long long mCounter;

    // Blend state cache
    static std::size_t hashBlendState(const gl::BlendState &blendState);
    static bool compareBlendStates(const gl::BlendState &a, const gl::BlendState &b);
    static const unsigned int kMaxBlendStates;

    typedef std::size_t (*BlendStateHashFunction)(const gl::BlendState &);
    typedef bool (*BlendStateEqualityFunction)(const gl::BlendState &, const gl::BlendState &);
    typedef std::pair<ID3D11BlendState*, unsigned long long> BlendStateCounterPair;
    typedef std::unordered_map<gl::BlendState, BlendStateCounterPair, BlendStateHashFunction, BlendStateEqualityFunction> BlendStateMap;
    BlendStateMap mBlendStateCache;

    // Rasterizer state cache
    struct RasterizerStateKey
    {
        gl::RasterizerState rasterizerState;
        unsigned int depthSize;
    };
    static std::size_t hashRasterizerState(const RasterizerStateKey &rasterState);
    static bool compareRasterizerStates(const RasterizerStateKey &a, const RasterizerStateKey &b);
    static const unsigned int kMaxRasterizerStates;

    typedef std::size_t (*RasterizerStateHashFunction)(const RasterizerStateKey &);
    typedef bool (*RasterizerStateEqualityFunction)(const RasterizerStateKey &, const RasterizerStateKey &);
    typedef std::pair<ID3D11RasterizerState*, unsigned long long> RasterizerStateCounterPair;
    typedef std::unordered_map<RasterizerStateKey, RasterizerStateCounterPair, RasterizerStateHashFunction, RasterizerStateEqualityFunction> RasterizerStateMap;
    RasterizerStateMap mRasterizerStateCache;

    ID3D11Device* mDevice;
};

}

#endif // LIBGLESV2_RENDERER_RENDERSTATECACHE_H_