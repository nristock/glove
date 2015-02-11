#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/target/IRenderTarget.hpp"

namespace glove {
/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT AbstractRenderTarget : public IRenderTarget {
public:
    virtual ~AbstractRenderTarget() = default;

    virtual void AddDependency(RenderTargetHandle const& dependency);
    virtual std::list<std::weak_ptr<IRenderTarget>> GetDependencies();

protected:
    std::list<std::weak_ptr<IRenderTarget>> dependencies;
};
}