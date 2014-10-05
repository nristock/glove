/*
 * MeshRenderer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */
#include "Mesh.h"

#include "core/GloveCore.h"
#include "core/RenderOperation.h"

#include "shader/ShaderProgram.h"
#include "shader/Material.h"

#include "rendering/FrameData.h"
#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/IndexData.h"

namespace glove {

Mesh::Mesh(MaterialPtr material) : GameComponent(), material(material) {
	shader = material->GetShader();

	vertexData = VertexDataPtr(new VertexData());
}

Mesh::~Mesh() {
	
}

void Mesh::Refresh() {
	GloveCore::Instance()->GetRenderer()->CreateVertexAttributeMappings(this);
}

void Mesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
	renderOp.vertexData = vertexData.get();
	renderOp.indexData = indexData.get();
	renderOp.material = material.get();
}

void Mesh::CreateIndexData() {
	indexData = IndexDataPtr(new IndexData());
}

} /* namespace glove */
