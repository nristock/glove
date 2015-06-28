#pragma once

#include <glove/rendering/Texture.hpp>
#include <glove/CommonTypes.hpp>

#include "../internal/OpenGLWrapper.hpp"

namespace BlueDwarf {
namespace gl {
struct GLTextureBase {
  public:
    GLTextureBase() { GL::GenTextures(1, &resource); }
    GLuint GetResource() const { return resource; }

  protected:
    GLuint resource;
};

class GLTexture2D : public Texture2D, public GLTextureBase {
  public:
    GLTexture2D(uint32 width, uint32 height, const PixelFormat& pixelFormat);
};
}
} /* namespace BlueDwarf */