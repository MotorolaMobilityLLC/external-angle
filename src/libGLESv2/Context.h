//
// Copyright (c) 2002-2012 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Context.h: Defines the gl::Context class, managing all GL state and performing
// rendering operations. It is the GLES2 specific implementation of EGLContext.

#ifndef LIBGLESV2_CONTEXT_H_
#define LIBGLESV2_CONTEXT_H_

#define GL_APICALL
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define EGLAPI
#include <EGL/egl.h>
#include <d3d9.h>

#include <string>
#include <map>
#ifdef _MSC_VER
#include <hash_map>
#else
#include <unordered_map>
#endif

#include "common/angleutils.h"
#include "common/RefCountObject.h"
#include "libGLESv2/ResourceManager.h"
#include "libGLESv2/HandleAllocator.h"
#include "libGLESv2/renderer/Renderer.h"

namespace egl
{
class Display;
class Surface;
class Config;
}

namespace gl
{
struct TranslatedAttribute;
struct TranslatedIndexData;

class Buffer;
class Shader;
class Program;
class ProgramBinary;
class Texture;
class Texture2D;
class TextureCubeMap;
class Framebuffer;
class Renderbuffer;
class RenderbufferStorage;
class Colorbuffer;
class Depthbuffer;
class StreamingIndexBuffer;
class Stencilbuffer;
class DepthStencilbuffer;
class VertexDataManager;
class IndexDataManager;
class Blit;
class Fence;
class Query;

enum
{
    D3D9_MAX_FLOAT_CONSTANTS = 256,
    D3D9_MAX_BOOL_CONSTANTS = 16,
    D3D9_MAX_INT_CONSTANTS = 16,

    MAX_VERTEX_ATTRIBS = 16,
    MAX_VERTEX_UNIFORM_VECTORS = D3D9_MAX_FLOAT_CONSTANTS - 2,   // Reserve space for dx_HalfPixelSize and dx_DepthRange.
    MAX_VARYING_VECTORS_SM2 = 8,
    MAX_VARYING_VECTORS_SM3 = 10,
    MAX_TEXTURE_IMAGE_UNITS = 16,
    MAX_VERTEX_TEXTURE_IMAGE_UNITS_VTF = 4,   // For devices supporting vertex texture fetch
    MAX_COMBINED_TEXTURE_IMAGE_UNITS_VTF = MAX_TEXTURE_IMAGE_UNITS + MAX_VERTEX_TEXTURE_IMAGE_UNITS_VTF,    
    MAX_FRAGMENT_UNIFORM_VECTORS_SM2 = 32 - 3,    // Reserve space for dx_Coord, dx_Depth, and dx_DepthRange. dx_PointOrLines and dx_FrontCCW use separate bool registers.
    MAX_FRAGMENT_UNIFORM_VECTORS_SM3 = 224 - 3,
    MAX_DRAW_BUFFERS = 1,

    GL_BGRA4_ANGLEX = 0x6ABC,
    GL_BGR5_A1_ANGLEX = 0x6ABD
};

enum QueryType
{
    QUERY_ANY_SAMPLES_PASSED,
    QUERY_ANY_SAMPLES_PASSED_CONSERVATIVE,

    QUERY_TYPE_COUNT
};

const float ALIASED_LINE_WIDTH_RANGE_MIN = 1.0f;
const float ALIASED_LINE_WIDTH_RANGE_MAX = 1.0f;
const float ALIASED_POINT_SIZE_RANGE_MIN = 1.0f;
const float ALIASED_POINT_SIZE_RANGE_MAX_SM2 = 1.0f;

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
};

// Helper structure describing a single vertex attribute
class VertexAttribute
{
  public:
    VertexAttribute() : mType(GL_FLOAT), mSize(0), mNormalized(false), mStride(0), mPointer(NULL), mArrayEnabled(false), mDivisor(0)
    {
        mCurrentValue[0] = 0.0f;
        mCurrentValue[1] = 0.0f;
        mCurrentValue[2] = 0.0f;
        mCurrentValue[3] = 1.0f;
    }

