#include <core/BifrostLoader.h>

#include <vendor/gtest/gtest.h>

#include "testlib/TestExtensionUuid.h"

namespace glove {

class BifrostLoaderTests : public ::testing::Test {
  protected:
    static const char* extensionName;
};

const char* BifrostLoaderTests::extensionName = "libtests_bifrost_testlib";

TEST_F(BifrostLoaderTests, CanConstructLoader) { ASSERT_NO_THROW(BifrostLoader loader()); }

TEST_F(BifrostLoaderTests, CanLoadAndUnloadExtensionModule) {
    BifrostLoader* loader;

    ASSERT_NO_THROW(loader = new BifrostLoader());

    ISystemExtensionPtr sysExtensionWeakPtr = loader->LoadSystemExtension(extensionName);

    {
        auto sysExtension = sysExtensionWeakPtr.lock();
        ASSERT_NE(nullptr, sysExtension.get());

        ExtensionUuid uuid = TEST_EXTENSION_UUID;
        ASSERT_EQ(uuid, sysExtension->GetExtensionUuid());
        ASSERT_EQ(std::string(TEST_EXTENSION_NAME), sysExtension->GetExtensionName());
    }

    ASSERT_NO_THROW(loader->UnloadSystemExtension(sysExtensionWeakPtr));

    ASSERT_NO_THROW(delete loader);
}
}