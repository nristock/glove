#include <gmock/gmock.hpp>

#include <glove/rendering/mesh/Mesh.hpp>
#include <glove/rendering/RenderOperation.hpp>

#include "tests/rendering/mock/MockVertexData.hpp"
#include "tests/rendering/mock/MockIndexData.hpp"
#include "tests/rendering/mock/MockMesh.hpp"

namespace glove {
TEST(MeshTest, ConstructorStoresVertexAndIndexData) {
    IIndexDataPtr indexData(new MockIndexData());
    IVertexDataPtr vertexData(new MockVertexData());

    MockMesh mesh(vertexData, indexData);

    EXPECT_EQ(nullptr, mesh.GetMaterial().get());
    EXPECT_EQ(indexData, mesh.GetIndexData());
    EXPECT_EQ(vertexData, mesh.GetVertexData());
}
}