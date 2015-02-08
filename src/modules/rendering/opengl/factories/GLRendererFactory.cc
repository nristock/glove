#include <glove/GloveCore.h>

#include "factories/GLRendererFactory.h"
#include "subsystem/OpenGLRendererModule.h"
#include "GLRenderer.h"

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