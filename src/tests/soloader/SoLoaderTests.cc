#include <core/internal/so/SoLoader.h>

#include <vendor/gtest/gtest.h>
#include <core/GloveException.h>
#include <dlfcn.h>

namespace glove {

class SoLoaderTests : public ::testing::Test {
  protected:
    static const char* libraryFile;
    SoLoader* loader;

    void CreateLoader() {
        ClearDLErrors();

        ASSERT_NO_THROW(loader = new SoLoader(libraryFile));
    }

    void DeleteSoLoader() {
        ClearDLErrors();

        ASSERT_NO_THROW(delete loader);
        ASSERT_EQ(nullptr, dlerror());
    }

    void ClearDLErrors() {
        dlerror();
    }
};

const char* SoLoaderTests::libraryFile = "../lib/libtests_soloader_testlib.so";

TEST_F(SoLoaderTests, ConstructorLoadsLibrary) {
    ClearDLErrors();
    ASSERT_NO_THROW(SoLoader loader(libraryFile));
    ASSERT_EQ(nullptr, dlerror());
}

TEST_F(SoLoaderTests, ConstructorThrowsOnFailure) {
    ASSERT_THROW(SoLoader loader("../lib/very_awesome_non_existing_lib_name.so"), GloveException);
}

TEST_F(SoLoaderTests, DestructorUnloadsLibrary) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());
    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());
}

TEST_F(SoLoaderTests, CanLoadSymbol) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());

    ClearDLErrors();
    void* loadedSymbol;
    EXPECT_NO_THROW(loadedSymbol = loader->LoadSymbol("TestLibFunction"));
    ASSERT_EQ(nullptr, dlerror());

    typedef int (*TestLibFunction)(int);
    TestLibFunction testFunction = (TestLibFunction)loadedSymbol;
    EXPECT_EQ(5, testFunction(5));

    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());

}

TEST_F(SoLoaderTests, ThrowsIfSymbolCouldntBeLoaded) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());

    EXPECT_THROW(loader->LoadSymbol("TotallyRandomFunctionName"), GloveException);

    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());
}

TEST_F(SoLoaderTests, CanLoadLibraryLoaderFunction) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());

    LoadSystemExtensionLibraryFunc extensionLoaderFunc = loader->GetLibraryLoaderFunc();
    ASSERT_NE(nullptr, extensionLoaderFunc);
    EXPECT_EQ(nullptr, extensionLoaderFunc());

    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());
}

TEST_F(SoLoaderTests, CanLoadLibraryUnloaderFunction) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());

    UnloadSystemExtensionLibraryFunc extensionLoaderFunc = loader->GetLibraryUnloaderFunc();
    EXPECT_NE(nullptr, extensionLoaderFunc);

    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());
}

TEST_F(SoLoaderTests, CanReloadLibrary) {
    ASSERT_NO_FATAL_FAILURE(CreateLoader());

    EXPECT_NO_THROW(loader->ReloadLibrary());

    ASSERT_NO_FATAL_FAILURE(DeleteSoLoader());
}
}