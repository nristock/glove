#include "Mesh.h"

#include "core/GloveCore.h"
#include <core/rendering/RenderOperation.h>
#include <core/rendering/IRenderer.h>

#include "shader/ShaderProgram.h"
#include "shader/Material.h"

#include <core/rendering/FrameData.h>
#include <core/rendering/vertex/VertexData.h>
#include <core/rendering/vertex/IndexData.h>

namespace glove {

Mesh::Mesh(const RendererPtr& renderer, const IGpuBufferManagerPtr gpuBufferManager, MaterialPtr material)
    : GameComponent(), renderer(renderer), gpuBufferManager(gpuBufferManager), material(material), EnableProfilable() {
    shader = material->GetShader();

    vertexData = VertexDataPtr(new VertexData());
}

Mesh::~Mesh() {}

void Mesh::Refresh() { renderer->CreateVertexAttributeMappings(this); }

void Mesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
    renderOp.vertexData = vertexData.get();
    renderOp.indexData = indexData.get();
    renderOp.material = material.get();
}

void Mesh::CreateIndexData() { indexData = IndexDataPtr(new IndexData(gpuBufferManager)); }

} /* namespace glove */
