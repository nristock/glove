#include "VertexLayout.h"

namespace glove {

VertexLayout::VertexLayout() : EnableProfilable() {

}

VertexLayout::~VertexLayout() {

}

void VertexLayout::AddElement(const VertexAttribute& element) {
    attributeList.push_back(element);
}

void VertexLayout::AddElement(size_t binding, size_t offset, VertexAttributeType attributeType, VertexAttributeSemantic attributeSemantic) {
    attributeList.push_back(VertexAttribute(binding, offset, attributeType, attributeSemantic));
}

const VertexAttribute* VertexLayout::GetAttribute(unsigned short index) const {
    VertexAttributeList::const_iterator it = std::next(attributeList.begin(), index);
    return &(*it);
}

} // namespace glove