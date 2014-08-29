/*
 * IndexedMesh.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef INDEXEDMESH_H_
#define INDEXEDMESH_H_

#include "core/GloveFwd.h"

#include "Mesh.h"

namespace glove {

class IndexedMesh: public Mesh {
	GLOVE_MEM_ALLOC_FUNCS("IndexedMesh")
public:
	IndexedMesh(IndexedMeshDataPtr indexedMeshData, ShaderPtr shader);
	virtual ~IndexedMesh();

	virtual void Render();

private:
	IndexedMeshDataPtr indexedMeshData;
};

} /* namespace glove */

#endif /* INDEXEDMESH_H_ */
