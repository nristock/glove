#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace glove {
void PrintShaderCompilerLog(GLuint shaderId);
void PrintShaderProgramLinkLog(GLuint programId);
} // namespace glove
