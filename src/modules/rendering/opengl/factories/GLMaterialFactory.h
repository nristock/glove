#pragma once

#include <core/rendering/Rendering.h>
#include <core/rendering/factories/IMaterialFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLMaterialFactory : public IMaterialFactory {
  public:
    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram);
};

}
}