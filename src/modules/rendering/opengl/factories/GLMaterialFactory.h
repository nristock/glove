#pragma once

#include <glove/rendering/Rendering.h>
#include <glove/rendering/factories/IMaterialFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLMaterialFactory : public IMaterialFactory {
  public:
    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram);
};
}
}