#include <boost/format.hpp>

#include "glove/filesystem/compression/ZipArchive.hpp"
#include "glove/GloveException.hpp"

namespace glove {

ZipArchive::ZipArchive(const Path& path) : ZipArchive(path, false) {
}

ZipArchive::ZipArchive(const Path& path, bool checkConsistency) : path(path) {
    int error = 0;

    // Have to use NativeFilesystemAccessor here since zip_open implicitly accesses the native file system
    zipStruct = zip_open(path.ToString().c_str(), checkConsistency ? ZIP_CHECKCONS : 0, &error);

    switch (error) {
        case 0:
            break;

        case ZIP_ER_EXISTS:
            throw GLOVE_EXCEPTION("The file specified by path exists and ZIP_EXCL is set.");

        case ZIP_ER_INCONS:
            throw GLOVE_EXCEPTION("Inconsistencies were found in the file specified by path.");

        case ZIP_ER_INVAL:
            throw GLOVE_EXCEPTION("The path argument is NULL.");

        case ZIP_ER_MEMORY:
            throw GLOVE_EXCEPTION("Required memory could not be allocated.");

        case ZIP_ER_NOENT:
            throw GLOVE_EXCEPTION("The file specified by path does not exist and ZIP_CREATE is not set.");

        case ZIP_ER_NOZIP:
            throw GLOVE_EXCEPTION("The file specified by path is not a zip archive.");

        case ZIP_ER_OPEN:
            throw GLOVE_EXCEPTION("The file specified by path could not be opened.");

        case ZIP_ER_READ:
            throw GLOVE_EXCEPTION("A read error occurred");

        case ZIP_ER_SEEK:
            throw GLOVE_EXCEPTION("The file specified by path does not allow seeks.");

        default:
            throw GLOVE_EXCEPTION("An unknown error occured while opening a zip archive.");
    }
}

const std::vector<ZipEntry>& ZipArchive::GetEntries() {
    if(fileEntries.size() == 0) {
        ReadFileIndex();
    }

    return fileEntries;
}

void ZipArchive::ReadFileIndex() {
    zip_int64_t numEntries =static_cast<std::size_t>(zip_get_num_entries(zipStruct, 0));
    if(numEntries < 0) {
        throw GLOVE_EXCEPTION("Invalid archive pointer.");
    }

    fileEntries.reserve(static_cast<std::size_t>(numEntries));

    struct zip_stat stat;
    zip_stat_init(&stat);

    for(zip_int64_t i = 0; i < numEntries; ++i) {
        zip_stat_index(zipStruct, static_cast<zip_uint64_t>(i), 0, &stat);
        fileEntries.emplace_back(stat);
    }
}

ZipArchive::~ZipArchive() {
    if(zipStruct) {
        zip_close(zipStruct);
    }
}

bool ZipArchive::HasEntry(const std::string& entryName) {
    return zip_name_locate(zipStruct, entryName.c_str(), ZIP_FL_ENC_GUESS) != -1;
}

ZipEntry ZipArchive::GetEntry(const std::string& entryName) {
    struct zip_stat stat;
    zip_stat_init(&stat);

    zip_int64_t entryIndex = zip_name_locate(zipStruct, entryName.c_str(), ZIP_FL_ENC_GUESS);
    if(entryIndex == -1) {
        throw GLOVE_EXCEPTION((boost::format("Zip file entry %1% not found in %2%") % entryName.c_str() % path.ToString()).str());
    }

    zip_stat_index(zipStruct, static_cast<zip_uint64_t>(entryIndex), 0, &stat);
    return ZipEntry(stat);
}

zip* ZipArchive::GetZipStruct() const {
    return zipStruct;
}

}