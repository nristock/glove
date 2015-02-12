#include <gmock/gmock.hpp>

#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>

#include "mock/MockFilesystemAccessor.hpp"

namespace {
const glove::FileInfo existingDirectory(glove::FileInfo::FileType::DIRECTORY, 0);
const glove::FileInfo existingFile(glove::FileInfo::FileType::REGULAR, 0);
const glove::FileInfo nonExistingFile(glove::FileInfo::FileType::NOT_FOUND, 0);
const glove::FileInfo unknownFile(glove::FileInfo::FileType::UNKNOWN, 0);

const glove::Path directoryPath("existing/directory");
const glove::Path filePath("existing/file");
const glove::Path nonExistingPath("nonexisting");
const glove::Path unknownFileTypePath("unknown");
}

using ::testing::Return;

namespace glove {

TEST(FileTest, CanConstructFromPath) {
    FilesystemHandle filesystem(new FilesystemAccessorMock());

    File file(::directoryPath, filesystem);
    EXPECT_EQ(::directoryPath, file.GetPath());
}

TEST(FileTest, CanDistinguishBetweenFilesAndDirectories) {
    FilesystemHandle filesystem(new testing::NiceMock<FilesystemAccessorMock>());
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(directoryPath)).WillByDefault(Return(existingDirectory));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(filePath)).WillByDefault(Return(existingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(nonExistingPath)).WillByDefault(Return(nonExistingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(unknownFileTypePath)).WillByDefault(Return(unknownFile));

    File directoryFile(::directoryPath, filesystem);
    EXPECT_TRUE(directoryFile.IsDirectory());
    EXPECT_FALSE(directoryFile.IsRegularFile());

    File regularFile(::filePath, filesystem);
    EXPECT_TRUE(regularFile.IsRegularFile());
    EXPECT_FALSE(regularFile.IsDirectory());
}

TEST(FileTest, CanCheckExistance) {
    FilesystemHandle filesystem(new testing::NiceMock<FilesystemAccessorMock>());
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(directoryPath)).WillByDefault(Return(existingDirectory));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(filePath)).WillByDefault(Return(existingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(nonExistingPath)).WillByDefault(Return(nonExistingFile));
    ON_CALL(*dynamic_cast<FilesystemAccessorMock*>(filesystem.get()), GetFileInfo(unknownFileTypePath)).WillByDefault(Return(unknownFile));

    EXPECT_TRUE(File(::directoryPath, filesystem).Exists());
    EXPECT_TRUE(File(::filePath, filesystem).Exists());
    EXPECT_TRUE(File(::unknownFileTypePath, filesystem).Exists());
    EXPECT_FALSE(File(::nonExistingPath, filesystem).Exists());
}

} /* namespace glove */