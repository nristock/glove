#pragma once

#include <streambuf>
#include <vector>

#include "glove/GloveApi.hpp"
#include "glove/filesystem/compression/ZipEntry.hpp"
#include "glove/filesystem/compression/Compression.hpp"

namespace glove {
class GLOVE_API_EXPORT ZipEntryBuffer : public std::streambuf {
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