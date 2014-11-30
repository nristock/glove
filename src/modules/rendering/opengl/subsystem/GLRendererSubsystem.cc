#include "GLRendererSubsystem.h"

#include <boost/format.hpp>

#include <core/GloveCore.h>

#include "../internal/GlfwWrapper.h"

#include "../factories/GLGpuBufferFactory.h"
#include "../factories/GLMeshFactory.h"
#include "../factories/GLRendererFactory.h"
#include "../factories/GLShaderFactory.h"
#include "../factories/GLShaderProgramFactory.h"
#include "../factories/GLMaterialFactory.h"

namespace glove {
namespace gl {

GLRendererSubsystem::GLRendererSubsystem(const GloveCorePtr& engineCore) {
    gpuBufferFactory = GLGpuBufferFactoryPtr(new GLGpuBufferFactory());
    meshFactory = GLMeshFactoryPtr(new GLMeshFactory());
    rendererFactory = GLRendererFactoryPtr(new GLRendererFactory(engineCore->GetEventBus()));
    shaderFactory = GLShaderFactoryPtr(new GLShaderFactory());
    shaderProgramFactory = GLShaderProgramFactoryPtr(new GLShaderProgramFactory());
    materialFactory = GLMaterialFactoryPtr(new GLMaterialFactory());

    LOG(logger, info, (boost::format("Create OpenGL rendering subsystem (GLFW: %1%)") % GlfwWrapper::GetGlfwVersion()).str());
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

}
}