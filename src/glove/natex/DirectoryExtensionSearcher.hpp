#pragma once

#include <string>

#include "glove/natex/ExtensionSearcher.hpp"

namespace glove {

class GLOVE_API_EXPORT DirectoryExtensionSearcher : public ExtensionSearcher {
  public:
    DirectoryExtensionSearcher(const std::string& searchDirectory);
    virtual ~DirectoryExtensionSearcher();

    virtual const ExtensionFileList& GetExtensions() const override;

  private:
    ExtensionFileList extensionFileList;
};

} /* namespace glove */