    int typeSize() const
    {
        switch (mType)
        {
          case GL_BYTE:           return mSize * sizeof(GLbyte);
          case GL_UNSIGNED_BYTE:  return mSize * sizeof(GLubyte);
          case GL_SHORT:          return mSize * sizeof(GLshort);
          case GL_UNSIGNED_SHORT: return mSize * sizeof(GLushort);
          case GL_FIXED:          return mSize * sizeof(GLfixed);
          case GL_FLOAT:          return mSize * sizeof(GLfloat);
          default: UNREACHABLE(); return mSize * sizeof(GLfloat);
        }
    }

    GLsizei stride() const
    {
        return mStride ? mStride : typeSize();
    }

    // From glVertexAttribPointer
    GLenum mType;
    GLint mSize;
    bool mNormalized;
    GLsizei mStride;   // 0 means natural stride

    union
    {
        const void *mPointer;
        intptr_t mOffset;
    };

    BindingPointer<Buffer> mBoundBuffer;   // Captured when glVertexAttribPointer is called.

    bool mArrayEnabled;   // From glEnable/DisableVertexAttribArray
    float mCurrentValue[4];   // From glVertexAttrib
    unsigned int mDivisor;
};

typedef VertexAttribute VertexAttributeArray[MAX_VERTEX_ATTRIBS];

// Helper structure to store all raw state
struct State
{
    Color colorClearValue;
    GLclampf depthClearValue;
    int stencilClearValue;

    bool cullFace;
    GLenum cullMode;
    GLenum frontFace;
    bool depthTest;
    GLenum depthFunc;
    bool blend;
    GLenum sourceBlendRGB;
    GLenum destBlendRGB;
    GLenum sourceBlendAlpha;
    GLenum destBlendAlpha;
    GLenum blendEquationRGB;
    GLenum blendEquationAlpha;
    Color blendColor;
    bool stencilTest;
    GLenum stencilFunc;
    GLint stencilRef;
    GLuint stencilMask;
    GLenum stencilFail;
    GLenum stencilPassDepthFail;
    GLenum stencilPassDepthPass;
    GLuint stencilWritemask;
    GLenum stencilBackFunc;
    GLint stencilBackRef;
    GLuint stencilBackMask;
    GLenum stencilBackFail;
    GLenum stencilBackPassDepthFail;
    GLenum stencilBackPassDepthPass;
    GLuint stencilBackWritemask;
    bool polygonOffsetFill;
    GLfloat polygonOffsetFactor;
    GLfloat polygonOffsetUnits;
    bool sampleAlphaToCoverage;
    bool sampleCoverage;
    GLclampf sampleCoverageValue;
    bool sampleCoverageInvert;
    bool scissorTest;
    bool dither;

    GLfloat lineWidth;

    GLenum generateMipmapHint;
    GLenum fragmentShaderDerivativeHint;

    GLint viewportX;
    GLint viewportY;
    GLsizei viewportWidth;
    GLsizei viewportHeight;
    float zNear;
    float zFar;

    GLint scissorX;
    GLint scissorY;
    GLsizei scissorWidth;
    GLsizei scissorHeight;

    bool colorMaskRed;
    bool colorMaskGreen;
    bool colorMaskBlue;
    bool colorMaskAlpha;
    bool depthMask;

    unsigned int activeSampler;   // Active texture unit selector - GL_TEXTURE0
    BindingPointer<Buffer> arrayBuffer;
    BindingPointer<Buffer> elementArrayBuffer;
    GLuint readFramebuffer;
    GLuint drawFramebuffer;
    BindingPointer<Renderbuffer> renderbuffer;
    GLuint currentProgram;

    VertexAttribute vertexAttribute[MAX_VERTEX_ATTRIBS];
    BindingPointer<Texture> samplerTexture[TEXTURE_TYPE_COUNT][MAX_COMBINED_TEXTURE_IMAGE_UNITS_VTF];
    BindingPointer<Query> activeQuery[QUERY_TYPE_COUNT];

    GLint unpackAlignment;
    GLint packAlignment;
    bool packReverseRowOrder;
};

// Helper class to construct and cache vertex declarations
class VertexDeclarationCache
{
  public:
    VertexDeclarationCache();
    ~VertexDeclarationCache();

