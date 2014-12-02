#include <core/natex/ISystemExtension.h>

#include "GLRendererExtension.h"

#include "../internal/GlfwWrapper.h"

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