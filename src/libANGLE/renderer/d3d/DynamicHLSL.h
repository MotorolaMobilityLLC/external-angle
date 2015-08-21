//
// Copyright (c) 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DynamicHLSL.h: Interface for link and run-time HLSL generation
//

#ifndef LIBANGLE_RENDERER_D3D_DYNAMICHLSL_H_
#define LIBANGLE_RENDERER_D3D_DYNAMICHLSL_H_

#include <map>
#include <vector>

#include "angle_gl.h"
#include "common/angleutils.h"
#include "libANGLE/Constants.h"
#include "libANGLE/Program.h"
#include "libANGLE/formatutils.h"

namespace sh
{
struct Attribute;
struct ShaderVariable;
}

namespace gl
{
class InfoLog;
struct VariableLocation;
struct LinkedVarying;
struct VertexAttribute;
struct PackedVarying;
struct Data;
}

namespace rx
{
class RendererD3D;
class ShaderD3D;

typedef const gl::PackedVarying *VaryingPacking[gl::IMPLEMENTATION_MAX_VARYING_VECTORS][4];

struct PixelShaderOutputVariable
{
    GLenum type;
    std::string name;
    std::string source;
    size_t outputIndex;
};

class DynamicHLSL : angle::NonCopyable
{
  public:
    explicit DynamicHLSL(RendererD3D *const renderer);

    int packVaryings(gl::InfoLog &infoLog, VaryingPacking packing, ShaderD3D *fragmentShader,
                     ShaderD3D *vertexShader, const std::vector<std::string>& transformFeedbackVaryings);
    std::string generateVertexShaderForInputLayout(const std::string &sourceShader,
                                                   const gl::InputLayout &inputLayout,
                                                   const std::vector<sh::Attribute> &shaderAttributes) const;
    std::string generatePixelShaderForOutputSignature(const std::string &sourceShader, const std::vector<PixelShaderOutputVariable> &outputVariables,
                                                      bool usesFragDepth, const std::vector<GLenum> &outputLayout) const;
    bool generateShaderLinkHLSL(const gl::Data &data,
                                const gl::Program::Data &programData,
                                gl::InfoLog &infoLog,
                                int registers,
                                const VaryingPacking packing,
                                std::string &pixelHLSL,
                                std::string &vertexHLSL,
                                std::vector<gl::LinkedVarying> *linkedVaryings,
                                std::vector<PixelShaderOutputVariable> *outPixelShaderKey,
                                bool *outUsesFragDepth) const;

    std::string generateGeometryShaderHLSL(int registers,
                                           const ShaderD3D *fragmentShader,
                                           const ShaderD3D *vertexShader) const;

  private:
    RendererD3D *const mRenderer;

    struct SemanticInfo;

    std::string getVaryingSemantic(bool pointSize) const;
    SemanticInfo getSemanticInfo(int startRegisters, bool position, bool fragCoord, bool pointCoord,
                                 bool pointSize, bool pixelShader) const;
    std::string generateVaryingLinkHLSL(const SemanticInfo &info, const std::string &varyingHLSL) const;
    std::string generateVaryingHLSL(const ShaderD3D *shader) const;
    void storeUserLinkedVaryings(const ShaderD3D *vertexShader, std::vector<gl::LinkedVarying> *linkedVaryings) const;
    void storeBuiltinLinkedVaryings(const SemanticInfo &info, std::vector<gl::LinkedVarying> *linkedVaryings) const;
    std::string generatePointSpriteHLSL(int registers,
                                        const ShaderD3D *fragmentShader,
                                        const ShaderD3D *vertexShader) const;

    // Prepend an underscore
    static std::string decorateVariable(const std::string &name);

    std::string generateAttributeConversionHLSL(gl::VertexFormatType vertexFormatType,
                                                const sh::ShaderVariable &shaderAttrib) const;
};

}

#endif // LIBANGLE_RENDERER_D3D_DYNAMICHLSL_H_
