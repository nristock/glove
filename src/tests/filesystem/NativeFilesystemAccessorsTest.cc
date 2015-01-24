#include <vendor/gtest/gtest.h>

#include <core/filesystem/Filesystem.hpp>
#include <core/filesystem/Path.hpp>
#include <core/filesystem/io/File.hpp>

namespace {
const glove::Path directoryPath("testdata/a_directory");
const glove::Path filePath("testdata/a_directory/a_file");
const glove::Path nonExistingPath("testdata/a_not_existing_directory");
}

namespace glove {

TEST(NativeFilesystemAccessorsTest, SeparatorCharacterIsSetCorrectly) {
    #if defined(ON_WINDOWS)
    EXPECT_EQ('\\', NativeFilesystemAccessor::SEPARATOR);
    #else
    EXPECT_EQ("/", NativeFilesystemAccessor::SEPARATOR);
    #endif
}

TEST(NativeFilesystemAccessorsTest, CanDistinguishBetweenFilesAndDirectories) {
    FilesystemAccessorHandle filesystem(new NativeFilesystemAccessor());

    File directoryFile(::directoryPath, filesystem);
    EXPECT_TRUE(directoryFile.IsDirectory());
    EXPECT_FALSE(directoryFile.IsRegularFile());

    File regularFile(::filePath, filesystem);
    EXPECT_TRUE(regularFile.IsRegularFile());
    EXPECT_FALSE(regularFile.IsDirectory());
}

TEST(NativeFilesystemAccessorsTest, CanCheckExistance) {
    FilesystemAccessorHandle filesystem(new NativeFilesystemAccessor());

    EXPECT_TRUE(File(::directoryPath, filesystem).Exists());
    EXPECT_TRUE(File(::filePath, filesystem).Exists());
    EXPECT_FALSE(File(::nonExistingPath, filesystem).Exists());
}

} /* namespace glove */