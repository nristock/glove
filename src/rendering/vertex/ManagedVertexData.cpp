#include "ManagedVertexData.h"

#include "rendering/vertex/VertexLayouts.h"

namespace glove {
	
ManagedVertexData<vertexlayouts::Position>::ManagedVertexData() : VertexData() {
	vertexLayout = vertexlayouts::Position::GetLayout();
	CreateBuffers();
}

ManagedVertexData<vertexlayouts::PositionColor>::ManagedVertexData() : VertexData() {
	vertexLayout = vertexlayouts::PositionColor::GetLayout();
	CreateBuffers();
}

ManagedVertexData<vertexlayouts::PositionNormal>::ManagedVertexData() : VertexData() {
	vertexLayout = vertexlayouts::PositionNormal::GetLayout();
	CreateBuffers();
}

} // namespace glove