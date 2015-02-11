#include "target/GLDefaultRenderTarget.hpp"
#include "internal/OpenGLWrapper.hpp"

namespace glove {
namespace gl {
GLDefaultRenderTarget::GLDefaultRenderTarget(const ScreenDimensions& targetDimensions) : targetDimensions(targetDimensions) {

}

const ScreenDimensions& GLDefaultRenderTarget::GetDimensions() const {
    return targetDimensions;
}

void GLDefaultRenderTarget::Bind() {
    GL::BindFramebuffer(GL_FRAMEBUFFER, 0);
    GL::Viewport(0, 0, static_cast<GLsizei>(targetDimensions.GetWidth()), static_cast<GLsizei>(targetDimensions.GetHeight()));
}
}
}