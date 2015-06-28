#include <glove/rendering/VertexBindingFactory.hpp>
#include <glove/rendering/Material.hpp>
#include "glove/rendering/MeshBatch.hpp"
#include "glove/geometry/MeshComponent.hpp"
#include "glove/rendering/PrimitiveDrawInterface.hpp"

#include "glove/world/scene/SceneProxy.hpp"
#include "glove/rendering/MaterialProxy.hpp"
#include "glove/rendering/Shader.hpp"
#include "glove/rendering/GpuBuffer.hpp"
#include "glove/rendering/VertexBinding.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"

namespace BlueDwarf {


//class MeshMaterial : public Material {
//  public:
//    MeshMaterial(const ShaderProgramHandle& shaderProgram) : Material(shaderProgram) {}
//
//    virtual MaterialProxyHandle CreateRenderProxy() override {
//        auto mvpParameter = shaderProgram->GetUniformParameterIndex("MatMVP");
//        return MaterialProxyHandle(
//            new MaterialProxy(shaderProgram, {}, UniformParameter::Handle{new UniformParameter(mvpParameter)}));
//    };
//};


SceneProxyHandle MeshComponent::CreateSceneProxy() {
    return std::make_shared<MeshSceneProxy>(material);
}

void MeshComponent::Tick(double time) {
}

void MeshSceneProxy::CreateResources(const RenderResourceFactory& resourceFactory) {
    materialProxy = sourceMaterial->CreateRenderProxy();

    meshIndexBuffer = std::unique_ptr<MeshIndexBuffer>(new MeshIndexBuffer(resourceFactory));
    InitIndexBuffer(*meshIndexBuffer);

    meshVertexBuffer = std::unique_ptr<MeshVertexBuffer>(new MeshVertexBuffer(resourceFactory));
    InitVertexBuffer(*meshVertexBuffer);

    vertexBindingFactory.SetVertexStreams({meshVertexBuffer->GetVertexBuffer()});

    VertexLayout& vertexLayout = vertexBindingFactory.GetVertexLayout();
    vertexLayout.AddElement(
            {0, 0, sizeof(float) * 3, VertexElementType::Float3, ShaderParameterSemantic::Position});

    vertexBinding = vertexBindingFactory.CreateBinding(
            materialProxy->GetShaderProgram()->GetVertexShader()->GetParameterMap(), resourceFactory);
}

void MeshSceneProxy::DrawDynamicElements(PrimitiveDrawInterface& pdi, const SceneView& view) {
    MeshBatch meshBatch{vertexBinding, materialProxy};
    meshBatch.AddElement({meshIndexBuffer->GetIndexBuffer(), 2, 0, 3, GetTransform().ToMatrix()});

    pdi.DrawMesh(meshBatch);
}

MeshSceneProxy::MeshVertexBuffer::MeshVertexBuffer(const RenderResourceFactory& resourceFactory) {
    vertexBuffer = resourceFactory.CreateVertexBuffer();
}

MeshSceneProxy::MeshIndexBuffer::MeshIndexBuffer(const RenderResourceFactory& resourceFactory) {
    indexBuffer = resourceFactory.CreateIndexBuffer();
}

void MeshSceneProxy::InitVertexBuffer(MeshSceneProxy::MeshVertexBuffer& vertexBuffer) {
    std::vector<MeshVertex> array{MeshVertex{-0.5f, -1, 0}, MeshVertex{0.5f, -1, 0}, MeshVertex{0, 1, 0}};
    vertexBuffer.StoreVertices(std::move(array));
}

void MeshSceneProxy::MeshVertexBuffer::StoreVertices(std::vector<MeshSceneProxy::MeshVertex>&& vertices) const {
    vertexBuffer->Store(vertices.size() * sizeof(MeshVertex), vertices.data());
}

void MeshSceneProxy::MeshIndexBuffer::StoreIndices(std::vector<ushort>&& indices) const {
    indexBuffer->Store(sizeof(ushort) * indices.size(), indices.data());
}

void MeshSceneProxy::InitIndexBuffer(MeshSceneProxy::MeshIndexBuffer& indexBuffer) {
    std::vector<ushort> indices = {0, 1, 2};
    indexBuffer.StoreIndices(std::move(indices));
}

void MeshComponent::SetMaterial(Material::Handle material) {
    this->material = material;
}
}