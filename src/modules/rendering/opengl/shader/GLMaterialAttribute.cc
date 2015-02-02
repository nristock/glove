#include "GLMaterialAttribute.h"

#include <glm/gtc/type_ptr.hpp>
#include <glove/GloveException.h>

#include "GLMaterial.h"
#include "GLShaderProgram.h"
#include "../internal/OpenGLWrapper.h"

namespace glove {
namespace gl {

GLMaterialAttribute::GLMaterialAttribute(const GLint attributePosition, const GLMaterialRef materialRef)
    : attributePosition(attributePosition), material(materialRef) {
}

void GLMaterialAttribute::Set(glm::mat3& value) {
    BindMaterial();
    GL::UniformMatrix3fv(attributePosition, 1, GL_FALSE, glm::value_ptr(value));
}

void GLMaterialAttribute::Set(glm::mat4& value) {
    BindMaterial();
    GL::UniformMatrix4fv(attributePosition, 1, GL_FALSE, glm::value_ptr(value));
}

void GLMaterialAttribute::Set(glm::vec3& value) {
    BindMaterial();
    GL::Uniform3fv(attributePosition, 1, glm::value_ptr(value));
}

void GLMaterialAttribute::Set(glm::vec4& value) {
    BindMaterial();
    GL::Uniform4fv(attributePosition, 1, glm::value_ptr(value));
}

void GLMaterialAttribute::Set(float& value) {
    BindMaterial();
    GL::Uniform1f(attributePosition, value);
}

void GLMaterialAttribute::BindMaterial() {
    if (material.expired()) {
        throw GLOVE_EXCEPTION("Material attribute has expired because the bound material has been destroyed.")
    }

    material.lock()->GetShaderProgram()->Enable();
}
}
}