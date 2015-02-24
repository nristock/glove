#include "subsystem/GLRenderingModule.hpp"

#include "factories/GLGpuBufferFactory.hpp"
#include "factories/GLMaterialFactory.hpp"
#include "factories/GLMeshFactory.hpp"
#include "factories/GLRendererFactory.hpp"
#include "factories/GLRenderOperationFactory.hpp"
#include "factories/GLShaderFactory.hpp"
#include "factories/GLShaderProgramFactory.hpp"
#include "factories/GLTextureFactory.hpp"

namespace {
const auto moduleName = std::string("mod_glrenderer");

const auto moduleVersion = glove::ModuleVersionInfo(1, 0, 0);
}

namespace glove {
namespace gl {

void GLRenderingModule::Load() {

}

void GLRenderingModule::Unload() {

}

void GLRenderingModule::RegisterServices(ServiceRegistry& serviceRegistry) {
    auto gpuBufferFactory = std::make_shared<GLGpuBufferFactory>();
    serviceRegistry.RegisterService(gpuBufferFactory);

    auto materialFactory = std::make_shared<GLMaterialFactory>();
    serviceRegistry.RegisterService(materialFactory);

    auto meshFactory = std::make_shared<GLMeshFactory>();
    serviceRegistry.RegisterService(meshFactory);

    auto rendererFactory = std::make_shared<GLRendererFactory>(); //todo eventbus
    serviceRegistry.RegisterService(rendererFactory);

    auto renderOperationFactory = std::make_shared<GLRenderOperationFactory>();
    serviceRegistry.RegisterService(renderOperationFactory);

    auto shaderFactory = std::make_shared<GLShaderFactory>();
    serviceRegistry.RegisterService(shaderFactory);

    auto shaderProgramFactory = std::make_shared<GLShaderProgramFactory>();
    serviceRegistry.RegisterService(shaderProgramFactory);

    auto textureFactory = std::make_shared<GLTextureFactory>();
    serviceRegistry.RegisterService(textureFactory);
}

const std::string &GLRenderingModule::GetName() const {
    return ::moduleName;
}

const ModuleVersionInfo &GLRenderingModule::GetVersion() const {
    return ::moduleVersion;
}
}
}