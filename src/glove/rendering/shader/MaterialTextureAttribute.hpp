#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT MaterialTextureAttribute {
  public:
    virtual ~MaterialTextureAttribute() = default;

    virtual void Set(const TextureHandle& texture) = 0;
};

} /* namespace glove */