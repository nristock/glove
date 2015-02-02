#pragma once

#include <mutex>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_set>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glove/log/Log.h>

#include <glove/GloveException.h>
#include <glove/GloveFwd.hpp>
#include <glove/rendering/RenderOperation.h>
#include <glove/rendering/RendererBase.h>
#include <glove/rendering/Rendering.h>
#include <glove/rendering/FrameData.h>
#include <glove/rendering/vertex/VertexAttributeType.h>
#include <glove/natex/Natex.h>
#include <glove/rendering/WindowConstructionHints.h>
#include <glove/graph/Graph.h>

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
