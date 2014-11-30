#pragma once

#include <string>

#include <core/rendering/Rendering.h>
#include <core/rendering/shader/IMaterial.h>
#include <core/log/Log.h>

#include "../subsystem/OpenGLRendererModule.h"

namespace glove {
namespace gl {

/// @ingroup Shader
class GLMaterial : public IMaterial, public std::enable_shared_from_this<GLMaterial> {
  public:
    GLMaterial(const GLShaderProgramPtr& shader);
    virtual ~GLMaterial() = default;

    virtual IShaderProgramPtr GetShaderProgram() const;
    virtual IMaterialAttributePtr GetMaterialAttribute(const std::string& name);

  private:
    logging::GloveLogger logger;

    GLShaderProgramPtr shader;
};

}
} // namespace glove