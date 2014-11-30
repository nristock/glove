#include "VertexAttribute.h"

#include <core/GloveException.h>

#include "VertexAttributeUtils.h"

namespace glove {

VertexAttribute::VertexAttribute(std::size_t bufferIndex, std::size_t offset, VertexAttributeType dataType,
                                 VertexAttributeSemantic semantic)
    : bufferIndex(bufferIndex), offset(offset), dataType(dataType), semantic(semantic) {
}

std::size_t VertexAttribute::GetSizeInBytes() const {
    switch (dataType) {
    case VertexAttributeType::FLOAT3:
        return VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize();
    case VertexAttributeType::FLOAT4:
        return VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetTypeSize();
    }
}

VertexAttributeSemantic VertexAttribute::GetSemantic() const {
    return semantic;
}

VertexAttributeType VertexAttribute::GetType() const {
    return dataType;
}

std::size_t VertexAttribute::GetByteOffset() const {
    return offset;
}

std::size_t VertexAttribute::GetBufferIndex() const {
    return bufferIndex;
}

std::size_t VertexAttribute::GetNumberOfComponents() const {
    switch (dataType) {
    case VertexAttributeType::FLOAT3:
        return VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetComponentCount();
    case VertexAttributeType::FLOAT4:
        return VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetComponentCount();
    }
}

bool VertexAttribute::operator==(const VertexAttribute& other) const {
    return bufferIndex == other.bufferIndex && offset == other.offset && dataType == other.dataType &&
           semantic == other.semantic;
}

} // namespace glove