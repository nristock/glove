#pragma once

#include "glove/resources/Resources.hpp"
#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT Texture {
  public:
    ImageHandle GetImage() const;

    virtual void Bind() = 0;

  protected:
    Texture(const ImageHandle& image);
    virtual ~Texture() = default;

    ImageHandle image;
};

} /* namespace glove */