#pragma once

#include <string>

#include <core/GloveFwd.h>
#include "Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class WindowConstructionHints {
public:
    WindowConstructionHints(const ScreenPoint& position, const ScreenDimensions& size, const std::string& title);

    virtual GLOVE_INLINE int GetWidth() const;
    virtual GLOVE_INLINE int GetHeight() const;

    virtual GLOVE_INLINE int GetPositionX() const;
    virtual GLOVE_INLINE int GetPositionY() const;

    virtual GLOVE_INLINE const std::string GetTitle() const;

private:
    ScreenPoint position;
    ScreenDimensions size;
    std::string title;
};

} /* namespace glove */