#include <random>
#include <chrono>

#include <vendor/gmock/gmock.h>

#include <core/rendering/vertex/VertexLayout.h>

namespace glove {
TEST(VertexLayoutTest, NewVertexLayoutHasNoElements) {
    VertexLayout layout;

    EXPECT_EQ(0, layout.GetAttributeCount());
}

TEST(VertexLayoutTest, CanAddElements) {
    std::default_random_engine generator(
        static_cast<ulong>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(0, 1000);

    VertexLayout layout;

    VertexAttribute attribute({static_cast<std::size_t>(distribution(generator)),
                               static_cast<std::size_t>(distribution(generator)), VertexAttributeType::FLOAT3,
                               VertexAttributeSemantic::POSITION});
    layout.AddAttribute(attribute);

    EXPECT_EQ(1, layout.GetAttributeCount());
    EXPECT_EQ(attribute, layout.GetAttribute(0));
}

TEST(VertexLayoutTest, UpdatesStrideForBuffersWhenAddindElements) {
    VertexLayout layout;

    VertexAttribute attribute1({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout.AddAttribute(attribute1);
    VertexAttribute attribute2({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout.AddAttribute(attribute2);
    VertexAttribute attribute3({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout.AddAttribute(attribute3);

    EXPECT_EQ(sizeof(float) * 4, layout.GetStrideForBufferIndex(0));
    EXPECT_EQ(sizeof(float) * 8, layout.GetStrideForBufferIndex(1));
}

TEST(VertexLayoutTest, ComparisonOperatorComparesAttributeList) {
    VertexLayout layout1;
    VertexAttribute attribute1({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute1);
    VertexAttribute attribute2({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute2);
    VertexAttribute attribute3({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout1.AddAttribute(attribute3);

    VertexLayout layout2;
    layout2.AddAttribute(attribute1);
    layout2.AddAttribute(attribute2);
    layout2.AddAttribute(attribute3);

    EXPECT_TRUE(layout1 == layout2);
}

TEST(VertexLayoutTest, ComparisonOperatorChecksAttributeListElementEquality) {
    VertexLayout layout1;
    VertexAttribute attribute1({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute1);
    VertexAttribute attribute2({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute2);
    VertexAttribute attribute3({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout1.AddAttribute(attribute3);

    VertexLayout layout2;
    layout2.AddAttribute(attribute1);
    layout2.AddAttribute(attribute2);
    VertexAttribute attribute3b({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout2.AddAttribute(attribute3b);

    EXPECT_FALSE(layout1 == layout2);
}

TEST(VertexLayoutTest, ComparisonOperatorChecksAttributeListLength) {
    VertexLayout layout1;
    VertexAttribute attribute1({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute1);
    VertexAttribute attribute2({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::POSITION});
    layout1.AddAttribute(attribute2);
    VertexAttribute attribute3({1, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout1.AddAttribute(attribute3);

    VertexLayout layout2;
    layout2.AddAttribute(attribute1);
    layout2.AddAttribute(attribute2);
    layout2.AddAttribute(attribute3);
    VertexAttribute attribute3b({0, 0, VertexAttributeType::FLOAT4, VertexAttributeSemantic::COLOR});
    layout2.AddAttribute(attribute3b);

    EXPECT_FALSE(layout1 == layout2);
}
}