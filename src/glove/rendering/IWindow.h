#pragma once

#include <glm/glm.hpp>

#include "glove/rendering/Rendering.h"
#include "utils/ScreenDimensions.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IWindow {
  public:
    virtual ~IWindow() {}

    virtual ScreenPoint GetPosition() const = 0;
    virtual ScreenDimensions GetDimensions() const = 0;

    virtual void SetPosition(const ScreenPoint& newPosition) = 0;
    virtual void SetDimensions(const ScreenDimensions& newDimensions) = 0;

    virtual bool CloseRequested() const = 0;

    virtual glm::mat4 GetProjectionMatrix() const = 0;

    virtual void PollSystemEvents() = 0;
};

} /* namespace glove */
