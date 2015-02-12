#include <gtest/gtest.hpp>

#include <glove/filesystem/Filesystem.hpp>
#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>

namespace {
const glove::Path directoryPath("testdata/a_directory");
const glove::Path filePath("testdata/a_directory/a_file");
const glove::Path nonExistingPath("testdata/a_not_existing_directory");
}

namespace glove {

TEST(NativeFilesystemAccessorsTest, CanDistinguishBetweenFilesAndDirectories) {
    FilesystemHandle filesystem(new NativeFilesystemAccessor());

    File directoryFile(::directoryPath, filesystem);
    EXPECT_TRUE(directoryFile.IsDirectory());
    EXPECT_FALSE(directoryFile.IsRegularFile());

    File regularFile(::filePath, filesystem);
    EXPECT_TRUE(regularFile.IsRegularFile());
    EXPECT_FALSE(regularFile.IsDirectory());
}

TEST(NativeFilesystemAccessorsTest, CanCheckExistance) {
    FilesystemHandle filesystem(new NativeFilesystemAccessor());

    EXPECT_TRUE(File(::directoryPath, filesystem).Exists());
    EXPECT_TRUE(File(::filePath, filesystem).Exists());
    EXPECT_FALSE(File(::nonExistingPath, filesystem).Exists());
}

} /* namespace glove */