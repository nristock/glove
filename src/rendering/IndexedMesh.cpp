/*
 * IndexedMesh.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "IndexedMesh.h"

#include "IndexedMeshData.h"
#include "shader/Shader.h"
#include "buffers/GPUBuffer.h"

namespace glove {

IndexedMesh::IndexedMesh(IndexedMeshDataPtr indexedMeshData, ShaderPtr shader) : Mesh(indexedMeshData, shader) {
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

} /* namespace glove */
