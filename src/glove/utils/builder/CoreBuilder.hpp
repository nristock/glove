#pragma once

#include "glove/natex/Natex.hpp"
#include "glove/GloveApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/configuration/Configuration.hpp"

namespace glove {

class GLOVE_API_EXPORT CoreBuilder {
  public:
    CoreBuilder();

    CoreBuilder& ParseCommandLineArgs(int argc, const char** argv);
    CoreBuilder& LoadConfigurationFile();
    CoreBuilder& LoadConfigurationFile(const std::string& filePath);
    CoreBuilder& SetEventBus(const EventBusPtr& eventBus);
    CoreBuilder& LoadNativeModules();
    CoreBuilder& LoadNativeModules(ExtensionSearcher& extensionSearcher);
    CoreBuilder& SetModuleLoader(ModuleLoaderHandle loader);
    CoreBuilder& SetServiceRegistry(ServiceRegistryHandle serviceRegistry);
    CoreBuilder& SkipModuleLoading();

    template<class T>
    CoreBuilder& RegisterService(std::shared_ptr<T> service) {
        EnsureServiceRegistry();

        serviceRegistry->RegisterService(std::move(service));

        return *this;
    }

    GloveCorePtr Finalize();

  protected:
    void ApplyCommandLineArgumentsToConfig();

    void SetDefaultEventBus();
    void SetDefaultModuleLoader();
    void SetDefaultServiceRegistry();

    void EnsureEventBus();
    void EnsureModuleLoader();
    void EnsureServiceRegistry();

    logging::GloveLogger logger;

    Configuration engineConfig;

    // Command Line Options
    bool skipNatex;
    std::string configPath;

    ServiceRegistryHandle serviceRegistry;

    // Natex
    std::vector<std::shared_ptr<Module>> loadedModules;
    ModuleLoaderHandle  moduleLoader;
};

} /* namespace glove */