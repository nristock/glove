#include "glove/filesystem/compression/ZipEntry.hpp"

namespace {
const std::string g_directorySeparator("/");
}

namespace BlueDwarf {

ZipEntry::ZipEntry(const struct zip_stat& stat)
    : name(stat.name), index(stat.index), uncompressedSize(stat.size), compressedSize(stat.comp_size),
      compressionMethod(stat.comp_method) {
}

const std::string& ZipEntry::GetName() const  {
    return name;
}

zip_uint64_t ZipEntry::GetIndex() const {
    return index;
}

uint64_t ZipEntry::GetUncompressedSize() const {
    return uncompressedSize;
}

uint64_t ZipEntry::GetCompressedSize() const {
    return compressedSize;
}

uint64_t ZipEntry::GetCompressionMethod() const {
    return compressionMethod;
}

bool ZipEntry::IsDirectory() const {
    return name.back() == '/';
}
}