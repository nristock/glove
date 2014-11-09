#include <array>
#include <list>
#include <algorithm>

#include <vendor/gtest/gtest.h>
#include "pitamem/MemoryProfile.h"
#include "pitamem/MemoryProfiler.h"
#include "utils/Demangle.h"

namespace glove {
class MemoryProfileTest : public ::testing::Test {
public:
    MemoryProfileTest() {
    }
};

TEST_F(MemoryProfileTest, InstantiationSetsSizeInBytes) {
	size_t testSize = 500;
	MemoryProfile profile(typeid(MemoryProfile), testSize, nullptr, MG_GENERIC, false);

	ASSERT_EQ(testSize, profile.GetSizeInBytes());
}

TEST_F(MemoryProfileTest, InstantiationSetsTypeName) {
	const std::type_info& testType = typeid(MemoryProfile);

	std::string typeName = Demangle(testType.name());
	MemoryProfile profile(testType, 0, nullptr, MG_GENERIC, false);

	ASSERT_EQ(typeName, profile.GetTypeName());
}

TEST_F(MemoryProfileTest, InstantiationSetsMemoryGroup) {
	const std::type_info& testType = typeid(MemoryProfile);

	MemoryProfile profile(testType, 0, nullptr, MG_GENERIC, false);

	ASSERT_EQ(MG_GENERIC, profile.GetMemoryGroup());
}

TEST_F(MemoryProfileTest, InstantiationSetsRootMemory) {
	int testValue = 5;

	void* testPointer = &testValue;
	MemoryProfile profile(typeid(MemoryProfile), 0, testPointer, MG_GENERIC, false);

	ASSERT_EQ(testPointer, profile.GetMemoryRoot());
}

TEST_F(MemoryProfileTest, AutomaticallyRegistersWithProfilerOnInstantiation) {
	MemoryProfiler* testProfiler = new MemoryProfiler();
	MemoryProfiler::SetProfilerInstance(testProfiler);

	MemoryProfile* testProfile = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC);

	// MemoryProfiler should only have a single registered object wich is our testProfile
	testProfiler->IterateRegisteredObjects([&](MemoryProfile* profile){
		ASSERT_EQ(testProfile, profile);
	});
}

TEST_F(MemoryProfileTest, CanSetAndGetSiblings) {
	MemoryProfile* testProfile1 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);
	MemoryProfile* testProfile2 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);
	MemoryProfile* testProfile3 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);

	testProfile1->SetSibling(testProfile2);
	testProfile1->SetSibling(testProfile3);

	ASSERT_EQ(testProfile2, testProfile1->GetImmediateSibling());
	ASSERT_EQ(testProfile3, testProfile2->GetImmediateSibling());
}

TEST_F(MemoryProfileTest, TestSiblingIterator) {
	MemoryProfile* testProfile1 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);
	MemoryProfile* testProfile2 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);
	MemoryProfile* testProfile3 = new MemoryProfile(typeid(MemoryProfile), 0, nullptr, MG_GENERIC, false);

	testProfile1->SetSibling(testProfile2);
	testProfile1->SetSibling(testProfile3);
	
	auto iter = testProfile1->GetSiblings();
	ASSERT_TRUE(iter.HasNext());
	ASSERT_EQ(testProfile2, (*iter));
	++iter;
	ASSERT_FALSE(iter.HasNext());
	ASSERT_EQ(testProfile3, (*iter));
}

}