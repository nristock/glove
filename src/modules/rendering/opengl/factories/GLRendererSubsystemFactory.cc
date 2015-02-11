#include "factories/GLRendererSubsystemFactory.hpp"
#include "subsystem/GLRendererSubsystem.hpp"
#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

ISubsystemPtr GLRendererSubsystemFactory::CreateSubsystem(const GloveCorePtr& engineCore) {
    return GLRendererSubsystemPtr(new GLRendererSubsystem(engineCore), [](GLRendererSubsystem* ptr) { delete ptr; });
}
}
}