#pragma once

#include "glove/GloveApi.hpp"
#include "glove/CommonTypes.hpp"
#include "glove/world/Transform.hpp"
#include "glove/threading/TaskQueue.hpp"

using namespace BlueDwarf;

namespace glove {

struct SceneView;
class PrimitiveDrawInterface;
class RenderResourceFactory;

/**
* A SceneProxy is the rendering threads representation of an EntityComponent.
*
* This can either be an actual primitive or simply a light.
* Once a SceneProxy has been submitted to the rendering thread for Scene insertion the rendering thread owns the
* SceneProxy and all its data. Updating a SceneProxy from the game thread should be done using custom render thread jobs
* since the default proxy implementations do not use any kind of locking. It is technically possible to implement a
* custom proxy which uses locks. Doing so, however, can impact rendering and game thread performance.
*/
class GLOVE_API_EXPORT SceneProxy {
  public:
    using Handle = std::shared_ptr<SceneProxy>;

    virtual ~SceneProxy() = default;

    /**
    * Called when the rendering thread adds the SceneProxy to its Scene.
    *
    * Can be used to allocate GPU resources.
    */
    virtual void CreateResources(const RenderResourceFactory& resourceFactory){};

    /**
    * Called when the rendering thread removes the SceneProxy from its Scene.
    *
    * Can be used to free unmanaged GPU resources.
    */
    virtual void DestroyResources(){};

    /**
    * Draws the dynamic elements of this proxy.
    *
    * Called once per frame for every proxy.
    */
    virtual void DrawDynamicElements(PrimitiveDrawInterface& pdi, const SceneView& view){};

    void SetTransform(const Transform& transform) { this->transform = transform; }
    const Transform& GetTransform() { return transform; }

  protected:
    Transform transform;
};

/**
* Simple job which allows updating a scene proxies transform.
*
* Create and enqueue this task from the game thread using RenderDispatcher::DispatchTask.
*/
class GLOVE_API_EXPORT UpdateProxyTransformJob : public Task {
  public:
    UpdateProxyTransformJob(const SceneProxy::Handle& targetProxy, const Transform& newTransform)
            : targetProxy(targetProxy), newTransform(newTransform) {}

    virtual void Execute() override {
        targetProxy->SetTransform(newTransform);
    }

  protected:
    SceneProxy::Handle targetProxy;
    Transform newTransform;
};

} /* namespace glove */