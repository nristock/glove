#include <gmock/gmock.hpp>

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/mesh/Mesh.hpp>

namespace glove {
class MockMesh : public Mesh {
  public:
    MockMesh(const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData) : Mesh(vertexData, indexData) {}

    MOCK_METHOD1(BindMaterial, void(const IMaterialPtr& material));
};
}