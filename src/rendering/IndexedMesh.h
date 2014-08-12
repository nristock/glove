/*
 * IndexedMesh.h
 *
 *  Created on: Aug 18, 2014
 *      Author: monofraps
 */

#ifndef INDEXEDMESH_H_
#define INDEXEDMESH_H_

#include "Mesh.h"
#include "IndexedMeshData.h"

#include "../shader/Shader.h"

namespace glove {
namespace gl {
namespace rendering {

class IndexedMesh: public Mesh {
public:
	IndexedMesh(IndexedMeshDataPtr indexedMeshData, shader::ShaderPtr shader);
	virtual ~IndexedMesh();

	virtual void Render();

private:
	IndexedMeshDataPtr indexedMeshData;
};

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */

#endif /* INDEXEDMESH_H_ */
