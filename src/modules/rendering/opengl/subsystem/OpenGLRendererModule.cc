
#include <glove/natex/ISystemExtension.h>

#include "subsystem/GLRendererExtension.h"
#include "internal/GlfwWrapper.h"

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