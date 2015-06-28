#pragma once

#include <memory>

#include "glove/GloveApi.hpp"
#include "glove/math/IntPoint.hpp"
#include "glove/log/Log.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
struct Transform;
}

namespace glove {
struct RenderTarget;
class SceneRenderer;
class RenderCommandList;
class SceneViewComposition;
class RenderHardwareInterface;
class PoolTask;

/**
 * A ViewportClient is the physical target of a rendered frame.
 *
 * This can be an OS window or a client which saves screenshots.
 * Viewport clients are attached to an ApplicationViewport which will call ViewportClient::Flush each time a frame has
 * finished rendering.
 */
class GLOVE_API_EXPORT ViewportClient {
  public:
    virtual ~ViewportClient() = default;

    /*
     * Returns the dimensions of this viewport client in pixel.
     *
     * The dimensions returned by this function are used by the host ApplicationViewport to create an appropriately
     * sized render target texture.
     *
     * Called from the render thread.
     */
    virtual IntPoint GetClientArea() const = 0;

    /// Called by the host ApplicationViewport each time a frame has finished rendering. Called from rendering thread.
    virtual void Flush(const RenderTarget& renderTarget) = 0;

    /// @deprecated Returns whether the ViewportClient (window) was requested to close.
    virtual bool ShouldClose() = 0;
};

/**
* An ApplicationViewport is the canvas to which a frame is rendered. A single ApplicationViewport can host multiple
* @link ViewportClient ViewportClients @endlink of the same size and the final render target when a frame is done
* rendering.
*/
class GLOVE_API_EXPORT  ApplicationViewport : public std::enable_shared_from_this<ApplicationViewport> {
  public:
    ApplicationViewport(std::shared_ptr<RenderHardwareInterface> rhi);
    virtual ~ApplicationViewport();

    void SetSceneRenderer(std::unique_ptr<SceneRenderer> sceneRenderer);

    /// Queues a DrawViewportTask to be executed on the rendering thread.
    void BeginDraw(std::shared_ptr<ViewportClient> viewportClient);

    /// Waits for the most recently queued DrawViewportTask to finish.
    void EndDraw();

    /*
     * Draws and presents this ApplicationViewport.
     *
     * This method is the main entry point for the DrawViewportTask. It first checks whether the render target needs to
     * be re-initialized (e.g. due to a client viewport size change). Then a RenderCommandList is created and all
     * commands required to draw the viewport are queued. Last the command list is sent to the render hardware interface.
     */
    virtual void Draw(std::shared_ptr<ViewportClient> viewportClient);

    /// Initializes the SceneViewComposition.
    virtual SceneViewComposition InitViews();

  protected:
    /// Begins the frame. The default implementation will queue a BeginFrame RHI command.
    virtual void BeginFrame(RenderCommandList& renderCommandList, std::shared_ptr<ViewportClient> viewportClient);
    /// Ends the frame. The default implementation will queue an EndFrame RHI command.
    virtual void EndFrame(RenderCommandList& renderCommandList, std::shared_ptr<ViewportClient> viewportClient);

    virtual void DrawScene(RenderCommandList& renderCommandList);
    virtual void DrawGui(RenderCommandList& renderCommandList);

    void UpdateRenderTarget(const ViewportClient& viewportClient);

  private:
    std::shared_ptr<RenderHardwareInterface> renderHardwareInterface;

    /// The GUI renderer to use when rendering the GUI. GUI rendering is done after scene rendering.
    // std::unique_ptr<GUIRenderer> guiRenderer;

    /// The scene renderer to use when rendering
    std::unique_ptr<SceneRenderer> sceneRenderer;

    /// The primary render target. This is the link between different render stages (e.g. scene -> gui)
    std::unique_ptr<RenderTarget> renderTarget;

    std::shared_ptr<PoolTask> currentRenderTask;

    Logger logger;
};
} // namespace glove
