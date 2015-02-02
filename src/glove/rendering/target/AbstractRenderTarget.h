#pragma once

#include "glove/rendering/Rendering.h"
#include "glove/rendering/target/IRenderTarget.h"

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