#include <core/natex/ISystemExtension.h>

#include "GLRendererExtension.h"

extern "C" {

/// @ingroup OpenGLRenderer
glove::ISystemExtensionPtr LoadExtension() {
    return glove::ISystemExtensionPtr(new glove::gl::GLRendererExtension(),
                                      [=](glove::gl::GLRendererExtension* ptr) { delete ptr; });
}

/// @ingroup OpenGLRenderer
void UnloadExtension() {
}
}