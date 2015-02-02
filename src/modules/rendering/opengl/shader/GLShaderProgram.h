#pragma once

#include <GL/glew.h>
#include <list>

#include <glove/log/Log.h>
#include <glove/rendering/Rendering.h>
#include <glove/rendering/shader/IShaderProgram.h>
#include <glove/rendering/vertex/VertexAttributeSemantic.h>

#include "../subsystem/OpenGLRendererModule.h"

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
