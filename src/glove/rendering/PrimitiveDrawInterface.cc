#include "glove/rendering/PrimitiveDrawInterface.hpp"
#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/SceneView.hpp"
#include "glove/rendering/MaterialProxy.hpp"

namespace BlueDwarf {

void BatchCollector::DrawMesh(const MeshBatch& meshBatch) {
    meshBatches.emplace_back(meshBatch);
}

void BatchCollector::DrawBatches(RenderCommandList& cmdList, const SceneView& view) {
    for(auto& batch : meshBatches) {
        DrawBatch(batch, cmdList, view);
    }
}

void BatchCollector::DrawBatch(const MeshBatch& batch, RenderCommandList& cmdList, const SceneView& view) {
    cmdList.EnableVertexBinding(batch.GetVertexBinding());

    for(auto& batchElement : batch.GetElements()) {
        batch.GetMaterialProxy()->SetMesh(cmdList, view, batchElement);
        cmdList.DrawIndexed(batchElement.GetIndexBuffer(), batchElement.GetFirstVertexIndex(), batchElement.GetLastVertexIndex());
    }
}
}