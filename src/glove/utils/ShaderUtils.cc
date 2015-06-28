#include <iostream>

#include <GL/glew.h>

#include "glove/utils/ShaderUtils.hpp"
#include "glove/log/Log.hpp"

GLEWContext* glewGetContext();

namespace BlueDwarf {

void PrintShaderCompilerLog(GLuint shaderId) {
    GLint logLength = 0;
    GLint charsWritten = 0;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        GLchar* infoLog = new GLchar[logLength];
        glGetShaderInfoLog(shaderId, logLength, &charsWritten, infoLog);

        LOG(Error, fmt::format("Shader Compile Log: \n{0}", infoLog));
        delete[] infoLog;
    }
}

void PrintShaderProgramLinkLog(GLuint programId) {
    GLint logLength = 0;
    GLint charsWritten = 0;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        GLchar* linkLog = new GLchar[logLength];
        glGetProgramInfoLog(programId, logLength, &charsWritten, linkLog);

        LOG(Error, fmt::format("Shader Link Log:\n {0}", linkLog));
        delete[] linkLog;
    }
}

} // namespcae BlueDwarf

