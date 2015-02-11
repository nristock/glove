#include <gmock/gmock.hpp>

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/buffers/IGpuBuffer.hpp>

namespace glove {
class MockGpuBuffer : public IGpuBuffer {
  public:
    MOCK_METHOD0(Bind, void());
    MOCK_METHOD0(Unbind, void());
    MOCK_METHOD2(WriteData, void(std::size_t sizeInBytes, const void* data));
};
}