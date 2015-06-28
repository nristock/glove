#pragma once

#include <memory>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

class Entity;

class SceneProxy;
using SceneProxyHandle = std::shared_ptr<SceneProxy>;

/**
* An EntityComponent can be attached to either an Entity or another EntityComponent.
*
* Use these components to define Entity related behaviour.
*/
class BD_API_EXPORT EntityComponent {
  public:
    virtual ~EntityComponent() = default;

    /// Advances the simulation by @p time seconds.
    virtual void Tick(double time) = 0;

    /**
    * Sets the internal owner field. - Intended to be used by Entity and classes deriving from Entity.
    *
    * Note: This does neither notify the old nor the new owner about ownership changes. Use the appropriate
    * Detach/Attach methods on the Entity class to ensure proper change propagation.
    *
    * @param newOwner [in] The new owner.
    */
    void SetOwner(std::weak_ptr<Entity> newOwner) { owner = newOwner; }

    virtual SceneProxyHandle CreateSceneProxy() {return SceneProxyHandle(); };

  protected:
    std::weak_ptr<Entity> owner;
};

} /* namespace BlueDwarf */