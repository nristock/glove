#include <core/internal/so/SoLoader.h>

#include <vendor/gtest/gtest.h>
#include <core/GloveException.h>
#include <dlfcn.h>

namespace glove {

class SoLoaderTests : public ::testing::Test {
  protected:
    static const char* libraryFile;
};

const char* SoLoaderTests::libraryFile = "../lib/libtests_soloader_testlib.so";

TEST_F(SoLoaderTests, ConstructorLoadsLibrary) {
    dlerror();
    ASSERT_NO_THROW(SoLoader loader(libraryFile));
    ASSERT_EQ(nullptr, dlerror());
}

TEST_F(SoLoaderTests, ConstructorThrowsOnFailure) {
    ASSERT_THROW(SoLoader loader("../lib/very_awesome_non_existing_lib_name.so"), GloveException);
}

TEST_F(SoLoaderTests, DestructorUnloadsLibrary) {
    SoLoader* soLoader;
    ASSERT_NO_THROW(soLoader = new SoLoader(libraryFile));

    dlerror();
    ASSERT_NO_THROW(delete soLoader);
    ASSERT_EQ(nullptr, dlerror());
}

TEST_F(SoLoaderTests, CanLoadSymbol) {
    SoLoader* loader;
    ASSERT_NO_THROW(loader = new SoLoader(libraryFile));

    dlerror();
    void* loadedSymbol;
    ASSERT_NO_THROW(loadedSymbol = loader->LoadSymbol("TestLibFunction"));
    ASSERT_EQ(nullptr, dlerror());

    typedef int (*TestLibFunction)(int);

    TestLibFunction testFunction = (TestLibFunction)loadedSymbol;
    ASSERT_EQ(5, testFunction(5));

    ASSERT_NO_THROW(delete loader);
}

TEST_F(SoLoaderTests, ThrowsIfSymbolCouldntBeLoaded) {
    SoLoader* loader;
    ASSERT_NO_THROW(loader = new SoLoader(libraryFile));

    ASSERT_THROW(loader->LoadSymbol("TotallyRandomFunctionName"), GloveException);

    ASSERT_NO_THROW(delete loader);
}

TEST_F(SoLoaderTests, CanReloadLibrary) {
    SoLoader* loader;
    ASSERT_NO_THROW(loader = new SoLoader(libraryFile));
    ASSERT_NO_THROW(loader->ReloadLibrary());
    ASSERT_NO_THROW(delete loader);
}
}