#include "DirectoryExtensionSearcher.h"

#include <boost/filesystem.hpp>
#include <core/GloveException.h>
#include <boost/format.hpp>

#if defined(ON_UINX)
#include <dirent.h>
#endif

namespace glove {

bool EndsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

DirectoryExtensionSearcher::DirectoryExtensionSearcher(const std::string& searchDirectory) {
    DIR* dir = opendir(searchDirectory.c_str());

    if (!dir) {
        throw GLOVE_EXCEPTION((boost::format("Unable to open directory %1%") % searchDirectory).str());
    }

    dirent* entry = nullptr;
    while ((entry = readdir(dir)) != nullptr) {
        std::string entryName(entry->d_name);
#if defined(ON_UNIX)
        if (EndsWith(entryName, ".so")) {
            extensionFileList.push_back(searchDirectory + "/" + entryName);
        }
#elif defined(ON_WINDOWS)
        if (EndsWith(entryName, ".dll")) {
            extensionFileList.push_back(entryName);
        }
#endif
    }

    closedir(dir);
}

DirectoryExtensionSearcher::~DirectoryExtensionSearcher() {
}

IExtensionSearcher::ExtensionFileList const& DirectoryExtensionSearcher::GetExtensions() const {
    return extensionFileList;
}
}