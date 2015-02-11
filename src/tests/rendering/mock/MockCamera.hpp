#include <gmock/gmock.hpp>

#include <glove/rendering/gamecomponent/CameraBase.hpp>

namespace glove {
class MockCamera : public GameComponents::CameraBase {
  public:
    MockCamera() = default;
    MOCK_METHOD1(SetAspectRatio, void(float aspectRatio));

    MOCK_METHOD0(RecalculateProjectionMatrix, void());

    void SetAspectRatioBase(float aspectRatio) {
      GameComponents::CameraBase::SetAspectRatio(aspectRatio);
    }
};
}