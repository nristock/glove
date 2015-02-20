#include <gtest/gtest.hpp>

#include <dlfcn.h>
#include <glove/natex/impl/UnixSharedLibrary.hpp>
#include <glove/GloveException.hpp>
#include <glove/natex/exceptions/SharedLibraryLoadFailed.hpp>
#include <glove/natex/exceptions/SymbolNotFound.hpp>

namespace glove {

class UnixSharedLibraryTest : public ::testing::Test {
  protected:
    static const char* libraryFile;
    UnixSharedLibrary* library;

    void CreateLibrary() {
        ClearDLErrors();

        ASSERT_NO_THROW(library = new UnixSharedLibrary(libraryFile));
    }

    void DestroyLibrary() {
        ClearDLErrors();

        ASSERT_NO_THROW(delete library);
        ASSERT_EQ(nullptr, dlerror());
    }

    void ClearDLErrors() { dlerror(); }
};

const char* UnixSharedLibraryTest::libraryFile = "../lib/libtests_natex_testlib.so";

TEST_F(UnixSharedLibraryTest, ConstructorLoadsLibrary) {
    ClearDLErrors();
    ASSERT_NO_THROW(CreateLibrary());
    ASSERT_EQ(nullptr, dlerror());
}

TEST_F(UnixSharedLibraryTest, ConstructorThrowsOnFailure) {
    ASSERT_THROW(UnixSharedLibrary loader("../lib/very_awesome_non_existing_lib_name.so"), SharedLibraryLoadFailed);
}

TEST_F(UnixSharedLibraryTest, DestructorUnloadsLibrary) {
    ASSERT_NO_FATAL_FAILURE(CreateLibrary());
    ASSERT_NO_FATAL_FAILURE(DestroyLibrary());
}

TEST_F(UnixSharedLibraryTest, CanLoadSymbol) {
    ASSERT_NO_FATAL_FAILURE(CreateLibrary());

    ClearDLErrors();

    // Try loading a symbol
    void* loadedSymbol;
    EXPECT_NO_THROW(loadedSymbol = library->GetSymbol("TestLibFunction"));
    ASSERT_EQ(nullptr, dlerror());

    // Make sure the loaded symbol is actually valid
    typedef int (*TestLibFunction)(int);
    TestLibFunction testFunction = (TestLibFunction)loadedSymbol;
    EXPECT_EQ(5, testFunction(5));

    ASSERT_NO_FATAL_FAILURE(DestroyLibrary());
}

TEST_F(UnixSharedLibraryTest, ThrowsIfSymbolCouldntBeLoaded) {
    ASSERT_NO_FATAL_FAILURE(CreateLibrary());

    EXPECT_THROW(library->GetSymbol("TotallyRandomFunctionName"), SymbolNotFound);

    ASSERT_NO_FATAL_FAILURE(DestroyLibrary());
}
}