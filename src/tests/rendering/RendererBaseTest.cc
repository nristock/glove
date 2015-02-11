#include <gmock/gmock.hpp>

#include "tests/rendering/mock/MockCamera.hpp"
#include "tests/rendering/mock/MockRendererBase.hpp"
#include "tests/rendering/mock/MockRenderTarget.hpp"
#include "tests/graph/mock/GameObjectMock.hpp"

using ::testing::ReturnRef;
using ::testing::_;

namespace glove {
TEST(RendererBaseTest, MappingCameraToTargetSetsCamerasAspectRatio) {
    MockRendererBase rendererBase;

    ScreenDimensions targetDimensions(800, 600);
    RenderTargetHandle renderTarget = RenderTargetHandle(new MockRenderTarget());
    EXPECT_CALL(*(MockRenderTarget*)renderTarget.get(), GetDimensions()).Times(1).WillOnce(ReturnRef(targetDimensions));

    GameObjectHandle gameObject = GameObjectHandle(new GameObjectMock());

    CameraBaseHandle camera = CameraBaseHandle(new MockCamera());
    EXPECT_CALL(*(MockCamera*)camera.get(), SetAspectRatio(targetDimensions.GetAspectRatio())).Times(1);

    gameObject->AddComponent(camera);

    rendererBase.MapCameraToTarget(camera, renderTarget);
}
}