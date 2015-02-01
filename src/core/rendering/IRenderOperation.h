#pragma once

#include <functional>

#include "Rendering.h"

namespace glove {

class IRenderOperation {
public:
    typedef std::function<void(const glm::mat4&)> PreRenderCallback;
    typedef std::function<void(void)> PostRenderCallback;

    virtual ~IRenderOperation() = default;

    /// @brief Return a boolean to indicate the render operation executor whether or not to delete the render op pointer
    ///        after executing it.
    virtual bool ShouldDelete() const = 0;

    /// @brief Executes the render operation.
    virtual void Execute(const IRendererPtr& renderer) = 0;

    virtual void SetMesh(const IMeshPtr& mesh) = 0;
    virtual void SetPreRenderUserCallback(PreRenderCallback callback) = 0;
    virtual void SetPostRenderUserCallback(PostRenderCallback callback) = 0;
};

}