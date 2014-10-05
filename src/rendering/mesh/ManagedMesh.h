#ifndef RENDERING_MESH_MANAGEDMESH_H_
#define RENDERING_MESH_MANAGEDMESH_H_

#include "core/GloveFwd.h"
#include "core/RenderOperation.h"

#include "graph/GameComponent.h"

#include "rendering/IRenderable.h"
#include "rendering/mesh/IMesh.h"
#include "rendering/vertex/ManagedVertexData.h"
#include "rendering/vertex/ManagedIndexData.h"

namespace glove {

/** Represents a mesh using managed data (ManagedVertexData and ManagedIndexData) */
template<class VertexLayoutType> class ManagedMesh : public GameComponent, public IRenderable, public IMesh, public std::enable_shared_from_this<ManagedMesh<VertexLayoutType>> {
	GLOVE_MEM_ALLOC_FUNCS("ManagedMesh")
public:
	typedef std::shared_ptr<ManagedVertexData<VertexLayoutType>> ManagedVertexDataPtr;

	ManagedMesh(MaterialPtr material) : GameComponent(), material(material) {
		shader = material->GetShader();

		managedVertexData = ManagedVertexDataPtr(new ManagedVertexData<VertexLayoutType>());
		vertexData = std::dynamic_pointer_cast<VertexData>(managedVertexData);
	}

	virtual ~ManagedMesh() {	}
	
	virtual void Refresh() {
		GloveCore::Instance()->GetRenderer()->CreateVertexAttributeMappings(this);
	}

	virtual const MaterialPtr& GetMaterial() const { return material; }

	virtual const VertexDataPtr& GetVertexData() const { return vertexData; }
	virtual const IndexDataPtr& GetIndexData() const { return indexData; }
	virtual const ShaderProgramPointer& GetShader() const { return shader; }

	virtual const ManagedVertexDataPtr& GetManagedVertexData() const { return managedVertexData; }
	virtual const ManagedIndexDataPtr& GetManagedIndexData() const { return managedIndexData; }

	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
		renderOp.vertexData = vertexData.get();
		renderOp.indexData = indexData.get();
		renderOp.material = material.get();
	}
	
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) = 0;

	virtual void CreateIndexData() {
		managedIndexData = ManagedIndexDataPtr(new ManagedIndexData());
		indexData = std::dynamic_pointer_cast<IndexData>(managedIndexData);
	}
protected:
	ManagedVertexDataPtr managedVertexData;
	ManagedIndexDataPtr managedIndexData;
	VertexDataPtr vertexData;
	IndexDataPtr indexData;

	MaterialPtr material;
	ShaderProgramPointer shader;
};


} // namespace glove

#endif