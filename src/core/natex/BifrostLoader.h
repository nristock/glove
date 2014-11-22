#pragma once

#include <string>
#include <map>

#include <core/GloveFwd.h>
#include "Natex.h"
#include "ISharedLibraryLoaderFactory.h"
#include "ISystemExtensionLoader.h"
#include "ISystemExtension.h"
#include <core/log/Log.h>

namespace glove {

/// @brief The Bifrost loader is the default system extension loader.
class BifrostLoader : public ISystemExtensionLoader {
  public:
    typedef std::pair<ISharedLibraryLoaderPtr, ISystemExtensionSharedPtr> SystemExtensionAndLoader;
    typedef std::map<ExtensionUuid, SystemExtensionAndLoader> SystemExtensionMap;

    BifrostLoader();
    BifrostLoader(const ISharedLibraryLoaderFactoryPtr& sharedLibraryLoaderFactory);
    virtual ~BifrostLoader() {}

    virtual ISystemExtensionPtr LoadSystemExtension(const std::string& extensionFile);
    virtual void UnloadSystemExtension(const ISystemExtensionPtr& systemExtension);

  private:
    logging::GloveLogger logger;

    SystemExtensionMap loadedExtensions;

    ISharedLibraryLoaderFactoryPtr loaderFactory;

    ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath);
};
} /* namespace glove */