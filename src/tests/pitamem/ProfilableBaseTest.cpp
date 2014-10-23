#include <array>
#include <list>
#include <algorithm>

#include "tests/gtest/gtest.h"
#include "pitamem/MemoryProfiler.h"
#include "pitamem/MemoryProfile.h"

namespace glove {
class ProfilableBaseTest : public ::testing::Test {
public:
	ProfilableBaseTest() {
    }
};

TEST_F(ProfilableBaseTest, CanSetAndGetCurrentProfilerInstance) {
}


}