    GLenum applyDeclaration(IDirect3DDevice9 *device, TranslatedAttribute attributes[], ProgramBinary *programBinary, GLsizei instances, GLsizei *repeatDraw);

    void markStateDirty();

  private:
    UINT mMaxLru;

    enum { NUM_VERTEX_DECL_CACHE_ENTRIES = 32 };

    struct VBData
    {
        unsigned int serial;
        unsigned int stride;
        unsigned int offset;
    };

    VBData mAppliedVBs[MAX_VERTEX_ATTRIBS];
    IDirect3DVertexDeclaration9 *mLastSetVDecl;
    bool mInstancingEnabled;

    struct VertexDeclCacheEntry
    {
        D3DVERTEXELEMENT9 cachedElements[MAX_VERTEX_ATTRIBS + 1];
        UINT lruCount;
        IDirect3DVertexDeclaration9 *vertexDeclaration;
    } mVertexDeclCache[NUM_VERTEX_DECL_CACHE_ENTRIES];
};

class Context
{
  public:
    Context(const egl::Config *config, const gl::Context *shareContext, bool notifyResets, bool robustAccess);

    ~Context();

    void makeCurrent(egl::Display *display, egl::Surface *surface);

    virtual void markAllStateDirty();
    void markDxUniformsDirty();

    virtual void markContextLost();
    bool isContextLost();

    // State manipulation
    void setClearColor(float red, float green, float blue, float alpha);

    void setClearDepth(float depth);

    void setClearStencil(int stencil);

    void setCullFace(bool enabled);
    bool isCullFaceEnabled() const;

    void setCullMode(GLenum mode);

    void setFrontFace(GLenum front);

    void setDepthTest(bool enabled);
    bool isDepthTestEnabled() const;

    void setDepthFunc(GLenum depthFunc);

    void setDepthRange(float zNear, float zFar);
    
    void setBlend(bool enabled);
    bool isBlendEnabled() const;

    void setBlendFactors(GLenum sourceRGB, GLenum destRGB, GLenum sourceAlpha, GLenum destAlpha);
    void setBlendColor(float red, float green, float blue, float alpha);
    void setBlendEquation(GLenum rgbEquation, GLenum alphaEquation);

    void setStencilTest(bool enabled);
    bool isStencilTestEnabled() const;

    void setStencilParams(GLenum stencilFunc, GLint stencilRef, GLuint stencilMask);
    void setStencilBackParams(GLenum stencilBackFunc, GLint stencilBackRef, GLuint stencilBackMask);
    void setStencilWritemask(GLuint stencilWritemask);
    void setStencilBackWritemask(GLuint stencilBackWritemask);
    void setStencilOperations(GLenum stencilFail, GLenum stencilPassDepthFail, GLenum stencilPassDepthPass);
    void setStencilBackOperations(GLenum stencilBackFail, GLenum stencilBackPassDepthFail, GLenum stencilBackPassDepthPass);

    void setPolygonOffsetFill(bool enabled);
    bool isPolygonOffsetFillEnabled() const;

    void setPolygonOffsetParams(GLfloat factor, GLfloat units);

    void setSampleAlphaToCoverage(bool enabled);
    bool isSampleAlphaToCoverageEnabled() const;

    void setSampleCoverage(bool enabled);
    bool isSampleCoverageEnabled() const;

    void setSampleCoverageParams(GLclampf value, bool invert);

    void setScissorTest(bool enabled);
    bool isScissorTestEnabled() const;

    void setDither(bool enabled);
    bool isDitherEnabled() const;

    void setLineWidth(GLfloat width);

    void setGenerateMipmapHint(GLenum hint);
    void setFragmentShaderDerivativeHint(GLenum hint);

    void setViewportParams(GLint x, GLint y, GLsizei width, GLsizei height);

    void setScissorParams(GLint x, GLint y, GLsizei width, GLsizei height);

    void setColorMask(bool red, bool green, bool blue, bool alpha);
    void setDepthMask(bool mask);

    void setActiveSampler(unsigned int active);

    GLuint getReadFramebufferHandle() const;
    GLuint getDrawFramebufferHandle() const;
    GLuint getRenderbufferHandle() const;

