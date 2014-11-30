#pragma once

#include <GL/glew.h>

#include <core/rendering/shader/IMaterialAttribute.h>

#include "../subsystem/OpenGLRendererModule.h"

namespace glove {
namespace gl {

/// @ingroup Shader
class GLMaterialAttribute : public IMaterialAttribute {
  public:
    GLMaterialAttribute(const GLint attributePosition, const GLMaterialRef materialRef);

    virtual void Set(glm::mat3& value);
    virtual void Set(glm::mat4& value);
    virtual void Set(glm::vec3& value);
    virtual void Set(glm::vec4& value);
    virtual void Set(float& value);

  private:
    GLint attributePosition;
    GLMaterialRef material;

    void BindMaterial();
};

}
} /* namespace glove */