#include <GL/glew.h>
#include <glove/utils/FileUtils.hpp>

#include "factories/GLShaderFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "shader/GLShader.hpp"

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