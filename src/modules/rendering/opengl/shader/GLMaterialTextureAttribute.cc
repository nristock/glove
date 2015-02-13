#include <glove/GloveException.hpp>

#include "subsystem/OpenGLRendererModule.hpp"
#include "internal/OpenGLWrapper.hpp"
#include "shader/GLMaterialTextureAttribute.hpp"
#include "shader/GLMaterial.hpp"
#include "shader/GLShaderProgram.hpp"
#include "texture/GLTexture.hpp"

namespace glove {
namespace gl {
GLMaterialTextureAttribute::GLMaterialTextureAttribute(const GLint attributePosition, const GLMaterialRef& material, const GLuint textureUnit)
    : attributePosition(attributePosition), material(material), textureUnit(textureUnit) {
}

void GLMaterialTextureAttribute::Set(const TextureHandle& texture) {
    this->texture = texture;
}

void GLMaterialTextureAttribute::BindTexture() {
    GL::Uniform1i(attributePosition, textureUnit);
    GL::ActiveTexture(GL_TEXTURE0 + textureUnit);
    texture->Bind();
}

void GLMaterialTextureAttribute::BindMaterial() {
    if (material.expired()) {
        throw GLOVE_EXCEPTION("Material attribute has expired because the bound material has been destroyed.")
    }

    material.lock()->GetShaderProgram()->Enable();
}
}
}