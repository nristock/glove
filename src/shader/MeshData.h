/*
 * MeshData.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef MESHDATA_H_
#define MESHDATA_H_

#include "../buffers/VertexAttributeBuffer.h"
#include <vector>
#include <memory>

namespace glove {
namespace gl {
namespace shader {

class MeshData {
public:
	MeshData(int numVertices);
	virtual ~MeshData();

	void AddGPUBuffer(buffers::VABPtr gpuBuffer);

	const std::vector<buffers::VABPtr>& getGpuBuffers() const {
		return gpuBuffers;
	}

	int getNumVertices() const {
		return numVertices;
	}

	void setNumVertices(int numVertices) {
		this->numVertices = numVertices;
	}

private:
	int numVertices;

	std::vector<buffers::VABPtr> gpuBuffers;
};

typedef std::shared_ptr<MeshData> MeshDataPtr;

} /* namespace shader */
} /* namespace gl */
} /* namespace glove */

#endif /* MESHDATA_H_ */
