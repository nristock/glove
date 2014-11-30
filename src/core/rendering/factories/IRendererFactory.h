#pragma once

#include "../Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRendererFactory {
  public:
    virtual ~IRendererFactory(){};

    virtual IRendererPtr CreateRenderer(const WindowConstructionHints& windowDescription) = 0;
};

} /* namespace glove */