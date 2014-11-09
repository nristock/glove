#pragma once
#if defined(ON_UNIX)

#include <string>

#include <core/ISharedLibraryLoader.h>
#include <log/Log.h>

namespace glove {

class SoLoader : public ISharedLibraryLoader {
public:
    SoLoader(const std::string& soFilePath);
    virtual ~SoLoader();


    virtual void* LoadSymbol(const std::string& symbolName);

private:
    logging::GloveLogger logger;

    void* libraryHandle;
};

} /* namespace glove */

#endif // defined(ON_UNIX)