#include <gmock/gmock.hpp>

#include <glove/input/events/KeyStateChanged.hpp>

namespace glove {
TEST(KeyStateChangedTest, StoresAxisValue) {
    auto testValue = 15.3f;
    KeyStateChanged eventData(testValue);

    EXPECT_EQ(testValue, eventData.GetAxisValue());
}

TEST(KeyStateChangedTest, CanDeriveButtonState) {
    auto isDown = true;
    KeyStateChanged eventData(isDown);

    EXPECT_EQ(isDown, eventData.IsKeyDown());
    EXPECT_NE(eventData.IsKeyDown(), eventData.IsKeyUp());
}
}