#pragma once

#include <streambuf>
#include <vector>

#include "core/filesystem/compression/ZipEntry.hpp"
#include "core/filesystem/compression/Compression.hpp"

namespace glove {
class ZipEntryBuffer : public std::streambuf {
public:
    ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive);
    ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive, std::size_t bufferSize);
    ZipEntryBuffer(const ZipEntry& zipEntry, const ZipArchiveHandle& zipArchive, std::size_t bufferSize, std::size_t putBack);

    ~ZipEntryBuffer();

protected:
    virtual int_type underflow() override;

private:
    ZipArchiveHandle zipArchive;
    zip_file* zipFile;
    const std::size_t putBack;
    ZipEntry zipEntry;
    std::vector<char> buffer;

};
}