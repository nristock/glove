#include "ShaderUtils.h"

#include <iostream>

#include <GL/glew.h>

#include "glove/log/Log.h"

GLEWContext* glewGetContext();

namespace glove {

void PrintShaderCompilerLog(GLuint shaderId) {
    GLint logLength = 0;
    GLint charsWritten = 0;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        GLchar* infoLog = new GLchar[logLength];
        glGetShaderInfoLog(shaderId, logLength, &charsWritten, infoLog);

        LOG(logging::globalLogger, error, "Shader Compile Log: " << std::endl << infoLog);
        delete[] infoLog;
    }
}

void PrintShaderProgramLinkLog(GLuint programId) {
    GLint logLength = 0;
    GLint charsWritten = 0;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        GLchar* linkLog = new GLchar[logLength];
        glGetProgramInfoLog(programId, logLength, &logLength, linkLog);

        LOG(logging::globalLogger, error, "Shader Link Log: " << std::endl << linkLog);
        delete[] linkLog;
    }
}

} // namespcae glove

