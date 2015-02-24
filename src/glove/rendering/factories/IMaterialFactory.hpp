#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IMaterialFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IMaterialFactory() : BasicService(serviceType) {}
    virtual ~IMaterialFactory() = default;

    virtual IMaterialPtr CreateMaterial(const IShaderProgramPtr& shaderProgram) = 0;
};
}