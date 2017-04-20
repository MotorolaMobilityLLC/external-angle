//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Image.h: Defines the egl::Image class representing the EGLimage object.

#ifndef LIBANGLE_IMAGE_H_
#define LIBANGLE_IMAGE_H_

#include "common/angleutils.h"
#include "libANGLE/AttributeMap.h"
#include "libANGLE/Error.h"
#include "libANGLE/FramebufferAttachment.h"
#include "libANGLE/RefCountObject.h"
#include "libANGLE/formatutils.h"

#include <set>

namespace rx
{
class EGLImplFactory;
class ImageImpl;
}

namespace egl
{
class Image;

// Only currently Renderbuffers and Textures can be bound with images. This makes the relationship
// explicit, and also ensures that an image sibling can determine if it's been initialized or not,
// which is important for the robust resource init extension with Textures and EGLImages.
class ImageSibling : public RefCountObject, public gl::FramebufferAttachmentObject
{
  public:
    ImageSibling(GLuint id);
    virtual ~ImageSibling();

  protected:
    // Set the image target of this sibling
    void setTargetImage(egl::Image *imageTarget);

    // Orphan all EGL image sources and targets
    gl::Error orphanImages();

  private:
    friend class Image;

    // Called from Image only to add a new source image
    void addImageSource(egl::Image *imageSource);

    // Called from Image only to remove a source image when the Image is being deleted
    void removeImageSource(egl::Image *imageSource);

    std::set<Image *> mSourcesOf;
    BindingPointer<Image> mTargetOf;
};

struct ImageState : angle::NonCopyable
{
    ImageState(EGLenum target, ImageSibling *buffer, const AttributeMap &attribs);

    gl::ImageIndex imageIndex;
    BindingPointer<ImageSibling> source;
    std::set<ImageSibling *> targets;
};

class Image final : public RefCountObject
{
  public:
    Image(rx::EGLImplFactory *factory,
          EGLenum target,
          ImageSibling *buffer,
          const AttributeMap &attribs);
    ~Image();

    const gl::Format &getFormat() const;
    size_t getWidth() const;
    size_t getHeight() const;
    size_t getSamples() const;

    Error initialize();

    rx::ImageImpl *getImplementation() const;

  private:
    friend class ImageSibling;

    // Called from ImageSibling only notify the image that a new target sibling exists for state
    // tracking.
    void addTargetSibling(ImageSibling *sibling);

    // Called from ImageSibling only to notify the image that a sibling (source or target) has
    // been respecified and state tracking should be updated.
    gl::Error orphanSibling(ImageSibling *sibling);

    ImageState mState;
    rx::ImageImpl *mImplementation;
};
}  // namespace egl

#endif  // LIBANGLE_IMAGE_H_
