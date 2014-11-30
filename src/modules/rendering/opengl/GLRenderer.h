#pragma once

#include <mutex>
#include <vector>
#include <utility>

#include <GL/glew.h>
#include <GL/gl.h>
#include <core/log/Log.h>

#include <core/GloveException.h>
#include <core/GloveFwd.h>
#include <core/rendering/RenderOperation.h>
#include <core/rendering/IRenderer.h>
#include <core/rendering/Rendering.h>
#include <core/rendering/FrameData.h>
#include <core/rendering/vertex/VertexAttributeType.h>
#include <core/natex/Natex.h>
#include <core/rendering/WindowConstructionHints.h>
#include <modules/rendering/opengl/subsystem/OpenGLRendererModule.h>

#include "GLWindow.h"

struct GLFWwindow;

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLRenderer : public IRenderer {
  public:
    GLRenderer(const EventBusPtr& eventBus, const WindowConstructionHints& windowConstructionHints,
               const ContextId contextId);

    virtual ~GLRenderer() = default;

    virtual void ClearBuffers();
    virtual void RenderScene(ScenegraphPointer scenegraph, FrameData& frameData);
    virtual void SwapBuffers();

    virtual IWindowPtr GetAssociatedWindow();

  private:
    logging::GloveLogger logger;
    EventBusPtr eventBus;
    ContextId contextId;

    GLWindowPtr window;

    RenderOperation currentRenderOperation;

    void CreateWindow(const WindowConstructionHints& windowCreationHints);
    void RenderObject(RenderOperation& renderOp, const FrameData& frameData, const GLBaseMeshPtr& baseMesh);
};
}
} /* namespace glove */
