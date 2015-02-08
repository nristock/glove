#include <vendor/gmock/gmock.h>

#include <glove/rendering/Rendering.h>
#include <glove/rendering/mesh/Mesh.h>

namespace glove {
class MockMesh : public Mesh {
  public:
    MockMesh(const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData) : Mesh(vertexData, indexData) {}

    MOCK_METHOD1(BindMaterial, void(const IMaterialPtr& material));
};
}