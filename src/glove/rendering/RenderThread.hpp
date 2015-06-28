#pragma once

#include <memory>

#include "glove/BlueDwarfApi.hpp"
#include "glove/threading/Thread.hpp"
#include "glove/threading/ThreadPool.hpp"
#include "glove/world/scene/Scene.hpp"
#include "glove/rendering/ApplicationViewport.hpp"

namespace BlueDwarf {
class BD_API_EXPORT RenderDispatcher {
  public:
    static void Initialize() {
        instance = std::unique_ptr<RenderDispatcher>(new RenderDispatcher{});
        RunOnRenderThread([](){
            instance->renderThreadId = std::this_thread::get_id();
        });
    }
    static std::shared_ptr<PoolTask> DispatchTask(TaskHandle task) {return instance->thread.SubmitWork(std::move(task)); }

    static void EnsureRenderThread() {
        DebugAssert(instance->renderThreadId == std::this_thread::get_id());
    }

    template <typename TFunc> static std::shared_ptr<PoolTask> RunOnRenderThread(TFunc func) {
        class RenderTask : public Task {
          public:
            RenderTask(TFunc&& callable) : callable(callable) {}

            void Execute() { callable(); }

          private:
            TFunc callable;
        };

        auto task = std::make_shared<RenderTask>(std::move(func));
        return std::move(instance->thread.SubmitWork(std::move(task)));
    }

  private:
    static std::unique_ptr<RenderDispatcher> instance;

    std::thread::id renderThreadId;

    RenderDispatcher() : thread(1) {}
    ThreadPool thread;
};

class SceneProxy;
using SceneProxyHandle = std::shared_ptr<SceneProxy>;

struct InsertSceneProxyTask : public Task {
    InsertSceneProxyTask(Scene::Handle scene, SceneProxyHandle proxy) : scene(scene), proxy(std::move(proxy)) {}

    void Execute() {
        scene->InsertProxy(std::move(proxy));
    }

  private:
    Scene::Handle scene;
    SceneProxyHandle proxy;
};

struct DrawViewportTask : public Task {
    DrawViewportTask(std::shared_ptr<ApplicationViewport> viewport, std::shared_ptr<ViewportClient> viewportClient) : viewport(viewport), viewportClient(viewportClient) {}

    void Execute() {
        viewport->Draw(viewportClient);
    }
  private:
    std::shared_ptr<ApplicationViewport> viewport;
    std::shared_ptr<ViewportClient> viewportClient;
};
}