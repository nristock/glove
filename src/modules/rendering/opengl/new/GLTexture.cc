#include "GLTexture.hpp"

GLenum ConvertPixelFormatToGLInternal(const BlueDwarf::PixelFormat& pixelFormat) {
    switch (pixelFormat) {
        case BlueDwarf::PixelFormat::A8R8G8B8:
        case BlueDwarf::PixelFormat::R8G8B8A8:
            return GL_RGBA;

        case BlueDwarf::PixelFormat::Depth24Stencil8:
        case BlueDwarf::PixelFormat::Depth32FStencil8:
            return GL_DEPTH24_STENCIL8;
    }
}

GLenum ConvertPixelFormatToGLFormat(const BlueDwarf::PixelFormat& pixelFormat) {
    switch (pixelFormat) {
        case BlueDwarf::PixelFormat::A8R8G8B8:
        case BlueDwarf::PixelFormat::R8G8B8A8:
            return GL_RGBA;

        case BlueDwarf::PixelFormat::Depth24Stencil8:
        case BlueDwarf::PixelFormat::Depth32FStencil8:
            return GL_DEPTH_STENCIL_EXT;
    }
}

GLenum ConvertPixelFormatToGLType(const BlueDwarf::PixelFormat& pixelFormat) {
    switch (pixelFormat) {
        case BlueDwarf::PixelFormat::A8R8G8B8:
        case BlueDwarf::PixelFormat::R8G8B8A8:
            return GL_UNSIGNED_INT_8_8_8_8;

        case BlueDwarf::PixelFormat::Depth24Stencil8:
        case BlueDwarf::PixelFormat::Depth32FStencil8:
            return GL_UNSIGNED_INT_24_8_EXT;
    }
}

namespace BlueDwarf {
namespace gl {
GLTexture2D::GLTexture2D(uint32 width, uint32 height, const PixelFormat& pixelFormat) : Texture2D(width, height, pixelFormat) {
    GL::BindTexture(GL_TEXTURE_2D, GetResource());
    GL::TexImage2D(GL_TEXTURE_2D, 0, ConvertPixelFormatToGLInternal(pixelFormat), width, height, 0, ConvertPixelFormatToGLFormat(pixelFormat), ConvertPixelFormatToGLType(pixelFormat), nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
}
}