#include "glove/rendering/VertexBindingFactory.hpp"
#include "glove/rendering/ShaderParameter.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"
#include "glove/rendering/VertexBinding.hpp"
#include "glove/rendering/VertexLayout.hpp"

namespace glove {
std::unique_ptr<VertexBinding> VertexBindingFactory::CreateBinding(const ShaderParameterMap& shaderParameters,
                                                                   const RenderResourceFactory& resourceFactory) {
    auto vertexBindingBuilder = VertexBinding::Builder();

    vertexBindingBuilder.AddVertexStreams(vertexStreams);

    for(const auto& vertexElement : vertexLayout.GetElements()) {
        vertexBindingBuilder.AddBinding(vertexElement, shaderParameters.GetAttributeIndexFor(vertexElement.semantic));
    }

    return std::move(vertexBindingBuilder.Finalize(resourceFactory));
}
} /* namespace glove */