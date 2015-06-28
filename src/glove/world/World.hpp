#pragma once

#include <memory>
#include <vector>
#include <list>

#include "glove/BlueDwarfApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/world/entity/Entity.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {

class WorldComponent;
using WorldComponentHandle = std::shared_ptr<WorldComponent>;

class Entity;
using EntityHandle = std::shared_ptr<Entity>;

class Scene;

class RendererService;

/// Entity life expectancy which is used by a World to apply optimizations to entities.
enum class EntityLifeExpectancy : char { LONG, SHORT };

/// WorldConstructionHints are hints used by World::World for optimizations.
struct WorldConstructionHints {
    std::size_t expectedWorldComponentCount = 32;
    std::size_t expectedStaticEntityCount = 64;
};

/**
* A World is the game logic thread's representation of the game world.
*
* A World can have WorldComponents and Entities attached to it.
* WorldComponents are held in continuous memory to allow CPU prefetching optimizations. See World::worldComponents.
* Entities can be stored in either continuous memory or in a linked-list like structure. See World::AddEntity.
*/
class BD_API_EXPORT World : public std::enable_shared_from_this<World> {
  public:
    using Handle = std::shared_ptr<World>;

    World(WorldConstructionHints constructionHints, std::shared_ptr<RendererService> rendererService);

    ~World();

    /**
    * Adds an existing Entity to the World taking ownership of the entity.
    *
    * World stores entities in two in separate structures depending on the life expectancy of the Entity.
    * Entities which are expected to exist for a long time (e.g. the player) are stored in a continuous memory data
    * structure while entities with a short life expectancy will be stored in a list like data structure.
    *
    * Continuous blocks of memory are slightly faster to iterate since we can exploit cache prefetching. Such data
    * structures do however require a reallocation when more objects are added.
    *
    * @param entity [in] The Entity to add. This World will take ownership of the Entity.
    * @param lifeExpectancy [in] The entities life expectancy which is used for optimizations.
    * @return Returns a shared handle to the Entity added.
    */
    EntityHandle AddEntity(std::unique_ptr<Entity> entity, EntityLifeExpectancy lifeExpectancy);

    /**
     * Create a new Entity of type TEntity forwarding all arguments to TEntity's constructor.
     *
     * Internally forwards the created entity instance to World::AddEntity(std::unique_ptr<Entity>,
     * EntityLifeExpectancy).
     *
     * @return Returns a shared handle to the newly create Entity.
     */
    template <class TEntity, class... TArgs>
    EntityHandle AddEntity(TArgs&&... args, EntityLifeExpectancy lifeExpectancy) {
        return AddEntity(std::make_unique<TEntity>(std::forward<TArgs>(args)...), lifeExpectancy);
    }

    EntityHandle AddEntity(EntityLifeExpectancy lifeExpectancy) {
        return AddEntity(std::make_unique<Entity>(shared_from_this()), lifeExpectancy);
    }

    /**
    * Adds an existing WorldComponent to the World taking ownership of the WorldComponent.
    *
    * @param component [in] The WorldComponent to add. This World will take ownership of the WorldComponent.
    * @return Returns a shared handle to the WorldComponent added.
    */
    WorldComponentHandle AddWorldComponent(std::unique_ptr<WorldComponent> component);

    /**
    * Creates a new WorldComponent using TFactory's () operator forwarding all arguments.
    *
    * Internally creates a new instance of TFactory and passes the () operator's return value to
    * World::AddWorldComponent(std::unique_ptr<WorldComponent>).
    *
    * @return Returns a shared handle to the WorldComponent added.
    */
    template <class TFactory, class... TArgs> WorldComponentHandle CreateWorldComponent(TArgs&&... args) {
        return AddWorldComponent(TFactory{}(std::forward<TArgs>(args)...));
    }

    /**
    * Ticks all attached world components and entities.
    *
    * Effectively advances the simulation by @p time seconds.
    * WorldComponents are updated in the calling thread. Once all WorldComponents are updated an UpdateEntityJob will be
    * created and scheduled for each entity in this World.
    * Tick will return once all update jobs have been processed.
    */
    void Tick(double time);

    std::shared_ptr<Scene> GetScene() const { return scene; }

  private:
    /**
    * All WorldComponents attached to this world.
    *
    * This isn't expected to change often during normal gameplay. It is therefore better to use a vector here to allow
    * cache prefetching.
    */
    std::vector<WorldComponentHandle> worldComponents;

    /**
    * This World's entities which have a EntityLifeExpectancy::LONG life expectancy.
    *
    * Allows fast iteration but slow insertions.
    */
    std::vector<EntityHandle> staticEntities;

    /**
    * This World's entities which have a EntityLifeExpectancy::SHORT life expectancy.
    *
    * Allows fast insertions and removals but relatively slow iteration.
    */
    std::list<EntityHandle> dynamicEntities;

    /**
    * The rendering threads representation of this world.
    *
    * The rendering thread has it's own representation of the world to reduce the number of locks required while on the
    * other hand increasing the amount of memory required.
    */
    std::shared_ptr<Scene> scene;

    Logger logger{"World"};
};

} /* namespace BlueDwarf */