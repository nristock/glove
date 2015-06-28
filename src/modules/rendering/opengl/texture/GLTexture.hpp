#pragma once

#include <GL/glew.h>

#include <glove/rendering/texture/Texture.hpp>

namespace BlueDwarf {
namespace gl {

class GLTexture : public Texture {
  public:
    GLTexture(const ImageHandle& image);
    GLTexture(const GLTexture& other) = delete;

    virtual void Bind();

  private:
    GLuint textureId;
};
}
} /* namespace BlueDwarf */