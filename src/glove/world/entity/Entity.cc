#include "glove/world/entity/Entity.hpp"
#include "glove/world/component/EntityComponent.hpp"
#include "glove/world/World.hpp"
#include "glove/world/scene/Scene.hpp"

namespace glove {

Entity::Entity(std::weak_ptr<World> world) : world(world) {

}

EntityComponentHandle Entity::AttachComponent(std::unique_ptr<EntityComponent> component) {
    auto entityComponentHandle = EntityComponentHandle{std::move(component)};

    auto sceneProxy = entityComponentHandle->CreateSceneProxy();
    if(sceneProxy) {
        world.lock()->GetScene()->BeginInsertProxy(std::move(sceneProxy));
    }

    return entityComponentHandle;
}

void Entity::Tick(double time) {
    TickComponents(time);
}

void Entity::TickComponents(double time) {
    for (auto component : components) {
        component->Tick(time);
    }
}
}