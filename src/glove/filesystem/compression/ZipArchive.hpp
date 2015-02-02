#pragma once

#include <memory>

#include <zip.h>

#include "glove/filesystem/Path.hpp"
#include "glove/filesystem/compression/ZipEntry.hpp"

namespace glove {
class ZipArchive {
  public:
    ZipArchive(const Path& path);
    ZipArchive(const Path& path, bool checkConsistency);

    ZipArchive(const ZipArchive& other) = delete;

    virtual ~ZipArchive();

    const std::vector<ZipEntry>& GetEntries();
    bool HasEntry(const std::string& entryName);
    ZipEntry GetEntry(const std::string& entryName);

  private:
    friend class ZipEntryBuffer;

    void ReadFileIndex();
    zip* GetZipStruct() const;

    const Path path;
    zip* zipStruct;

    std::vector<ZipEntry> fileEntries;
};
}