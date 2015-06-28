#include <gtest/gtest.hpp>

#include <glove/filesystem/inmemory/InMemoryFilesystem.hpp>
#include <glove/filesystem/Filesystem.hpp>
#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>

#include "tests/filesystem/mock/MockFilesystemAccessor.hpp"

namespace {
const BlueDwarf::Path directoryPath("testdata/a_directory");
const BlueDwarf::Path filePath("testdata/a_directory/a_file");
const BlueDwarf::Path nonExistingPath("testdata/a_not_existing_directory");
}

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

namespace BlueDwarf {

TEST(InMemoryFilesystemTest, CanConstruct) {
    EXPECT_NO_THROW(InMemoryFilesystem filesystem);
}

TEST(InMemoryFilesystemTest, GetFileInfoRedirectsToCorrectFilesystem) {
    InMemoryFilesystem filesystem;

    FileInfo mockInfo(FileInfo::FileType::UNKNOWN, 0);
    FilesystemHandle mockFilesystem = FilesystemHandle(new FilesystemAccessorMock());
    EXPECT_CALL(*dynamic_cast<FilesystemAccessorMock*>(mockFilesystem.get()), GetFileInfo(_)).Times(2).WillRepeatedly(Return(mockInfo));

    filesystem.Mount(Path("/data"), mockFilesystem);
    EXPECT_EQ(mockInfo, filesystem.GetFileInfo(Path("/data/myfile")));
    EXPECT_EQ(mockInfo, filesystem.GetFileInfo(Path("/data/mydir/more/file.ext")));
}

} /* namespace BlueDwarf */