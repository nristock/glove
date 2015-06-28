#pragma once

#include "glove/CommonTypes.hpp"
#include "glove/BlueDwarfApi.hpp"
#include "glove/rendering/SceneRenderer.hpp"
#include "glove/rendering/RenderHardwareInterface.hpp"
#include "glove/rendering/SceneView.hpp"
#include "glove/rendering/RenderResourceFactory.hpp"
#include "PrimitiveDrawUtils.hpp"

namespace BlueDwarf {
struct RenderTarget;
class RenderCommandList;

class RenderHardwareInterface;

/**
* This scene renderer uses single pass forward shading. The complete rendering process, however, requires at least two
* passes.
*
* The first pass renders scene geometry to a scene render target. The second pass renders a fullscreen quad using post
* processing shaders and writes the color output to the ViewComposition's render target.
*/
class BD_API_EXPORT ForwardSceneRenderer : public SceneRenderer {
  public:
    ForwardSceneRenderer(const SceneHandle& scene, const RenderHardwareInterfaceHandle& renderer) : SceneRenderer(scene, renderer) {
        resourceFactory = renderer->CreateResourceFactory();
    }

    virtual void CreateResources();
    virtual void RenderComposition(SceneViewComposition& composition, RenderCommandList& renderCommandList, RenderTarget& renderTarget) override;

  private:
    void RenderView(const SceneView& view, RenderCommandList& renderCommandList);
    bool RenderTargetReallocationRequired(const SceneViewComposition& composition) {
        return composition.GetCompositionHeight() != previousViewCompositionHeight ||
               composition.GetCompositionWidth() != previousViewCompositionWidth;
    }

    std::unique_ptr<RenderResourceFactory> resourceFactory;
    std::unique_ptr<RenderTarget> colorTarget;
    std::unique_ptr<RenderTarget> depthTarget;
    std::unique_ptr<RenderTarget> stencilTarget;

    std::unique_ptr<PrimitiveDrawUtils> primitiveUtils;

  private:
    uint32 previousViewCompositionWidth = 0;
    uint32 previousViewCompositionHeight = 0;

    void AllocateRenderTarget(uint32 width, uint32 height);
};

} /* namespace BlueDwarf */