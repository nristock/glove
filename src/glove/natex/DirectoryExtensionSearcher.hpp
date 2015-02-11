#pragma once

#include <string>

#include "glove/natex/IExtensionSearcher.hpp"

namespace glove {

class GLOVE_API_EXPORT DirectoryExtensionSearcher : public IExtensionSearcher {
  public:
    DirectoryExtensionSearcher(const std::string& searchDirectory);
    virtual ~DirectoryExtensionSearcher();

    virtual const ExtensionFileList& GetExtensions() const override;

  private:
    ExtensionFileList extensionFileList;
};

} /* namespace glove */