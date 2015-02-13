#include "glove/rendering/texture/Texture.hpp"

namespace glove {

Texture::Texture(const ImageHandle& image) : image(image) {

}

ImageHandle Texture::GetImage() const {
    return image;
}
}