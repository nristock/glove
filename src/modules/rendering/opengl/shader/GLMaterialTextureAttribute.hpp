#pragma once

#include <GL/glew.h>

#include <glove/rendering/shader/MaterialTextureAttribute.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

class GLMaterialTextureAttribute : public MaterialTextureAttribute {
  public:
    GLMaterialTextureAttribute(const GLint attributePosition, const GLMaterialRef& material, const GLuint textureUnit);

    virtual void Set(const TextureHandle& texture);

    void BindTexture();

  private:
    GLint attributePosition;
    GLMaterialRef material;
    GLuint textureUnit;
    TextureHandle texture;
    
    void BindMaterial();
};
}
} /* namespace glove */