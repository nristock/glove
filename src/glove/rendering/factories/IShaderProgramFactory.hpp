#pragma once

#include <list>

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IShaderProgramFactory {
  public:
    virtual ~IShaderProgramFactory() = default;

    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders) = 0;
};
}