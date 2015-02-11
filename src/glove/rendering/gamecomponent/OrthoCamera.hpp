#pragma once

#include "glove/rendering/gamecomponent/CameraBase.hpp"

namespace glove {
namespace GameComponents {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT OrthoCamera : public CameraBase {
public:
    OrthoCamera(float orthoSize, float aspectRatio);

    void SetOrthoSize(float newOrthoSize);

protected:
    virtual void RecalculateProjectionMatrix();
    float orthoSize;
};

}
}