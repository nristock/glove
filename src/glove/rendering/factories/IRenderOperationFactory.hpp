#pragma once

#include "glove/rendering/Rendering.hpp"

namespace glove {

class GLOVE_API_EXPORT IRenderOperationFactory {
public:
    virtual ~IRenderOperationFactory() = default;

    virtual IRenderOperation* CreateRenderOperation(bool autoDelete) = 0;
};

} /* namespace glove */