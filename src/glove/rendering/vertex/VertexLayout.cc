#include "glove/rendering/vertex/VertexLayout.hpp"

namespace glove {

void VertexLayout::AddAttribute(const VertexAttribute& element) {
    attributes.push_back(element);

    strideMap[element.GetBufferIndex()] += element.GetSizeInBytes();
}

const VertexAttribute& VertexLayout::GetAttribute(std::size_t index) const {
    assert(index < GetAttributeCount());

    VertexAttributeList::const_iterator it = std::next(attributes.begin(), index);
    return *it;
}

std::size_t VertexLayout::GetAttributeCount() const {
    return attributes.size();
}

const std::size_t VertexLayout::GetStrideForBufferIndex(std::size_t bufferIndex) {
    return strideMap[bufferIndex];
}

bool VertexLayout::operator==(const VertexLayout& other) const {
    return attributes == other.attributes;
}

} // namespace glove