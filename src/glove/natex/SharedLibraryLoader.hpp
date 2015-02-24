#pragma once

#include <memory>

#include "glove/GloveApi.hpp"
#include "glove/natex/SharedLibrary.hpp"

namespace glove {

class GLOVE_API_EXPORT SharedLibraryLoader {
  public:
    virtual ~SharedLibraryLoader() = default;

    virtual std::unique_ptr<SharedLibrary> LoadLibrary(const std::string& fileName) = 0;
};

} /* namespace glove */