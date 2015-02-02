#pragma once

#include "glove/rendering/Rendering.h"
#include "glove/rendering/shader/MaterialAttributeSemantic.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IMaterial {
  public:
    virtual ~IMaterial() = default;

    virtual IShaderProgramPtr GetShaderProgram() const = 0;
    virtual IMaterialAttributePtr GetMaterialAttribute(const std::string& name) = 0;
    virtual IMaterialAttributePtr GetMaterialAttribute(const MaterialAttributeSemantic semantic) = 0;
    virtual void MapAttributeSemantic(const MaterialAttributeSemantic semantic, const std::string& attributeName) = 0;
};
}