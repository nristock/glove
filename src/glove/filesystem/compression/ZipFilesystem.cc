#include "glove/filesystem/compression/ZipFilesystem.hpp"
#include "glove/GloveException.hpp"
#include "glove/exceptions/OperationNotSupported.hpp"
#include "glove/filesystem/compression/ZipArchive.hpp"
#include "glove/filesystem/compression/ZipEntryBuffer.hpp"
#include "glove/filesystem/FileInfo.hpp"

namespace {
void StreamDeleter(std::istream::event event, std::ios_base& ios, int index) {
    if (event == ios.erase_event) {
        delete dynamic_cast<std::istream&>(ios).rdbuf();
    }
}
}

namespace glove {

ZipFilesystem::ZipFilesystem(const ZipArchiveHandle& zipArchive) : archive(zipArchive) {
}


ZipFilesystem::~ZipFilesystem() {
}

const FileInfo ZipFilesystem::GetFileInfo(const Path& path) {
    std::string stringPath = path.ToString();
    if (path.IsAbsolute()) {
        stringPath.erase(0, 1);
    }

    try {
        ZipEntry entry = archive->GetEntry(stringPath);
        return FileInfo(entry.IsDirectory() ? FileInfo::FileType::DIRECTORY : FileInfo::FileType::REGULAR, entry.GetUncompressedSize());
    } catch (const GloveException& ex) {
        return FileInfo(FileInfo::FileType::NOT_FOUND, 0);
    }
}

std::istream* ZipFilesystem::CreateFileReadStream(const Path& path) {
    std::string stringPath = path.ToString();
    if (path.IsAbsolute()) {
        stringPath.erase(0, 1);
    }

    ZipEntry zipEntry = archive->GetEntry(stringPath);
    ZipEntryBuffer* buffer = new ZipEntryBuffer(zipEntry, archive);

    std::istream* stream = new std::istream(buffer);
    stream->register_callback(::StreamDeleter, 0);

    return stream;
}

std::ostream* ZipFilesystem::CreateFileWriteStream(const Path& path) {
    GLOVE_THROW(OperationNotSupportedException, "IFilesystem::CreateFileWriterStream", "ZipFilesystem");
}
}