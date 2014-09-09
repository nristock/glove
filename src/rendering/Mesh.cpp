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
#include "MeshData.h"
#include "buffers/VertexAttributeBuffer.h"

namespace glove {

Mesh::Mesh(MeshDataPtr meshData, ShaderPtr shader) {
	glGenVertexArrays(1, &vertexArrayId);

	this->meshData = meshData;
	this->shader = shader;

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

void Mesh::SetMeshData(MeshDataPtr meshData) {
	this->meshData = meshData;
}

void Mesh::SetShader(ShaderPtr shader) {
	this->shader = shader;
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

void Mesh::Render() {
	shader->Enable();
	glBindVertexArray(vertexArrayId);

	glDrawArrays(GL_TRIANGLES, 0, meshData->getNumVertices());
}

} /* namespace glove */
