#include <vendor/gmock/gmock.h>

#include <glove/rendering/Rendering.h>
#include <glove/rendering/vertex/VertexLayout.h>
#include <glove/rendering/vertex/IVertexData.h>

namespace glove {
class MockVertexData : public IVertexData {
  public:
    MOCK_CONST_METHOD0(GetGpuBufferCount, const std::size_t());
    MOCK_CONST_METHOD1(GetGpuBuffer, const IGpuBufferPtr&(std::size_t bufferIndex));
    MOCK_CONST_METHOD0(GetVertexLayout, const VertexLayout&());
    MOCK_CONST_METHOD0(GetVertexCount, const std::size_t());
    MOCK_METHOD0(BindAllBuffers, void());
};
}