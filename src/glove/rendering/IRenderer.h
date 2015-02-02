#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/rendering/Rendering.h"
#include "glove/rendering/FrameData.h"
#include "glove/rendering/buffers/BufferUsage.h"
#include "glove/graph/Graph.h"
#include "utils/ScreenDimensions.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderer {
  public:
    virtual ~IRenderer() {}

    virtual void ClearBuffers() = 0;
    virtual RenderTargetHandle CreateRenderTarget(const ScreenDimensions& dimensions) = 0;
    virtual RenderTargetHandle GetDefaultRenderTarget() = 0;

    virtual void SwapBuffers() = 0;
    virtual void MapCameraToTarget(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget) = 0;
    virtual void RenderScene(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget) = 0;

    virtual IWindowPtr GetAssociatedWindow() = 0;
};

} /* namespace glove */