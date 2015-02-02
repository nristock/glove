#pragma once

#include <string>
#include <map>

#include "glove/GloveFwd.hpp"
#include "glove/natex/Natex.h"
#include "glove/natex/ISharedLibraryLoaderFactory.h"
#include "glove/natex/ISystemExtensionLoader.h"
#include "glove/natex/ISystemExtension.h"
#include "glove/log/Log.h"

namespace glove {

/// @brief The Bifrost loader is the default system extension loader.
class BifrostLoader : public ISystemExtensionLoader {
  public:
    typedef std::pair<ISharedLibraryLoaderPtr, ISystemExtensionPtr> SystemExtensionAndLoader;
    typedef std::map<ExtensionUuid, SystemExtensionAndLoader> SystemExtensionMap;

    BifrostLoader();
    BifrostLoader(const ISharedLibraryLoaderFactoryPtr& sharedLibraryLoaderFactory);
    virtual ~BifrostLoader() {}

    virtual ISystemExtensionPtr LoadSystemExtension(const std::string& extensionFile);
    virtual void UnloadSystemExtension(ISystemExtensionPtr& systemExtension);

  private:
    logging::GloveLogger logger;

    SystemExtensionMap loadedExtensions;

    ISharedLibraryLoaderFactoryPtr loaderFactory;

    ISharedLibraryLoaderPtr CreateLibraryLoader(const std::string& libraryFilePath);
};
} /* namespace glove */