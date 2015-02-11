#pragma once
#if defined(ON_UNIX)

#include <string>

#include "glove/natex/ISharedLibraryLoader.hpp"
#include "glove/log/Log.hpp"

namespace glove {

class SoLoader : public ISharedLibraryLoader {
  public:
    SoLoader(const std::string& soFilePath);
    virtual ~SoLoader();

    virtual void* LoadSymbol(const std::string& symbolName) override;

    virtual void ReloadLibrary() override;

    virtual LoadSystemExtensionLibraryFunc GetLibraryLoaderFunc() override;

    virtual UnloadSystemExtensionLibraryFunc GetLibraryUnloaderFunc() override;

  private:
    const std::string libraryFile;
    logging::GloveLogger logger;

    void* libraryHandle;

    void LoadLibrary();
    void UnloadLibrary();
};

} /* namespace glove */

#endif // defined(ON_UNIX)