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
    CoreBuilder& SetSubsystemDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& registry);
    CoreBuilder& SetSubsystemInstanceRegistry(const ISubsystemInstanceRegistryPtr& registry);
    CoreBuilder& SetEventBus(const EventBusPtr& eventBus);
    CoreBuilder& LoadNativeExtensions();
    CoreBuilder& LoadNativeExtensions(const IExtensionSearcherPtr& searcher);
    CoreBuilder& SetSystemExtensionLoader(const ISystemExtensionLoaderHandle& loader);
    CoreBuilder& InstantiateSubsystems();
    CoreBuilder& SetInputManager(const InputManagerPtr& inputManager);
    CoreBuilder& SkipSubsystemInstantiation();

    GloveCorePtr Finalize();

  protected:
    void ApplyCommandLineArgumentsToConfig();

    void SetDefaultInputManager();
    void SetDefaultEventBus();
    void SetDefaultSubsystemDefinitionRegistry();
    void SetDefaultSubsystemInstanceRegistry();
    void SetDefaultSystemExtensionLoader();

    void EnsureEventBus();
    void EnsureSubsystemDefinitionRegistry();
    void EnsureSubsystemInstanceRegistry();
    void EnsureInputManager();
    void EnsureSystemExtensionLoader();

    logging::GloveLogger logger;

    Configuration engineConfig;

    // Command Line Options
    bool skipNatex;
    std::string configPath;

    EventBusPtr eventBus;
    InputManagerPtr inputManager;

    // Natex
    bool subsystemInstantiated;
    ISubsystemDefinitionRegistryPtr subsystemDefinitionRegistry;
    ISubsystemInstanceRegistryPtr subsystemInstanceRegistry;
    ISystemExtensionLoaderHandle systemExtensionLoader;
};

} /* namespace glove */