#include "factories/GLShaderProgramFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "shader/GLShaderProgram.hpp"

namespace glove {
namespace gl {

IShaderProgramPtr GLShaderProgramFactory::CreateShaderProgram(const std::list<IShaderPtr>& shaders) {
    return GLShaderProgramPtr(new GLShaderProgram(shaders));
}
}
}