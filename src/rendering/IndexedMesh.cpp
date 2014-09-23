#include "IndexedMesh.h"

#include "IndexedMeshData.h"
#include "shader/ShaderProgram.h"
#include "buffers/GPUBuffer.h"

namespace glove {

IndexedMesh::IndexedMesh(IndexedMeshDataPtr indexedMeshData, MaterialPtr material, GameObjectPtr parent) : Mesh(indexedMeshData, material, parent) {
	this->indexedMeshData = indexedMeshData;
}

IndexedMesh::~IndexedMesh() {
}

void IndexedMesh::OnRender(FrameData& frameData) {
	indexedMeshData->getIndexBuffer()->Bind();

	glDrawElements(GL_TRIANGLES, indexedMeshData->getNumIndices(), GL_UNSIGNED_INT, 0);
}

} /* namespace glove */
