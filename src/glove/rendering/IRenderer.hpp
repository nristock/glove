#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/FrameData.hpp"
#include "glove/rendering/buffers/BufferUsage.hpp"
#include "glove/graph/Graph.hpp"
#include "glove/utils/ScreenDimensions.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IRenderer {
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