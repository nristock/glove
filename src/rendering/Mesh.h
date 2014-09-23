/*
 * MeshRenderer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"
#include "graph/GameComponent.h"
#include "IRenderable.h"

namespace glove {

class Mesh : public GameComponent, public IRenderable {
	GLOVE_MEM_ALLOC_FUNCS("Mesh")
public:
	Mesh(MeshDataPtr meshData, MaterialPtr material, GameObjectPtr parent);
	virtual ~Mesh();
	
	void GenerateAttribAssociations();

	virtual void SetupRender(FrameData& frameData);
	virtual void PreRender(FrameData& frameData) {}
	virtual void OnRender(FrameData& frameData);
	virtual void PostRender(FrameData& frameData) {}

	virtual void Render(FrameData& frameData);

	virtual MaterialPtr GetMaterial() const { return material; }
	virtual MeshDataPtr GetMeshData() const { return meshData; }

protected:
	GLuint vertexArrayId;

	MeshDataPtr meshData;
	MaterialPtr material;
	ShaderProgramPointer shader;
};

} /* namespace glove */

#endif /* MESHRENDERER_H_ */
