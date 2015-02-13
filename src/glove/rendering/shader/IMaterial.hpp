#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/shader/MaterialAttributeSemantic.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IMaterial {
  public:
    virtual ~IMaterial() = default;

    virtual IShaderProgramPtr GetShaderProgram() const = 0;
    virtual IMaterialAttributePtr GetMaterialAttribute(const std::string& name) = 0;
    virtual IMaterialAttributePtr GetMaterialAttribute(const MaterialAttributeSemantic semantic) = 0;
    virtual void MapAttributeSemantic(const MaterialAttributeSemantic semantic, const std::string& attributeName) = 0;
    virtual MaterialTextureAttributeHandle GetTextureAttribute(const std::string& name) = 0;

    virtual void Enable() = 0;
};
}