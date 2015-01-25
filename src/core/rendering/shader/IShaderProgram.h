#pragma once

#include "../Rendering.h"

namespace glove {

/// @brief A shader program is a collection of individual shaders linked together.
/// @ingroup RenderSubsystemInterface
class IShaderProgram {
  public:
    virtual ~IShaderProgram() = default;

    virtual IVertexAttributeMappingPtr GetVertexAttributeMapping() = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
};
}