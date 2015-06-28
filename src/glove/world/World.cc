#include "glove/world/World.hpp"
#include "glove/world/scene/Scene.hpp"
#include "glove/world/entity/Entity.hpp"
#include "glove/world/component/WorldComponent.hpp"

namespace BlueDwarf {

World::World(WorldConstructionHints constructionHints, std::shared_ptr<RendererService> rendererService) {
    worldComponents.reserve(constructionHints.expectedWorldComponentCount);
    staticEntities.reserve(constructionHints.expectedStaticEntityCount);

    scene = std::make_unique<Scene>(rendererService);
}

EntityHandle World::AddEntity(std::unique_ptr<Entity> entity, EntityLifeExpectancy lifeExpectancy) {
    EntityHandle entityHandle{std::move(entity)};

    switch (lifeExpectancy) {
    case EntityLifeExpectancy::SHORT:
        dynamicEntities.push_back(entityHandle);
        break;

    case EntityLifeExpectancy::LONG:
#if defined(BD_ENABLE_PROFILING)
        if (staticEntities.size() + 1 > staticEntities.capacity()) {
            logger.Warning(
                fmt::format("World's staticEntities container is over capacity - reallocating! Current capacity: {0}",
                            staticEntities.capacity()),
                M_TAG);
        }
#endif
        staticEntities.push_back(entityHandle);
        break;
    }

    return entityHandle;
}

WorldComponentHandle World::AddWorldComponent(std::unique_ptr<WorldComponent> component) {
    WorldComponentHandle componentHandle{std::move(component)};

#if defined(BD_ENABLE_PROFILING)
    if (worldComponents.size() + 1 > worldComponents.capacity()) {
        logger.Warning(
            fmt::format("World's worldComponents container is over capacity - reallocating! Current capacity: {0}",
                        worldComponents.capacity()),
            M_TAG);
    }
#endif
    worldComponents.push_back(componentHandle);

    return componentHandle;
}

void World::Tick(double time) {
}

World::~World() {
}
}