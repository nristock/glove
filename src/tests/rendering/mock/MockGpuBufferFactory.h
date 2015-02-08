#include <vendor/gmock/gmock.h>

#include <glove/rendering/Rendering.h>
#include <glove/rendering/factories/IGpuBufferFactory.h>

namespace glove {
class MockGpuBufferFactory : public IGpuBufferFactory {
  public:
    MOCK_CONST_METHOD1(CreateVertexBuffer, IGpuBufferPtr(BufferUsage bufferUsage));
    MOCK_CONST_METHOD0(CreateIndexBuffer, IGpuBufferPtr());
};
}