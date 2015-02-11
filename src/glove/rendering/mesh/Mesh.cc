#include "Mesh.hpp"

#include "glove/rendering/RenderOperation.hpp"

namespace glove {

Mesh::Mesh(const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData)
    : vertexData(vertexData), indexData(indexData) {
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
