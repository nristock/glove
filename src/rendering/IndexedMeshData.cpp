/*
 * IndexedMeshData.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#include <GL/glew.h>
#include <GL/gl.h>
#include "IndexedMeshData.h"
#include "../shader/MeshData.h"

namespace glove {
namespace gl {
namespace rendering {

IndexedMeshData::IndexedMeshData(int numVertices) : shader::MeshData(numVertices), numIndices(0) {
	indexBuffer = buffers::GPUBufferPtr(new buffers::GPUBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW));
}

IndexedMeshData::~IndexedMeshData() {
	// TODO Auto-generated destructor stub
}

void IndexedMeshData::SetIndices(GLuint* indexData, int numberOfIndices) {
	indexBuffer->FillData(sizeof(GLuint) * numberOfIndices, indexData);
	numIndices = numberOfIndices;
}

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */
