#pragma once

#include <queue>

#include "glove/graph/gamecomponent/GameComponent.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT MeshRenderer : public GameComponent {
public:
    MeshRenderer(const IMeshPtr& mesh, const RenderOperationFactoryHandle& renderOperationFactory);

    virtual void QueueRenderOperation(std::queue<IRenderOperation*>& renderQueue);

protected:
    IMeshPtr sharedMesh;
    IRenderOperation* persistentRenderOp;
};

}
}