#include <vendor/gmock/gmock.h>

#include <glove/rendering/RendererBase.h>

namespace glove {
class MockRendererBase : public RendererBase {
public:
    MockRendererBase() : RendererBase() {}

    MOCK_METHOD0(ClearBuffers, void());
    MOCK_METHOD0(SwapBuffers, void());

    MOCK_METHOD0(GetAssociatedWindow, IWindowPtr());
    MOCK_METHOD0(GetDefaultRenderTarget, RenderTargetHandle());
    MOCK_METHOD1(CreateRenderTarget, RenderTargetHandle(const ScreenDimensions& dimensions));
};
}