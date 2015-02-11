#pragma once

#include <string>
#include <zip.h>

#include "glove/GloveApi.hpp"

namespace glove {
class GLOVE_API_EXPORT ZipEntry {
  public:
    ZipEntry(const struct zip_stat& stat);

    const std::string& GetName() const;
    zip_uint64_t GetIndex() const;
    uint64_t GetUncompressedSize() const;
    uint64_t GetCompressedSize() const;
    uint64_t GetCompressionMethod() const;

    bool IsDirectory() const;

private:
    std::string name;
    zip_uint64_t index;

    std::uint64_t uncompressedSize;
    std::uint64_t compressedSize;
    std::uint64_t compressionMethod;
};
}