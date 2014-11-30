#include "GLMaterial.h"

#include <glm/gtc/type_ptr.hpp>

#include "GLMaterialAttribute.h"
#include "GLShaderProgram.h"

namespace glove {
namespace gl {

GLMaterial::GLMaterial(const GLShaderProgramPtr& shader) : shader(shader) {
}

IShaderProgramPtr GLMaterial::GetShaderProgram() const {
    return shader;
}

IMaterialAttributePtr GLMaterial::GetMaterialAttribute(const std::string& name) {
    return IMaterialAttributePtr(new GLMaterialAttribute(shader->GetUniformLocation(name), shared_from_this()));
}
}
} // namespace glove