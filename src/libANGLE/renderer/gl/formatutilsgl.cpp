//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// formatutilsgl.cpp: Queries for GL image formats and their translations to native
// GL formats.

#include "libANGLE/renderer/gl/formatutilsgl.h"

#include <map>

#include "common/string_utils.h"

namespace rx
{

namespace nativegl
{

SupportRequirement::SupportRequirement()
    : majorVersion(std::numeric_limits<GLuint>::max()),
      minorVersion(std::numeric_limits<GLuint>::max()),
      versionExtensions(),
      requiredExtensions()
{
}

InternalFormat::InternalFormat()
    : texture(),
      filter(),
      renderbuffer(),
      framebufferAttachment()
{
}

static inline SupportRequirement VersionOrExts(GLuint major, GLuint minor, const std::string &versionExt)
{
    SupportRequirement requirement;
    requirement.majorVersion = major;
    requirement.minorVersion = minor;
    angle::SplitStringAlongWhitespace(versionExt, &requirement.versionExtensions);
    return requirement;
}

static inline SupportRequirement VersionAndExts(GLuint major, GLuint minor, const std::string &requiredExt)
{
    SupportRequirement requirement;
    requirement.majorVersion = major;
    requirement.minorVersion = minor;
    angle::SplitStringAlongWhitespace(requiredExt, &requirement.requiredExtensions);
    return requirement;
}

static inline SupportRequirement VersionOrExtsAndExts(GLuint major, GLuint minor, const std::string &versionExt,
                                                      const std::string &requiredExt)
{    SupportRequirement requirement;
    requirement.majorVersion = major;
    requirement.minorVersion = minor;
    angle::SplitStringAlongWhitespace(versionExt, &requirement.versionExtensions);
    angle::SplitStringAlongWhitespace(requiredExt, &requirement.requiredExtensions);
    return requirement;
}

static inline SupportRequirement VersionOnly(GLuint major, GLuint minor)
{
    SupportRequirement requirement;
    requirement.majorVersion = major;
    requirement.minorVersion = minor;
    return requirement;
}

static inline SupportRequirement ExtsOnly(const std::string &ext)
{
    SupportRequirement requirement;
    angle::SplitStringAlongWhitespace(ext, &requirement.requiredExtensions);
    return requirement;
}

static inline SupportRequirement Always()
{
    SupportRequirement requirement;
    requirement.majorVersion = 0;
    requirement.minorVersion = 0;
    return requirement;
}

static inline SupportRequirement Never()
{
    SupportRequirement requirement;
    requirement.majorVersion = std::numeric_limits<GLuint>::max();
    requirement.minorVersion = std::numeric_limits<GLuint>::max();
    return requirement;
}

struct InternalFormatInfo
{
    InternalFormat glesInfo;
    InternalFormat glInfo;
};

typedef std::pair<GLenum, InternalFormatInfo> InternalFormatInfoPair;
typedef std::map<GLenum, InternalFormatInfo> InternalFormatInfoMap;

// A helper function to insert data into the format map with fewer characters.
static inline void InsertFormatMapping(InternalFormatInfoMap *map, GLenum internalFormat,
                                       const SupportRequirement &desktopTexture, const SupportRequirement &desktopFilter, const SupportRequirement &desktopRender,
                                       const SupportRequirement &esTexture, const SupportRequirement &esFilter, const SupportRequirement &esRender)
{
    InternalFormatInfo formatInfo;
    formatInfo.glInfo.texture = desktopTexture;
    formatInfo.glInfo.filter = desktopFilter;
    formatInfo.glInfo.renderbuffer = desktopRender;
    formatInfo.glInfo.framebufferAttachment = desktopRender;
    formatInfo.glesInfo.texture = esTexture;
    formatInfo.glesInfo.filter = esTexture;
    formatInfo.glesInfo.renderbuffer = esFilter;
    formatInfo.glesInfo.framebufferAttachment = esRender;
    map->insert(std::make_pair(internalFormat, formatInfo));
}

static InternalFormatInfoMap BuildInternalFormatInfoMap()
{
    InternalFormatInfoMap map;

    //                       | Format              | OpenGL texture support                          | Filter  | OpenGL render support                        | OpenGL ES texture support                 | Filter  | OpenGL ES render support                 |
    InsertFormatMapping(&map, GL_R8,                VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Always(), VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOrExts(3, 0, "GL_EXT_texture_rg"),   Always(), VersionOrExts(3, 0, "GL_EXT_texture_rg")  );
    InsertFormatMapping(&map, GL_R8_SNORM,          VersionOnly(3, 1),                                Always(), Never(),                                       VersionOnly(3, 0),                          Always(), Never()                                   );
    InsertFormatMapping(&map, GL_RG8,               VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Always(), VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOrExts(3, 0, "GL_EXT_texture_rg"),   Always(), VersionOrExts(3, 0, "GL_ARB_texture_rg")  );
    InsertFormatMapping(&map, GL_RG8_SNORM,         VersionOnly(3, 1),                                Always(), Never(),                                       VersionOnly(3, 0),                          Always(), Never()                                   );
    InsertFormatMapping(&map, GL_RGB8,              Always(),                                         Always(), Always(),                                      VersionOrExts(3, 0, "GL_OES_rgb8_rgba8"),   Always(), Always()                                  );
    InsertFormatMapping(&map, GL_RG8_SNORM,         VersionOnly(3, 1),                                Always(), Never(),                                       VersionOnly(3, 0),                          Always(), Never()                                   );
    InsertFormatMapping(&map, GL_RGB565,            Always(),                                         Always(), Always(),                                      Always(),                                   Always(), Always()                                  );
    InsertFormatMapping(&map, GL_RGBA4,             Always(),                                         Always(), Always(),                                      Always(),                                   Always(), Always()                                  );
    InsertFormatMapping(&map, GL_RGB5_A1,           Always(),                                         Always(), Always(),                                      Always(),                                   Always(), Always()                                  );
    InsertFormatMapping(&map, GL_RGBA8,             Always(),                                         Always(), Always(),                                      VersionOrExts(3, 0, "GL_OES_rgb8_rgba8"),   Always(), VersionOrExts(3, 0, "GL_OES_rgb8_rgba8")  );
    InsertFormatMapping(&map, GL_RGBA8_SNORM,       VersionOnly(3, 1),                                Always(), Never(),                                       VersionOnly(3, 0),                          Always(), Never()                                   );
    InsertFormatMapping(&map, GL_RGB10_A2,          Always(),                                         Always(), Always(),                                      VersionOnly(3, 0),                          Always(), VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGB10_A2UI,        VersionOrExts(3, 3, "GL_ARB_texture_rgb10_a2ui"), Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_SRGB8,             VersionOrExts(2, 1, "GL_EXT_texture_sRGB"),       Always(), VersionOrExts(2, 1, "GL_EXT_texture_sRGB"),    VersionOrExts(3, 0, "GL_EXT_texture_sRGB"), Always(), VersionOrExts(3, 0, "GL_EXT_texture_sRGB"));
    InsertFormatMapping(&map, GL_SRGB8_ALPHA8,      VersionOrExts(2, 1, "GL_EXT_texture_sRGB"),       Always(), VersionOrExts(2, 1, "GL_EXT_texture_sRGB"),    VersionOrExts(3, 0, "GL_EXT_texture_sRGB"), Always(), VersionOrExts(3, 0, "GL_EXT_texture_sRGB"));
    InsertFormatMapping(&map, GL_R8I,               VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_R8UI,              VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_R16I,              VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_R16UI,             VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_R32I,              VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_R32UI,             VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG8I,              VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG8UI,             VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG16I,             VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG16UI,            VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG32I,             VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RG32UI,            VersionOrExts(3, 0, "GL_ARB_texture_rg"),         Never(),  VersionOrExts(3, 0, "GL_ARB_texture_rg"),      VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGB8I,             VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGB8UI,            VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGB16I,            VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGB16UI,           VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGB32I,            VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGB32UI,           VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  Never(),                                       VersionOnly(3, 0),                          Never(),  Never()                                   );
    InsertFormatMapping(&map, GL_RGBA8I,            VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGBA8UI,           VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGBA16I,           VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGBA16UI,          VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGBA32I,           VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );
    InsertFormatMapping(&map, GL_RGBA32UI,          VersionOrExts(3, 0, "GL_EXT_texture_integer"),    Never(),  VersionOrExts(3, 0, "GL_EXT_texture_integer"), VersionOnly(3, 0),                          Never(),  VersionOnly(3, 0)                         );

    // From GL_EXT_texture_compression_dxt1
    InsertFormatMapping(&map, GL_BGRA8_EXT,         Never(),                                          Never(),  Never(),                                       ExtsOnly("GL_EXT_texture_format_BGRA8888"), Always(), ExtsOnly("GL_EXT_texture_format_BGRA8888"));

    // Floating point formats
    //                       | Format              | OpenGL texture support                                       | Filter  | OpenGL render support                                                                            | OpenGL ES texture support                                         | Filter                                                 | OpenGL ES render support                                         |
    InsertFormatMapping(&map, GL_R11F_G11F_B10F,    VersionOrExts(3, 0, "GL_EXT_packed_float"),                    Always(), VersionOrExtsAndExts(3, 0, "GL_EXT_packed_float", "GL_ARB_color_buffer_float"),                    VersionOnly(3, 0),                                                  Always(),                                                VersionAndExts(3, 0, "GL_EXT_color_buffer_float")                 );
    InsertFormatMapping(&map, GL_RGB9_E5,           VersionOrExts(3, 0, "GL_EXT_texture_shared_exponent"),         Always(), VersionOrExtsAndExts(3, 0, "GL_EXT_texture_shared_exponent", "GL_ARB_color_buffer_float"),         VersionOnly(3, 0),                                                  Always(),                                                VersionAndExts(3, 0, "GL_EXT_color_buffer_float")                 );
    InsertFormatMapping(&map, GL_R16F,              VersionOrExts(3, 0, "GL_ARB_texture_rg ARB_texture_float"),    Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float", "GL_ARB_color_buffer_float"), VersionOrExts(3, 0, "GL_OES_texture_half_float GL_EXT_texture_rg"), VersionOrExts(3, 0, "GL_OES_texture_half_float_linear"), VersionOrExts(3, 0, "GL_OES_texture_half_float GL_EXT_texture_rg"));
    InsertFormatMapping(&map, GL_RG16F,             VersionOrExts(3, 0, "GL_ARB_texture_rg ARB_texture_float"),    Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float", "GL_ARB_color_buffer_float"), VersionOrExts(3, 0, "GL_OES_texture_half_float GL_EXT_texture_rg"), VersionOrExts(3, 0, "GL_OES_texture_half_float_linear"), VersionOrExts(3, 0, "GL_OES_texture_half_float GL_EXT_texture_rg"));
    InsertFormatMapping(&map, GL_RGB16F,            VersionOrExts(3, 0, "GL_ARB_texture_float"),                   Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_float", "GL_ARB_color_buffer_float"),                   VersionOrExts(3, 0, "GL_OES_texture_half_float"),                   VersionOrExts(3, 0, "GL_OES_texture_half_float_linear"), VersionOrExts(3, 0, "GL_OES_texture_half_float")                  );
    InsertFormatMapping(&map, GL_RGBA16F,           VersionOrExts(3, 0, "GL_ARB_texture_float"),                   Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_float", "GL_ARB_color_buffer_float"),                   VersionOrExts(3, 0, "GL_OES_texture_half_float"),                   VersionOrExts(3, 0, "GL_OES_texture_half_float_linear"), VersionOrExts(3, 0, "GL_OES_texture_half_float")                  );
    InsertFormatMapping(&map, GL_R32F,              VersionOrExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float"), Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float", "GL_ARB_color_buffer_float"), VersionOrExts(3, 0, "GL_OES_texture_float GL_EXT_texture_rg"),      VersionOrExts(3, 0, "GL_OES_texture_float_linear"),      VersionOrExts(3, 0, "GL_OES_texture_float GL_EXT_texture_rg")     );
    InsertFormatMapping(&map, GL_RG32F,             VersionOrExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float"), Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_rg GL_ARB_texture_float", "GL_ARB_color_buffer_float"), VersionOrExts(3, 0, "GL_OES_texture_float GL_EXT_texture_rg"),      VersionOrExts(3, 0, "GL_OES_texture_float_linear"),      VersionOrExts(3, 0, "GL_OES_texture_float GL_EXT_texture_rg")     );
    InsertFormatMapping(&map, GL_RGB32F,            VersionOrExts(3, 0, "GL_ARB_texture_float"),                   Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_float", "GL_ARB_color_buffer_float"),                   VersionOrExts(3, 0, "GL_OES_texture_float"),                        VersionOrExts(3, 0, "GL_OES_texture_float_linear"),      VersionOrExts(3, 0, "GL_OES_texture_float")                       );
    InsertFormatMapping(&map, GL_RGBA32F,           VersionOrExts(3, 0, "GL_ARB_texture_float"),                   Always(), VersionOrExtsAndExts(3, 0, "GL_ARB_texture_float", "GL_ARB_color_buffer_float"),                   VersionOrExts(3, 0, "GL_OES_texture_float"),                        VersionOrExts(3, 0, "GL_OES_texture_float_linear"),      VersionOrExts(3, 0, "GL_OES_texture_float")                       );

    // Depth stencil formats
    //                       | Format                  | OpenGL texture support                          | Filter                                     | OpenGL render support                           | OpenGL ES texture support                  | Filter                                     | OpenGL ES render support                                              |
    InsertFormatMapping(&map, GL_DEPTH_COMPONENT16,     VersionOnly(1, 5),                                VersionOrExts(1, 5, "GL_ARB_depth_texture"), VersionOnly(1, 5),                                VersionOnly(2, 0),                           VersionOrExts(3, 0, "GL_OES_depth_texture"), VersionOnly(2, 0)                                                      );
    InsertFormatMapping(&map, GL_DEPTH_COMPONENT24,     VersionOnly(1, 5),                                VersionOrExts(1, 5, "GL_ARB_depth_texture"), VersionOnly(1, 5),                                VersionOnly(2, 0),                           VersionOrExts(3, 0, "GL_OES_depth_texture"), VersionOnly(2, 0)                                                      );
    InsertFormatMapping(&map, GL_DEPTH_COMPONENT32_OES, VersionOnly(1, 5),                                VersionOrExts(1, 5, "GL_ARB_depth_texture"), VersionOnly(1, 5),                                ExtsOnly("GL_OES_depth_texture"),            Always(),                                    ExtsOnly("GL_OES_depth_texture")                                       );
    InsertFormatMapping(&map, GL_DEPTH_COMPONENT32F,    VersionOrExts(3, 0, "GL_ARB_depth_buffer_float"), Always(),                                    VersionOrExts(3, 0, "GL_ARB_depth_buffer_float"), VersionOnly(3, 0),                           VersionOrExts(3, 0, "GL_OES_depth_texture"), VersionOnly(3, 0)                                                      );
    InsertFormatMapping(&map, GL_DEPTH24_STENCIL8,      VersionOrExts(3, 0, "GL_ARB_framebuffer_object"), VersionOrExts(3, 0, "GL_ARB_depth_texture"), VersionOrExts(3, 0, "GL_ARB_framebuffer_object"), VersionOrExts(3, 0, "GL_OES_depth_texture"), Always(),                                    VersionOrExts(3, 0, "GL_OES_depth_texture GL_OES_packed_depth_stencil"));
    InsertFormatMapping(&map, GL_DEPTH32F_STENCIL8,     VersionOrExts(3, 0, "GL_ARB_depth_buffer_float"), Always(),                                    VersionOrExts(3, 0, "GL_ARB_depth_buffer_float"), VersionOnly(3, 0),                           Always(),                                    VersionOnly(3, 0)                                                      );

    // Luminance alpha formats (TODO)
    InsertFormatMapping(&map, GL_ALPHA8_EXT,             Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE8_EXT,         Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_ALPHA32F_EXT,           Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE32F_EXT,       Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_ALPHA16F_EXT,           Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE16F_EXT,       Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE8_ALPHA8_EXT,  Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE_ALPHA32F_EXT, Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_LUMINANCE_ALPHA16F_EXT, Never(), Never(), Never(), Never(), Never(), Never());

    // Compressed formats, From ES 3.0.1 spec, table 3.16
    InsertFormatMapping(&map, GL_COMPRESSED_R11_EAC,                        Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_SIGNED_R11_EAC,                 Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_RG11_EAC,                       Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_SIGNED_RG11_EAC,                Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_RGB8_ETC2,                      Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_SRGB8_ETC2,                     Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,  Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_RGBA8_ETC2_EAC,                 Never(), Never(), Never(), Never(), Never(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,          Never(), Never(), Never(), Never(), Never(), Never());

    // From GL_EXT_texture_compression_dxt1
    //                       | Format                            | OpenGL texture support                     | Filter  | Render | OpenGL ES texture support                    | Filter  | Render |
    InsertFormatMapping(&map, GL_COMPRESSED_RGB_S3TC_DXT1_EXT,    ExtsOnly("GL_EXT_texture_compression_s3tc"), Always(), Never(), ExtsOnly("GL_EXT_texture_compression_dxt1"),   Always(), Never());
    InsertFormatMapping(&map, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,   ExtsOnly("GL_EXT_texture_compression_s3tc"), Always(), Never(), ExtsOnly("GL_EXT_texture_compression_dxt1"),   Always(), Never());

    // From GL_ANGLE_texture_compression_dxt3
    InsertFormatMapping(&map, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, ExtsOnly("GL_EXT_texture_compression_s3tc"), Always(), Never(), ExtsOnly("GL_ANGLE_texture_compression_dxt3"), Always(), Never());

    // From GL_ANGLE_texture_compression_dxt5
    InsertFormatMapping(&map, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, ExtsOnly("GL_EXT_texture_compression_s3tc"), Always(), Never(), ExtsOnly("GL_ANGLE_texture_compression_dxt5"), Always(), Never());

    return map;
}

static const InternalFormatInfoMap &GetInternalFormatMap()
{
    static const InternalFormatInfoMap formatMap = BuildInternalFormatInfoMap();
    return formatMap;
}

const InternalFormat &GetInternalFormatInfo(GLenum internalFormat, bool es)
{
    const InternalFormatInfoMap &formatMap = GetInternalFormatMap();
    InternalFormatInfoMap::const_iterator iter = formatMap.find(internalFormat);
    if (iter != formatMap.end())
    {
        const InternalFormatInfo &info = iter->second;
        return es ? info.glesInfo : info.glInfo;
    }
    else
    {
        static const InternalFormat defaultInternalFormat;
        return defaultInternalFormat;
    }
}

}

}
