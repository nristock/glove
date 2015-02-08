#pragma once

#include <glove/log/Log.h>
#include <glove/natex/ISubsystem.h>
#include <glove/rendering/Rendering.h>
#include <glove/rendering/RenderingInterfaces.h>
#include <modules/rendering/opengl/factories/GLRenderOperationFactory.h>

#include "subsystem/OpenGLRendererModule.h"

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