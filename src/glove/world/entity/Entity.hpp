#pragma once

#include <memory>
#include <list>

#include "glove/GloveApi.hpp"

#include "glove/world/Transform.hpp"

using namespace BlueDwarf;

namespace glove {

class EntityComponent;
using EntityComponentHandle = std::shared_ptr<EntityComponent>;

class World;

/**
* An Entity is anything that can be placed in a world. It has a transform and EntityComponents can be attached to it.
*/
class GLOVE_API_EXPORT Entity {
  public:
    Entity(std::weak_ptr<World> world);
    virtual ~Entity() = default;

    /**
    * Attaches an existing component to this Entity and takes ownership of that component.
    *
    * @param component [in] The EntityComponent to attach. This Entity will take ownership of the EntityComponent.
    * @return Returns a shared handle to the EntityComponent added.
    */
    EntityComponentHandle AttachComponent(std::unique_ptr<EntityComponent> component);

    /// Ticks all attached EntityComponents. Effectively advances the simulation by @p time seconds.
    virtual void Tick(double time);

  protected:
    void TickComponents(double time);

  private:
    std::weak_ptr<World> world;

    Transform transform;
    std::list<EntityComponentHandle> components;
};

} /* namespace glove */