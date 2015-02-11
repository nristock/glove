#include "factories/GLMaterialFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "shader/GLMaterial.hpp"
#include "shader/GLShaderProgram.hpp"

namespace glove {
namespace gl {

IMaterialPtr GLMaterialFactory::CreateMaterial(const IShaderProgramPtr& shaderProgram) {
    GLShaderProgramPtr glShaderProgram = std::dynamic_pointer_cast<GLShaderProgram>(shaderProgram);
    return GLMaterialPtr(new GLMaterial(glShaderProgram));
}
}
}
