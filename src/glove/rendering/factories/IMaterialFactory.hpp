#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IMaterialFactory {
  public:
    virtual ~IMaterialFactory() = default;

    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram) = 0;
};
}