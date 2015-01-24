#include "UnixAbstractionLayer.hpp"

namespace glove {
const std::string UnixAbstractionLayer::SEPARATOR = "/";

const FileInfo UnixAbstractionLayer::GetFileInfo(const std::string& path) {
    struct stat unixFileInfo;
    if(stat(path.c_str(), &unixFileInfo) == -1) {
        switch (errno) {
            case EBADF:
                break;

            case EFAULT:
                break;

            case ELOOP:
                break;

            case ENAMETOOLONG:
                break;

            case ENOENT:
                return FileInfo(FileInfo::FileType::NONE, 0);

            case ENOMEM:
                break;

            case ENOTDIR:
                return FileInfo(FileInfo::FileType::NONE, 0);

            case EOVERFLOW:
                break;
        }
    }

    if(S_ISREG(unixFileInfo.st_mode)) {
        return FileInfo(FileInfo::FileType::REGULAR, static_cast<std::size_t>(unixFileInfo.st_size));
    } else if(S_ISDIR(unixFileInfo.st_mode)) {
        return FileInfo(FileInfo::FileType::DIRECTORY, static_cast<std::size_t>(unixFileInfo.st_size));
    }

    //TODO not expected
}
}