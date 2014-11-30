#include "GLMaterialFactory.h"

#include "../subsystem/OpenGLRendererModule.h"
#include "../shader/GLMaterial.h"
#include "../shader/GLShaderProgram.h"

namespace glove {
namespace gl {

IMaterialPtr GLMaterialFactory::CreateMaterial(const IShaderProgramPtr& shaderProgram) {
    GLShaderProgramPtr glShaderProgram = std::dynamic_pointer_cast<GLShaderProgram>(shaderProgram);
    return GLMaterialPtr(new GLMaterial(glShaderProgram));
}
}
}
