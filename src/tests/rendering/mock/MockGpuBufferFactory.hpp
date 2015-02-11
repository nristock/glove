#include <gmock/gmock.hpp>

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/factories/IGpuBufferFactory.hpp>

namespace glove {
class MockGpuBufferFactory : public IGpuBufferFactory {
  public:
    MOCK_CONST_METHOD1(CreateVertexBuffer, IGpuBufferPtr(BufferUsage bufferUsage));
    MOCK_CONST_METHOD0(CreateIndexBuffer, IGpuBufferPtr());
};
}