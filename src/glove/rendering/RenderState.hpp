#pragma once

#include <list>
#include <queue>

#include <glm/glm.hpp>

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT RenderState {
public:
    typedef std::queue<IRenderOperation*> RenderQueue;

    RenderState(const glm::mat4& viewProjectionMatrix);
    virtual ~RenderState() = default;

    RenderQueue& GetRenderQueue();

protected:
    RenderQueue renderQueue;
    const glm::mat4 viewProjectionMatrix;
};

}