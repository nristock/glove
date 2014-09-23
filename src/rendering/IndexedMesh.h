#ifndef INDEXEDMESH_H_
#define INDEXEDMESH_H_

#include "core/GloveFwd.h"

#include "Mesh.h"

namespace glove {

class IndexedMesh : public Mesh {
	GLOVE_MEM_ALLOC_FUNCS("IndexedMesh")
public:
	IndexedMesh(IndexedMeshDataPtr indexedMeshData, MaterialPtr material, GameObjectPtr parent);
	virtual ~IndexedMesh();

	virtual void OnRender(FrameData& frameData);

private:
	IndexedMeshDataPtr indexedMeshData;
};

} /* namespace glove */

#endif /* INDEXEDMESH_H_ */
