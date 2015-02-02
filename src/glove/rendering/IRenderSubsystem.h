#pragma once

#include "glove/natex/Natex.h"
#include "glove/rendering/Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderSubsystem {
  public:
    /// @brief Subsystem type for rendering systems.
    static const SubsystemType subsystemType;

    virtual ~IRenderSubsystem() = default;

    virtual IGpuBufferFactoryPtr GetGpuBufferFactory(const IRendererPtr& owningRenderer) = 0;
    virtual IMeshFactoryPtr GetMeshFactory(const IRendererPtr& owningRenderer) = 0;
    virtual IRendererFactoryPtr GetRendererFactory() = 0;
    virtual IShaderFactoryPtr GetShaderFactory(const IRendererPtr& owningRenderer) = 0;
    virtual IShaderProgramFactoryPtr GetShaderProgramFactory() = 0;
    virtual IMaterialFactoryPtr GetMaterialFactory() = 0;
  virtual RenderOperationFactoryHandle GetRenderOperationFactory() = 0;
};

} /* namespace glove */