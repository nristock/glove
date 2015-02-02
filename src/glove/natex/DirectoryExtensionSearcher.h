#pragma once

#include <string>

#include "glove/natex/IExtensionSearcher.h"

namespace glove {

class DirectoryExtensionSearcher : public IExtensionSearcher {
  public:
    DirectoryExtensionSearcher(const std::string& searchDirectory);
    virtual ~DirectoryExtensionSearcher();

    virtual const ExtensionFileList& GetExtensions() const override;

  private:
    ExtensionFileList extensionFileList;
};

} /* namespace glove */