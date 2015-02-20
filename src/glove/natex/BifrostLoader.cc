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
    LOG(logger, info, "Initializing Bifrost loader with default SoLoaderFactory (UNIX, .so)");
#elif defined(ON_WINDOWS)
    LOG(logger, info, "Initializing Bifrost loader with default DllLoaderFactory (WINDOWS, .dll)");
#else
    LOG(logger, warning, "Initializing Bifrost loader without a default SharedLibraryLoaderFactory!");
#pragma warning("Bifrost loader will not initialize a default shared library loader for the target platform")
#endif
}

std::unique_ptr<Module> BifrostLoader::LoadModule(const std::string& extensionFile) {
    LOG(logger, info, (boost::format("Loading DSO %1%...") % extensionFile).str());

    auto sharedLibrary = libraryLoader->LoadLibrary(extensionFile);
    auto moduleCreateFunc = GetModuleCreateFunc(*sharedLibrary);

    LOG(logger, info, (boost::format("Invoking module creation function for %1%...") % extensionFile).str());

    auto module = moduleCreateFunc();
    auto sharedLibModule = std::make_unique<SharedLibraryModule>(std::move(module), std::move(sharedLibrary));

    LOG(logger, info, (boost::format("Module %1% (%2%) has been created.") % module->GetName() % module->GetVersion().ToString()).str());
    return module;
}

ModuleCreateFunc BifrostLoader::GetModuleCreateFunc(SharedLibrary& library) const {
    return (ModuleCreateFunc)library.GetSymbol("CreateModule");
}
}