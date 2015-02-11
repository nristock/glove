#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "glove/GloveApi.hpp"

namespace glove {
void GLOVE_API_EXPORT PrintShaderCompilerLog(GLuint shaderId);
void GLOVE_API_EXPORT PrintShaderProgramLinkLog(GLuint programId);
} // namespace glove
