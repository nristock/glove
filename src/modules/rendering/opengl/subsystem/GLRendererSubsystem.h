#pragma once

#include <core/log/Log.h>
#include <core/natex/ISubsystem.h>
#include <core/rendering/Rendering.h>
#include <core/rendering/RenderingInterfaces.h>

#include "OpenGLRendererModule.h"

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

  private:
    logging::GloveLogger logger;

    GloveCorePtr engineCore;
    IGpuBufferFactoryPtr gpuBufferFactory;
    IMeshFactoryPtr meshFactory;
    GLRendererFactoryPtr rendererFactory;
    IShaderFactoryPtr shaderFactory;
    GLMaterialFactoryPtr materialFactory;
    GLShaderProgramFactoryPtr shaderProgramFactory;
};
}
} /* namespace glove */