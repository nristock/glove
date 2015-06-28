#include "glove/rendering/VertexBinding.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"
#include "glove/rendering/RenderCommandList.hpp"

namespace BlueDwarf {
std::unique_ptr<VertexBinding> VertexBinding::Builder::Finalize(const RenderResourceFactory& resourceFactory) {
    if (vertexStreams.empty()) {
        // todo throw
    }

    return std::move(resourceFactory.CreateVertexBinding(shaderAttributeBindings, vertexStreams));
}

} /* namespace BlueDwarf */