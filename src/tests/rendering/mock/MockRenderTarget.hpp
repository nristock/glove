#include <gmock/gmock.hpp>

#include <glove/rendering/target/IRenderTarget.hpp>

namespace glove {
class MockRenderTarget : public IRenderTarget {
  public:
    MockRenderTarget() = default;

    MOCK_METHOD1(AddDependency, void(const RenderTargetHandle& dependency));
    MOCK_METHOD0(GetDependencies, std::list<std::weak_ptr<IRenderTarget>>());
    MOCK_CONST_METHOD0(GetDimensions, const ScreenDimensions&());
    MOCK_METHOD0(Bind, void());
};
}