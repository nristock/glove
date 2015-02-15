#include <glove/natex/ISubsystemInstanceRegistry.hpp>
#include "factories/GLRendererSubsystemFactory.hpp"
#include "subsystem/GLRendererSubsystem.hpp"
#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {
ISubsystemPtr GLRendererSubsystemFactory::CreateSubsystem(const ISubsystemInstanceRegistryPtr& subsystemInstanceRegistry, const EventBusPtr& eventBus) {
    return GLRendererSubsystemPtr(new GLRendererSubsystem(eventBus), [](GLRendererSubsystem* ptr) { delete ptr; });
}
}
}