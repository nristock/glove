#include "GLRenderTarget.h"

#include "../internal/OpenGLWrapper.h"

namespace glove {
namespace gl {

GLRenderTarget::GLRenderTarget(const ScreenDimensions& targetDimensions) : targetDimensions(targetDimensions) {
    GL::GenFramebuffers(1, &framebufferId);

    GL::GenTextures(1, &targetTexture);
    GL::BindTexture(GL_TEXTURE_2D, targetTexture);

    GL::TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(targetDimensions.GetWidth()),
                   static_cast<GLsizei>(targetDimensions.GetHeight()), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    GL::BindFramebuffer(GL_FRAMEBUFFER, framebufferId);
    GL::FramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, targetTexture, 0);

    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    GL::DrawBuffers(1, drawBuffers);
}

const ScreenDimensions& GLRenderTarget::GetDimensions() const {
    return targetDimensions;
}

void GLRenderTarget::Bind() {
    GL::BindFramebuffer(GL_FRAMEBUFFER, framebufferId);
    GL::Viewport(0, 0, static_cast<GLsizei>(targetDimensions.GetWidth()),
                 static_cast<GLsizei>(targetDimensions.GetHeight()));
}
}
}