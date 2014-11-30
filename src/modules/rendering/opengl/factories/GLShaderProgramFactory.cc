#include "GLShaderProgramFactory.h"

#include "../subsystem/OpenGLRendererModule.h"
#include "../shader/GLShaderProgram.h"

namespace glove {
namespace gl {

IShaderProgramPtr GLShaderProgramFactory::CreateShaderProgram(const std::list<IShaderPtr>& shaders) {
    return GLShaderProgramPtr(new GLShaderProgram(shaders));
}

}
}