#include "glove/natex/NatexFacet.hpp"
#include "glove/natex/BifrostLoader.hpp"
#include "glove/log/Log.hpp"

namespace glove {

NatexFacet::NatexFacet(ServiceRegistryHandle serviceRegistry)
    : NatexFacet(std::move(serviceRegistry), std::make_shared<BifrostLoader>()) {
}

NatexFacet::NatexFacet(ServiceRegistryHandle serviceRegistry, std::shared_ptr<ModuleLoader> moduleLoader)
    : ApplicationFacet("NatexFacet"), serviceRegistry(serviceRegistry), moduleLoader(moduleLoader) {
}

void NatexFacet::AddExtensionSearcher(std::shared_ptr<ExtensionSearcher> searcher) {
    extensionSearchers.push_back(std::move(searcher));
}

void NatexFacet::Bootstrap() {
    if (!loadNativeExtensions) {
        L_INFO("Skipping Natex loading");
        return;
    }

    if (extensionSearchers.empty()) {
        L_WARNING("NatexFacet has no extension searchers. Not loading any extensions.")
        return;
    }

    for (auto& searcher : extensionSearchers) {
        LoadNativeModules(*searcher);
    }
}

void NatexFacet::LoadNativeModules(ExtensionSearcher& searcher) {
    try {
        for (auto extension : searcher.GetExtensions()) {
            try {
                auto module = moduleLoader->LoadModule(extension);
                module->Load();
                module->RegisterServices(*serviceRegistry);

                modules.push_back(std::move(module));
            } catch (GloveException& ex) {
                L_ERROR(ex);
            }
        }
    } catch (GloveException& ex) {
        L_ERROR(fmt::format("Failed to load native extensions: {0}", ex.what()));
    }
}
}