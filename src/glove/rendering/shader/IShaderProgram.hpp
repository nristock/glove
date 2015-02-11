#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @brief A shader program is a collection of individual shaders linked together.
/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IShaderProgram {
  public:
    virtual ~IShaderProgram() = default;

    virtual IVertexAttributeMappingPtr GetVertexAttributeMapping() = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
};
}