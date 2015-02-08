#include "factories/GLRendererSubsystemFactory.h"
#include "subsystem/GLRendererSubsystem.h"
#include "subsystem/OpenGLRendererModule.h"

namespace glove {
namespace gl {

ISubsystemPtr GLRendererSubsystemFactory::CreateSubsystem(const GloveCorePtr& engineCore) {
    return GLRendererSubsystemPtr(new GLRendererSubsystem(engineCore), [](GLRendererSubsystem* ptr) { delete ptr; });
}
}
}