#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "glove/CommonTypes.hpp"
#include "glove/GloveApi.hpp"
#include "glove/utils/DebugUtils.hpp"
#include "glove/rendering/VertexBindingFactory.hpp"

namespace glove {
class VertexBinding;
using VertexBindingHandle = std::shared_ptr<VertexBinding>;

class IndexBuffer;
using IndexBufferHandle = std::shared_ptr<IndexBuffer>;

class MaterialProxy;
using MaterialProxyHandle = std::shared_ptr<MaterialProxy>;

/**
* The element of a MeshBatch. A MeshBatchElement is immutable once it has been created.
*
* A MeshBatchElement holds information about the indices to use for rendering it.
*/
struct GLOVE_API_EXPORT MeshBatchElement {
  public:
    MeshBatchElement(IndexBufferHandle indexBuffer, uint32 numPrimitives, uint32 firstVertexIndex,
                     uint32 lastVertexIndex, glm::mat4 localToWorld)
        : indexBuffer(indexBuffer), numPrimitives(numPrimitives), firstVertexIndex(firstVertexIndex),
          lastVertexIndex(lastVertexIndex), localToWorld(localToWorld) {
        DebugAssert((bool)indexBuffer);
        DebugAssert(numPrimitives > 0);
        DebugAssert(firstVertexIndex >= 0);
        DebugAssert(lastVertexIndex > firstVertexIndex);
    }

    IndexBufferHandle GetIndexBuffer() const { return indexBuffer; }
    uint32 GetNumPrimitives() const { return numPrimitives; }
    uint32 GetFirstVertexIndex() const { return firstVertexIndex; }
    uint32 GetLastVertexIndex() const { return lastVertexIndex; }
    const glm::mat4& GetLocalToWorld() const { return localToWorld; }

  private:
    const IndexBufferHandle indexBuffer;

    const uint32 numPrimitives;
    const uint32 firstVertexIndex;
    const uint32 lastVertexIndex;

    const glm::mat4 localToWorld;
};

/**
* A MeshBatch is a batch of elements which share the same material and vertex stream but can have different indices.
*/
struct GLOVE_API_EXPORT MeshBatch {
  public:
    MeshBatch(VertexBindingHandle vertexBinding, MaterialProxyHandle materialProxy)
        : vertexBinding(std::move(vertexBinding)), materialProxy(std::move(materialProxy)) {}

    const std::vector<MeshBatchElement>& GetElements() const { return elements; }
    VertexBindingHandle GetVertexBinding() const { return vertexBinding; }
    MaterialProxyHandle GetMaterialProxy() const { return materialProxy; }

    void AddElement(const MeshBatchElement& batchElement) { elements.push_back(batchElement); }

    void AddElement(MeshBatchElement&& batchElement) { elements.push_back(batchElement); }

  private:
    std::vector<MeshBatchElement> elements;
    VertexBindingHandle vertexBinding;
    MaterialProxyHandle materialProxy;
};
} // namespace glove
