#pragma once

#include "rendering/gamecomponent/CameraBase.h"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class OrthoCamera : public CameraBase {
public:
    OrthoCamera(float orthoSize, float aspectRatio);

    void SetOrthoSize(float newOrthoSize);

protected:
    virtual void RecalculateProjectionMatrix();
    float orthoSize;
};

}
}