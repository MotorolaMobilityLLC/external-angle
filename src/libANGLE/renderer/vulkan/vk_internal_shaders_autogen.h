// GENERATED FILE - DO NOT EDIT.
// Generated by gen_vk_internal_shaders.py using data from shaders/src/*
//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// vk_internal_shaders_autogen.h:
//   Pre-generated shader library for the ANGLE Vulkan back-end.

#ifndef LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_
#define LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_

#include "libANGLE/renderer/vulkan/vk_utils.h"

namespace rx
{
namespace vk
{
namespace InternalShader
{
namespace BlitResolve_frag
{
enum flags
{
    kSrcIsArray = 0x00000001,
    kIsResolve  = 0x00000002,
};
enum Blit
{
    kBlitColorFloat   = 0x00000000,
    kBlitColorInt     = 0x00000004,
    kBlitColorUint    = 0x00000008,
    kBlitDepth        = 0x0000000C,
    kBlitStencil      = 0x00000010,
    kBlitDepthStencil = 0x00000014,
};
constexpr size_t kArrayLen = 0x00000018;
}  // namespace BlitResolve_frag

namespace BlitResolveStencilNoExport_comp
{
enum flags
{
    kSrcIsArray = 0x00000001,
    kIsResolve  = 0x00000002,
};
constexpr size_t kArrayLen = 0x00000004;
}  // namespace BlitResolveStencilNoExport_comp

namespace BufferUtils_comp
{
enum flags
{
    kIsAligned = 0x00000001,
};
enum Function
{
    kIsClear = 0x00000000,
    kIsCopy  = 0x00000002,
};
enum Format
{
    kIsFloat = 0x00000000,
    kIsSint  = 0x00000004,
    kIsUint  = 0x00000008,
};
constexpr size_t kArrayLen = 0x0000000C;
}  // namespace BufferUtils_comp

namespace ConvertIndex_comp
{
enum flags
{
    kIsPrimitiveRestartEnabled = 0x00000001,
    kIsIndirect                = 0x00000002,
};
constexpr size_t kArrayLen = 0x00000004;
}  // namespace ConvertIndex_comp

namespace ConvertIndexIndirectLineLoop_comp
{
enum IndicesBitsWidth
{
    kIs8Bits  = 0x00000000,
    kIs16Bits = 0x00000001,
    kIs32Bits = 0x00000002,
};
constexpr size_t kArrayLen = 0x00000003;
}  // namespace ConvertIndexIndirectLineLoop_comp

namespace ConvertIndirectLineLoop_comp
{
constexpr size_t kArrayLen = 0x00000001;
}  // namespace ConvertIndirectLineLoop_comp

namespace ConvertVertex_comp
{
enum Conversion
{
    kSintToSint   = 0x00000000,
    kUintToUint   = 0x00000001,
    kSintToFloat  = 0x00000002,
    kUintToFloat  = 0x00000003,
    kSnormToFloat = 0x00000004,
    kUnormToFloat = 0x00000005,
    kFixedToFloat = 0x00000006,
    kFloatToFloat = 0x00000007,
};
constexpr size_t kArrayLen = 0x00000008;
}  // namespace ConvertVertex_comp

namespace FullScreenQuad_vert
{
constexpr size_t kArrayLen = 0x00000001;
}  // namespace FullScreenQuad_vert

namespace ImageClear_frag
{
enum AttachmentIndex
{
    kAttachment0 = 0x00000000,
    kAttachment1 = 0x00000001,
    kAttachment2 = 0x00000002,
    kAttachment3 = 0x00000003,
    kAttachment4 = 0x00000004,
    kAttachment5 = 0x00000005,
    kAttachment6 = 0x00000006,
    kAttachment7 = 0x00000007,
};
enum Format
{
    kIsFloat = 0x00000000,
    kIsSint  = 0x00000008,
    kIsUint  = 0x00000010,
};
constexpr size_t kArrayLen = 0x00000018;
}  // namespace ImageClear_frag

namespace ImageCopy_frag
{
enum DestFormat
{
    kDestIsFloat = 0x00000000,
    kDestIsSint  = 0x00000001,
    kDestIsUint  = 0x00000002,
};
enum SrcFormat
{
    kSrcIsFloat = 0x00000000,
    kSrcIsSint  = 0x00000004,
    kSrcIsUint  = 0x00000008,
};
enum SrcType
{
    kSrcIs2D      = 0x00000000,
    kSrcIs2DArray = 0x00000010,
    kSrcIs3D      = 0x00000020,
};
constexpr size_t kArrayLen = 0x0000002B;
}  // namespace ImageCopy_frag

namespace OverlayCull_comp
{
enum SubgroupSize
{
    kIs8x4 = 0x00000000,
    kIs8x8 = 0x00000001,
};
enum SubgroupOp
{
    kSupportsBallot     = 0x00000000,
    kSupportsArithmetic = 0x00000002,
    kSupportsNone       = 0x00000004,
};
constexpr size_t kArrayLen = 0x00000006;
}  // namespace OverlayCull_comp

namespace OverlayDraw_comp
{
enum SubgroupSize
{
    kIs8x4 = 0x00000000,
    kIs8x8 = 0x00000001,
};
constexpr size_t kArrayLen = 0x00000002;
}  // namespace OverlayDraw_comp

}  // namespace InternalShader

class ShaderLibrary final : angle::NonCopyable
{
  public:
    ShaderLibrary();
    ~ShaderLibrary();

