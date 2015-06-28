#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/RenderHardwareResource.hpp"
#include "glove/CommonTypes.hpp"

namespace glove {
enum class PixelFormat {
    Unknown = 0,
    R8G8B8A8,
    A8R8G8B8,
    Depth24Stencil8,
    Depth32FStencil8
};

/**
* The Texture interface represents the common handle for textures. Do not create instances of this class directly, use
* the renderer implementation instead.
*
* Implementation details are up to the renderer implementation.
*/
class GLOVE_API_EXPORT Texture : public RenderHardwareResource {
  public:
    virtual ~Texture() = default;

    PixelFormat GetPixelFormat() const { return pixelFormat; }

  protected:
    Texture(PixelFormat pixelFormat) : pixelFormat(pixelFormat) {}

    const PixelFormat pixelFormat;
};

/**
* Texture2D is the base interface for all two dimensional textures. Since implementation details are up to the renderer
* implementation you should use the RenderResourceFactory to create instances of this class.
*/
class GLOVE_API_EXPORT Texture2D : public Texture {
  public:
    using Handle = std::shared_ptr<Texture2D>;
    virtual ~Texture2D() = default;

    uint32 GetWidth() const { return width; }
    uint32 GetHeight() const { return height; }

  protected:
    Texture2D(uint32 width, uint32 height, PixelFormat pixelFormat) : Texture(pixelFormat), width(width), height(height) {}

    const uint32 width;
    const uint32 height;
};

} /* namespace glove */