#pragma once

#include "graph/gamecomponent/GameComponent.h"

#include <queue>
#include "rendering/Rendering.h"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class MeshRenderer : public GameComponent {
public:
    MeshRenderer(const IMeshPtr& mesh, const RenderOperationFactoryHandle& renderOperationFactory);

    virtual void QueueRenderOperation(std::queue<IRenderOperation*>& renderQueue);

protected:
    IMeshPtr sharedMesh;
    IRenderOperation* persistentRenderOp;
};

}
}