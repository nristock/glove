#pragma once

#include <list>

#include "glove/rendering/Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IShaderProgramFactory {
  public:
    virtual ~IShaderProgramFactory() = default;

    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders) = 0;
};
}