#include <gtest/gtest.hpp>

#include <glove/utils/StringId.hpp>

#include <iostream>

namespace BlueDwarf {

TEST(StringIdDatabaseTest, GetIdInsertsIfEntryDoesNotExist) {
    StringIdDatabase<Hash::Fnv1a> database;

    auto sid = database.GetId("Test");
}

TEST(StringIdDatabaseTest, CanResolveInsertedStrings) {
    StringIdDatabase<Hash::Fnv1a> database;

    auto sid = database.GetId("Test");
    EXPECT_EQ(std::string("Test"), database.Resolve(sid));
}

TEST(StringIdDatabaseTest, ReturnsEmptyStringIfEntryDoesNotExist) {
    StringIdDatabase<Hash::Fnv1a> database;

    EXPECT_EQ(std::string(""), database.Resolve(StringId{1235135}));
}
}