#pragma once

#include <memory>

#include "glove/GloveApi.hpp"
#include "GpuBuffer.hpp"
#include "RenderResourceFactory.hpp"

namespace glove {
using VertexBufferHandle = std::shared_ptr<VertexBuffer>;
using IndexBufferHandle = std::shared_ptr<IndexBuffer>;

class GLOVE_API_EXPORT GenericVertexBufferWrapper {
  public:
    GenericVertexBufferWrapper(const RenderResourceFactory& resourceFactory);

    VertexBufferHandle GetHardwareResource() const;

    template<class TVertex> void SetVertices(const std::vector<TVertex>& vertices) {
        vertexBuffer->Store(vertices.size() * sizeof(TVertex), static_cast<void*>(vertices.data()));
    }
    template<class TVertex> void SetVertices(std::vector<TVertex>&& vertices) {
        vertexBuffer->Store(vertices.size() * sizeof(TVertex), static_cast<void*>(vertices.data()));
    }

  private:
    VertexBufferHandle vertexBuffer;
};

class GLOVE_API_EXPORT GenericIndexBufferWrapper {
  public:
    GenericIndexBufferWrapper(const RenderResourceFactory& resourceFactory);

    IndexBufferHandle GetHardwareResource() const;

    template<class TIndex> void SetIndices(const std::vector<TIndex>& indices) {
        indexBuffer->Store(indices.size() * sizeof(TIndex), static_cast<void*>(indices.data()));
    }
    template<class TIndex> void SetIndices(std::vector<TIndex>&& indices) {
        indexBuffer->Store(indices.size() * sizeof(TIndex), static_cast<void*>(indices.data()));
    }

  private:
    IndexBufferHandle indexBuffer;
};

} /* namespace glove */