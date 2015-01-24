#include <vendor/gmock/gmock.h>

#include <core/filesystem/Path.hpp>
#include <core/filesystem/io/File.hpp>

#include "mock/MockFilesystemAccessor.hpp"

namespace {
const glove::FileInfo existingDirectory(glove::FileInfo::FileType::DIRECTORY, 0);
const glove::FileInfo existingFile(glove::FileInfo::FileType::REGULAR, 0);
const glove::FileInfo nonExistingFile(glove::FileInfo::FileType::NONE, 0);

const glove::Path directoryPath("existing/directory");
const glove::Path filePath("existing/file");
const glove::Path nonExistingPath("nonexisting");
}

using ::testing::Return;

namespace glove {

TEST(FileTest, CanConstructFromPath) {
    FilesystemAccessorHandle filesystem(new FilesystemAccessorMock());

    File file(::directoryPath, filesystem);
    EXPECT_EQ(::directoryPath, file.GetPath());
}

TEST(FileTest, CanDistinguishBetweenFilesAndDirectories) {
    FilesystemAccessorHandle filesystem(new testing::NiceMock<FilesystemAccessorMock>());
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(directoryPath.ToString())).WillByDefault(Return(existingDirectory));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(filePath.ToString())).WillByDefault(Return(existingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(nonExistingPath.ToString())).WillByDefault(Return(nonExistingFile));

    File directoryFile(::directoryPath, filesystem);
    EXPECT_TRUE(directoryFile.IsDirectory());
    EXPECT_FALSE(directoryFile.IsRegularFile());

    File regularFile(::filePath, filesystem);
    EXPECT_TRUE(regularFile.IsRegularFile());
    EXPECT_FALSE(regularFile.IsDirectory());
}

TEST(FileTest, CanCheckExistance) {
    FilesystemAccessorHandle filesystem(new testing::NiceMock<FilesystemAccessorMock>());
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(directoryPath.ToString())).WillByDefault(Return(existingDirectory));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(filePath.ToString())).WillByDefault(Return(existingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(nonExistingPath.ToString())).WillByDefault(Return(nonExistingFile));

    EXPECT_TRUE(File(::directoryPath, filesystem).Exists());
    EXPECT_TRUE(File(::filePath, filesystem).Exists());
    EXPECT_FALSE(File(::nonExistingPath, filesystem).Exists());
}

} /* namespace glove */