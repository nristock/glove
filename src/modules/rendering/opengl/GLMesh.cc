#include "GLMesh.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveCore.h"
#include <core/rendering/IRenderer.h>
#include <core/rendering/vertex/VertexAttributeType.h>

#include <core/rendering/buffers/IGpuBuffer.h>

#include <core/rendering/vertex/VertexLayout.h>
#include <core/rendering/FrameData.h>
#include <core/rendering/vertex/IVertexData.h>

#include "GLRenderer.h"
#include <core/rendering/shader/IMaterial.h>
#include <core/rendering/shader/IShaderProgram.h>
#include <core/rendering/vertex/IVertexAttributeMapping.h>

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
}
} // namespace glove