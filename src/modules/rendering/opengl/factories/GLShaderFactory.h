#pragma once

#include <glove/rendering/factories/IShaderFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLShaderFactory : public IShaderFactory {
  public:
    virtual IShaderPtr CreateVertexShader(std::string fileName);
    virtual IShaderPtr CreateFragmentShader(std::string fileName);
};
}
}