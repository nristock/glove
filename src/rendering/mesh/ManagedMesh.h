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
template<class VertexLayoutType> class ManagedMesh : public GameComponent, public IRenderable, public IMesh, public std::enable_shared_from_this<Mesh> {
	GLOVE_MEM_ALLOC_FUNCS("ManagedMesh")
public:
	typedef std::shared_ptr<ManagedVertexData<VertexLayoutType>> ManagedVertexDataPtr;

	ManagedMesh(MaterialPtr material, GameObjectPtr parent) : GameComponent(parent), material(material) {
		shader = material->GetShader();

		vertexData = ManagedVertexDataPtr(new ManagedVertexData<VertexLayoutType>());
	}

	virtual ~ManagedMesh() {	}
	
	virtual void Refresh() {
		GloveCore::Instance()->GetRenderer()->CreateVertexAttributeMappings(this);
	}

	virtual MaterialPtr GetMaterial() const { return material; }

	virtual const VertexDataPtr& GetVertexData() const { return std::dynamic_pointer_cast<VertexData>(vertexData); }
	virtual const IndexDataPtr& GetIndexData() const { return std::dynamic_pointer_cast<IndexData>(indexData); }
	virtual const ShaderProgramPointer& GetShader() const { return shader; }

	virtual const ManagedVertexDataPtr& GetManagedVertexData() const { return vertexData; }
	virtual const ManagedIndexDataPtr& GetManagedIndexData() const { return indexData; }

	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
		renderOp.vertexData = (VertexData*)vertexData.get();
		renderOp.indexData = (IndexData*)indexData.get();
		renderOp.material = material.get();
	}
	
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) = 0;

	virtual void CreateIndexData() {
		indexData = ManagedIndexDataPtr(new ManagedIndexData());
	}
protected:
	ManagedVertexDataPtr vertexData;
	ManagedIndexDataPtr indexData;
	MaterialPtr material;
	ShaderProgramPointer shader;
};


} // namespace glove

#endif