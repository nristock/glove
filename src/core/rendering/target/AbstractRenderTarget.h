#pragma once

#include <core/rendering/Rendering.h>
#include "rendering/target/IRenderTarget.h"

namespace glove {
/// @ingroup RenderSubsystemInterface
class AbstractRenderTarget : public IRenderTarget {
public:
    virtual ~AbstractRenderTarget() = default;

    virtual void AddDependency(RenderTargetHandle const& dependency);
    virtual std::list<std::weak_ptr<IRenderTarget>> GetDependencies();

protected:
    std::list<std::weak_ptr<IRenderTarget>> dependencies;
};
}