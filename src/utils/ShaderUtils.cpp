/*
 * ShaderUtils.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: monofraps
 */

#include "ShaderUtils.h"

#include <iostream>

#include <GL/glew.h>

#include "log/log.h"
#include "memory/GloveMemory.h"


namespace glove {

void PrintShaderCompilerLog(GLuint shaderId) {
	GLint logLength = 0;
	GLint charsWritten = 0;

	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0) {
		GLchar *infoLog = GLOVE_NEW_ARRAY("ShaderCompilerLog/infoLog", GLchar, logLength);
		glGetShaderInfoLog(shaderId, logLength, &charsWritten, infoLog);

		LOG(logging::globalLogger, error, "Shader Compile Log: " << std::endl << infoLog);
		GLOVE_DELETE(infoLog);
	}
}

void PrintShaderProgramLinkLog(GLuint programId) {
	GLint logLength = 0;
	GLint charsWritten = 0;

	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength > 0) {
		GLchar *linkLog = GLOVE_NEW("ShaderProgramLinkLog/linkLog", GLchar, logLength);
		glGetProgramInfoLog(programId, logLength, &logLength, linkLog);

		LOG(logging::globalLogger, error, "Shader Link Log: " << std::endl << linkLog);
		GLOVE_DELETE(linkLog);
	}
}

} // namespcae glove

