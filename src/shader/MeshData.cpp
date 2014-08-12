/*
 * MeshData.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include <GL/glew.h>

#include "MeshData.h"

namespace glove {
namespace gl {
namespace shader {

MeshData::MeshData(int numVertices) : numVertices(numVertices) {
}

MeshData::~MeshData() {
	gpuBuffers.clear();
}

void MeshData::AddGPUBuffer(buffers::VABPtr gpuBuffer) {
	gpuBuffers.push_back(gpuBuffer);
}

} /* namespace shader */
} /* namespace gl */
} /* namespace glove */
