#include "internal/GlfwWrapper.hpp"
#include "subsystem/GLRenderingModule.hpp"

#include "factories/GLWindowFactory.hpp"
#include "subsystem/GLRendererService.hpp"

namespace {
const auto moduleName = std::string("mod_glrenderer");

const auto moduleVersion = BlueDwarf::ModuleVersionInfo(1, 0, 0);
}

namespace BlueDwarf {
namespace gl {

void GLRenderingModule::Load() {
    GlfwWrapper::InitWrapper();
}

void GLRenderingModule::Unload() {

}

void GLRenderingModule::RegisterServices(ServiceRegistry& serviceRegistry) {
    auto rendererService = std::make_shared<GLRendererService>();
    serviceRegistry.RegisterService(rendererService);

    auto windowFactory = std::make_shared<GLWindowFactory>();
    serviceRegistry.RegisterService(windowFactory);
}

const std::string &GLRenderingModule::GetName() const {
    return ::moduleName;
}

const ModuleVersionInfo &GLRenderingModule::GetVersion() const {
    return ::moduleVersion;
}
}
}