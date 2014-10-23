#include "ManagedVertexData.h"

#include "rendering/vertex/VertexLayouts.h"

namespace glove {

template<>
ManagedVertexData<vertexlayouts::Position>::ManagedVertexData() : VertexData(), EnableProfilable() {
    vertexLayout = vertexlayouts::Position::GetLayout();
    CreateBuffers();
}

template<>
ManagedVertexData<vertexlayouts::PositionColor>::ManagedVertexData() : VertexData(), EnableProfilable() {
    vertexLayout = vertexlayouts::PositionColor::GetLayout();
    CreateBuffers();
}

template<>
ManagedVertexData<vertexlayouts::PositionNormal>::ManagedVertexData() : VertexData(), EnableProfilable() {
    vertexLayout = vertexlayouts::PositionNormal::GetLayout();
    CreateBuffers();
}

} // namespace glove