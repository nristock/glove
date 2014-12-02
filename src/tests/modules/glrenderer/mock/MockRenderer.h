#include <vendor/gmock/gmock.h>

#include <core/GloveFwd.h>
#include <core/rendering/Rendering.h>
#include <core/rendering/IRenderer.h>

namespace glove {
class MockRenderer : public IRenderer {
  public:
    MOCK_METHOD0(ClearBuffers, void());
    MOCK_METHOD2(RenderScene, void(ScenegraphPointer, FrameData& frameData));
    MOCK_METHOD0(SwapBuffers, void());

    MOCK_METHOD0(GetAssociatedWindow, IWindowPtr());
};
}