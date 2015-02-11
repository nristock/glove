#include "MeshRenderer.hpp"

#include "glove/rendering/IRenderOperation.hpp"
#include "glove/rendering/factories/IRenderOperationFactory.hpp"

namespace glove {
namespace GameComponents {
MeshRenderer::MeshRenderer(const IMeshPtr& mesh, const RenderOperationFactoryHandle& renderOperationFactory) : sharedMesh(mesh) {
    persistentRenderOp = renderOperationFactory->CreateRenderOperation(false);
    persistentRenderOp->SetMesh(mesh);
}


void MeshRenderer::QueueRenderOperation(std::queue<IRenderOperation*>& renderQueue) {
    renderQueue.push(persistentRenderOp);
}
}
}