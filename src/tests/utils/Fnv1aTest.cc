#include <gtest/gtest.hpp>

#include <chrono>

#include <glove/utils/hash/Fnv1a.hpp>

namespace BlueDwarf {
namespace Hash {
TEST(Fnv1aTest, CheckKnownHashes) {
    EXPECT_EQ(0x3d58dee72d4e0c27, Fnv1a::Hash("Hello World"));
    EXPECT_EQ(0xe441b6962e4bbf9b, Fnv1a::Hash("I'm awesome"));
    EXPECT_EQ(0xdd12a542800be888, Fnv1a::Hash("Monofraps"));
    EXPECT_EQ(0xec5cfab664eb1668, Fnv1a::Hash("Just some more random text"));
}

TEST(DISABLED_Fnv1aBench, Benchmark) {
    const auto str = std::string("str");
    const uint64 iterations = 0x100000000;
    uint64 aggregator = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < iterations; ++i) {
        aggregator ^= Fnv1a::Hash(str);
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << milliseconds << " [" << (float)(iterations / milliseconds) << "]"
              << " (" << aggregator << ")" << std::endl;
}
}
}