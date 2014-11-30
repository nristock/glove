#include "Mesh.h"

#include <core/rendering/RenderOperation.h>

namespace glove {

Mesh::Mesh(const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData)
    : vertexData(vertexData), indexData(indexData) {
}

void Mesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
    renderOp.vertexData = vertexData.get();
    renderOp.indexData = indexData.get();
    renderOp.material = material.get();
}

void Mesh::PostRender(RenderOperation& renderOp, const FrameData& frameData) {
}

const IMaterialPtr& Mesh::GetMaterial() const {
    return material;
}

const IVertexDataPtr& Mesh::GetVertexData() const {
    return vertexData;
}

const IIndexDataPtr& Mesh::GetIndexData() const {
    return indexData;
}

} /* namespace glove */
