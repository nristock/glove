// FIXME
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <tclap/CmdLine.h>

#include "glove/GloveConfig.hpp"
#include "glove/GloveCore.hpp"
#include "glove/natex/Natex.hpp"
#include "glove/GloveException.hpp"
#include "glove/log/Log.hpp"
#include "glove/utils/builder/CoreBuilder.hpp"
#include "glove/services/impl/GloveServiceRegistry.hpp"

namespace glove {

CoreBuilder::CoreBuilder() : skipNatex(false) {
    loadedModules.reserve(20);
    engineConfig.LoadDefaults();
    configPath = "data/glove.yaml";
}

CoreBuilder &CoreBuilder::ParseCommandLineArgs(int argc, const char **argv) {
    using namespace TCLAP;

    try {
        CmdLine cmd("Glove Engine", ' ', GLOVE_VERSION_STRING);

        ValueArg<std::string> configFile("c", "config", "Path to engine configuration", false,
                "data/glove.yaml", "path", cmd);
        SwitchArg skipNatexLoading("", "no-natex", "Skip native extension loading", cmd);
        cmd.parse(argc, argv);

        skipNatex = skipNatexLoading.isSet();
        configPath = configFile.getValue();
    } catch (ArgException &ex) {
        // Failing to parse the command line is a recoverable error so don't bubble up the exception and continue as
        // usual
        LOG(logger, error, (boost::format("Failed to parse command line: %1%") % ex.error()).str());
    }

    return *this;
}

CoreBuilder &CoreBuilder::LoadConfigurationFile() {
    return LoadConfigurationFile(configPath);
}

CoreBuilder &CoreBuilder::LoadConfigurationFile(const std::string &filePath) {
    if (!boost::filesystem::exists(filePath)) {
        engineConfig.SaveToFile(filePath);
        return *this;
    }

    try {
        engineConfig.LoadFromFile(filePath);
    } catch (GloveException &ex) {
        LOG(logger, error, (boost::format("Failed to load glove.yaml: \n%1%") % ex.what()).str());
    }

    ApplyCommandLineArgumentsToConfig();

    return *this;
}

void CoreBuilder::ApplyCommandLineArgumentsToConfig() {
    if (skipNatex) {
        engineConfig.engine.loadNativeExtensions = false;
    }
}

GloveCorePtr CoreBuilder::Finalize() {
    EnsureServiceRegistry();

    return std::make_shared<GloveCore>(engineConfig, serviceRegistry, loadedModules);
}

CoreBuilder &CoreBuilder::LoadNativeModules(ExtensionSearcher &searcher) {
    if (!engineConfig.engine.loadNativeExtensions || skipNatex) {
        return *this;
    }

    EnsureServiceRegistry();
    EnsureModuleLoader();

    try {
        for (auto extension : searcher.GetExtensions()) {
            try {
                auto module = moduleLoader->LoadModule(extension);
                module->Load();
            } catch (GloveException &ex) {
                LOG(logger, error, ex.what());
            }
        }
    } catch (GloveException &ex) {
        LOG(logger, error, (boost::format("Failed to load native extensions: %1%") % ex.what()).str());
    }

    return *this;
}

CoreBuilder &CoreBuilder::SetModuleLoader(ModuleLoaderHandle loader) {
    if (moduleLoader) {
        //todo: throw
    }

    moduleLoader = loader;
    return *this;
}

void CoreBuilder::EnsureModuleLoader() {
    if (!moduleLoader) {
        SetDefaultModuleLoader();
    }
}

CoreBuilder &CoreBuilder::LoadNativeModules() {
    auto extensionSearcher = DirectoryExtensionSearcher("data/natex");
    return LoadNativeModules(extensionSearcher);
}

void CoreBuilder::SetDefaultModuleLoader() {
    SetModuleLoader(std::make_shared<BifrostLoader>());
}

CoreBuilder &CoreBuilder::SkipModuleLoading() {
    skipNatex = true;
    return *this;
}

CoreBuilder &CoreBuilder::SetServiceRegistry(ServiceRegistryHandle serviceRegistry) {
    if (this->serviceRegistry) {
        //todo throw
    }

    this->serviceRegistry = serviceRegistry;

    return *this;
}

void CoreBuilder::SetDefaultServiceRegistry() {
    SetServiceRegistry(std::make_shared<GloveServiceRegistry>());
}

void CoreBuilder::EnsureServiceRegistry() {
    if (!serviceRegistry) {
        SetDefaultServiceRegistry();
    }
}
}