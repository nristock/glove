#pragma once

#include <glove/rendering/PrimitiveDrawInterface.hpp>
#include "glove/BlueDwarfApi.hpp"
#include "glove/world/scene/SceneProxy.hpp"

#include "glove/world/component/EntityComponent.hpp"

namespace BlueDwarf {

class BD_API_EXPORT MeshSceneProxy : public SceneProxy {
  public:
    struct MeshVertex {
        float x, y, z;

        MeshVertex(float x, float y, float z) : x(x), y(y), z(z) {}
    };

    MeshSceneProxy(Material::Handle sourceMaterial) : sourceMaterial(std::move(sourceMaterial)) {}

    virtual void CreateResources(const RenderResourceFactory& resourceFactory) override;

    // TODO move to material
    virtual ShaderParameterMap CreateShaderParameterMap() {
        ShaderParameterMap shaderParameterMap{1};
        shaderParameterMap.AddParameter({0, ShaderParameterSemantic::Position, "InPosition"});
        return shaderParameterMap;
    }

  protected:
    /// Wrapper for hardware resource vertex buffer
    class MeshVertexBuffer {
      public:
        MeshVertexBuffer(const RenderResourceFactory& resourceFactory);
        VertexBufferHandle GetVertexBuffer() const { return vertexBuffer; }
        void StoreVertices(std::vector<MeshVertex>&& vertices) const;

      private:
        VertexBufferHandle vertexBuffer;
    };

    /// Wrapper for hardware resource index buffer
    class MeshIndexBuffer {
      public:
        MeshIndexBuffer(const RenderResourceFactory& resourceFactory);
        IndexBufferHandle GetIndexBuffer() const { return indexBuffer; }
        void StoreIndices(std::vector<ushort>&& indices) const;

      private:
        IndexBufferHandle indexBuffer;
    };


    virtual void InitVertexBuffer(MeshVertexBuffer& vertexBuffer);
    virtual void InitIndexBuffer(MeshIndexBuffer& indexBuffer);

    virtual void DrawDynamicElements(PrimitiveDrawInterface& pdi, const SceneView& view) override;

  private:
    VertexBindingFactory vertexBindingFactory;
    VertexBindingHandle vertexBinding;

    const Material::Handle sourceMaterial;
    MaterialProxyHandle materialProxy;

    std::unique_ptr<MeshIndexBuffer> meshIndexBuffer;
    std::unique_ptr<MeshVertexBuffer> meshVertexBuffer;
};

class BD_API_EXPORT MeshComponent : public EntityComponent {
  public:
    virtual ~MeshComponent() = default;

    virtual void Tick(double time);

    virtual void SetMaterial(Material::Handle material);
    virtual SceneProxyHandle CreateSceneProxy() override;

  private:
    Material::Handle material;
};
}
