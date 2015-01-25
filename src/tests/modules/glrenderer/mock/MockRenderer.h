#include <vendor/gmock/gmock.h>

#include <core/GloveFwd.h>
#include <core/rendering/Rendering.h>
#include <core/rendering/IRenderer.h>

namespace glove {
class MockRenderer : public IRenderer {
  public:
    MOCK_METHOD0(ClearBuffers, void());
    MOCK_METHOD1(CreateRenderTarget, RenderTargetHandle(const ScreenDimensions& dimensions));
    MOCK_METHOD0(GetDefaultRenderTarget, RenderTargetHandle());

    MOCK_METHOD0(SwapBuffers, void());
    MOCK_METHOD2(RenderScene, void(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget));
    MOCK_METHOD2(MapCameraToTarget, void(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget));

    MOCK_METHOD0(GetAssociatedWindow, IWindowPtr());
};
}