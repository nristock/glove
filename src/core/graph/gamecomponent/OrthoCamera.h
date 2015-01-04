#pragma once

#include "graph/gamecomponent/CameraBase.h"

namespace glove {
namespace GameComponents {

class OrthoCamera : public CameraBase {
public:
    OrthoCamera(float orthoSize, float aspectRatio);

protected:
    virtual void RecalculateProjectionMatrix();
    float orthoSize;
};

}
}