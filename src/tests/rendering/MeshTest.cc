#include <vendor/gmock/gmock.h>

#include <core/rendering/mesh/Mesh.h>
#include <core/rendering/RenderOperation.h>

#include "mock/MockVertexData.h"
#include "mock/MockIndexData.h"
#include "mock/MockMesh.h"

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