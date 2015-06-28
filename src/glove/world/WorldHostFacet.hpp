#pragma once

#include "glove/GloveApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/world/World.hpp"

namespace glove {
class RendererService;

class GLOVE_API_EXPORT WorldHostFacet : public ApplicationFacet {
  public:
    WorldHostFacet(ServiceRegistryHandle serviceRegistry)  : ApplicationFacet("WorldHostFacet"), serviceRegistry(serviceRegistry) {}

    virtual void Initialize() override {
        auto rawRendererService = serviceRegistry->GetService(RendererService::Type);
        auto rendererService = std::dynamic_pointer_cast<RendererService>(rawRendererService);

        gameWorld = std::make_shared<World>(WorldConstructionHints{}, rendererService);
    }

    World::Handle GetWorld() const {return gameWorld;}

  private:
    ServiceRegistryHandle serviceRegistry;
    World::Handle gameWorld;
};
}