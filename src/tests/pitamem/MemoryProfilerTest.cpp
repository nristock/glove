#include <array>
#include <list>
#include <algorithm>

#include "tests/gtest/gtest.h"
#include "pitamem/MemoryProfiler.h"
#include "pitamem/MemoryProfile.h"

namespace glove {
class MemoryProfilerTest : public ::testing::Test {
public:
    MemoryProfilerTest() {
        // Always create a new test profiler and overwrite the current one
        // to make sure all tests are independent.
        MemoryProfiler* testProfiler = new MemoryProfiler();
        MemoryProfiler::SetProfilerInstance(testProfiler);
    }

protected:
    MemoryProfiler* GetProfiler() {
        return MemoryProfiler::GetProfilerInstance();
    }
};

TEST_F(MemoryProfilerTest, CanSetAndGetCurrentProfilerInstance) {
    MemoryProfiler* localProfiler = new MemoryProfiler();
    MemoryProfiler::SetProfilerInstance(localProfiler);
    ASSERT_EQ(localProfiler, MemoryProfiler::GetProfilerInstance());
}

TEST_F(MemoryProfilerTest, InitialMemoryUsageIsZero) {
    ASSERT_EQ(0, GetProfiler()->GetCurrentMemoryUsage());
    ASSERT_EQ(0, GetProfiler()->GetPeakMemoryUsage());
}


TEST_F(MemoryProfilerTest, AddingAndRemovingProfilablesUpdatesObjectCountAndMemoryUsages) {
    const int profilableMemUsage = 150;
    MemoryProfile* profilable = new MemoryProfile(typeid(MemoryProfile), 150, nullptr, MG_GENERIC, false);

    ASSERT_EQ(0, GetProfiler()->GetRegisteredObjectCount());

    GetProfiler()->RegisterProfilable(profilable);
    ASSERT_EQ(1, GetProfiler()->GetRegisteredObjectCount());
    ASSERT_EQ(profilableMemUsage, GetProfiler()->GetCurrentMemoryUsage());
    ASSERT_EQ(profilableMemUsage, GetProfiler()->GetPeakMemoryUsage());
    GetProfiler()->UnregisterProfilable(profilable);
    ASSERT_EQ(0, GetProfiler()->GetRegisteredObjectCount());
    ASSERT_EQ(0, GetProfiler()->GetCurrentMemoryUsage());
    ASSERT_EQ(profilableMemUsage, GetProfiler()->GetPeakMemoryUsage());
}

TEST_F(MemoryProfilerTest, ProvidesProfilableObjectList) {
    std::array<unsigned long, 5> profilableMemUsages = {150, 40, 123, 2359, 24};
    std::list<MemoryProfile*> profilables;

    for (int i = 0; i < 5; i++) {
		MemoryProfile* profilable =new MemoryProfile(typeid(MemoryProfile), profilableMemUsages[i], nullptr, MG_GENERIC, false);
        profilables.push_back(profilable);
        GetProfiler()->RegisterProfilable(profilable);
    }

    GetProfiler()->IterateRegisteredObjects([&](MemoryProfile* profilable) {
        auto iter = std::find(profilables.begin(), profilables.end(), profilable);
        ASSERT_NE(profilables.end(), iter);
    });
}

}