    GLuint getArrayBufferHandle() const;

    GLuint getActiveQuery(GLenum target) const;

    void setEnableVertexAttribArray(unsigned int attribNum, bool enabled);
    const VertexAttribute &getVertexAttribState(unsigned int attribNum);
    void setVertexAttribState(unsigned int attribNum, Buffer *boundBuffer, GLint size, GLenum type,
                              bool normalized, GLsizei stride, const void *pointer);
    const void *getVertexAttribPointer(unsigned int attribNum) const;

    const VertexAttributeArray &getVertexAttributes();

    void setUnpackAlignment(GLint alignment);
    GLint getUnpackAlignment() const;

    void setPackAlignment(GLint alignment);
    GLint getPackAlignment() const;

    void setPackReverseRowOrder(bool reverseRowOrder);
    bool getPackReverseRowOrder() const;

    // These create  and destroy methods are merely pass-throughs to 
    // ResourceManager, which owns these object types
    GLuint createBuffer();
    GLuint createShader(GLenum type);
    GLuint createProgram();
    GLuint createTexture();
    GLuint createRenderbuffer();

    void deleteBuffer(GLuint buffer);
    void deleteShader(GLuint shader);
    void deleteProgram(GLuint program);
    void deleteTexture(GLuint texture);
    void deleteRenderbuffer(GLuint renderbuffer);

    // Framebuffers are owned by the Context, so these methods do not pass through
    GLuint createFramebuffer();
    void deleteFramebuffer(GLuint framebuffer);

    // Fences are owned by the Context.
    GLuint createFence();
    void deleteFence(GLuint fence);
    
    // Queries are owned by the Context;
    GLuint createQuery();
    void deleteQuery(GLuint query);

    void bindArrayBuffer(GLuint buffer);
    void bindElementArrayBuffer(GLuint buffer);
    void bindTexture2D(GLuint texture);
    void bindTextureCubeMap(GLuint texture);
    void bindReadFramebuffer(GLuint framebuffer);
    void bindDrawFramebuffer(GLuint framebuffer);
    void bindRenderbuffer(GLuint renderbuffer);
    void useProgram(GLuint program);
    void linkProgram(GLuint program);
    void setProgramBinary(GLuint program, const void *binary, GLint length);

    void beginQuery(GLenum target, GLuint query);
    void endQuery(GLenum target);

    void setFramebufferZero(Framebuffer *framebuffer);

    void setRenderbufferStorage(RenderbufferStorage *renderbuffer);

    void setVertexAttrib(GLuint index, const GLfloat *values);
    void setVertexAttribDivisor(GLuint index, GLuint divisor);

    Buffer *getBuffer(GLuint handle);
    Fence *getFence(GLuint handle);
    Shader *getShader(GLuint handle);
    Program *getProgram(GLuint handle);
    Texture *getTexture(GLuint handle);
    Framebuffer *getFramebuffer(GLuint handle);
    Renderbuffer *getRenderbuffer(GLuint handle);
    Query *getQuery(GLuint handle, bool create, GLenum type);

    Buffer *getArrayBuffer();
    Buffer *getElementArrayBuffer();
    ProgramBinary *getCurrentProgramBinary();
    Texture2D *getTexture2D();
    TextureCubeMap *getTextureCubeMap();
    Texture *getSamplerTexture(unsigned int sampler, TextureType type);
    Framebuffer *getReadFramebuffer();
    Framebuffer *getDrawFramebuffer();

    bool getFloatv(GLenum pname, GLfloat *params);
    bool getIntegerv(GLenum pname, GLint *params);
    bool getBooleanv(GLenum pname, GLboolean *params);

