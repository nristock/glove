/*
 * IndexedMeshData.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include "IndexedMeshData.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "MeshData.h"
#include "buffers/GPUBuffer.h"

namespace glove {

IndexedMeshData::IndexedMeshData(int numVertices) : MeshData(numVertices), numIndices(0) {
	indexBuffer = GPUBufferPtr(new GPUBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW));
}

IndexedMeshData::~IndexedMeshData() {
	// TODO Auto-generated destructor stub
}

void IndexedMeshData::SetIndices(GLuint* indexData, int numberOfIndices) {
	indexBuffer->FillData(sizeof(GLuint) * numberOfIndices, indexData);
	numIndices = numberOfIndices;
}

} /* namespace glove */
