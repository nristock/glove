#pragma once

#include <core/pitamem/MemoryProfile.h>
#include <core/GloveFwd.h>

namespace glove {

class GameComponent {
    Profilable();

  public:
    GameComponent();

    virtual ~GameComponent();

    virtual const GameObjectPtr& GetOwnerRef() const { return owner; }

    virtual GameObjectPtr GetOwner() const { return owner; }

    virtual void OnAttach(GameObjectPtr owner);

    virtual void OnDetach();

    // Frame updates
    virtual void SyncEarlyUpdate(){};

    virtual void SyncUpdate(){};

    virtual void AsyncUpdate(){};

    virtual void SyncLateUpdate(){};

    // Physics updates
    virtual void AsyncPrePhysicsUpdate(){};

    virtual void SyncPhysicsUpdate(){};

    virtual void AsyncPostPhysicsUpdate(){};

  protected:
    GameObjectPtr owner;
};

} // namespace glove