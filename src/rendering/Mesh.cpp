/*
 * MeshRenderer.cpp
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#include <GL/glew.h>

#include "../core/GloveObject.h"
#include "Mesh.h"

namespace glove {
namespace gl {
namespace rendering {

Mesh::Mesh(shader::MeshDataPtr meshData, shader::ShaderPtr shader) {
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
			auto attribIdentifier = definition->getAttributeIdentifier();

			auto attribIndex = shader->GetVertexAttributePosition(attribIdentifier);

			glDisableVertexAttribArray(attribIndex);
		}
	}

	glDeleteVertexArrays(1, &vertexArrayId);
}

void Mesh::SetMeshData(shader::MeshDataPtr meshData) {
	this->meshData = meshData;
}

void Mesh::SetShader(shader::ShaderPtr shader) {
	this->shader = shader;
}

void Mesh::GenerateAttribAssociations() {
	glBindVertexArray(vertexArrayId);

	for(auto gpuBuffer : meshData->getGpuBuffers()) {
		gpuBuffer->Bind();

		for (auto it : gpuBuffer->getVertexLayout()) {
			auto definition = it.second;
			auto attribIdentifier = definition->getAttributeIdentifier();

			auto attribIndex = shader->GetVertexAttributePosition(attribIdentifier);
			if (attribIndex < 0) {
				OLOG(warning) << "Vertex Attribute in buffer not mapped to shader attribute index.";
				continue;
			}

			glVertexAttribPointer(attribIndex, definition->getSize(), definition->getType(), definition->getNormalized(), gpuBuffer->getStride(), reinterpret_cast<void*>(definition->getRelativeOffset()));
			glEnableVertexAttribArray(attribIndex);
		}
	}
}

void Mesh::Render() {
	shader->Enable();
	glBindVertexArray(vertexArrayId);

	glDrawArrays(GL_TRIANGLES, 0, meshData->getNumVertices());
}

} /* namespace rendering */
} /* namespace gl */
} /* namespace glove */
