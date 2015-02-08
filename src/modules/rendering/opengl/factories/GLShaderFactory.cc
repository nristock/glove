#include "GLShaderFactory.h"

#include <glove/utils/FileUtils.h>
#include <GL/glew.h>

#include "../subsystem/OpenGLRendererModule.h"
#include "../shader/GLShader.h"

namespace glove {
namespace gl {

IShaderPtr GLShaderFactory::CreateVertexShader(std::string fileName) {
    std::string shaderSource = ReadFileToString(fileName);

    return GLShaderPtr(new GLShader(shaderSource, GL_VERTEX_SHADER));
}

IShaderPtr GLShaderFactory::CreateFragmentShader(std::string fileName) {
    std::string shaderSource = ReadFileToString(fileName);

    return GLShaderPtr(new GLShader(shaderSource, GL_FRAGMENT_SHADER));
}
}
}