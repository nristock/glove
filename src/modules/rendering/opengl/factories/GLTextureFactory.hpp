#pragma once

#include <glove/rendering/factories/TextureFactory.hpp>

namespace glove {
namespace gl {
class GLTextureFactory : public TextureFactory {
  public:
    virtual TextureHandle CreateFromImage(const ImageHandle& image);
};
}
} /* namespace glove */