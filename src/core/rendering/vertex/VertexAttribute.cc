#include <core/GloveException.h>
#include "VertexAttribute.h"
#include "VertexAttributeUtils.h"

namespace glove {

VertexAttribute::VertexAttribute(std::size_t binding, std::size_t offset, VertexAttributeType attributeType, VertexAttributeSemantic attributeSemantic) :
          binding(binding),
          offset(offset),
          attributeType(attributeType),
          attributeSemantic(attributeSemantic),
          EnableProfilable() {

}

VertexAttribute::~VertexAttribute() {

}

std::size_t VertexAttribute::GetNumberOfComponents() const {
    switch (attributeType) {
        case VAT_FLOAT3:
            return 3;
        case VAT_FLOAT4:
            return 4;
    }

    throw GLOVE_EXCEPTION("Unexpected control flow in VertexAttribute::GetNumberOfComponents");
}

std::size_t VertexAttribute::GetSize() const {
    return VertexAttributeUtils::GetAttributeTypeSize(attributeType);
}

VertexAttributeSemantic VertexAttribute::GetSemantic() const {
    return attributeSemantic;
}

VertexAttributeType VertexAttribute::GetType() const {
    return attributeType;
}

size_t VertexAttribute::GetOffset() const {
    return offset;
}

size_t VertexAttribute::GetBindingSlot() const {
    return binding;
}
} // namespace glove