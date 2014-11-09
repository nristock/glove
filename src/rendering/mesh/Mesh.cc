#include "Mesh.h"

#include "core/GloveCore.h"
#include "core/RenderOperation.h"
#include "core/IRenderer.h"

#include "shader/ShaderProgram.h"
#include "shader/Material.h"

#include "rendering/FrameData.h"
#include "rendering/vertex/VertexData.h"
#include "rendering/vertex/IndexData.h"

namespace glove {

Mesh::Mesh(const RendererPtr& renderer, const GpuBufferManagerPtr gpuBufferManager, MaterialPtr material) : GameComponent(), renderer(renderer), gpuBufferManager(gpuBufferManager), material(material), EnableProfilable() {
    shader = material->GetShader();

    vertexData = VertexDataPtr(new VertexData());
}

Mesh::~Mesh() {

}

void Mesh::Refresh() {
    renderer->CreateVertexAttributeMappings(this);
}

void Mesh::SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
    renderOp.vertexData = vertexData.get();
    renderOp.indexData = indexData.get();
    renderOp.material = material.get();
}

void Mesh::CreateIndexData() {
    indexData = IndexDataPtr(new IndexData(gpuBufferManager));
}

} /* namespace glove */
