#include "glove/rendering/RendererBase.hpp"
#include "glove/graph/Scenegraph.hpp"
#include "glove/rendering/gamecomponent/CameraBase.hpp"
#include "glove/rendering/target/IRenderTarget.hpp"
#include "glove/rendering/RenderState.hpp"
#include "glove/rendering/IRenderOperation.hpp"

namespace glove {
void RendererBase::MapCameraToTarget(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget) {
    const ScreenDimensions& targetDimensions = renderTarget->GetDimensions();
    camera->SetAspectRatio(targetDimensions.GetAspectRatio());

    cameraTargetMapping.insert(std::pair<RenderTargetHandle, CameraBaseHandle>(renderTarget, camera));
}

void RendererBase::RenderScene(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget) {
    std::unordered_set<RenderTargetHandle> renderedTargets;

    RenderSceneToTarget(scenegraph, renderTarget, renderedTargets);
}

void RendererBase::RenderSceneToTarget(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget, std::unordered_set<RenderTargetHandle>& renderedTargets) {
    // Nothing to be done if the target has already been rendered
    if(renderedTargets.count(renderTarget) != 0) {
        return;
    }

    for(const std::weak_ptr<IRenderTarget>& targetDependency : renderTarget->GetDependencies()) {
        RenderSceneToTarget(scenegraph, targetDependency.lock(), renderedTargets);
    }

    CameraTargetMappingRange cameras = cameraTargetMapping.equal_range(renderTarget);

    for(CameraTargetMapping::iterator iter = cameras.first; iter != cameras.second; ++iter) {
        RenderState renderState(iter->second->GetViewProjectionMatrix());

        scenegraph->IterateGameObjects([&](const GameObjectHandle& gameObject) {
            gameObject->IterateComponents([&](const GameComponentHandle& component) {
                component.lock()->QueueRenderOperation(renderState.GetRenderQueue());
            });
        });

        while (!renderState.GetRenderQueue().empty()) {
            IRenderOperation* renderOp = renderState.GetRenderQueue().front();
            renderState.GetRenderQueue().pop();

            renderOp->Execute(shared_from_this());
            if (renderOp->ShouldDelete()) {
                delete renderOp;
            }
        }
    }
}

}