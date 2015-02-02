#pragma once

#include <list>
#include <memory>

#include "utils/ScreenDimensions.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderTarget {
public:
    virtual ~IRenderTarget() = default;

    virtual void AddDependency(const RenderTargetHandle& dependency) = 0;
    virtual std::list<std::weak_ptr<IRenderTarget>> GetDependencies() = 0;

    virtual const ScreenDimensions& GetDimensions() const = 0;
    virtual void Bind() = 0;
};

}