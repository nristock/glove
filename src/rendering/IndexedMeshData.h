/*
 * IndexedMeshData.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef INDEXEDMESHDATA_H_
#define INDEXEDMESHDATA_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveFwd.h"

#include "MeshData.h"

namespace glove {

class IndexedMeshData: public MeshData {
	GLOVE_MEM_ALLOC_FUNCS("IndexedMeshData");
public:
	IndexedMeshData(int numVertices);
	virtual ~IndexedMeshData();

	void SetIndices(GLuint* indexData, int numberOfIndices);

	const GPUBufferPtr& getIndexBuffer() const {
		return indexBuffer;
	}

	int getNumIndices() const {
		return numIndices;
	}

private:
	GPUBufferPtr indexBuffer;
	int numIndices;
};

typedef std::shared_ptr<IndexedMeshData> IndexedMeshDataPtr;

} /* namespace glove */

#endif /* INDEXEDMESHDATA_H_ */
