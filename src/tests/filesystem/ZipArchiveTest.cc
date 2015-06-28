#include <gtest/gtest.hpp>

#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/compression/ZipArchive.hpp>
#include "glove/DwarfException.hpp"

namespace {
const BlueDwarf::Path zipFile("testdata/testzip.zip");
}

namespace BlueDwarf {

TEST(ZipArchiveTest, CanConstructFromPath) {
    ZipArchive archive(zipFile);
}

TEST(ZipArchiveTest, CanListContainedFiles) {
    ZipArchive archive(zipFile);

    std::vector<ZipEntry> zipEntries = archive.GetEntries();

    EXPECT_EQ(3, zipEntries.size());

    for (const ZipEntry& zipEntry : zipEntries) {
        if (zipEntry.GetName() != "testdir/" && zipEntry.GetName() != "testdir/subtestfile.txt" &&
            zipEntry.GetName() != "testfile.txt") {
            FAIL();
        }
    }
}

TEST(ZipArchiveTest, ReadsCorrectFileInfo) {
    ZipArchive archive(zipFile);

    std::vector<ZipEntry> zipEntries = archive.GetEntries();

    EXPECT_EQ(3, zipEntries.size());

    for (const ZipEntry& zipEntry : zipEntries) {
        if(zipEntry.GetName() == "testdir/") {
            EXPECT_TRUE(zipEntry.IsDirectory());
            EXPECT_EQ(0, zipEntry.GetCompressedSize());
            EXPECT_EQ(0, zipEntry.GetUncompressedSize());
            EXPECT_EQ(0, zipEntry.GetCompressionMethod());
        } else if(zipEntry.GetName() == "testdir/subtestfile.txt") {
            EXPECT_FALSE(zipEntry.IsDirectory());
            EXPECT_EQ(17, zipEntry.GetCompressedSize());
            EXPECT_EQ(17, zipEntry.GetUncompressedSize());
            EXPECT_EQ(0, zipEntry.GetCompressionMethod());
        } else if(zipEntry.GetName() == "testfile.txt") {
            EXPECT_FALSE(zipEntry.IsDirectory());
            EXPECT_EQ(12, zipEntry.GetCompressedSize());
            EXPECT_EQ(12, zipEntry.GetUncompressedSize());
            EXPECT_EQ(0, zipEntry.GetCompressionMethod());
        } else {
            FAIL();
        }
    }
}

TEST(ZipArchiveTest, CanCheckForEntryExistence) {
    ZipArchive archive(zipFile);

    EXPECT_TRUE(archive.HasEntry("testdir/"));
    EXPECT_TRUE(archive.HasEntry("testdir/subtestfile.txt"));
    EXPECT_TRUE(archive.HasEntry("testfile.txt"));

    EXPECT_FALSE(archive.HasEntry("blob"));
}

TEST(ZipArchiveTest, CanGetEntry) {
    ZipArchive archive(zipFile);

    ZipEntry entry = archive.GetEntry("testdir/subtestfile.txt");
    EXPECT_EQ(std::string("testdir/subtestfile.txt"), entry.GetName());
}

TEST(ZipArchiveTest, ThrowsIfQueriedForNonExistingEntry) {
    ZipArchive archive(zipFile);

    ASSERT_FALSE(archive.HasEntry("blob"));
    EXPECT_THROW(archive.GetEntry("blob"), DwarfException);
}

} /* namespace BlueDwarf */