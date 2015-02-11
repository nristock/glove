#include <gtest/gtest.hpp>

#include <random>

#include <glove/utils/BitMask.hpp>

namespace glove {
TEST(BitMaskTest, NewBitMaskIsAllZero) {
    BitMask mask;

	EXPECT_EQ(0, mask.ToInt32());
}

TEST(BitMaskTest, CanSetAndTestBits) {
    BitMask mask;

    std::default_random_engine generator;
    std::uniform_int_distribution<BitMask::BitIndex> distribution(0, BitMask::MAX_INDEX);

    for(short i = 0; i < 100; ++i) {
        BitMask::BitIndex index = distribution(generator);
        mask.Set(index);
        EXPECT_TRUE(mask.IsSet(index));
    }
}

TEST(BitMaskTest, CanClearBits) {
    BitMask mask;

    std::default_random_engine generator;
    std::uniform_int_distribution<BitMask::BitIndex> distribution(0, BitMask::MAX_INDEX);

    for(short i = 0; i < 100; ++i) {
        BitMask::BitIndex index = distribution(generator);
        mask.Set(index);
        mask.Clear(index);
        EXPECT_FALSE(mask.IsSet(index));
    }
}

TEST(BitMaskTest, CanUseArrayAccessOperator) {
    BitMask mask;

    std::default_random_engine generator;
    std::uniform_int_distribution<BitMask::BitIndex> distribution(0, BitMask::MAX_INDEX);

    for(short i = 0; i < 100; ++i) {
        BitMask::BitIndex index = distribution(generator);
        mask.Set(index);
        EXPECT_TRUE(mask[index]);
    }
}

TEST(BitMaskTest, ContainsReturnsTrueIfAllBitsInTestMaskWithASingleSetBitAreSetInMask) {
    BitMask primaryMask;
    primaryMask.Set(4);
    primaryMask.Set(5);
    primaryMask.Set(8);
    primaryMask.Set(28);

    BitMask testMask;
    testMask.Set(8);

    EXPECT_TRUE(primaryMask.Contains(testMask));
}

TEST(BitMaskTest, ContainsReturnsTrueIfAllBitsInTestMaskWithMultipleSetBitsAreSetInMask) {
    BitMask primaryMask;
    primaryMask.Set(4);
    primaryMask.Set(5);
    primaryMask.Set(8);
    primaryMask.Set(28);

    BitMask testMask;
    testMask.Set(5);
    testMask.Set(28);

    EXPECT_TRUE(primaryMask.Contains(testMask));
}

TEST(BitMaskTest, ContainsReturnsFalseIfBitInTestMaskWithSingleBitIsNotSetInMask) {
    BitMask primaryMask;
    primaryMask.Set(4);
    primaryMask.Set(5);
    primaryMask.Set(8);
    primaryMask.Set(28);

    BitMask testMask;
    testMask.Set(9);

    EXPECT_FALSE(primaryMask.Contains(testMask));
}

TEST(BitMaskTest, ContainsReturnsFalseIfOnlyASingleBitInTestMaskIsNotSetInMask) {
    BitMask primaryMask;
    primaryMask.Set(4);
    primaryMask.Set(5);
    primaryMask.Set(8);
    primaryMask.Set(28);

    BitMask testMask;
    testMask.Set(5);
    testMask.Set(9);

    EXPECT_FALSE(primaryMask.Contains(testMask));
}
}