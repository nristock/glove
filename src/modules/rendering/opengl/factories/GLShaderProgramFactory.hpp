#pragma once

#include <glove/rendering/factories/IShaderProgramFactory.hpp>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLShaderProgramFactory : public IShaderProgramFactory {
  public:
    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders);
};
}
}