/*
 * MeshRenderer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */
#include "Mesh.h"

#include <GL/glew.h>

#include "core/GloveObject.h"
#include "shader/ShaderProgram.h"
#include "shader/Material.h"
#include "MeshData.h"
#include "buffers/VertexAttributeBuffer.h"
#include "rendering/FrameData.h"

namespace glove {

Mesh::Mesh(MeshDataPtr meshData, MaterialPtr material) : meshData(meshData), material(material) {
	glGenVertexArrays(1, &vertexArrayId);
	shader = material->GetShader();
	
	GenerateAttribAssociations();
}

Mesh::~Mesh() {
	glBindVertexArray(vertexArrayId);
	
	for (auto gpuBuffer : meshData->getGpuBuffers()) {
		gpuBuffer->Bind();

		for (auto it : gpuBuffer->getVertexLayout()) {
			auto definition = it.second;
			auto attribIdentifier = definition->attributeIdentifier;

			auto attribIndex = shader->GetVertexAttributePosition(attribIdentifier);

			glDisableVertexAttribArray(attribIndex);
		}
	}

	glDeleteVertexArrays(1, &vertexArrayId);
	vertexArrayId = 0;
}

void Mesh::GenerateAttribAssociations() {
	glBindVertexArray(vertexArrayId);
		
	for(auto gpuBuffer : meshData->getGpuBuffers()) {
		gpuBuffer->Bind();

		for (auto it : gpuBuffer->getVertexLayout()) {
			auto definition = it.second;
			auto attribIdentifier = definition->attributeIdentifier;

			auto attribIndex = shader->GetVertexAttributePosition(attribIdentifier);
			if (attribIndex < 0) {
				OLOG(warning, "Vertex Attribute in buffer not mapped to shader attribute index.");
				continue;
			}

			glVertexAttribPointer(attribIndex, definition->size, definition->type, definition->normalized, gpuBuffer->getStride(), reinterpret_cast<void*>(definition->relativeOffset));
			glEnableVertexAttribArray(attribIndex);
		}
	}
}

void Mesh::SetupRender(FrameData& frameData) {
	material->Enable();
	glBindVertexArray(vertexArrayId);

	material->SetMaterialAttribute(MMA_MAT_MVP, frameData.viewProjectionMatrix);
}

void Mesh::OnRender(FrameData& frameData) {
	glDrawArrays(GL_TRIANGLES, 0, meshData->getNumVertices());
}

void Mesh::Render(FrameData& frameData) {
	SetupRender(frameData);
	PreRender(frameData);
	OnRender(frameData);
	PostRender(frameData);
}

} /* namespace glove */
