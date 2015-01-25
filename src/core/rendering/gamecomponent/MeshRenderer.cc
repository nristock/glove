#include "rendering/IRenderOperation.h"
#include "MeshRenderer.h"

#include "rendering/factories/IRenderOperationFactory.h"

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