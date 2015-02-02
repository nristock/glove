#include <glove/GloveException.h>
#include <utils/ShaderUtils.h>

#include "GLShader.h"
#include "../internal/OpenGLWrapper.h"

namespace glove {
namespace gl {

GLShader::GLShader(const std::string& shaderSource, const GLenum shaderType) {
    if (shaderSource.empty()) {
        throw GLOVE_EXCEPTION("Shader source is empty.");
    }

    const char* cstrShaderSource = shaderSource.c_str();
    GLint sourceLength = (int)shaderSource.length();

    shaderName = GL::CreateShader(shaderType);
    GL::ShaderSource(shaderName, 1, &cstrShaderSource, &sourceLength);

    GLint compileStatus = 0;
    GL::CompileShader(shaderName);
    GL::GetShaderiv(shaderName, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        GL::DeleteShader(shaderName);
        PrintShaderCompilerLog(shaderName);
        throw GLOVE_EXCEPTION("Failed to compile shader.");
    }
}

GLShader::~GLShader() {
    GL::DeleteShader(shaderName);
}

const GLuint GLShader::GetGLShaderId() const {
    return shaderName;
}
}
}