#include "factories/GLTextureFactory.hpp"
#include "texture/GLTexture.hpp"

namespace glove {
namespace gl {
TextureHandle GLTextureFactory::CreateFromImage(const ImageHandle& image) {
    return TextureHandle(new GLTexture(image));
}
}
}