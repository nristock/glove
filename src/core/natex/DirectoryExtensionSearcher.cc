#include "DirectoryExtensionSearcher.h"

#include <boost/filesystem.hpp>
#include <core/GloveException.h>
#include <boost/format.hpp>

#if defined(ON_UNIX)
#include <dirent.h>
#elif defined(ON_WINDOWS)
#include <windows.h>
#include <strsafe.h>
#endif

namespace glove {

bool EndsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

#if defined(ON_UNIX)
DirectoryExtensionSearcher::DirectoryExtensionSearcher(const std::string& searchDirectory) {
    DIR* dir = opendir(searchDirectory.c_str());

    if (!dir) {
        throw GLOVE_EXCEPTION((boost::format("Unable to open directory %1%") % searchDirectory).str());
    }

    dirent* entry = nullptr;
    while ((entry = readdir(dir)) != nullptr) {
        std::string entryName(entry->d_name);

        if (EndsWith(entryName, ".so")) {
            extensionFileList.push_back(searchDirectory + "/" + entryName);
        }
    }

    closedir(dir);
}
#elif defined(ON_WINDOWS)
DirectoryExtensionSearcher::DirectoryExtensionSearcher(const std::string& searchDirectory) {
    TCHAR searchDir[MAX_PATH];

    StringCchCopy(searchDir, MAX_PATH, searchDirectory.c_str());
    StringCchCat(searchDir, MAX_PATH, TEXT("\\*.dll"));

    WIN32_FIND_DATA fileFindData;
    HANDLE findHandle = FindFirstFile(searchDir, &fileFindData);

    if (findHandle == INVALID_HANDLE_VALUE) {
        DWORD winApiError = GetLastError();
        if (winApiError == ERROR_FILE_NOT_FOUND) {
            return;
        }

        throw GLOVE_EXCEPTION((boost::format("Error finding first file in directory %1% (WinApi Error %2%)") %
                               searchDirectory % winApiError).str());
    }

    do {
        if (fileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }

        extensionFileList.push_back(searchDirectory + "\\" + fileFindData.cFileName);
    } while (FindNextFile(findHandle, &fileFindData) != 0);
}
#endif

DirectoryExtensionSearcher::~DirectoryExtensionSearcher() {
}

IExtensionSearcher::ExtensionFileList const& DirectoryExtensionSearcher::GetExtensions() const {
    return extensionFileList;
}
}