    bool getQueryParameterInfo(GLenum pname, GLenum *type, unsigned int *numParams);

    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei *bufSize, void* pixels);
    void clear(GLbitfield mask);
    void drawArrays(GLenum mode, GLint first, GLsizei count, GLsizei instances);
    void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instances);
    void sync(bool block);   // flush/finish

    void drawLineLoop(GLsizei count, GLenum type, const GLvoid *indices, int minIndex);

    void recordInvalidEnum();
    void recordInvalidValue();
    void recordInvalidOperation();
    void recordOutOfMemory();
    void recordInvalidFramebufferOperation();

    GLenum getError();
    GLenum getResetStatus();
    virtual bool isResetNotificationEnabled();

    bool supportsShaderModel3() const;
    float getMaximumPointSize() const;
    int getMaximumVaryingVectors() const;
    unsigned int getMaximumVertexTextureImageUnits() const;
    unsigned int getMaximumCombinedTextureImageUnits() const;
    int getMaximumFragmentUniformVectors() const;
    int getMaximumRenderbufferDimension() const;
    int getMaximumTextureDimension() const;
    int getMaximumCubeTextureDimension() const;
    int getMaximumTextureLevel() const;
    GLsizei getMaxSupportedSamples() const;
    int getNearestSupportedSamples(D3DFORMAT format, int requested) const;
    const char *getExtensionString() const;
    const char *getRendererString() const;
    bool supportsEventQueries() const;
    bool supportsOcclusionQueries() const;
    bool supportsDXT1Textures() const;
    bool supportsDXT3Textures() const;
    bool supportsDXT5Textures() const;
    bool supportsFloat32Textures() const;
    bool supportsFloat32LinearFilter() const;
    bool supportsFloat32RenderableTextures() const;
    bool supportsFloat16Textures() const;
    bool supportsFloat16LinearFilter() const;
    bool supportsFloat16RenderableTextures() const;
    bool supportsLuminanceTextures() const;
    bool supportsLuminanceAlphaTextures() const;
    bool supportsDepthTextures() const;
    bool supports32bitIndices() const;
    bool supportsNonPower2Texture() const;
    bool supportsInstancing() const;
    bool supportsTextureFilterAnisotropy() const;

    bool getCurrentReadFormatType(GLenum *format, GLenum *type);

    float getTextureMaxAnisotropy() const;

    void blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, 
                         GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                         GLbitfield mask);

    Blit *getBlitter() { return mBlit; }

    const D3DCAPS9 &getDeviceCaps() { return mDeviceCaps; }

  private:
    DISALLOW_COPY_AND_ASSIGN(Context);

    bool applyRenderTarget(bool ignoreViewport);
    void applyState(GLenum drawMode);
    GLenum applyVertexBuffer(GLint first, GLsizei count, GLsizei instances, GLsizei *repeatDraw);
    GLenum applyIndexBuffer(const GLvoid *indices, GLsizei count, GLenum mode, GLenum type, TranslatedIndexData *indexInfo);
    void applyShaders();
    void applyTextures();
    void applyTextures(SamplerType type);

    void detachBuffer(GLuint buffer);
    void detachTexture(GLuint texture);
    void detachFramebuffer(GLuint framebuffer);
    void detachRenderbuffer(GLuint renderbuffer);

    Texture *getIncompleteTexture(TextureType type);

    bool skipDraw(GLenum drawMode);
    bool isTriangleMode(GLenum drawMode);

    void initExtensionString();
    void initRendererString();

    const egl::Config *const mConfig;
    egl::Display *mDisplay;
    IDirect3DDevice9 *mDevice;
    renderer::Renderer *mRenderer;

    State mState;

    BindingPointer<Texture2D> mTexture2DZero;
    BindingPointer<TextureCubeMap> mTextureCubeMapZero;

