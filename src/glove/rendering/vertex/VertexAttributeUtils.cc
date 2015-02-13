#include "glove/rendering/vertex/VertexAttributeUtils.hpp"

namespace glove {

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT2>::GetTypeSize() {
    return 2 * sizeof(float);
}

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT2>::GetComponentCount() {
    return 2;
}

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize() {
    return 3 * sizeof(float);
}

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetComponentCount() {
    return 3;
}

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetTypeSize() {
    return 4 * sizeof(float);
}

template <> std::size_t VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetComponentCount() {
    return 4;
}
}