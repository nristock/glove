#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "glove/GloveApi.hpp"
#include "glove/CommonTypes.hpp"
#include "glove/rendering/VertexLayout.hpp"

namespace glove {
struct VertexElement;
struct ShaderParameter;

class VertexBuffer;
using VertexBufferHandle = std::shared_ptr<VertexBuffer>;

class RenderResourceFactory;

class RenderCommandList;

/**
* A VertexBinding defines the relation between a shader and a VertexBindingFactory. Implementation details are up to the
* renderer implementation. Thus, either a RenderResourceFactory or the Builder should be used to create instances of
* this class.
*/
class GLOVE_API_EXPORT VertexBinding {
  public:
    struct Builder {
        Builder& AddBinding(const VertexElement& vertexElement, uint8 shaderAttributeIndex) {
            shaderAttributeBindings.insert({shaderAttributeIndex, vertexElement});
            return *this;
        }

        Builder& AddVertexStream(VertexBufferHandle stream) {
            vertexStreams.push_back(std::move(stream));
            return *this;
        }

        Builder& AddVertexStreams(std::vector<VertexBufferHandle> streams) {
            for(const auto& vertexStream : streams) {
                vertexStreams.push_back(vertexStream);
            }
            return *this;
        }

        std::unique_ptr<VertexBinding> Finalize(const RenderResourceFactory& resourceFactory);

        std::unordered_map<uint8, VertexElement> shaderAttributeBindings;
        std::vector<VertexBufferHandle> vertexStreams;
    };

    virtual ~VertexBinding() = default;

  protected:
    VertexBinding(const std::unordered_map<uint8, VertexElement>& shaderAttributeBindings,
                  const std::vector<VertexBufferHandle>& vertexStreams)
        : shaderAttributeBindings(shaderAttributeBindings), vertexStreams(vertexStreams) {}

    const std::unordered_map<uint8, VertexElement> shaderAttributeBindings;
    const std::vector<VertexBufferHandle> vertexStreams;
};

} /* namespace glove */