#include <gtest/gtest.hpp>

#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/compression/ZipArchive.hpp>
#include <glove/GloveException.hpp>
#include <glove/filesystem/compression/ZipEntryBuffer.hpp>

namespace {
const glove::Path zipFile("testdata/testzip.zip");
}

namespace glove {

TEST(ZipEntryBufferTest, CanReadZipEntryUsingIstream) {
    ZipArchiveHandle archive(new ZipArchive(zipFile));

    ZipEntry entry = archive->GetEntry("testdir/subtestfile.txt");
    EXPECT_EQ(std::string("testdir/subtestfile.txt"), entry.GetName());

    ZipEntryBuffer zipEntryBuffer(entry, archive);
    std::istream entryInStream(&zipEntryBuffer);

    char* destination = new char[6];
    entryInStream.read(destination, 5);
    destination[5] = '\0';

    EXPECT_STREQ("Hello", destination);
}

} /* namespace glove */