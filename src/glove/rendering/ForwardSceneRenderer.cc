#include "ForwardSceneRenderer.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"
#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/RenderTarget.hpp"
#include "glove/rendering/Texture.hpp"
#include "glove/world/scene/Scene.hpp"
#include "glove/world/scene/SceneProxy.hpp"
#include "glove/rendering/PrimitiveDrawInterface.hpp"

namespace glove {
void ForwardSceneRenderer::RenderComposition(SceneViewComposition& composition, RenderCommandList& renderCommandList, RenderTarget& renderTarget) {
    if (RenderTargetReallocationRequired(composition)) {
        previousViewCompositionHeight = composition.GetCompositionHeight();
        previousViewCompositionWidth = composition.GetCompositionWidth();

        AllocateRenderTarget(previousViewCompositionWidth, previousViewCompositionHeight);
    }

    std::vector<RenderTarget> colorTargets = {*colorTarget};
    renderCommandList.SetRenderTargets(colorTargets, *depthTarget);
    renderCommandList.ClearFramebuffer(true, true, true);

    for(auto& view : composition.GetViews()) {
        RenderView(view, renderCommandList);
    }

    renderCommandList.SetRenderTargets(std::vector<RenderTarget>{renderTarget}, RenderTarget{});
    renderCommandList.ClearFramebuffer(true, true, true);
    primitiveUtils->DrawFullscreenQuad(renderCommandList, colorTarget->GetTexture());
}

void ForwardSceneRenderer::AllocateRenderTarget(uint32 width, uint32 height) {
    colorTarget = std::make_unique<RenderTarget>(resourceFactory->CreateTexture2D(width, height, PixelFormat::R8G8B8A8));
    depthTarget = std::make_unique<RenderTarget>(resourceFactory->CreateTexture2D(width, height, PixelFormat::Depth24Stencil8));
}

void ForwardSceneRenderer::RenderView(const SceneView& view, RenderCommandList& renderCommandList) {
    renderCommandList.SetViewport(view.GetViewRect().GetX(), view.GetViewRect().GetY(), view.GetViewRect().GetWidth(), view.GetViewRect().GetHeight());

    BatchCollector dynamicBatchCollector{};
    for(auto& proxy : scene->GetProxies()) {
        proxy->DrawDynamicElements(dynamicBatchCollector, view);
    }

    dynamicBatchCollector.DrawBatches(renderCommandList, view);
}

void ForwardSceneRenderer::CreateResources() {
    primitiveUtils = std::make_unique<PrimitiveDrawUtils>(*resourceFactory);
}
} /* namespace glove */