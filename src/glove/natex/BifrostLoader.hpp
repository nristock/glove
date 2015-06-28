#pragma once

#include <string>
#include <map>

#include "glove/GloveFwd.hpp"
#include "glove/natex/Natex.hpp"
#include "glove/natex/SharedLibraryLoader.hpp"
#include "glove/natex/ModuleLoader.hpp"
#include "glove/natex/Module.hpp"
#include "glove/log/Log.hpp"

using namespace BlueDwarf;

namespace glove {

/// @brief The default native extension module loader.
class GLOVE_API_EXPORT BifrostLoader : public ModuleLoader {
  public:
    BifrostLoader();

    template <class T>
    BifrostLoader(std::unique_ptr<T> sharedLibraryLoader)
        : libraryLoader(std::move(sharedLibraryLoader)) {}
    virtual ~BifrostLoader() {}

    virtual std::unique_ptr<Module> LoadModule(const std::string &extensionFile);

  private:
    ModuleCreateFunc GetModuleCreateFunc(SharedLibrary& library) const;

    Logger logger;
    std::unique_ptr<SharedLibraryLoader> libraryLoader;
};
} /* namespace glove */