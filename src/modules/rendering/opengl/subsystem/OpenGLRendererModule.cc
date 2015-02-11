#include <glove/natex/ISystemExtension.hpp>

#include "subsystem/GLRendererExtension.hpp"
#include "internal/GlfwWrapper.hpp"

extern "C" {

/// @ingroup OpenGLRenderer
glove::ISystemExtensionPtr LoadExtension() {
    glove::gl::GlfwWrapper::InitWrapper();

    return glove::ISystemExtensionPtr(new glove::gl::GLRendererExtension(),
                                      [=](glove::gl::GLRendererExtension* ptr) { delete ptr; });
}

/// @ingroup OpenGLRenderer
void UnloadExtension() {
}
}