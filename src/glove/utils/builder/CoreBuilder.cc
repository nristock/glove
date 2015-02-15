// FIXME
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <tclap/CmdLine.h>

#include "GloveConfig.h"
#include "glove/GloveCore.hpp"
#include "glove/natex/DirectoryExtensionSearcher.hpp"
#include "glove/events/type/PreExtensionLoadEvent.hpp"
#include "glove/events/type/NativeExtensionLoadedEvent.hpp"
#include "glove/events/EventBus.hpp"
#include "glove/natex/GloveSubsystemDefinitionRegistry.hpp"
#include "glove/natex/GloveSubsystemInstanceRegistry.hpp"
#include "glove/natex/IExtensionSearcher.hpp"
#include "glove/GloveException.hpp"
#include "glove/log/Log.hpp"
#include "glove/utils/builder/CoreBuilder.hpp"
#include "glove/input/InputManager.hpp"

namespace glove {

CoreBuilder::CoreBuilder() : skipNatex(false), subsystemInstantiated(false) {
    engineConfig.LoadDefaults();
    configPath = "data/glove.yaml";
}

CoreBuilder& CoreBuilder::ParseCommandLineArgs(int argc, const char** argv) {
    using namespace TCLAP;

    try {
        CmdLine cmd("Glove Engine", ' ', GLOVE_VERSION_STRING);

        ValueArg<std::string> configFile("c", "config", "Path to engine configuration", false,
                                         "data/glove.yaml", "path", cmd);
        SwitchArg skipNatexLoading("", "no-natex", "Skip native extension loading", cmd);
        cmd.parse(argc, argv);

        skipNatex = skipNatexLoading.isSet();
        configPath = configFile.getValue();
    } catch (ArgException& ex) {
        // Failing to parse the command line is a recoverable error so don't bubble up the exception and continue as
        // usual
        LOG(logger, error, (boost::format("Failed to parse command line: %1%") % ex.error()).str());
    }

    return *this;
}

CoreBuilder& CoreBuilder::LoadConfigurationFile() {
    return LoadConfigurationFile(configPath);
}

CoreBuilder& CoreBuilder::LoadConfigurationFile(const std::string& filePath) {
    if (!boost::filesystem::exists(filePath)) {
        engineConfig.SaveToFile(filePath);
        return *this;
    }

    try {
        engineConfig.LoadFromFile(filePath);
    } catch (GloveException& ex) {
        LOG(logger, error, (boost::format("Failed to load glove.yaml: \n%1%") % ex.what()).str());
    }

    ApplyCommandLineArgumentsToConfig();

    return *this;
}

void CoreBuilder::ApplyCommandLineArgumentsToConfig() {
    if(skipNatex) {
        engineConfig.engine.loadNativeExtensions = false;
    }
}

GloveCorePtr CoreBuilder::Finalize() {
    EnsureEventBus();
    EnsureInputManager();
    EnsureSystemExtensionLoader();
    EnsureSubsystemInstanceRegistry();

    if(!subsystemInstantiated) {
        InstantiateSubsystems();
    }

    return std::make_shared<GloveCore>(engineConfig, eventBus, inputManager, subsystemInstanceRegistry, systemExtensionLoader);
}

CoreBuilder& CoreBuilder::SetSubsystemDefinitionRegistry(const ISubsystemDefinitionRegistryPtr& registry) {
    if(subsystemDefinitionRegistry) {
        //todo: throw
    }

    subsystemDefinitionRegistry = registry;
    return *this;
}

CoreBuilder& CoreBuilder::SetSubsystemInstanceRegistry(const ISubsystemInstanceRegistryPtr& registry) {
    if(subsystemInstanceRegistry) {
        //todo: throw
    }

    subsystemInstanceRegistry = registry;
    return *this;
}

CoreBuilder& CoreBuilder::SetEventBus(const EventBusPtr& eventBus) {
    if(this->eventBus) {
        //todo: throw
    }

    this->eventBus = eventBus;
    return *this;
}

CoreBuilder& CoreBuilder::LoadNativeExtensions(const IExtensionSearcherPtr& searcher) {
    if(!engineConfig.engine.loadNativeExtensions) {
        return *this;
    }

    EnsureEventBus();
    EnsureSystemExtensionLoader();
    EnsureSubsystemDefinitionRegistry();

    try {
        for (auto extension : searcher->GetExtensions()) {
            try {
                PreExtensionLoadEvent preloadEvent;
                eventBus->Publish(preloadEvent);

                ISystemExtensionPtr systemExtension = systemExtensionLoader->LoadSystemExtension(extension);
                systemExtension->RegisterSubsystems(subsystemDefinitionRegistry);

                NativeExtensionLoadedEvent postloadEvent;
                eventBus->Publish(postloadEvent);
            } catch (GloveException& ex) {
                LOG(logger, error, ex.what());
            }
        }
    } catch (GloveException& ex) {
        LOG(logger, error, (boost::format("Failed to load native extensions: %1%") % ex.what()).str());
    }

    return *this;
}

CoreBuilder& CoreBuilder::InstantiateSubsystems() {
    EnsureSubsystemDefinitionRegistry();
    EnsureSubsystemInstanceRegistry();

    subsystemInstanceRegistry->InstantiateDefinitionRegistry(subsystemDefinitionRegistry);
    subsystemInstantiated = true;

    return *this;
}

CoreBuilder& CoreBuilder::SetInputManager(const InputManagerPtr& inputManager) {
    if(this->inputManager) {
        //todo: throw
    }

    this->inputManager = inputManager;
    return *this;
}

CoreBuilder& CoreBuilder::SetSystemExtensionLoader(const ISystemExtensionLoaderHandle& loader) {
    if(systemExtensionLoader) {
        //todo: throw
    }

    systemExtensionLoader = loader;
    return *this;
}

void CoreBuilder::SetDefaultSubsystemDefinitionRegistry() {
    SetSubsystemDefinitionRegistry(std::make_shared<GloveSubsystemDefinitionRegistry>());
}

void CoreBuilder::SetDefaultSubsystemInstanceRegistry() {
    EnsureEventBus();

    SetSubsystemInstanceRegistry(std::make_shared<GloveSubsystemInstanceRegistry>(eventBus));
}

void CoreBuilder::SetDefaultEventBus() {
    SetEventBus(std::make_shared<EventBus>());
}

void CoreBuilder::SetDefaultInputManager() {
    EnsureEventBus();

    SetInputManager(std::make_shared<InputManager>(eventBus));
}

void CoreBuilder::EnsureEventBus() {
    if(!eventBus) {
        SetDefaultEventBus();
    }
}

void CoreBuilder::EnsureInputManager() {
    if(!inputManager) {
        SetDefaultInputManager();
    }
}

void CoreBuilder::EnsureSubsystemDefinitionRegistry() {
    if(!subsystemDefinitionRegistry) {
        SetDefaultSubsystemDefinitionRegistry();
    }
}

void CoreBuilder::EnsureSubsystemInstanceRegistry() {
    if(!subsystemInstanceRegistry) {
        SetDefaultSubsystemInstanceRegistry();
    }
}

void CoreBuilder::EnsureSystemExtensionLoader() {
    if(!systemExtensionLoader) {
        SetDefaultSystemExtensionLoader();
    }
}

CoreBuilder& CoreBuilder::LoadNativeExtensions() {
    return LoadNativeExtensions(std::make_shared<DirectoryExtensionSearcher>("data/natex"));
}

void CoreBuilder::SetDefaultSystemExtensionLoader() {
    SetSystemExtensionLoader(std::make_shared<BifrostLoader>());
}

CoreBuilder& CoreBuilder::SkipSubsystemInstantiation() {
    subsystemInstantiated = true;
    return *this;
}
}