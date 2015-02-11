#include <boost/format.hpp>

#include <glove/GloveCore.hpp>

#include "subsystem/GLRendererSubsystem.hpp"
#include "internal/GlfwWrapper.hpp"
#include "factories/GLGpuBufferFactory.hpp"
#include "factories/GLMeshFactory.hpp"
#include "factories/GLRendererFactory.hpp"
#include "factories/GLShaderFactory.hpp"
#include "factories/GLShaderProgramFactory.hpp"
#include "factories/GLMaterialFactory.hpp"

namespace glove {
namespace gl {

GLRendererSubsystem::GLRendererSubsystem(const GloveCorePtr& engineCore) {
    gpuBufferFactory = GLGpuBufferFactoryPtr(new GLGpuBufferFactory());
    meshFactory = GLMeshFactoryPtr(new GLMeshFactory());
    rendererFactory = GLRendererFactoryPtr(new GLRendererFactory(engineCore->GetEventBus()));
    shaderFactory = GLShaderFactoryPtr(new GLShaderFactory());
    shaderProgramFactory = GLShaderProgramFactoryPtr(new GLShaderProgramFactory());
    materialFactory = GLMaterialFactoryPtr(new GLMaterialFactory());
    renderOperationFactory = GLRenderOperationFactoryHandle(new GLRenderOperationFactory());

    LOG(logger, info,
        (boost::format("Create OpenGL rendering subsystem (GLFW: %1%)") % GlfwWrapper::GetGlfwVersion()).str());
}

IGpuBufferFactoryPtr GLRendererSubsystem::GetGpuBufferFactory(const IRendererPtr& owningRenderer) {
    return gpuBufferFactory;
}

IMeshFactoryPtr GLRendererSubsystem::GetMeshFactory(const IRendererPtr& owningRenderer) {
    return meshFactory;
}

IRendererFactoryPtr GLRendererSubsystem::GetRendererFactory() {
    return rendererFactory;
}

IShaderFactoryPtr GLRendererSubsystem::GetShaderFactory(const IRendererPtr& owningRenderer) {
    return shaderFactory;
}

IShaderProgramFactoryPtr GLRendererSubsystem::GetShaderProgramFactory() {
    return shaderProgramFactory;
}

IMaterialFactoryPtr GLRendererSubsystem::GetMaterialFactory() {
    return materialFactory;
}

RenderOperationFactoryHandle GLRendererSubsystem::GetRenderOperationFactory() {
    return renderOperationFactory;
}
}
}