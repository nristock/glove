#include <glove/GloveCore.hpp>
#include <glove/events/EventBus.hpp>
#include <glove/utils/DebugUtils.hpp>

#include "factories/GLRendererFactory.hpp"
#include "GLRenderer.hpp"

namespace glove {
namespace gl {

GLRendererFactory::GLRendererFactory() : eventBus(), nextContextId(0) {
}

IRendererPtr GLRendererFactory::CreateRenderer(const WindowConstructionHints& windowDescription) {
    DebugAssert((bool)eventBus);

    return GLRendererPtr(new GLRenderer(eventBus, windowDescription, nextContextId++),
                         [=](GLRenderer* ptr) { delete ptr; });
}

bool GLRendererFactory::Init(ServiceRegistry& serviceRegistry) {
    try {
        auto eventBusService = serviceRegistry.GetService(EventBus::serviceType);
        eventBus = std::dynamic_pointer_cast<EventBus>(eventBusService);
    } catch (const GloveException& ex) {
        return false;
    }

    return true;
}
}
}