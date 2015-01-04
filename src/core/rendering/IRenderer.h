#pragma once

#include "core/GloveFwd.h"
#include <core/rendering/FrameData.h>
#include <core/rendering/buffers/BufferUsage.h>
#include <core/graph/Graph.h>

#include "Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderer {
  public:
    virtual ~IRenderer() {}

    virtual void ClearBuffers() = 0;
    virtual RenderTargetHandle CreateRenderTarget() = 0;
  virtual RenderTargetHandle GetDefaultRenderTarget() = 0;

    virtual void SwapBuffers() = 0;
    virtual void MapCameraToTarget(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget) = 0;
    virtual void RenderScene(const ScenegraphHandle& scenegraph) = 0;

    virtual IWindowPtr GetAssociatedWindow() = 0;
};

} /* namespace glove */