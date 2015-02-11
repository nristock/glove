#pragma once

#include <list>

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IShaderProgramFactory {
  public:
    virtual ~IShaderProgramFactory() = default;

    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders) = 0;
};
}