#include <gmock/gmock.hpp>

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/vertex/VertexLayout.hpp>
#include <glove/rendering/vertex/IVertexData.hpp>

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