#include <gtest/gtest.hpp>
#include <glove/natex/BifrostLoader.hpp>

#include "tests/bifrost/testlib/TestExtensionUuid.hpp"

namespace glove {

class BifrostLoaderTests : public ::testing::Test {
  protected:
    static const char* extensionName;
};

const char* BifrostLoaderTests::extensionName = "../lib/libtests_bifrost_testlib.so";

TEST_F(BifrostLoaderTests, CanConstructLoader) { ASSERT_NO_THROW(BifrostLoader loader); }

TEST_F(BifrostLoaderTests, CanLoadAndUnloadExtensionModule) {
    BifrostLoader* loader;

    ASSERT_NO_THROW(loader = new BifrostLoader());

    ISystemExtensionPtr sysExtension = loader->LoadSystemExtension(extensionName);

    ASSERT_NE(nullptr, sysExtension.get());

    ExtensionUuid uuid = TEST_EXTENSION_UUID;
    ASSERT_EQ(uuid, sysExtension->GetExtensionUuid());
    ASSERT_EQ(std::string(TEST_EXTENSION_NAME), sysExtension->GetExtensionName());

    ASSERT_NO_THROW(loader->UnloadSystemExtension(sysExtension));

    ASSERT_NO_THROW(delete loader);
}
}