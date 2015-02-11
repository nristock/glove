#pragma once

#include <mutex>
#include <vector>
#include <utility>
#include <queue>
#include <unordered_set>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glove/log/Log.hpp>

#include <glove/GloveException.hpp>
#include <glove/GloveFwd.hpp>
#include <glove/rendering/RenderOperation.hpp>
#include <glove/rendering/RendererBase.hpp>
#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/FrameData.hpp>
#include <glove/rendering/vertex/VertexAttributeType.hpp>
#include <glove/natex/Natex.hpp>
#include <glove/rendering/WindowConstructionHints.hpp>
#include <glove/graph/Graph.hpp>

#include "GLWindow.hpp"
#include "subsystem/OpenGLRendererModule.hpp"

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
