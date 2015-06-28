#pragma once

#include <vector>
#include <glove/CommonTypes.hpp>

#include "glove/BlueDwarfApi.hpp"
#include "glove/rendering/ShaderParameter.hpp"

namespace BlueDwarf {

/**
* The type of a VertexElement which is used to compute element sizes.
*/
enum class VertexElementType : uint8 { None, Float1, Float2, Float3, PackedNormal, Color, Short2, Short4 };

/**
* A VertexElement describes a single component of a VertexLayout.
*
* This class corresponds to the location of a vertex component in a vertex stream (e.g. in a VertexBuffer).
*/
struct BD_API_EXPORT VertexElement {
    VertexElement(uint8 offset, uint8 streamIndex, uint16 stride, VertexElementType const& type, ShaderParameterSemantic const& semantic)
            : offset(offset), streamIndex(streamIndex), stride(stride), type(type), semantic(semantic) {}

    uint8 offset;
    uint8 streamIndex;
    uint16 stride;
    VertexElementType type;
    ShaderParameterSemantic semantic;
};

/**
* A VertexLayout describes how a Mesh's vertices are mapped to GPU buffers.
*/
class BD_API_EXPORT VertexLayout {
  public:
    /// The default constructor initializes the elements vector with a capacity of 2.
    VertexLayout() { elements.reserve(2); }
    /// Create the layout and reserve @p numElements slots in the elements vector.
    VertexLayout(uint8 numElements) { elements.reserve(numElements); }

    void AddElement(const VertexElement& vertexElement) {
        elements.push_back(vertexElement);
    }

    void AddElement(VertexElement&& vertexElement) {
        elements.push_back(std::forward<VertexElement>(vertexElement));
    }

    const std::vector<VertexElement>& GetElements() {
        return elements;
    }

  protected:
    std::vector<VertexElement> elements;
};

} /* namespace BlueDwarf */