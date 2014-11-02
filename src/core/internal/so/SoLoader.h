#pragma once
#if defined(__unix__) || defined(__unix)

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

#endif // defined(__unix__) || defined(__unix)