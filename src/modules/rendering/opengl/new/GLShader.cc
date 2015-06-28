#include "GLShader.hpp"

#include <glove/utils/ShaderUtils.hpp>
#include <glove/GloveException.hpp>
#include <glove/log/Logger.hpp>
#include <glove/log/format.hpp>

namespace glove {
namespace gl {


GLShaderBase::GLShaderBase(const std::string& shaderSource, const GLenum shaderType) {
    if (shaderSource.empty()) {
        throw GLOVE_EXCEPTION("Shader source is empty.");
    }

    const char* cstrShaderSource = shaderSource.c_str();
    GLint sourceLength = (int)shaderSource.length();

    shaderId = GL::CreateShader(shaderType);
    GL::ShaderSource(shaderId, 1, &cstrShaderSource, &sourceLength);

    GLint compileStatus = 0;
    GL::CompileShader(shaderId);
    GL::GetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        PrintShaderCompilerLog(shaderId);
        GL::DeleteShader(shaderId);
        LOG(Error, "Failed to compile shader.");
        throw GLOVE_EXCEPTION("Failed to compile shader.");
    }
}

GLShaderBase::~GLShaderBase() {
    GL::DeleteShader(shaderId);
}

GLShaderProgram::GLShaderProgram(VertexShader::Handle vertexShader, FragmentShader::Handle fragmentShader) : ShaderProgram(vertexShader, fragmentShader) {
    programId = GL::CreateProgram();

    auto vertShaderId = dynamic_cast<GLVertexShader*>(vertexShader.get())->GetShaderId();
    auto fragShaderId = dynamic_cast<GLFragmentShader*>(fragmentShader.get())->GetShaderId();

    GL::AttachShader(programId, vertShaderId);
    GL::AttachShader(programId, fragShaderId);

    GL::LinkProgram(programId);

    GLint linkStatus;
    GL::GetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        PrintShaderProgramLinkLog(programId);
        GL::DeleteProgram(programId);
        LOG(Error, "Failed to link shader program");
        throw GLOVE_EXCEPTION("Failed to link shader program");
    }
}

UniformParameter::UniformIndex::Handle GLShaderProgram::GetUniformParameterIndex(const std::string& uniformName) {
    auto uniformLocation = GL::GetUniformLocation(programId, uniformName.c_str());

    return std::make_shared<GLUniformIndex>(uniformLocation);
}
}
}