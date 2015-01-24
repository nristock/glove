#include <vendor/gtest/gtest.h>

#include <core/filesystem/Path.hpp>

#include "mock/MockFilesystemAccessor.hpp"

namespace glove {

TEST(PathTest, CanConstructFromString) {
    Path path("testdata");
}

TEST(PathTest, CanConvertPathToString) {
    Path path("testdata/a_directory");
    EXPECT_EQ("testdata/a_directory", path.ToString());
}

TEST(PathTest, CanJoinPaths) {
    Path prefix("testdata");
    Path suffix("a_directory");
    Path joinedPath = Path::Join(prefix, suffix);

    Path expectedPath("testdata/a_directory");

    EXPECT_EQ(expectedPath, joinedPath);
    EXPECT_EQ("testdata/a_directory", joinedPath.ToString());
}

TEST(PathTest, CanComparePaths) {
    Path path("testdata");
    Path differentPath("a_directory");

    EXPECT_TRUE(path == path);
    EXPECT_FALSE(path != path);
    EXPECT_FALSE(path == differentPath);
    EXPECT_TRUE(path != differentPath);
}

TEST(PathTest, CanTranslatePaths) {
    Path path("testdata/a_directory");

    EXPECT_EQ("testdata#a_directory", Path::Translate<FilesystemAccessorMock>(path));
}

} /* namespace glove */