    void destroy(VkDevice device);

    angle::Result getBlitResolve_frag(Context *context,
                                      uint32_t shaderFlags,
                                      RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getBlitResolveStencilNoExport_comp(Context *context,
                                                     uint32_t shaderFlags,
                                                     RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getBufferUtils_comp(Context *context,
                                      uint32_t shaderFlags,
                                      RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getConvertIndex_comp(Context *context,
                                       uint32_t shaderFlags,
                                       RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getConvertIndexIndirectLineLoop_comp(Context *context,
                                                       uint32_t shaderFlags,
                                                       RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getConvertIndirectLineLoop_comp(Context *context,
                                                  uint32_t shaderFlags,
                                                  RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getConvertVertex_comp(Context *context,
                                        uint32_t shaderFlags,
                                        RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getFullScreenQuad_vert(Context *context,
                                         uint32_t shaderFlags,
                                         RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getImageClear_frag(Context *context,
                                     uint32_t shaderFlags,
                                     RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getImageCopy_frag(Context *context,
                                    uint32_t shaderFlags,
                                    RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getOverlayCull_comp(Context *context,
                                      uint32_t shaderFlags,
                                      RefCounted<ShaderAndSerial> **shaderOut);
    angle::Result getOverlayDraw_comp(Context *context,
                                      uint32_t shaderFlags,
                                      RefCounted<ShaderAndSerial> **shaderOut);

  private:
    RefCounted<ShaderAndSerial>
        mBlitResolve_frag_shaders[InternalShader::BlitResolve_frag::kArrayLen];
    RefCounted<ShaderAndSerial> mBlitResolveStencilNoExport_comp_shaders
        [InternalShader::BlitResolveStencilNoExport_comp::kArrayLen];
    RefCounted<ShaderAndSerial>
        mBufferUtils_comp_shaders[InternalShader::BufferUtils_comp::kArrayLen];
    RefCounted<ShaderAndSerial>
        mConvertIndex_comp_shaders[InternalShader::ConvertIndex_comp::kArrayLen];
    RefCounted<ShaderAndSerial> mConvertIndexIndirectLineLoop_comp_shaders
        [InternalShader::ConvertIndexIndirectLineLoop_comp::kArrayLen];
    RefCounted<ShaderAndSerial> mConvertIndirectLineLoop_comp_shaders
        [InternalShader::ConvertIndirectLineLoop_comp::kArrayLen];
    RefCounted<ShaderAndSerial>
        mConvertVertex_comp_shaders[InternalShader::ConvertVertex_comp::kArrayLen];
    RefCounted<ShaderAndSerial>
        mFullScreenQuad_vert_shaders[InternalShader::FullScreenQuad_vert::kArrayLen];
    RefCounted<ShaderAndSerial>
        mImageClear_frag_shaders[InternalShader::ImageClear_frag::kArrayLen];
    RefCounted<ShaderAndSerial> mImageCopy_frag_shaders[InternalShader::ImageCopy_frag::kArrayLen];
    RefCounted<ShaderAndSerial>
        mOverlayCull_comp_shaders[InternalShader::OverlayCull_comp::kArrayLen];
    RefCounted<ShaderAndSerial>
        mOverlayDraw_comp_shaders[InternalShader::OverlayDraw_comp::kArrayLen];
};
}  // namespace vk
}  // namespace rx

#endif  // LIBANGLE_RENDERER_VULKAN_VK_INTERNAL_SHADERS_AUTOGEN_H_
