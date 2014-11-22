#include "BifrostLoader.h"

#include <boost/uuid/uuid_io.hpp>
#include <boost/format.hpp>

#include <core/natex/ISharedLibraryLoader.h>

#if defined(__unix__) || defined(__unix)
#include <core/internal/so/SoLoaderFactory.h>
#endif

namespace glove {

BifrostLoader::BifrostLoader() {
#if defined(ON_UNIX)
    LOG(logger, info, "Initializing Bifrost loader with default SoLoaderFactory (UNIX, .so)");
    loaderFactory = std::make_shared<SoLoaderFactory>();
#elif defined(ON_WINDOWS)
    LOG(logger, info, "Initializing Bifrost loader with default DllLoaderFactory (WINDOWS, .dll)");
// Not implemented yet
#else
    LOG(logger, warning, "Initializing Bifrost loader without a default SharedLibraryLoaderFactory!");
#pragma warning("Bifrost loader will not initialize a default shared library loader for the target platform")
#endif
}

BifrostLoader::BifrostLoader(const ISharedLibraryLoaderFactoryPtr& sharedLibraryLoaderFactory)
    : loaderFactory(sharedLibraryLoaderFactory) {}

ISystemExtensionPtr BifrostLoader::LoadSystemExtension(const std::string& extensionFile) {
    LOG(logger, info, (boost::format("Creating library loader for %1%...") % extensionFile).str());

    ISharedLibraryLoaderPtr sharedLibraryLoader = this->CreateLibraryLoader(extensionFile);

    LoadSystemExtensionLibraryFunc extensionLoaderFunc = sharedLibraryLoader->GetLibraryLoaderFunc();

    LOG(logger, info, (boost::format("Invoking extension loader function for %1%...") % extensionFile).str());

    // We currently have to allocate the shared_ptr object inside the main module to prevent memory invalidation when
    // the extension's SO/DLL is unloaded
    ISystemExtensionSharedPtr systemExtension(extensionLoaderFunc());

    loadedExtensions.insert(
        std::make_pair(systemExtension->GetExtensionUuid(), std::make_pair(sharedLibraryLoader, systemExtension)));

    LOG(logger, info, (boost::format("Extension %1% (%2%) has been loaded.") % systemExtension->GetExtensionUuid() %
                       systemExtension->GetExtensionName()).str());
    return systemExtension;
}

void BifrostLoader::UnloadSystemExtension(const ISystemExtensionPtr& systemExtensionWeakPtr) {
    const ExtensionUuid extensionUuid = systemExtensionWeakPtr.lock()->GetExtensionUuid();
    const std::string extensionName = systemExtensionWeakPtr.lock()->GetExtensionName();

    {
        SystemExtensionMap::iterator iter = loadedExtensions.find(extensionUuid);

        UnloadSystemExtensionLibraryFunc extensionUnloaderFunc = iter->second.first->GetLibraryUnloaderFunc();

        if (!iter->second.second.unique()) {
            LOG(logger, warning,
                (boost::format("Unloading extension module %1% which still has references :(") % extensionUuid).str());
        }
        iter->second.second.reset();

        LOG(logger, info, (boost::format("Invoking extension unloader function for %1% (%2%)...") % extensionUuid %
                           extensionName).str());
        extensionUnloaderFunc();
    }

    loadedExtensions.erase(extensionUuid);

    LOG(logger, info, (boost::format("Extension %1% has been unloaded.") % extensionUuid).str());
}

ISharedLibraryLoaderPtr BifrostLoader::CreateLibraryLoader(const std::string& libraryFilePath) {
    return loaderFactory->CreateLibraryLoader(libraryFilePath);
}
}