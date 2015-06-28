#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
void BD_API_EXPORT PrintShaderCompilerLog(GLuint shaderId);
void BD_API_EXPORT PrintShaderProgramLinkLog(GLuint programId);
} // namespace BlueDwarf
