/*
 * IndexedMesh.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "IndexedMesh.h"

namespace glove {
namespace gl {
namespace rendering {

IndexedMesh::IndexedMesh(IndexedMeshDataPtr indexedMeshData, shader::ShaderPtr shader) : Mesh(indexedMeshData, shader) {
	this->indexedMeshData = indexedMeshData;
}

IndexedMesh::~IndexedMesh() {
}

void IndexedMesh::Render() {
	shader->Enable();
	glBindVertexArray(vertexArrayId);
	indexedMeshData->getIndexBuffer()->Bind();

	glDrawElements(GL_TRIANGLES, indexedMeshData->getNumIndices(), GL_UNSIGNED_INT, 0);
}

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */
