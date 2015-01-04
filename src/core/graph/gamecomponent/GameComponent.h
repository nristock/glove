#pragma once

#include <queue>

#include <core/GloveFwd.h>
#include "graph/Graph.h"
#include "rendering/Rendering.h"

namespace glove {

class GameComponent {
  public:
    GameComponent() = default;
    virtual ~GameComponent() = default;

    virtual const WeakGameObjectHandle& GetOwner() const { return owner; }

    virtual void OnAttach(const GameObjectHandle& owner);
    virtual void OnDetach();

    virtual void QueueRenderOperation(std::queue<IRenderOperation*>& renderQueue) {};

    // Frame updates
    virtual void SyncEarlyUpdate(){}
    virtual void SyncUpdate(){}
    virtual void AsyncUpdate(){}
    virtual void SyncLateUpdate(){}

    // Physics updates
    virtual void AsyncPrePhysicsUpdate(){}
    virtual void SyncPhysicsUpdate(){}
    virtual void AsyncPostPhysicsUpdate(){}

  protected:
    WeakGameObjectHandle owner;
};

} // namespace glove