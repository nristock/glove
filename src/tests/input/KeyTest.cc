#include <gmock/gmock.hpp>

#include <glove/input/Keys.hpp>

namespace glove {
TEST(KeyTest, CanCompareKeys) {
    Key myKey("MyKey", Key::Type::FLOAT_AXIS);
    Key equalKey("MyKey", Key::Type::FLOAT_AXIS);
    Key diffNameKey("SomeDifferentName", Key::Type::FLOAT_AXIS);
    Key diffTypeKey("MyKey", Key::Type::BUTTON);

    EXPECT_TRUE(myKey == equalKey);
    EXPECT_FALSE(myKey == diffNameKey);
    EXPECT_FALSE(myKey == diffTypeKey);
}

TEST(KeyTest, RaisesStateChangeEventWhenStateIsUpdated) {
    Key myKey("MyKey", Key::Type::BUTTON);
    KeyState newState(true);

    bool publishedState = false;
    myKey.OnStateChanged().Subscribe([&](const KeyStateChanged& event){
        publishedState = event.IsKeyDown();
    });

    myKey.UpdateState(newState);

    EXPECT_EQ(newState.IsKeyDown(), publishedState);
}

}