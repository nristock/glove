/*
 * Shader.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: monofraps
 */

#include "Shader.h"

#include <string>
#include <iostream>
#include <cstring>

#include <GL/glew.h>

#include "utils/FileUtils.h"
#include "utils/ShaderUtils.h"

namespace glove {

Shader::Shader(int numShaders) {
	shaderProgramId = 0;
	this->numShaders = numShaders;

	shaderIds = new GLuint[numShaders];
	memset(shaderIds, 0, sizeof(GLuint) * numShaders);
}

Shader::~Shader() {
	for (int i = 0; i < numShaders; ++i) {
		if (shaderIds[i] == 0) {
			std::cout << "Shader not initialized" << std::endl;
			continue;
		}

		glDetachShader(shaderProgramId, shaderIds[i]);
		glDeleteShader(shaderIds[i]);
	}

	glDeleteProgram(shaderProgramId);

	delete[] shaderIds;
}

void Shader::AttachShader(int shaderId, GLenum shaderType,
		std::string filePath) {
	std::string code = ReadFileToString(filePath);
	int codeLen = code.length();

	if (code.empty()) {
		std::cout << "No shader source" << std::endl;
	}

	shaderIds[shaderId] = glCreateShader(shaderType);
	const char* cStrShaderSource = code.c_str();
	glShaderSource(shaderIds[shaderId], 1, &cStrShaderSource, &codeLen);

	GLint compileStatus = 0;
	glCompileShader(shaderIds[shaderId]);
	glGetShaderiv(shaderIds[shaderId], GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == false) {
		std::cout << "Failed to compile shader" << std::endl;
		PrintShaderCompilerLog(shaderIds[shaderId]);

		glDeleteShader(shaderIds[shaderId]);
	}

}

void Shader::CreateProgram() {
	shaderProgramId = glCreateProgram();
	for (int i = 0; i < numShaders; ++i) {
		if (shaderIds[i] == 0) {
			std::cout << "Shader not initialized" << std::endl;
			continue;
		}
		glAttachShader(shaderProgramId, shaderIds[i]);
	}

	glLinkProgram(shaderProgramId);

	GLint linkStatus;
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == false) {
		std::cout << "Failed to link shader program" << std::endl;
		PrintShaderProgramLinkLog(shaderProgramId);
	}
}

void Shader::Enable() {
	glUseProgram(shaderProgramId);
}

void Shader::MapVertexAttribute(ushort attributeIdentifier, GLuint attribIndex) {
	vertexAttributeMap[attributeIdentifier] = attribIndex;
}

void Shader::Disable() {
	glUseProgram(0);
}

GLuint Shader::GetVertexAttributePosition(ushort attributeIdentifier) {
	if(vertexAttributeMap.find(attributeIdentifier) == vertexAttributeMap.end()) return -1;
	else return vertexAttributeMap.at(attributeIdentifier);
}

} /* namespace glove */

