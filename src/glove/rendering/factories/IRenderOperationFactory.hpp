#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IRenderOperationFactory : public BasicService {
public:
    static ServiceType serviceType;

    IRenderOperationFactory() : BasicService(serviceType) {}
    virtual ~IRenderOperationFactory() = default;

    virtual IRenderOperation* CreateRenderOperation(bool autoDelete) = 0;
};

} /* namespace glove */