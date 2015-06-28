#pragma once

#include <memory>

#include "glove/BlueDwarfApi.hpp"
#include "glove/natex/SharedLibrary.hpp"

namespace BlueDwarf {

class BD_API_EXPORT SharedLibraryLoader {
  public:
    virtual ~SharedLibraryLoader() = default;

    virtual std::unique_ptr<SharedLibrary> LoadLibrary(const std::string& fileName) = 0;
};

} /* namespace BlueDwarf */