#include <gtest/gtest.hpp>

#include <glove/filesystem/Path.hpp>
#include <glove/filesystem/io/File.hpp>
#include <glove/filesystem/io/UnbufferedFileReader.hpp>

namespace {
const BlueDwarf::Path directoryPath("testdata/a_directory");
const BlueDwarf::Path filePath("testdata/a_directory/a_file");
const BlueDwarf::Path nonExistingPath("testdata/a_non_existing_directory");
}

namespace BlueDwarf {

TEST(UnbufferedFileReaderTest, CanConstructFromFile) {
    File file(::filePath);
    UnbufferedFileReader reader(file);
}

TEST(FileTest, CanReadBytesFromFile) {
    File file(::filePath);
    UnbufferedFileReader reader(file);

    char character;
    reader.Read(&character, sizeof(char));

    EXPECT_EQ('G', character);
}

} /* namespace BlueDwarf */