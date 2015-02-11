#pragma once

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IRendererFactory {
  public:
    virtual ~IRendererFactory(){};

    virtual IRendererPtr CreateRenderer(const WindowConstructionHints& windowDescription) = 0;
};

} /* namespace glove */