#include <vendor/gmock/gmock.h>

#include <glove/rendering/Rendering.h>
#include <glove/rendering/vertex/IIndexData.h>

namespace glove {
class MockIndexData : public IIndexData {
  public:
    MOCK_CONST_METHOD0(GetIndexCount, const std::size_t());
    MOCK_CONST_METHOD0(GetGpuBuffer, const IGpuBufferPtr&());
    MOCK_METHOD0(BindBuffer, void());
};
}