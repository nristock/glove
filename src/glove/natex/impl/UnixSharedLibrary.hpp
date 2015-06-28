#pragma once

#include <string>

#include "glove/GloveApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/natex/SharedLibrary.hpp"

using namespace BlueDwarf;

namespace glove {

class GLOVE_API_EXPORT UnixSharedLibrary : public SharedLibrary {
  public:
    UnixSharedLibrary(const std::string& fileName);
    UnixSharedLibrary(const UnixSharedLibrary& other) = delete;
    ~UnixSharedLibrary();

    UnixSharedLibrary& operator=(const UnixSharedLibrary& other) = delete;

    virtual void* GetSymbol(const std::string& symbolName);

  private:
    void LoadDso();
    void UnloadDso();

    const std::string fileName;
    void* libraryHandle;

    Logger logger;
};

} /* namespace glove */