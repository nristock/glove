#include "VertexAttribute.h"

namespace glove {

VertexAttribute::VertexAttribute(size_t binding, size_t offset, VertexAttributeType attributeType, VertexAttributeSemantic attributeSemantic)
        : binding(binding),
          offset(offset),
          attributeType(attributeType),
          attributeSemantic(attributeSemantic),
          EnableProfilable() {

}

VertexAttribute::~VertexAttribute() {

}

size_t VertexAttribute::GetNumberOfComponents() const {
    switch (attributeType) {
        case VAT_FLOAT3:
            return 3;
        case VAT_FLOAT4:
            return 4;
    }
}

size_t VertexAttribute::GetSize(VertexAttributeType attributeType) {
    switch (attributeType) {
        case VAT_FLOAT3:
            return 3 * sizeof(float);
        case VAT_FLOAT4:
            return 4 * sizeof(float);
    }
}

size_t VertexAttribute::GetSize() const {
    return VertexAttribute::GetSize(attributeType);
}

} // namespace glove