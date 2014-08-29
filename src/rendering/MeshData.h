/*
 * MeshData.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef MESHDATA_H_
#define MESHDATA_H_

#include <vector>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

class MeshData : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("MeshData")
public:
	MeshData(int numVertices);
	virtual ~MeshData();

	void AddGPUBuffer(VABPtr gpuBuffer);

	const std::vector<VABPtr>& getGpuBuffers() const {
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

	std::vector<VABPtr> gpuBuffers;
};

} /* namespace glove */

#endif /* MESHDATA_H_ */
