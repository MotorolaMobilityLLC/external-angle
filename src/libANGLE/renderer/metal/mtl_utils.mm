//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// mtl_utils.mm:
//    Implements utilities functions that create Metal shaders, convert from angle enums
//    to Metal enums and so on.
//

#include "libANGLE/renderer/metal/mtl_utils.h"

#include <TargetConditionals.h>

#include "common/MemoryBuffer.h"
#include "gpu_info_util/SystemInfo.h"
#include "libANGLE/renderer/metal/ContextMtl.h"
#include "libANGLE/renderer/metal/DisplayMtl.h"
#include "libANGLE/renderer/metal/RenderTargetMtl.h"
#include "libANGLE/renderer/metal/mtl_render_utils.h"

namespace rx
{
namespace mtl
{

namespace
{

uint32_t GetDeviceVendorIdFromName(id<MTLDevice> metalDevice)
{
    struct Vendor
    {
        NSString *const trademark;
        uint32_t vendorId;
    };

    constexpr Vendor kVendors[] = {{@"AMD", angle::kVendorID_AMD},
                                   {@"Radeon", angle::kVendorID_AMD},
                                   {@"Intel", angle::kVendorID_Intel},
                                   {@"Geforce", angle::kVendorID_NVIDIA},
                                   {@"Quadro", angle::kVendorID_NVIDIA}};
    ANGLE_MTL_OBJC_SCOPE
    {
        if (metalDevice)
        {
            for (const Vendor &it : kVendors)
            {
                if ([metalDevice.name rangeOfString:it.trademark].location != NSNotFound)
                {
                    return it.vendorId;
                }
            }
        }

        return 0;
    }
}

#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
uint32_t GetDeviceVendorIdFromIOKit(id<MTLDevice> device)
{
    return angle::GetVendorIDFromMetalDeviceRegistryID(device.registryID);
}
#endif

}

angle::Result InitializeTextureContents(const gl::Context *context,
                                        const TextureRef &texture,
                                        const Format &textureObjFormat,
                                        const gl::ImageIndex &index)
{
    ASSERT(texture && texture->valid());
    ASSERT(texture->textureType() == MTLTextureType2D ||
           texture->textureType() == MTLTextureTypeCube);
    ContextMtl *contextMtl = mtl::GetImpl(context);

    const gl::InternalFormat &intendedInternalFormat = textureObjFormat.intendedInternalFormat();

    // This function is called in many places to initialize the content of a texture.
    // So it's better we do the sanity check here instead of let the callers do it themselves:
    if (!textureObjFormat.valid() || intendedInternalFormat.compressed ||
        intendedInternalFormat.depthBits > 0 || intendedInternalFormat.stencilBits > 0)
    {
        return angle::Result::Continue;
    }

    gl::Extents size = texture->size(index);

    // Initialize the content to black
    if (texture->isCPUAccessible() && index.getType() != gl::TextureType::_2DMultisample &&
        index.getType() != gl::TextureType::_2DMultisampleArray)
    {

        const angle::Format &dstFormat = angle::Format::Get(textureObjFormat.actualFormatId);
        const size_t dstRowPitch       = dstFormat.pixelBytes * size.width;
        angle::MemoryBuffer conversionRow;
        ANGLE_CHECK_GL_ALLOC(contextMtl, conversionRow.resize(dstRowPitch));

        if (textureObjFormat.initFunction)
        {
            textureObjFormat.initFunction(size.width, 1, 1, conversionRow.data(), dstRowPitch, 0);
        }
        else
        {
            const angle::Format &srcFormat = angle::Format::Get(
                intendedInternalFormat.alphaBits > 0 ? angle::FormatID::R8G8B8A8_UNORM
                                                     : angle::FormatID::R8G8B8_UNORM);
            const size_t srcRowPitch = srcFormat.pixelBytes * size.width;
            angle::MemoryBuffer srcRow;
            ANGLE_CHECK_GL_ALLOC(contextMtl, srcRow.resize(srcRowPitch));
            memset(srcRow.data(), 0, srcRowPitch);

            CopyImageCHROMIUM(srcRow.data(), srcRowPitch, srcFormat.pixelBytes, 0,
                              srcFormat.pixelReadFunction, conversionRow.data(), dstRowPitch,
                              dstFormat.pixelBytes, 0, dstFormat.pixelWriteFunction,
                              intendedInternalFormat.format, dstFormat.componentType, size.width, 1,
                              1, false, false, false);
        }

        auto mtlRowRegion = MTLRegionMake2D(0, 0, size.width, 1);

        for (NSUInteger r = 0; r < static_cast<NSUInteger>(size.height); ++r)
        {
            mtlRowRegion.origin.y = r;

            // Upload to texture
            texture->replaceRegion(contextMtl, mtlRowRegion, index.getLevelIndex(),
                                   index.hasLayer() ? index.cubeMapFaceIndex() : 0,
                                   conversionRow.data(), dstRowPitch);
        }
    }
    else
    {
        ANGLE_TRY(InitializeTextureContentsGPU(context, texture, textureObjFormat, index,
                                               MTLColorWriteMaskAll));
    }

    return angle::Result::Continue;
}

angle::Result InitializeTextureContentsGPU(const gl::Context *context,
                                           const TextureRef &texture,
                                           const Format &textureObjFormat,
                                           const gl::ImageIndex &index,
                                           MTLColorWriteMask channelsToInit)
{
    ContextMtl *contextMtl = mtl::GetImpl(context);
    // NOTE(hqle): Support layered textures
    ASSERT(!index.hasLayer());

    // Use clear render command
    RenderTargetMtl tempRtt;
    tempRtt.set(texture, index.getLevelIndex(), 0, textureObjFormat);

    // temporarily enable color channels requested via channelsToInit. Some emulated format has some
    // channels write mask disabled when the texture is created.
    MTLColorWriteMask oldMask = texture->getColorWritableMask();
    texture->setColorWritableMask(channelsToInit);

    RenderCommandEncoder *encoder;
    if (channelsToInit == MTLColorWriteMaskAll)
    {
        // If all channels will be initialized, use clear loadOp.
        Optional<MTLClearColor> blackColor = MTLClearColorMake(0, 0, 0, 1);
        encoder = contextMtl->getRenderTargetCommandEncoderWithClear(tempRtt, blackColor);
    }
    else
    {
        // If there are some channels don't need to be initialized, we must use clearWithDraw.
        encoder = contextMtl->getRenderTargetCommandEncoder(tempRtt);

        ClearRectParams clearParams;
        clearParams.clearColor     = {.alpha = 1};
        clearParams.dstTextureSize = texture->size();
        clearParams.enabledBuffers.set(0);
        clearParams.clearArea = gl::Rectangle(0, 0, texture->width(), texture->height());

        ANGLE_TRY(
            contextMtl->getDisplay()->getUtils().clearWithDraw(context, encoder, clearParams));
    }
    ANGLE_UNUSED_VARIABLE(encoder);
    contextMtl->endEncoding(true);

    // Restore texture's intended write mask
    texture->setColorWritableMask(oldMask);

    return angle::Result::Continue;
}

MTLViewport GetViewport(const gl::Rectangle &rect, double znear, double zfar)
{
    MTLViewport re;

    re.originX = rect.x;
    re.originY = rect.y;
    re.width   = rect.width;
    re.height  = rect.height;
    re.znear   = znear;
    re.zfar    = zfar;

    return re;
}

MTLViewport GetViewportFlipY(const gl::Rectangle &rect,
                             NSUInteger screenHeight,
                             double znear,
                             double zfar)
{
    MTLViewport re;

    re.originX = rect.x;
    re.originY = static_cast<double>(screenHeight) - rect.y1();
    re.width   = rect.width;
    re.height  = rect.height;
    re.znear   = znear;
    re.zfar    = zfar;

    return re;
}

MTLViewport GetViewport(const gl::Rectangle &rect,
                        NSUInteger screenHeight,
                        bool flipY,
                        double znear,
                        double zfar)
{
    if (flipY)
    {
        return GetViewportFlipY(rect, screenHeight, znear, zfar);
    }

    return GetViewport(rect, znear, zfar);
}

MTLScissorRect GetScissorRect(const gl::Rectangle &rect, NSUInteger screenHeight, bool flipY)
{
    MTLScissorRect re;

    re.x      = rect.x;
    re.y      = flipY ? (screenHeight - rect.y1()) : rect.y;
    re.width  = rect.width;
    re.height = rect.height;

    return re;
}

uint32_t GetDeviceVendorId(id<MTLDevice> metalDevice)
{
    uint32_t vendorId = 0;
#if TARGET_OS_OSX || TARGET_OS_MACCATALYST
    if (ANGLE_APPLE_AVAILABLE_XC(10.13, 13.0))
    {
        vendorId = GetDeviceVendorIdFromIOKit(metalDevice);
    }
#endif
    if (!vendorId)
    {
        vendorId = GetDeviceVendorIdFromName(metalDevice);
    }

    return vendorId;
}

AutoObjCPtr<id<MTLLibrary>> CreateShaderLibrary(id<MTLDevice> metalDevice,
                                                const std::string &source,
                                                AutoObjCPtr<NSError *> *error)
{
    return CreateShaderLibrary(metalDevice, source.c_str(), source.size(), error);
}

AutoObjCPtr<id<MTLLibrary>> CreateShaderLibrary(id<MTLDevice> metalDevice,
                                                const char *source,
                                                size_t sourceLen,
                                                AutoObjCPtr<NSError *> *errorOut)
{
    ANGLE_MTL_OBJC_SCOPE
    {
        NSError *nsError = nil;
        auto nsSource    = [[NSString alloc] initWithBytesNoCopy:const_cast<char *>(source)
                                                       length:sourceLen
                                                     encoding:NSUTF8StringEncoding
                                                 freeWhenDone:NO];
        auto options     = [[[MTLCompileOptions alloc] init] ANGLE_MTL_AUTORELEASE];
        auto library = [metalDevice newLibraryWithSource:nsSource options:options error:&nsError];

        [nsSource ANGLE_MTL_AUTORELEASE];

        *errorOut = std::move(nsError);

        return [library ANGLE_MTL_AUTORELEASE];
    }
}

AutoObjCPtr<id<MTLLibrary>> CreateShaderLibraryFromBinary(id<MTLDevice> metalDevice,
                                                          const uint8_t *binarySource,
                                                          size_t binarySourceLen,
                                                          AutoObjCPtr<NSError *> *errorOut)
{
    ANGLE_MTL_OBJC_SCOPE
    {
        NSError *nsError = nil;
        auto shaderSourceData =
            dispatch_data_create(binarySource, binarySourceLen, dispatch_get_main_queue(),
                                 ^{
                                 });

        auto library = [metalDevice newLibraryWithData:shaderSourceData error:&nsError];

        [shaderSourceData ANGLE_MTL_AUTORELEASE];

        *errorOut = std::move(nsError);

        return [library ANGLE_MTL_AUTORELEASE];
    }
}

MTLTextureType GetTextureType(gl::TextureType glType)
{
    switch (glType)
    {
        case gl::TextureType::_2D:
            return MTLTextureType2D;
        case gl::TextureType::CubeMap:
            return MTLTextureTypeCube;
        default:
            return MTLTextureTypeInvalid;
    }
}

MTLSamplerMinMagFilter GetFilter(GLenum filter)
{
    switch (filter)
    {
        case GL_LINEAR_MIPMAP_LINEAR:
        case GL_LINEAR_MIPMAP_NEAREST:
        case GL_LINEAR:
            return MTLSamplerMinMagFilterLinear;
        case GL_NEAREST_MIPMAP_LINEAR:
        case GL_NEAREST_MIPMAP_NEAREST:
        case GL_NEAREST:
            return MTLSamplerMinMagFilterNearest;
        default:
            UNIMPLEMENTED();
            return MTLSamplerMinMagFilterNearest;
    }
}

MTLSamplerMipFilter GetMipmapFilter(GLenum filter)
{
    switch (filter)
    {
        case GL_LINEAR:
        case GL_NEAREST:
            return MTLSamplerMipFilterNotMipmapped;
        case GL_LINEAR_MIPMAP_LINEAR:
        case GL_NEAREST_MIPMAP_LINEAR:
            return MTLSamplerMipFilterLinear;
        case GL_NEAREST_MIPMAP_NEAREST:
        case GL_LINEAR_MIPMAP_NEAREST:
            return MTLSamplerMipFilterNearest;
        default:
            UNIMPLEMENTED();
            return MTLSamplerMipFilterNotMipmapped;
    }
}

MTLSamplerAddressMode GetSamplerAddressMode(GLenum wrap)
{
    switch (wrap)
    {
        case GL_REPEAT:
            return MTLSamplerAddressModeRepeat;
        case GL_MIRRORED_REPEAT:
            return MTLSamplerAddressModeMirrorRepeat;
        case GL_CLAMP_TO_BORDER:
            // ES doesn't have border support
            return MTLSamplerAddressModeClampToEdge;
        case GL_CLAMP_TO_EDGE:
            return MTLSamplerAddressModeClampToEdge;
        default:
            UNIMPLEMENTED();
            return MTLSamplerAddressModeClampToEdge;
    }
}

MTLBlendFactor GetBlendFactor(GLenum factor)
{
    switch (factor)
    {
        case GL_ZERO:
            return MTLBlendFactorZero;
        case GL_ONE:
            return MTLBlendFactorOne;
        case GL_SRC_COLOR:
            return MTLBlendFactorSourceColor;
        case GL_DST_COLOR:
            return MTLBlendFactorDestinationColor;
        case GL_ONE_MINUS_SRC_COLOR:
            return MTLBlendFactorOneMinusSourceColor;
        case GL_SRC_ALPHA:
            return MTLBlendFactorSourceAlpha;
        case GL_ONE_MINUS_SRC_ALPHA:
            return MTLBlendFactorOneMinusSourceAlpha;
        case GL_DST_ALPHA:
            return MTLBlendFactorDestinationAlpha;
        case GL_ONE_MINUS_DST_ALPHA:
            return MTLBlendFactorOneMinusDestinationAlpha;
        case GL_ONE_MINUS_DST_COLOR:
            return MTLBlendFactorOneMinusDestinationColor;
        case GL_SRC_ALPHA_SATURATE:
            return MTLBlendFactorSourceAlphaSaturated;
        case GL_CONSTANT_COLOR:
            return MTLBlendFactorBlendColor;
        case GL_CONSTANT_ALPHA:
            return MTLBlendFactorBlendAlpha;
        case GL_ONE_MINUS_CONSTANT_COLOR:
            return MTLBlendFactorOneMinusBlendColor;
        case GL_ONE_MINUS_CONSTANT_ALPHA:
            return MTLBlendFactorOneMinusBlendAlpha;
        default:
            UNREACHABLE();
            return MTLBlendFactorZero;
    }
}

MTLBlendOperation GetBlendOp(GLenum op)
{
    switch (op)
    {
        case GL_FUNC_ADD:
            return MTLBlendOperationAdd;
        case GL_FUNC_SUBTRACT:
            return MTLBlendOperationSubtract;
        case GL_FUNC_REVERSE_SUBTRACT:
            return MTLBlendOperationReverseSubtract;
        case GL_MIN:
            return MTLBlendOperationMin;
        case GL_MAX:
            return MTLBlendOperationMax;
        default:
            UNREACHABLE();
            return MTLBlendOperationAdd;
    }
}

MTLCompareFunction GetCompareFunc(GLenum func)
{
    switch (func)
    {
        case GL_NEVER:
            return MTLCompareFunctionNever;
        case GL_ALWAYS:
            return MTLCompareFunctionAlways;
        case GL_LESS:
            return MTLCompareFunctionLess;
        case GL_LEQUAL:
            return MTLCompareFunctionLessEqual;
        case GL_EQUAL:
            return MTLCompareFunctionEqual;
        case GL_GREATER:
            return MTLCompareFunctionGreater;
        case GL_GEQUAL:
            return MTLCompareFunctionGreaterEqual;
        case GL_NOTEQUAL:
            return MTLCompareFunctionNotEqual;
        default:
            UNREACHABLE();
            return MTLCompareFunctionAlways;
    }
}

MTLStencilOperation GetStencilOp(GLenum op)
{
    switch (op)
    {
        case GL_KEEP:
            return MTLStencilOperationKeep;
        case GL_ZERO:
            return MTLStencilOperationZero;
        case GL_REPLACE:
            return MTLStencilOperationReplace;
        case GL_INCR:
            return MTLStencilOperationIncrementClamp;
        case GL_DECR:
            return MTLStencilOperationDecrementClamp;
        case GL_INCR_WRAP:
            return MTLStencilOperationIncrementWrap;
        case GL_DECR_WRAP:
            return MTLStencilOperationDecrementWrap;
        case GL_INVERT:
            return MTLStencilOperationInvert;
        default:
            UNREACHABLE();
            return MTLStencilOperationKeep;
    }
}

MTLWinding GetFontfaceWinding(GLenum frontFaceMode, bool invert)
{
    switch (frontFaceMode)
    {
        case GL_CW:
            return invert ? MTLWindingCounterClockwise : MTLWindingClockwise;
        case GL_CCW:
            return invert ? MTLWindingClockwise : MTLWindingCounterClockwise;
        default:
            UNREACHABLE();
            return MTLWindingClockwise;
    }
}

#if ANGLE_MTL_PRIMITIVE_TOPOLOGY_CLASS_AVAILABLE
PrimitiveTopologyClass GetPrimitiveTopologyClass(gl::PrimitiveMode mode)
{
    // NOTE(hqle): Support layered renderring in future.
    // In non-layered rendering mode, unspecified is enough.
    return MTLPrimitiveTopologyClassUnspecified;
}
#else  // ANGLE_MTL_PRIMITIVE_TOPOLOGY_CLASS_AVAILABLE
PrimitiveTopologyClass GetPrimitiveTopologyClass(gl::PrimitiveMode mode)
{
    return kPrimitiveTopologyClassTriangle;
}
#endif

MTLPrimitiveType GetPrimitiveType(gl::PrimitiveMode mode)
{
    switch (mode)
    {
        case gl::PrimitiveMode::Triangles:
            return MTLPrimitiveTypeTriangle;
        case gl::PrimitiveMode::Points:
            return MTLPrimitiveTypePoint;
        case gl::PrimitiveMode::Lines:
            return MTLPrimitiveTypeLine;
        case gl::PrimitiveMode::LineStrip:
        case gl::PrimitiveMode::LineLoop:
            return MTLPrimitiveTypeLineStrip;
        case gl::PrimitiveMode::TriangleStrip:
            return MTLPrimitiveTypeTriangleStrip;
        case gl::PrimitiveMode::TriangleFan:
            // NOTE(hqle): Emulate triangle fan.
        default:
            return MTLPrimitiveTypeInvalid;
    }
}

MTLIndexType GetIndexType(gl::DrawElementsType type)
{
    switch (type)
    {
        case gl::DrawElementsType::UnsignedShort:
            return MTLIndexTypeUInt16;
        case gl::DrawElementsType::UnsignedInt:
            return MTLIndexTypeUInt32;
        case gl::DrawElementsType::UnsignedByte:
            // NOTE(hqle): Convert to supported type
        default:
            return MTLIndexTypeInvalid;
    }
}

#if defined(__IPHONE_13_0) || defined(__MAC_10_15)
MTLTextureSwizzle GetTextureSwizzle(GLenum swizzle)
{
    switch (swizzle)
    {
        case GL_RED:
            return MTLTextureSwizzleRed;
        case GL_GREEN:
            return MTLTextureSwizzleGreen;
        case GL_BLUE:
            return MTLTextureSwizzleBlue;
        case GL_ALPHA:
            return MTLTextureSwizzleAlpha;
        case GL_ZERO:
            return MTLTextureSwizzleZero;
        case GL_ONE:
            return MTLTextureSwizzleOne;
        default:
            UNREACHABLE();
            return MTLTextureSwizzleZero;
    }
}
#endif

MTLColorWriteMask GetEmulatedColorWriteMask(const mtl::Format &mtlFormat, bool *isEmulatedOut)
{
    const angle::Format &intendedFormat = mtlFormat.intendedAngleFormat();
    const angle::Format &actualFormat   = mtlFormat.actualAngleFormat();
    bool isFormatEmulated               = false;
    MTLColorWriteMask colorWritableMask = MTLColorWriteMaskAll;
    if (intendedFormat.alphaBits == 0 && actualFormat.alphaBits)
    {
        isFormatEmulated = true;
        // Disable alpha write to this texture
        colorWritableMask = colorWritableMask & (~MTLColorWriteMaskAlpha);
    }
    if (intendedFormat.luminanceBits == 0)
    {
        if (intendedFormat.redBits == 0 && actualFormat.redBits)
        {
            isFormatEmulated = true;
            // Disable red write to this texture
            colorWritableMask = colorWritableMask & (~MTLColorWriteMaskRed);
        }
        if (intendedFormat.greenBits == 0 && actualFormat.greenBits)
        {
            isFormatEmulated = true;
            // Disable green write to this texture
            colorWritableMask = colorWritableMask & (~MTLColorWriteMaskGreen);
        }
        if (intendedFormat.blueBits == 0 && actualFormat.blueBits)
        {
            isFormatEmulated = true;
            // Disable blue write to this texture
            colorWritableMask = colorWritableMask & (~MTLColorWriteMaskBlue);
        }
    }

    *isEmulatedOut = isFormatEmulated;

    return colorWritableMask;
}

MTLColorWriteMask GetEmulatedColorWriteMask(const mtl::Format &mtlFormat)
{
    // Ignore isFormatEmulated boolean value
    bool isFormatEmulated;
    return GetEmulatedColorWriteMask(mtlFormat, &isFormatEmulated);
}

bool IsFormatEmulated(const mtl::Format &mtlFormat)
{
    bool isFormatEmulated;
    (void)GetEmulatedColorWriteMask(mtlFormat, &isFormatEmulated);
    return isFormatEmulated;
}

MTLClearColor EmulatedAlphaClearColor(MTLClearColor color, MTLColorWriteMask colorMask)
{
    MTLClearColor re = color;

    if (!(colorMask & MTLColorWriteMaskAlpha))
    {
        re.alpha = kEmulatedAlphaValue;
    }

    return re;
}

}  // namespace mtl
}  // namespace rx
