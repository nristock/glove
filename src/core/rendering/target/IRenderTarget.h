#pragma once

#include "utils/Dimensions.h"

namespace glove {

class IRenderTarget {
public:
    virtual ~IRenderTarget() = default;

    virtual const Dimensions& GetDimensions() const = 0;
    virtual void Bind() = 0;
};

}