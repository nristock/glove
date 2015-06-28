#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"
#include "glove/rendering/VertexBindingFactory.hpp"
#include "glove/rendering/MeshBatch.hpp"
#include "glove/rendering/GenericGpuBufferWrapper.hpp"

class MeshMaterialProxy;

namespace BlueDwarf {

class FullscreenQuad {
  public:
    void CreateResources(const RenderResourceFactory& resourceFactory);

    void Draw(RenderCommandList& cmdList, Texture2D::Handle texture);

  private:
    VertexBindingFactory vertexBindingFactory;
    VertexBindingHandle vertexBinding;

  private:
    std::shared_ptr<MeshMaterialProxy> materialProxy;

    std::unique_ptr<GenericIndexBufferWrapper> meshIndexBuffer;
    std::unique_ptr<GenericVertexBufferWrapper> meshVertexBuffer;
};

class BD_API_EXPORT PrimitiveDrawUtils {
  public:
    PrimitiveDrawUtils(RenderResourceFactory& resourceFactory);

    void DrawFullscreenQuad(RenderCommandList& cmdList, Texture2DHandle texture);

  private:
    std::shared_ptr<FullscreenQuad> fullscreenQuad;
};

} /* namespace BlueDwarf */