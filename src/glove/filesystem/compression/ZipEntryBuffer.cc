#include "ZipEntryBuffer.hpp"

#include <algorithm>
#include <cstring>

#include "glove/filesystem/compression/ZipArchive.hpp"

namespace glove {

ZipEntryBuffer::ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive) : ZipEntryBuffer(zipEntry, zipArchive, 1024) {
}

ZipEntryBuffer::ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive, std::size_t bufferSize)
    : ZipEntryBuffer(zipEntry, zipArchive, bufferSize, 8) {
}

ZipEntryBuffer::ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive, std::size_t bufferSize, std::size_t putBack)
    : zipArchive(zipArchive), putBack(putBack), zipEntry(zipEntry), buffer(std::max(bufferSize, putBack) + putBack) {
    zipFile = zip_fopen_index(zipArchive->GetZipStruct(), zipEntry.GetIndex(), ZIP_FL_ENC_GUESS);

    char* end = &buffer.front() + buffer.size();
    setg(end, end, end);
}

ZipEntryBuffer::int_type ZipEntryBuffer::underflow() {
    if(gptr() < egptr()) {
        return traits_type::to_int_type(*gptr());
    }

    char* base = &buffer.front();
    char* start = base;

    if(eback() == base) {
        std::memmove(base, egptr() - putBack, putBack);
        start+=putBack;
    }

    zip_int64_t bytesRead = zip_fread(zipFile, start, buffer.size() - (start - base));
    if(bytesRead == 0 || bytesRead == -1) {
        return traits_type::eof();
    }

    setg(base, start, start + bytesRead);

    return traits_type::to_int_type(*gptr());
}

ZipEntryBuffer::~ZipEntryBuffer() {
    zip_fclose(zipFile);
}
}