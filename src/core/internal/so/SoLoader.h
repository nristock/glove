#pragma once
#if defined(ON_UNIX)

#include <string>

#include <core/natex/ISharedLibraryLoader.h>
#include <log/Log.h>

namespace glove {

class SoLoader : public ISharedLibraryLoader {
  public:
    SoLoader(const std::string& soFilePath);
    virtual ~SoLoader();

    virtual void* LoadSymbol(const std::string& symbolName);

    virtual void ReloadLibrary();

  private:
    const std::string libraryFile;
    logging::GloveLogger logger;

    void* libraryHandle;

    void LoadLibrary();
    void UnloadLibrary();
};

} /* namespace glove */

#endif // defined(ON_UNIX)