#pragma once

#include <memory>
#include <vector>
#include <glove/rendering/RendererService.hpp>
#include <glove/rendering/RenderHardwareInterface.hpp>
#include <glove/rendering/RenderResourceFactory.hpp>
#include <glove/world/scene/SceneProxy.hpp>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class SceneProxy;
using SceneProxyHandle = std::shared_ptr<SceneProxy>;

class PoolTask;

class BD_API_EXPORT Scene : public std::enable_shared_from_this<Scene> {
  public:
    using Handle = std::shared_ptr<Scene>;

    Scene(std::shared_ptr<RendererService> rendererService) : rendererService(rendererService) {}

    /// Safe to call from game thread. Queues a proxy insertion task on the render thread.
    std::shared_ptr<PoolTask> BeginInsertProxy(SceneProxyHandle proxy);

    void InsertProxy(SceneProxyHandle proxy) {
        auto renderResourceFactory = rendererService->GetRenderHardwareInterface()->CreateResourceFactory();
        proxy->CreateResources(*renderResourceFactory);

        sceneProxies.push_back(std::move(proxy));
    }

    const std::vector<SceneProxyHandle>& GetProxies() const {return sceneProxies;}

  protected:
    std::shared_ptr<RendererService> rendererService;
    std::vector<SceneProxyHandle> sceneProxies;
};

} /* namespace BlueDwarf */