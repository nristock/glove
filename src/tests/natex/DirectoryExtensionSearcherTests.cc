#include <gtest/gtest.hpp>

#include <glove/natex/DirectoryExtensionSearcher.hpp>
#include "glove/DwarfException.hpp"

namespace BlueDwarf {

class DirectoryExtensionSearcherTests : public ::testing::Test {
  protected:
    static const char* directoryPath;

    static bool EndsWith(const std::string& fullString, const std::string& ending) {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }
    }
};

const char* DirectoryExtensionSearcherTests::directoryPath = "./testdata";

TEST_F(DirectoryExtensionSearcherTests, CanConstructSearcher) {
    ASSERT_NO_THROW(DirectoryExtensionSearcher searcher(directoryPath));
}

TEST_F(DirectoryExtensionSearcherTests, SearcherReturnsAllLibraryFilesInDirectory) {
    DirectoryExtensionSearcher* searcher;

    ASSERT_NO_THROW(searcher = new DirectoryExtensionSearcher(directoryPath));

    ASSERT_EQ(3, searcher->GetExtensions().size());

    for (auto fileName : searcher->GetExtensions()) {
#if defined(ON_UNIX)
        ASSERT_TRUE(EndsWith(fileName, ".so"));
#elif defined(ON_WINDOWS)
        ASSERT_TRUE(EndsWith(fileName, ".dll"));
#else
        FAIL();
#endif
    }

    ASSERT_NO_THROW(delete searcher);
}

TEST_F(DirectoryExtensionSearcherTests, ThrowsWhenCreatedWithInvalidDirectory) {
    ASSERT_THROW(DirectoryExtensionSearcher searcher("extremely_weird_directory_path"), DwarfException);
}
}