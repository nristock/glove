#include <vendor/gmock/gmock.h>

#include <core/rendering/Rendering.h>
#include <core/rendering/buffers/IGpuBuffer.h>

namespace glove {
class MockGpuBuffer : public IGpuBuffer {
  public:
    MOCK_METHOD0(Bind, void());
    MOCK_METHOD0(Unbind, void());
    MOCK_METHOD2(WriteData, void(std::size_t sizeInBytes, const void* data));
};
}