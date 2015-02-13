#pragma once

#include "glove/resources/Resources.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

class TextureFactory {
public:
    virtual ~TextureFactory() = default;

    virtual TextureHandle CreateFromImage(const ImageHandle& image) = 0;
};

}