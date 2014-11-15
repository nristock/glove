#include <vector>

#pragma once

namespace glove {

class IExtensionSearcher {
  public:
    typedef std::vector<std::string> ExtensionFileList;

    virtual ~IExtensionSearcher() {};

    /// @brief Returns all discovered extensions.
    ///
    /// @detail Extension discovery should happen during object construction following RAII principles.
    virtual const ExtensionFileList& GetExtensions() const = 0;
};

} /* namespace glove */