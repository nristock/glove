#pragma once

#include <memory>
#include <vector>

#include "glove/BlueDwarfApi.hpp"

#include "glove/rendering/VertexLayout.hpp"

namespace BlueDwarf {
class VertexBinding;
class ShaderParameterMap;
class RenderResourceFactory;

class VertexBuffer;
using VertexBufferHandle = std::shared_ptr<VertexBuffer>;

class BD_API_EXPORT VertexBindingFactory {
  public:
    virtual ~VertexBindingFactory() = default;

    std::unique_ptr<VertexBinding> CreateBinding(const ShaderParameterMap& shaderParameters, const RenderResourceFactory& resourceFactory);

    const VertexLayout& GetVertexLayout() const {
        return vertexLayout;
    }

    VertexLayout& GetVertexLayout() {
        return vertexLayout;
    }

    void SetVertexLayout(const VertexLayout& vertexLayout) {
        VertexBindingFactory::vertexLayout = vertexLayout;
    }

    const std::vector<VertexBufferHandle>& GetVertexStreams() const {
        return vertexStreams;
    }

    void SetVertexStreams(const std::vector<VertexBufferHandle>& vertexStreams) {
        VertexBindingFactory::vertexStreams = vertexStreams;
    }

  protected:
    VertexLayout vertexLayout;
    std::vector<VertexBufferHandle> vertexStreams;
};

} /* namespace BlueDwarf */