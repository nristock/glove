#pragma once

#include <glove/log/Log.hpp>
#include <glove/natex/ISubsystem.hpp>
#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/RenderingInterfaces.hpp>

#include "factories/GLRenderOperationFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLRendererSubsystem : public IRenderSubsystem, public ISubsystem {
  public:
    GLRendererSubsystem(const GloveCorePtr& engineCore);
    virtual ~GLRendererSubsystem() = default;

    virtual IGpuBufferFactoryPtr GetGpuBufferFactory(const IRendererPtr& owningRenderer);
    virtual IMeshFactoryPtr GetMeshFactory(const IRendererPtr& owningRenderer);
    virtual IRendererFactoryPtr GetRendererFactory();
    virtual IShaderFactoryPtr GetShaderFactory(const IRendererPtr& owningRenderer);
    virtual IShaderProgramFactoryPtr GetShaderProgramFactory();
    virtual IMaterialFactoryPtr GetMaterialFactory();
    virtual RenderOperationFactoryHandle GetRenderOperationFactory();

private:
    logging::GloveLogger logger;

    GloveCorePtr engineCore;
    IGpuBufferFactoryPtr gpuBufferFactory;
    IMeshFactoryPtr meshFactory;
    GLRendererFactoryPtr rendererFactory;
    IShaderFactoryPtr shaderFactory;
    GLMaterialFactoryPtr materialFactory;
    GLShaderProgramFactoryPtr shaderProgramFactory;
    GLRenderOperationFactoryHandle renderOperationFactory;
};
}
} /* namespace glove */