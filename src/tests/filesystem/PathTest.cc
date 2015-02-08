#include <vendor/gtest/gtest.h>

#include <glove/filesystem/Path.hpp>

#include "mock/MockFilesystemAccessor.hpp"

namespace glove {

TEST(PathTest, CanConstructFromString) {
    Path path("testdata");
}

TEST(PathTest, CanConvertPathToString) {
    Path path("testdata/a_directory");
    EXPECT_EQ("testdata/a_directory", path.ToString());
}

TEST(PathTest, CanComparePaths) {
    Path path("testdata");
    Path differentPath("a_directory");

    EXPECT_TRUE(path == path);
    EXPECT_FALSE(path != path);
    EXPECT_FALSE(path == differentPath);
    EXPECT_TRUE(path != differentPath);
}

TEST(PathTest, CanCompareToString) {
    Path path("testdata");

    EXPECT_TRUE(path == std::string("testdata"));
    EXPECT_FALSE(path != std::string("testdata"));
}

TEST(PathTest, CanCompareToCString) {
    Path path("testdata");

    EXPECT_TRUE(path == "testdata");
    EXPECT_FALSE(path != "testdata");
}

TEST(PathTest, CanCheckEmpty) {
    EXPECT_TRUE(Path("").IsEmpty());
    EXPECT_FALSE(Path("foo").IsEmpty());
}

TEST(PathTest, CanCheckForExtensions) {
    EXPECT_TRUE(Path("foo.ext").HasExtension());
    EXPECT_FALSE(Path(".foo").HasExtension());
    EXPECT_FALSE(Path("foo").HasExtension());
    EXPECT_FALSE(Path(".").HasExtension());
    EXPECT_FALSE(Path("..").HasExtension());
}

TEST(PathTest, CanExtractFilename) {
    EXPECT_EQ("foo.ext", Path("foo.ext").GetFilename());
    EXPECT_EQ(".foo", Path(".foo").GetFilename());
    EXPECT_EQ("foo", Path("foo").GetFilename());
    EXPECT_EQ("foo.ext", Path("/root/path/foo.ext").GetFilename());
    EXPECT_EQ("foo.ext", Path("relative/path/foo.ext").GetFilename());
    EXPECT_EQ("", Path("relative/path/foo/").GetFilename());
    EXPECT_EQ(".", Path(".").GetFilename());
    EXPECT_EQ("..", Path("..").GetFilename());
}

TEST(PathTest, CanExtractFilenameWithoutExtension) {
    EXPECT_EQ("foo", Path("foo.ext").GetFilenameWithoutExtension());
    EXPECT_EQ(".foo", Path(".foo").GetFilenameWithoutExtension());
    EXPECT_EQ("foo", Path("foo").GetFilenameWithoutExtension());
    EXPECT_EQ("foo", Path("/root/path/foo.ext").GetFilenameWithoutExtension());
    EXPECT_EQ("foo", Path("relative/path/foo.ext").GetFilenameWithoutExtension());
    EXPECT_EQ("", Path("relative/path/foo/").GetFilenameWithoutExtension());
    EXPECT_EQ(".", Path(".").GetFilenameWithoutExtension());
    EXPECT_EQ("..", Path("..").GetFilenameWithoutExtension());
}

TEST(PathTest, CanExtractParentPath) {
    EXPECT_EQ(Path(), Path("foo.ext").GetParentPath());
    EXPECT_EQ(Path(), Path(".foo").GetParentPath());
    EXPECT_EQ(Path(), Path("foo").GetParentPath());
    EXPECT_EQ(Path("/root/path/"), Path("/root/path/foo.ext").GetParentPath());
    EXPECT_EQ(Path("relative/path/"), Path("relative/path/foo.ext").GetParentPath());
    EXPECT_EQ(Path("relative/path/"), Path("relative/path/foo/").GetParentPath());
    EXPECT_EQ(Path(), Path(".").GetParentPath());
    EXPECT_EQ(Path(), Path("..").GetParentPath());
    EXPECT_EQ(Path(), Path("/").GetParentPath());
}

TEST(PathTest, CanIdentifyAbsolutePaths) {
    EXPECT_FALSE(Path("foo.ext").IsAbsolute());
    EXPECT_FALSE(Path(".foo").IsAbsolute());
    EXPECT_FALSE(Path("foo").IsAbsolute());
    EXPECT_TRUE(Path("/root/path/foo.ext").IsAbsolute());
    EXPECT_FALSE(Path("relative/path/foo.ext").IsAbsolute());
    EXPECT_FALSE(Path("relative/path/foo/").IsAbsolute());
    EXPECT_FALSE(Path(".").IsAbsolute());
    EXPECT_FALSE(Path("..").IsAbsolute());
    EXPECT_TRUE(Path("/").IsAbsolute());
}

TEST(PathTest, CanIdentifyRelativePaths) {
    EXPECT_TRUE(Path("foo.ext").IsRelative());
    EXPECT_TRUE(Path(".foo").IsRelative());
    EXPECT_TRUE(Path("foo").IsRelative());
    EXPECT_FALSE(Path("/root/path/foo.ext").IsRelative());
    EXPECT_TRUE(Path("relative/path/foo.ext").IsRelative());
    EXPECT_TRUE(Path("relative/path/foo/").IsRelative());
    EXPECT_TRUE(Path(".").IsRelative());
    EXPECT_TRUE(Path("..").IsRelative());
    EXPECT_FALSE(Path("/").IsRelative());
}

TEST(PathTest, CanExtractExtension) {
    EXPECT_EQ(".ext", Path("foo.ext").GetExtension());
    EXPECT_EQ("", Path(".foo").GetExtension());
    EXPECT_EQ("", Path("foo").GetExtension());
    EXPECT_EQ(".", Path("/root/path/foo.").GetExtension());
    EXPECT_EQ(".ext", Path("relative/path/foo.ext").GetExtension());
    EXPECT_EQ("", Path("relative/path/foo/").GetExtension());
    EXPECT_EQ("", Path(".").GetExtension());
    EXPECT_EQ("", Path("..").GetExtension());
}

TEST(PathTest, CanAddPathsUsingArithmeticPlus) {
    Path prefix("testdata");
    Path suffix("a_directory");
    Path joinedPath = prefix + suffix;

    EXPECT_EQ("testdata", prefix.ToString());
    EXPECT_EQ("a_directory", suffix.ToString());
    EXPECT_EQ("testdata/a_directory", joinedPath.ToString());
}

TEST(PathTest, CanJoinPathsWithTrailingSlashes) {
    Path prefix("testdata/");
    Path suffix("a_directory");
    Path joinedPath = prefix + suffix;

    EXPECT_EQ("testdata/", prefix.ToString());
    EXPECT_EQ("a_directory", suffix.ToString());
    EXPECT_EQ("testdata/a_directory", joinedPath.ToString());
}

TEST(PathTest, CanAddAppendPathUsingPlusEquals) {
    Path prefix("testdata");
    Path suffix("a_directory");
    prefix += suffix;

    EXPECT_EQ("testdata/a_directory", prefix.ToString());
    EXPECT_EQ("a_directory", suffix.ToString());
}

TEST(PathTest, CanAssignPathFromString) {
    Path prefix = std::string("testdata");

    EXPECT_EQ("testdata", prefix.ToString());
}

TEST(PathTest, CanAssignPathFromCString) {
    Path prefix = "testdata";

    EXPECT_EQ("testdata", prefix.ToString());
}

TEST(PathTest, CanJoinArbitraryNumberOfPaths) {
    Path prefix("testdata");
    Path infix("middle");
    Path suffix("end");

    EXPECT_EQ("testdata/middle/end", Path::Join(prefix, infix, suffix));
}

TEST(PathTest, CanJoinArbitraryNumberOfPathsWithTrailingSlashes) {
    Path prefix("testdata/");
    Path infix("middle/");
    Path suffix("end");

    EXPECT_EQ("testdata/middle/end", Path::Join(prefix, infix, suffix));
}

} /* namespace glove */