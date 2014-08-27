/*
 * MeshData.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include "MeshData.h"

#include <GL/glew.h>

#include "buffers/VertexAttributeBuffer.h"

namespace glove {

MeshData::MeshData(int numVertices) : numVertices(numVertices) {
}

MeshData::~MeshData() {
    gpuBuffers.clear();
}

void MeshData::AddGPUBuffer(VABPtr gpuBuffer) {
	gpuBuffers.push_back(gpuBuffer);
}

} /* namespace glove */
