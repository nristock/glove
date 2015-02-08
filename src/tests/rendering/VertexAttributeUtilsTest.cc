#include <vendor/gtest/gtest.h>

#include <glove/rendering/vertex/VertexAttributeUtils.h>

namespace glove {
TEST(VertexAttributeUtilsTypeSizeTests, SizeOfFloat3) {
    ASSERT_EQ(sizeof(float) * 3, VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize());
}

TEST(VertexAttributeUtilsTypeSizeTests, SizeOfFloat4) {
    ASSERT_EQ(sizeof(float) * 4, VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetTypeSize());
}

TEST(VertexAttributeUtilsTypeComponentCountTests, ComponentCountOfFloat3) {
    ASSERT_EQ(3, VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetComponentCount());
}

TEST(VertexAttributeUtilsTypeComponentCountTests, ComponentCountOfFloat4) {
    ASSERT_EQ(4, VertexAttributeUtils<VertexAttributeType::FLOAT4>::GetComponentCount());
}
}