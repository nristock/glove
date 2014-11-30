#pragma once

#include "../Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IMaterialFactory {
  public:
    virtual ~IMaterialFactory() = default;

    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram) = 0;
};
}