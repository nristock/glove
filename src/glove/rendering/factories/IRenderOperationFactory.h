#pragma once

#include "glove/rendering/Rendering.h"

namespace glove {

class IRenderOperationFactory {
public:
    virtual ~IRenderOperationFactory() = default;

    virtual IRenderOperation* CreateRenderOperation(bool autoDelete) = 0;
};

} /* namespace glove */