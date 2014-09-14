/*
 * IndexedMesh.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "IndexedMesh.h"

#include "IndexedMeshData.h"
#include "shader/ShaderProgram.h"
#include "buffers/GPUBuffer.h"

namespace glove {

IndexedMesh::IndexedMesh(IndexedMeshDataPtr indexedMeshData, MaterialPtr material) : Mesh(indexedMeshData, material) {
	this->indexedMeshData = indexedMeshData;
}

IndexedMesh::~IndexedMesh() {
}

void IndexedMesh::OnRender(FrameData& frameData) {
	indexedMeshData->getIndexBuffer()->Bind();

	glDrawElements(GL_TRIANGLES, indexedMeshData->getNumIndices(), GL_UNSIGNED_INT, 0);
}

} /* namespace glove */
