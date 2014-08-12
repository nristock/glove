/*
 * IndexedMeshData.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef INDEXEDMESHDATA_H_
#define INDEXEDMESHDATA_H_

#include <memory>
#include "../shader/MeshData.h"
#include "../buffers/GPUBuffer.h"

namespace glove {
namespace gl {
namespace rendering {

class IndexedMeshData: public shader::MeshData {
public:
	IndexedMeshData(int numVertices);
	virtual ~IndexedMeshData();

	void SetIndices(GLuint* indexData, int numberOfIndices);

	const buffers::GPUBufferPtr& getIndexBuffer() const {
		return indexBuffer;
	}

	int getNumIndices() const {
		return numIndices;
	}

private:
	buffers::GPUBufferPtr indexBuffer;
	int numIndices;
};

typedef std::shared_ptr<IndexedMeshData> IndexedMeshDataPtr;

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */

#endif /* INDEXEDMESHDATA_H_ */
