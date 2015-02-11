#pragma once

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/factories/IMaterialFactory.hpp>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLMaterialFactory : public IMaterialFactory {
  public:
    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram);
};
}
}