#include <gmock/gmock.hpp>

#include <glove/natex/Module.hpp>

#include "tests/mock/BasicModuleMock.hpp"

namespace BlueDwarf {
TEST(ModuleVersionInfoTest, StoresMinorMajorPatchVersions) {
    ModuleVersionInfo version(3, 4, 5);

    EXPECT_EQ(3, version.GetMajor());
    EXPECT_EQ(4, version.GetMinor());
    EXPECT_EQ(5, version.GetPatch());
}

TEST(ModuleVersionInfoTest, CompatibilityCheckReturnsTrueByDefault) {
    ModuleVersionInfo version(3, 4, 5);
    EngineVersionInfo engineVersion(1, 2, 3);

    EXPECT_TRUE(version.IsCompatibleWith(engineVersion));
}

TEST(ModuleVersionInfoTest, CheckDefaultVersionStringFormat) {
    ModuleVersionInfo version(3, 4, 5);

    EXPECT_EQ("3.4.5", version.ToString());
}

TEST(BasicModuleTest, ConstructorStoresNameAndVersion) {
    ModuleVersionInfo version(3, 4, 5);
    std::string moduleName = "TestModule";

    BasicModuleMock module(moduleName, version);

    EXPECT_EQ(moduleName, module.GetName());
    EXPECT_EQ(version, module.GetVersion());
}

}