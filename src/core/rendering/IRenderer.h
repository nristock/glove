#pragma once

#include "core/GloveFwd.h"
#include <core/rendering/FrameData.h>
#include <core/rendering/buffers/BufferUsage.h>

#include "Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderer {
  public:
    virtual ~IRenderer() {}

    virtual void ClearBuffers() = 0;
    virtual void RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) = 0;
    virtual void SwapBuffers() = 0;

    virtual IWindowPtr GetAssociatedWindow() = 0;
};

} /* namespace glove */