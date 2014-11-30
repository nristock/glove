#include <vendor/gmock/gmock.h>

#include <core/rendering/Rendering.h>
#include <core/rendering/vertex/IIndexData.h>

namespace glove {
class MockIndexData : public IIndexData {
public:
    MOCK_CONST_METHOD0(GetIndexCount, const std::size_t());
    MOCK_CONST_METHOD0(GetGpuBuffer, const IGpuBufferPtr&());
    MOCK_METHOD0(BindBuffer, void());
};
}