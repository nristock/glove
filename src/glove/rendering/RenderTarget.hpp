#pragma once

#include <memory>

#include "glove/CommonTypes.hpp"
#include "glove/BlueDwarfApi.hpp"
#include "glove/utils/DebugUtils.hpp"

namespace BlueDwarf {
class RenderResourceFactory;

class Texture2D;
using Texture2DHandle = std::shared_ptr<Texture2D>;

/**
* An off-screen render target which can be bound to either color or depth/stencil output.
*/
struct BD_API_EXPORT RenderTarget {
  public:
    RenderTarget() = default;

    RenderTarget(Texture2DHandle texture) : targetTexture(texture) {
        DebugAssert((bool)texture);
    }

    Texture2DHandle GetTexture() const { return targetTexture; }

    bool HasTexture() const { return (bool)targetTexture; }

  private:
    Texture2DHandle targetTexture;
};
} /* namespace BlueDwarf */