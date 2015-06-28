#include "glove/world/scene/Scene.hpp"
#include "glove/rendering/RenderThread.hpp"

namespace glove {
std::shared_ptr<PoolTask> Scene::BeginInsertProxy(SceneProxyHandle proxy) {
    auto insertTask = std::make_shared<InsertSceneProxyTask>(shared_from_this(), std::move(proxy));
    return RenderDispatcher::DispatchTask(insertTask);
}
} /* namespace glove */