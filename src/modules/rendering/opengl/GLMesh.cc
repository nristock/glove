#include "GLMesh.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glove/GloveCore.h>
#include <glove/rendering/IRenderer.h>
#include <glove/rendering/vertex/VertexAttributeType.h>
#include <glove/rendering/buffers/IGpuBuffer.h>
#include <glove/rendering/vertex/VertexLayout.h>
#include <glove/rendering/FrameData.h>
#include <glove/rendering/vertex/IVertexData.h>
#include <glove/rendering/shader/IMaterial.h>
#include <glove/rendering/shader/IShaderProgram.h>
#include <glove/rendering/vertex/IVertexAttributeMapping.h>

#include "internal/OpenGLWrapper.h"
#include "GLRenderer.h"

namespace {

GLenum TranslateVertexAttributeType(glove::VertexAttributeType attribType) {
    switch (attribType) {
    case glove::VertexAttributeType::FLOAT3:
    case glove::VertexAttributeType::FLOAT4:
        return GL_FLOAT;
    }

    throw GLOVE_EXCEPTION("Unexpected contorl flow.");
}
}

namespace glove {
namespace gl {

GLMesh::GLMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData)
    : Mesh(vertexData, indexData) {
    BindMaterial(material);
}

GLMesh::~GLMesh() {
    for (const std::pair<ContextId, GLuint>& vertexArrayIdContextMapping : vertexArrayIds) {
        GL::DeleteVertexArrays(1, &vertexArrayIdContextMapping.second);
    }
}

void GLMesh::BindMaterial(const IMaterialPtr& material) {
    for (const std::pair<ContextId, GLuint>& contextVAOMapping : vertexArrayIds) {
        InitVertexAttributeObjectStateForContext(contextVAOMapping.first);
    }

    this->material = material;
}

void GLMesh::InitVertexAttributeObjectStateForContext(ContextId contextId) {
    GL::BindVertexArray(GetVertexArrayId(contextId));

    IVertexAttributeMappingPtr shaderProgramAttributeMapping =
        material->GetShaderProgram()->GetVertexAttributeMapping();

    VertexLayout vertexLayout = vertexData->GetVertexLayout();

    for (std::size_t i = 0; i < vertexLayout.GetAttributeCount(); ++i) {
        const VertexAttribute vertexAttribute = vertexLayout.GetAttribute(i);
        SetupVertexAttribute(shaderProgramAttributeMapping, vertexLayout, vertexAttribute);
    }
}

void GLMesh::SetupVertexAttribute(const IVertexAttributeMappingPtr& shaderProgramAttributeMapping,
                                  VertexLayout& vertexLayout, const VertexAttribute& vertexAttribute) {
    const std::size_t bufferIndex = vertexAttribute.GetBufferIndex();
    const IGpuBufferPtr gpuBuffer = vertexData->GetGpuBuffer(bufferIndex);

    gpuBuffer->Bind();

    try {
        GLuint attribIndex = shaderProgramAttributeMapping->GetAttributeLocation(vertexAttribute.GetSemantic());

        GL::VertexAttribPointer(attribIndex, (GLint)vertexAttribute.GetNumberOfComponents(),
                                TranslateVertexAttributeType(vertexAttribute.GetType()), GL_FALSE,
                                (GLsizei)vertexLayout.GetStrideForBufferIndex(bufferIndex),
                                (void*)vertexAttribute.GetByteOffset());
        GL::EnableVertexAttribArray(attribIndex);
    } catch (const GloveException& ex) {
        LOG(logger, error, "Vertex attribute in buffer not mapped to shader attribute index.");
    }
}

void GLMesh::CreateVertexArrayObjectForContext(ContextId contextId) {
    if (vertexArrayIds.count(contextId)) {
    throw GLOVE_EXCEPTION("Cannot create multiple vertex array objects per mesh per context.")
    }

    GLuint temporaryId;
    GL::GenVertexArrays(1, &temporaryId);
    vertexArrayIds[contextId] = temporaryId;
}

const GLuint GLMesh::GetVertexArrayId(ContextId contextId) {
    const GLuint vertexArrayObjectId = vertexArrayIds[contextId];
    return vertexArrayObjectId;
}

void GLMesh::EnsureVertexArrayObjectExistsForContext(ContextId contextId) {
    if (vertexArrayIds.count(contextId)) {
        return;
    }

    CreateVertexArrayObjectForContext(contextId);
    InitVertexAttributeObjectStateForContext(contextId);
}

}
} // namespace glove