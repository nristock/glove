#pragma once

#include <GL/glew.h>

#include <glove/GloveFwd.hpp>
#include <glove/rendering/shader/IShader.h>

namespace glove {
namespace gl {

/// @ingroup Shader
class GLShader : public IShader {
  public:
    GLShader(const std::string& shaderSource, const GLenum shaderType);
    virtual ~GLShader();
    GLShader(const GLShader&) = delete;
    GLShader& operator=(const GLShader&) = delete;

    GLOVE_INLINE const GLuint GetGLShaderId() const;

  private:
    GLuint shaderName;
};
}
}