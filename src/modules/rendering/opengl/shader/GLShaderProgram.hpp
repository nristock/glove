#pragma once

#include <GL/glew.h>
#include <list>

#include <glove/log/Log.hpp>
#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/shader/IShaderProgram.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

/// @ingroup Shader
class GLShaderProgram : public IShaderProgram {
  public:
    GLShaderProgram(const std::list<IShaderPtr>& shaders);
    ~GLShaderProgram();
    GLShaderProgram(const GLShaderProgram&) = delete;
    GLShaderProgram& operator=(const GLShaderProgram&) = delete;

    GLint GetUniformLocation(const std::string& uniformName);
    GLint GetVertexAttributeLocation(const std::string& attributeName);
    virtual IVertexAttributeMappingPtr GetVertexAttributeMapping();

    virtual void Enable();
    virtual void Disable();

  private:
    logging::GloveLogger logger;

    GLuint shaderProgramId;
    std::list<GLShaderPtr> shaders;
    IVertexAttributeMappingPtr vertexAttributeMapping;
};
}
} /* namespace glove */