#ifndef HASH_MAP
# ifdef _MSC_VER
#  define HASH_MAP stdext::hash_map
# else
#  define HASH_MAP std::unordered_map
# endif
#endif

    typedef HASH_MAP<GLuint, Framebuffer*> FramebufferMap;
    FramebufferMap mFramebufferMap;
    HandleAllocator mFramebufferHandleAllocator;

    typedef HASH_MAP<GLuint, Fence*> FenceMap;
    FenceMap mFenceMap;
    HandleAllocator mFenceHandleAllocator;

    typedef HASH_MAP<GLuint, Query*> QueryMap;
    QueryMap mQueryMap;
    HandleAllocator mQueryHandleAllocator;

    std::string mExtensionString;
    std::string mRendererString;

    VertexDataManager *mVertexDataManager;
    IndexDataManager *mIndexDataManager;

    Blit *mBlit;

    StreamingIndexBuffer *mLineLoopIB;
    
    BindingPointer<Texture> mIncompleteTextures[TEXTURE_TYPE_COUNT];

    // Recorded errors
    bool mInvalidEnum;
    bool mInvalidValue;
    bool mInvalidOperation;
    bool mOutOfMemory;
    bool mInvalidFramebufferOperation;

    // Current/lost context flags
    bool mHasBeenCurrent;
    bool mContextLost;
    GLenum mResetStatus;
    GLenum mResetStrategy;
    bool mRobustAccess;

    unsigned int mAppliedTextureSerialPS[MAX_TEXTURE_IMAGE_UNITS];
    unsigned int mAppliedTextureSerialVS[MAX_VERTEX_TEXTURE_IMAGE_UNITS_VTF];
    unsigned int mAppliedProgramBinarySerial;
    unsigned int mAppliedRenderTargetSerial;
    unsigned int mAppliedDepthbufferSerial;
    unsigned int mAppliedStencilbufferSerial;
    unsigned int mAppliedIBSerial;
    bool mDepthStencilInitialized;
    bool mViewportInitialized;
    D3DVIEWPORT9 mSetViewport;
    bool mRenderTargetDescInitialized;
    D3DSURFACE_DESC mRenderTargetDesc;
    bool mDxUniformsDirty;
    BindingPointer<ProgramBinary> mCurrentProgramBinary;
    Framebuffer *mBoundDrawFramebuffer;

    bool mSupportsShaderModel3;
    float mMaximumPointSize;
    bool mSupportsVertexTexture;
    bool mSupportsNonPower2Texture;
    bool mSupportsInstancing;
    int  mMaxRenderbufferDimension;
    int  mMaxTextureDimension;
    int  mMaxCubeTextureDimension;
    int  mMaxTextureLevel;
    float mMaxTextureAnisotropy;
    std::map<D3DFORMAT, bool *> mMultiSampleSupport;
    GLsizei mMaxSupportedSamples;
    bool mSupportsEventQueries;
    bool mSupportsOcclusionQueries;
    bool mSupportsDXT1Textures;
    bool mSupportsDXT3Textures;
    bool mSupportsDXT5Textures;
    bool mSupportsFloat32Textures;
    bool mSupportsFloat32LinearFilter;
    bool mSupportsFloat32RenderableTextures;
    bool mSupportsFloat16Textures;
    bool mSupportsFloat16LinearFilter;
    bool mSupportsFloat16RenderableTextures;
    bool mSupportsLuminanceTextures;
    bool mSupportsLuminanceAlphaTextures;
    bool mSupportsDepthTextures;
    bool mSupports32bitIndices;
    bool mSupportsTextureFilterAnisotropy;
    int mNumCompressedTextureFormats;

    // state caching flags
    bool mClearStateDirty;
    bool mCullStateDirty;
    bool mDepthStateDirty;
    bool mMaskStateDirty;
    bool mPixelPackingStateDirty;
    bool mBlendStateDirty;
    bool mStencilStateDirty;
    bool mPolygonOffsetStateDirty;
    bool mScissorStateDirty;
    bool mSampleStateDirty;
    bool mFrontFaceDirty;
    bool mDitherStateDirty;

    IDirect3DStateBlock9 *mMaskedClearSavedState;

    D3DCAPS9 mDeviceCaps;

    ResourceManager *mResourceManager;

    VertexDeclarationCache mVertexDeclarationCache;
};
}

extern "C"
{
// Exported functions for use by EGL
gl::Context *glCreateContext(const egl::Config *config, const gl::Context *shareContext, bool notifyResets, bool robustAccess);
void glDestroyContext(gl::Context *context);
void glMakeCurrent(gl::Context *context, egl::Display *display, egl::Surface *surface);
gl::Context *glGetCurrentContext();
renderer::Renderer *glCreateRenderer(HMODULE hModule, HDC hDc);
void glDestroyRenderer(renderer::Renderer *renderer);

__eglMustCastToProperFunctionPointerType __stdcall glGetProcAddress(const char *procname);
bool __stdcall glBindTexImage(egl::Surface *surface);
}

#endif   // INCLUDE_CONTEXT_H_
