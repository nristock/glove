#include <glove/rendering/material/MaterialLoader.hpp>
#include "glove/application/DwarfApplication.hpp"

#include "glove/log/LoggingFacet.hpp"
#include "glove/rendering/RenderingCoreFacet.hpp"
#include "glove/services/ServicesFacet.hpp"
#include "glove/natex/NatexFacet.hpp"
#include "glove/world/WorldHostFacet.hpp"
#include "glove/rendering/ApplicationViewport.hpp"
#include "glove/rendering/ForwardSceneRenderer.hpp"
#include "glove/rendering/RendererService.hpp"

#include "glove/world/entity/Entity.hpp"
#include "glove/geometry/MeshComponent.hpp"
#include "glove/CommonTypes.hpp"

#include "facets/NatexFacetConfigurator.hpp"
#include "facets/WindowFacet.hpp"

using namespace BlueDwarf;

class SandboxApp : public DwarfApplication {
  public:
    SandboxApp() {
        loggingFacet = std::make_shared<LoggingFacet>();
        renderCoreFacet = std::make_shared<RenderingCoreFacet>();
        servicesFacet = std::make_shared<ServicesFacet>();
        natexFacet = std::make_shared<NatexFacet>(servicesFacet->GetServiceRegistry());
        natexConfigurator = std::make_shared<NatexFacetConfigurator>(natexFacet);
        worldHostFacet = std::make_shared<WorldHostFacet>(servicesFacet->GetServiceRegistry());
        windowFacet = std::make_shared<WindowFacet>(servicesFacet->GetServiceRegistry());

        AddFacet(loggingFacet);
        AddFacet(renderCoreFacet);
        AddFacet(servicesFacet);
        AddFacet(natexConfigurator);
        AddFacet(natexFacet);
        AddFacet(worldHostFacet);
        AddFacet(windowFacet);
    }

    virtual void RunLoop() override {
        auto rawRendererService = servicesFacet->GetServiceRegistry()->GetService(RendererService::Type);
        auto rendererService = std::dynamic_pointer_cast<RendererService>(rawRendererService);

        viewport = std::make_shared<ApplicationViewport>(rendererService->GetRenderHardwareInterface());
        auto sceneRenderer = std::make_unique<ForwardSceneRenderer>(worldHostFacet->GetWorld()->GetScene(), rendererService->GetRenderHardwareInterface());

        viewport->SetSceneRenderer(std::move(sceneRenderer));

        CreateWorld(*(rendererService->GetRenderHardwareInterface()));

        while(!windowFacet->ExitRequested()) {
            viewport->BeginDraw(windowFacet->GetWindow());
            viewport->EndDraw();
        }
    }

    void CreateWorld(RenderHardwareInterface& rhi) {
        MaterialLoader matLoader;
        auto futureMat = matLoader.Load(StringId("AwesomeMaterial"), rhi.CreateResourceFactory());

        auto world = worldHostFacet->GetWorld();

        auto quadEntity = world->AddEntity(EntityLifeExpectancy::LONG);

        auto meshComponent = std::unique_ptr<MeshComponent>{new MeshComponent()};
        meshComponent->SetMaterial(futureMat.GetMaterial());
        quadEntity->AttachComponent(std::move(meshComponent));

    }

  protected:
    std::shared_ptr<LoggingFacet> loggingFacet;
    std::shared_ptr<RenderingCoreFacet> renderCoreFacet;
    std::shared_ptr<ServicesFacet> servicesFacet;
    std::shared_ptr<NatexFacet> natexFacet;
    std::shared_ptr<NatexFacetConfigurator> natexConfigurator;
    std::shared_ptr<WorldHostFacet> worldHostFacet;
    std::shared_ptr<WindowFacet> windowFacet;

    std::shared_ptr<ApplicationViewport> viewport;
};

int main() {
    SandboxApp app{};
    app.Run();

    return 0;
}
