#include <glove/GloveCore.hpp>

#include "factories/GLRendererFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "GLRenderer.hpp"

namespace glove {
namespace gl {

GLRendererFactory::GLRendererFactory(const EventBusPtr& eventBus) : eventBus(eventBus), nextContextId(0) {
}

IRendererPtr GLRendererFactory::CreateRenderer(const WindowConstructionHints& windowDescription) {
    return GLRendererPtr(new GLRenderer(eventBus, windowDescription, nextContextId++),
                         [=](GLRenderer* ptr) { delete ptr; });
}
}
}