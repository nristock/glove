#pragma once

#include <glove/rendering/Shader.hpp>
#include <glove/rendering/MaterialProxy.hpp>

#include "internal/OpenGLWrapper.hpp"

namespace glove {
namespace gl {

class GLUniformIndex : public UniformParameter::UniformIndex {
  public:
    GLUniformIndex(GLuint uniformIndex) : uniformIndex(uniformIndex) {}

    GLuint GetUniformIndex() const { return uniformIndex; }

  private:
    GLuint uniformIndex;
};

class GLShaderBase {
  public:
    GLShaderBase(const std::string& shaderSource, const GLenum shaderType);
    virtual ~GLShaderBase();

    GLuint GetShaderId() const { return shaderId; }

  private:
    GLuint shaderId;
};

class GLVertexShader : public GLShaderBase, public VertexShader {
  public:
    GLVertexShader(std::string const& shaderSource,
                   ShaderParameterMap const& shaderParameterMap)
        : GLShaderBase(shaderSource, GL_VERTEX_SHADER), VertexShader(shaderParameterMap) {}
};

class GLFragmentShader : public GLShaderBase, public FragmentShader {
  public:
    GLFragmentShader(std::string const& shaderSource)
        : GLShaderBase(shaderSource, GL_FRAGMENT_SHADER) {}
};

class GLShaderProgram : public ShaderProgram {
  public:
    GLShaderProgram(VertexShader::Handle vertexShader, FragmentShader::Handle fragmentShader);

    UniformParameter::UniformIndex::Handle GetUniformParameterIndex(const std::string& uniformName);

    GLuint GetProgramId() const { return programId; }

  private:
    GLuint programId;
};
}
}