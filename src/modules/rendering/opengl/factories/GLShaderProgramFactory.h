#pragma once

#include <core/rendering/factories/IShaderProgramFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLShaderProgramFactory : public IShaderProgramFactory {
  public:
    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders);
};
}
}