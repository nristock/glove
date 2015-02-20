#pragma once

#include <vector>

#include "glove/GloveApi.hpp"

namespace glove {

class GLOVE_API_EXPORT ExtensionSearcher {
  public:
    typedef std::vector<std::string> ExtensionFileList;

    virtual ~ExtensionSearcher(){};

    /// @brief Returns all discovered extensions.
    ///
    /// @detail Extension discovery should happen during object construction following RAII principles.
    virtual const ExtensionFileList& GetExtensions() const = 0;
};

} /* namespace glove */