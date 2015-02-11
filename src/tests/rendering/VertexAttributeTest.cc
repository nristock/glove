#include <gmock/gmock.hpp>

#include <glove/rendering/vertex/VertexAttribute.hpp>
#include <glove/rendering/vertex/VertexAttributeUtils.hpp>

namespace glove {
TEST(VertexAttributeTest, ConstructorStoresBufferIndexOffsetDataTypeAndSemantic) {
    VertexAttribute referenceAttribute({0, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});

    EXPECT_EQ(0, referenceAttribute.GetBufferIndex());
    EXPECT_EQ(0, referenceAttribute.GetByteOffset());
    EXPECT_EQ(VertexAttributeType::FLOAT3, referenceAttribute.GetType());
    EXPECT_EQ(VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetComponentCount(),
              referenceAttribute.GetNumberOfComponents());
    EXPECT_EQ(VertexAttributeUtils<VertexAttributeType::FLOAT3>::GetTypeSize(), referenceAttribute.GetSizeInBytes());
    EXPECT_EQ(VertexAttributeSemantic::POSITION, referenceAttribute.GetSemantic());
}

TEST(VertexAttributeTest, ComparisonOperator) {
    VertexAttribute referenceAttribute({0, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});
    VertexAttribute correctAttribute({0, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});

    VertexAttribute wrongBufferBinding({1, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});
    VertexAttribute wrongOffset({0, 1, VertexAttributeType::FLOAT3, VertexAttributeSemantic::POSITION});
    VertexAttribute wrongAttributeType({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    VertexAttribute wrongSemantic({0, 0, VertexAttributeType::FLOAT3, VertexAttributeSemantic::COLOR});

    EXPECT_TRUE(correctAttribute == referenceAttribute);

    EXPECT_FALSE(wrongBufferBinding == referenceAttribute);
    EXPECT_FALSE(wrongOffset == referenceAttribute);
    EXPECT_FALSE(wrongAttributeType == referenceAttribute);
    EXPECT_FALSE(wrongSemantic == referenceAttribute);
}
}