#include <gtest/gtest.hpp>

#include <glove/filesystem/MountAwareFilesystem.hpp>
#include <glove/filesystem/Filesystem.hpp>
#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>
#include <glove/filesystem/exceptions/MountError.hpp>
#include <glove/filesystem/exceptions/MountLocationAlreadyOccupied.hpp>

#include "tests/filesystem/mock/MockFilesystemAccessor.hpp"

namespace glove {

class MountAwareFilesystemTest : public ::testing::Test, public MountAwareFilesystem {
  public:
    virtual const FileInfo GetFileInfo(const Path& path) {
        throw std::exception();
    }
    virtual std::istream* CreateFileReadStream(const Path& path) {
        throw std::exception();
    }
    virtual std::ostream* CreateFileWriteStream(const Path& path) {
        throw std::exception();
    }
};

TEST_F(MountAwareFilesystemTest, NewlyConstructedFilesystemHasNoMountPoints) {
    EXPECT_EQ(0, GetMountCount());
}

TEST_F(MountAwareFilesystemTest, MountingIncreasesMountCount) {
    std::shared_ptr<FilesystemAccessorMock> mockFilesystem = std::make_shared<FilesystemAccessorMock>();

    Mount(Path("/data"), mockFilesystem);
    EXPECT_EQ(1, GetMountCount());
}

TEST_F(MountAwareFilesystemTest, MountingAtRelativePathThrows) {
    std::shared_ptr<FilesystemAccessorMock> mockFilesystem = std::make_shared<FilesystemAccessorMock>();

    EXPECT_THROW(Mount(Path("data"), mockFilesystem), MountError);
}

TEST_F(MountAwareFilesystemTest, MountingTheSameLocationTwiceThrows) {
    std::shared_ptr<FilesystemAccessorMock> mockFilesystem = std::make_shared<FilesystemAccessorMock>();

    Mount(Path("/data"), mockFilesystem);
    EXPECT_THROW(Mount(Path("/data"), mockFilesystem), MountLocationAlreadyOccupied);
    EXPECT_THROW(Mount(Path("/data/"), mockFilesystem), MountLocationAlreadyOccupied);
}

TEST_F(MountAwareFilesystemTest, UnmountingDecreasesMountCount) {
    std::shared_ptr<FilesystemAccessorMock> mockFilesystem = std::make_shared<FilesystemAccessorMock>();

    Mount(Path("/data"), mockFilesystem);
    Unmount(Path("/data"));
    EXPECT_EQ(0, GetMountCount());
}

TEST_F(MountAwareFilesystemTest, UnmountingARelativePathThrows) {
    EXPECT_THROW(Unmount(Path("data")), MountError);
}

TEST_F(MountAwareFilesystemTest, UnmountingAnUnmountedLocationThrows) {
    EXPECT_THROW(Unmount(Path("/data")), MountError);
    EXPECT_THROW(Unmount(Path("/data/")), MountError);
}

TEST_F(MountAwareFilesystemTest, CanResolvePathToMountedFilesystem) {
    std::shared_ptr<FilesystemAccessorMock> mockFilesystem = std::make_shared<FilesystemAccessorMock>();

    Mount(Path("/data"), mockFilesystem);
    Mount(Path("/data2/"), mockFilesystem);

    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data/")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data/testdir/")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data/somefile.txt")).GetFilesystem());

    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data2")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data2/")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data2/testdir/")).GetFilesystem());
    EXPECT_EQ(mockFilesystem, ResolveToMount(Path("/data2/somefile.txt")).GetFilesystem());
}

TEST_F(MountAwareFilesystemTest, ResolvingARelativePathThrows) {
    EXPECT_THROW(ResolveToMount(Path("some/relative/path")), MountError);
}

TEST_F(MountAwareFilesystemTest, ResolvingAPathToANonMountLocationThrows) {
    EXPECT_THROW(ResolveToMount(Path("/some/relative/path")), MountError);
}

TEST_F(MountAwareFilesystemTest, CanCalculateMountRelativePath) {
    MountInfo mountInfo(FilesystemHandle(), Path("/data/"));
    EXPECT_EQ(Path("/some/more/stuff"), CalculateMountRelativePath(mountInfo, Path("/data/some/more/stuff")));
}
} /* namespace glove */