#pragma once

#include <list>

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IShaderProgramFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IShaderProgramFactory() : BasicService(serviceType) {}
    virtual ~IShaderProgramFactory() = default;

    virtual IShaderProgramPtr CreateShaderProgram(const std::list<IShaderPtr>& shaders) = 0;
};
}