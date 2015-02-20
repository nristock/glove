#include <gtest/gtest.hpp>

#include <glove/natex/impl/SharedLibraryModule.hpp>

#include "tests/mock/SharedLibraryMock.hpp"
#include "tests/mock/ModuleMock.hpp"
#include "tests/mock/ServiceRegistryMock.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Ref;
using ::testing::ReturnRef;

namespace glove {

TEST(SharedLibraryModuleTest, ForwardsLoadMethodInvokation) {
    std::unique_ptr<SharedLibraryMock> dso = std::make_unique<SharedLibraryMock>();
    std::unique_ptr<ModuleMock> moduleImpl = std::make_unique<ModuleMock>();
    EXPECT_CALL(*moduleImpl, Load()).Times(1);

    SharedLibraryModule module(std::move(moduleImpl), std::move(dso));
    module.Load();
}

TEST(SharedLibraryModuleTest, ForwardsUnloadMethodInvokation) {
    std::unique_ptr<SharedLibraryMock> dso = std::make_unique<SharedLibraryMock>();
    std::unique_ptr<ModuleMock> moduleImpl = std::make_unique<ModuleMock>();
    EXPECT_CALL(*moduleImpl, Unload()).Times(1);

    SharedLibraryModule module(std::move(moduleImpl), std::move(dso));
    module.Unload();
}

TEST(SharedLibraryModuleTest, ForwardsRegisterServicesMethodInvokation) {
    ServiceRegistryMock serviceRegistry;

    std::unique_ptr<SharedLibraryMock> dso = std::make_unique<SharedLibraryMock>();
    std::unique_ptr<ModuleMock> moduleImpl = std::make_unique<ModuleMock>();
    EXPECT_CALL(*moduleImpl, RegisterServices(Ref(serviceRegistry))).Times(1);

    SharedLibraryModule module(std::move(moduleImpl), std::move(dso));
    module.RegisterServices(serviceRegistry);
}

TEST(SharedLibraryModuleTest, ForwardsGetNameMethodInvokation) {
    std::string testName = "AwesomeModuleName";

    std::unique_ptr<SharedLibraryMock> dso = std::make_unique<SharedLibraryMock>();
    std::unique_ptr<ModuleMock> moduleImpl = std::make_unique<ModuleMock>();
    EXPECT_CALL(*moduleImpl, GetName()).Times(1).WillOnce(ReturnRef(testName));

    SharedLibraryModule module(std::move(moduleImpl), std::move(dso));
    EXPECT_EQ(testName, module.GetName());
}

TEST(SharedLibraryModuleTest, ForwardsGetVersionMethodInvokation) {
    auto versionInfo = ModuleVersionInfo(1, 2, 3);

    auto dso = std::make_unique<SharedLibraryMock>();
    auto moduleImpl = std::make_unique<ModuleMock>();
    EXPECT_CALL(*moduleImpl, GetVersion()).Times(1).WillOnce(ReturnRef(versionInfo));

    SharedLibraryModule module(std::move(moduleImpl), std::move(dso));
    EXPECT_EQ(versionInfo, module.GetVersion());
}

}