#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IRendererFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IRendererFactory() : BasicService(serviceType) {}
    virtual ~IRendererFactory(){};

    virtual IRendererPtr CreateRenderer(const WindowConstructionHints& windowDescription) = 0;
};

} /* namespace glove */