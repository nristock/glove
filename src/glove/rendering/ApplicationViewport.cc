#include "glove/rendering/ApplicationViewport.hpp"
#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/SceneRenderer.hpp"
#include "glove/rendering/SceneView.hpp"
#include "glove/rendering/Texture.hpp"
#include "glove/rendering/RenderThread.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {

ApplicationViewport::~ApplicationViewport() = default;

void ApplicationViewport::Draw(std::shared_ptr<ViewportClient> viewportClient) {
    if (!renderTarget) {
        UpdateRenderTarget(*viewportClient);
    }

    RenderCommandList cmdList;

    BeginFrame(cmdList, viewportClient);

    DrawScene(cmdList);
    DrawGui(cmdList);

    EndFrame(cmdList, viewportClient);

//    std::stringstream ss;
//    cmdList.Visualize(ss);
//    logger.Info(ss.str());
    cmdList.Execute(*renderHardwareInterface);
}

void ApplicationViewport::BeginFrame(RenderCommandList& renderCommandList,
                                     std::shared_ptr<ViewportClient> viewportClient) {
    renderCommandList.BeginFrame(viewportClient);
}

void ApplicationViewport::EndFrame(RenderCommandList& renderCommandList,
                                   std::shared_ptr<ViewportClient> viewportClient) {
    renderCommandList.EndFrame(viewportClient, *renderTarget);
}

void ApplicationViewport::DrawScene(RenderCommandList& renderCommandList) {
    // Don't render anything if there's no scene renderer attached.
    if (!sceneRenderer) {
        return;
    }

    static bool b = false;
    if(!b) {
        sceneRenderer->CreateResources();
        b = true;
    }


    auto viewComposition = InitViews();
    sceneRenderer->RenderComposition(viewComposition, renderCommandList, *renderTarget);
}

void ApplicationViewport::DrawGui(RenderCommandList& renderCommandList) {
    // todo
}

void ApplicationViewport::SetSceneRenderer(std::unique_ptr<SceneRenderer> ptr) {
    sceneRenderer = std::move(ptr);
}

SceneViewComposition ApplicationViewport::InitViews() {
    auto targetTexture = renderTarget->GetTexture();

    auto primarySceneView = SceneViewBuilder::OrthogonalProjectionView(1)
                                .SetViewRect({0, 0, targetTexture->GetWidth(), targetTexture->GetHeight()})
                                .Finalize();
    auto viewComposition = SceneViewComposition{{primarySceneView}, *renderTarget};

    return std::move(viewComposition);
}

void ApplicationViewport::BeginDraw(std::shared_ptr<ViewportClient> viewportClient) {
    DebugAssert(!currentRenderTask);

    auto drawTask = std::make_shared<DrawViewportTask>(shared_from_this(), viewportClient);
    currentRenderTask = RenderDispatcher::DispatchTask(drawTask);
}

void ApplicationViewport::UpdateRenderTarget(const ViewportClient& viewportClient) {
    auto clientArea = viewportClient.GetClientArea();
    auto targetTexture = renderHardwareInterface->CreateResourceFactory()->CreateTexture2D(
        static_cast<uint32>(clientArea.x), static_cast<uint32>(clientArea.y), PixelFormat::R8G8B8A8);

    renderTarget = std::make_unique<RenderTarget>(std::move(targetTexture));
}

void ApplicationViewport::EndDraw() {
    DebugAssert((bool)currentRenderTask);

    currentRenderTask->AwaitCompletion();
    currentRenderTask.reset();
}

ApplicationViewport::ApplicationViewport(std::shared_ptr<RenderHardwareInterface> rhi) : renderHardwareInterface(rhi) {
}
}