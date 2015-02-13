#include <glove/resources/image/Image.hpp>

#include "texture/GLTexture.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "internal/OpenGLWrapper.hpp"

namespace {
inline GLenum TranslateImageFormateToGL(glove::Image::ImageFormat engineFormat) {
    switch (engineFormat) {
    case glove::Image::ImageFormat::RGB:
        return GL_RGB;
    case glove::Image::ImageFormat::RGBA:
        return GL_RGBA;
    }
}

inline GLenum TranslateImageBitDepthToGLType(unsigned char bitDepth) {
    if (bitDepth == 8) {
        return GL_UNSIGNED_BYTE;
    } else if (bitDepth == 16) {
        return GL_UNSIGNED_SHORT;
    } else {
        // todo: throw
    }
}
}

namespace glove {
namespace gl {
GLTexture::GLTexture(const ImageHandle& image) : Texture(image) {
    GL::GenTextures(1, &textureId);

    GL::BindTexture(GL_TEXTURE_2D, textureId);
    GL::TexImage2D(GL_TEXTURE_2D, 0, ::TranslateImageFormateToGL(image->GetImageFormat()), image->GetWidth(),
                   image->GetHeight(), 0, ::TranslateImageFormateToGL(image->GetImageFormat()),
                   ::TranslateImageBitDepthToGLType(image->GetBitDepth()), image->GetImageData().data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //todo
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void GLTexture::Bind() {
    GL::BindTexture(GL_TEXTURE_2D, textureId);
}
}
}