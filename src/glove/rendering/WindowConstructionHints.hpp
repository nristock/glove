#pragma once

#include <string>

#include "glove/GloveFwd.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/utils/ScreenDimensions.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class WindowConstructionHints {
  public:
    WindowConstructionHints(const ScreenPoint& position, const ScreenDimensions& size, const std::string& title);

    virtual int GetWidth() const;
    virtual int GetHeight() const;

    virtual int GetPositionX() const;
    virtual int GetPositionY() const;

    virtual const std::string GetTitle() const;

  private:
    ScreenPoint position;
    ScreenDimensions size;
    std::string title;
};

} /* namespace glove */