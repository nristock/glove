#include <boost/uuid/uuid_io.hpp>
#include <boost/format.hpp>

#include "glove/natex/BifrostLoader.hpp"
#include "glove/log/Log.hpp"
#include "glove/GloveException.hpp"

#include "glove/natex/impl/GloveSharedLibraryLoader.hpp"
#include "glove/natex/impl/SharedLibraryModule.hpp"

namespace glove {

BifrostLoader::BifrostLoader() : BifrostLoader(std::make_unique<GloveSharedLibraryLoader>()) {
#if defined(ON_UNIX)
    logger.Info("Initializing Bifrost loader with default SoLoaderFactory (UNIX, .so)");
#elif defined(ON_WINDOWS)
    logger.Info("Initializing Bifrost loader with default DllLoaderFactory (WINDOWS, .dll)");
#else
    logger.Warning("Initializing Bifrost loader without a default SharedLibraryLoaderFactory!");
#pragma warning("Bifrost loader will not initialize a default shared library loader for the target platform")
#endif
}

std::unique_ptr<Module> BifrostLoader::LoadModule(const std::string& extensionFile) {
    logger.Info(fmt::format("Loading DSO {0}...", extensionFile), M_TAG);

    auto sharedLibrary = libraryLoader->LoadLibrary(extensionFile);
    auto moduleCreateFunc = GetModuleCreateFunc(*sharedLibrary);

    logger.Info(fmt::format("Invoking module creation function for {0}...", extensionFile), M_TAG);

    auto module = moduleCreateFunc();
    std::unique_ptr<Module> sharedLibModule = std::make_unique<SharedLibraryModule>(std::move(module), std::move(sharedLibrary));

    logger.Info(fmt::format("Module {0} ({1}) has been created.", sharedLibModule->GetName(), sharedLibModule->GetVersion().ToString()), M_TAG);
    return sharedLibModule;
}

ModuleCreateFunc BifrostLoader::GetModuleCreateFunc(SharedLibrary& library) const {
    return (ModuleCreateFunc)library.GetSymbol("CreateModule");
}
}