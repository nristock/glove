#pragma once

#include "glove/application/DwarfApplication.hpp"
#include "glove/services/ServiceRegistry.hpp"
#include "glove/rendering/WindowFactoryService.hpp"
#include "glove/rendering/ApplicationViewport.hpp"

using namespace BlueDwarf;

class WindowFacet : public ApplicationFacet {
  public:
    WindowFacet(ServiceRegistryHandle serviceRegistry)
        : ApplicationFacet("WindowFacet"), serviceRegistry(serviceRegistry) {}

    virtual void Initialize() override {
        RenderDispatcher::RunOnRenderThread(
            [this]() {
                auto service = serviceRegistry->GetService(WindowFactoryService::Type);
                auto windowFactory = std::dynamic_pointer_cast<WindowFactoryService>(service);

                window = WindowBuilder().SetSize({800, 600}).SetTitle("Awesome Window").Finalize(*windowFactory);
            })->AwaitCompletion();
    }

    std::shared_ptr<ViewportClient> GetWindow() const { return window; }

    bool ExitRequested() { return window->ShouldClose(); }

  private:
    ServiceRegistryHandle serviceRegistry;

    std::shared_ptr<ViewportClient> window;
};