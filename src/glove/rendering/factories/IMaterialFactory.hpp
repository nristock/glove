#pragma once

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IMaterialFactory {
  public:
    virtual ~IMaterialFactory() = default;

    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram) = 0;
};
}