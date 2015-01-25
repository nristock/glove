#pragma once

#include <mutex>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_set>

#include <GL/glew.h>
#include <GL/gl.h>
#include <core/log/Log.h>

#include <core/GloveException.h>
#include <core/GloveFwd.h>
#include <core/rendering/RenderOperation.h>
#include <core/rendering/RendererBase.h>
#include <core/rendering/Rendering.h>
#include <core/rendering/FrameData.h>
#include <core/rendering/vertex/VertexAttributeType.h>
#include <core/natex/Natex.h>
#include <core/rendering/WindowConstructionHints.h>
#include <core/graph/Graph.h>

#include "subsystem/OpenGLRendererModule.h"
#include "GLWindow.h"

struct GLFWwindow;

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLRenderer : public RendererBase {
  public:
    GLRenderer(const EventBusPtr& eventBus, const WindowConstructionHints& windowConstructionHints,
               const ContextId contextId);

    virtual ~GLRenderer() = default;

    virtual void ClearBuffers();

    virtual RenderTargetHandle CreateRenderTarget(const ScreenDimensions& dimensions);
    virtual RenderTargetHandle GetDefaultRenderTarget();

    virtual void SwapBuffers();

    virtual IWindowPtr GetAssociatedWindow();
    ContextId GetContextId() const;

  private:
    RenderTargetHandle defaultRenderTarget;

    logging::GloveLogger logger;
    EventBusPtr eventBus;
    ContextId contextId;

    GLWindowPtr window;

    void CreateWindow(const WindowConstructionHints& windowCreationHints);
    void RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GLMeshPtr& baseMesh);
};
}
} /* namespace glove */
