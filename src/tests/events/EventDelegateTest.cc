#include <gmock/gmock.hpp>

#include <glove/events/EventDelegate.hpp>

namespace {
struct TestEventData {
    int someValue;
};

}

namespace glove {
TEST(EventDelegateTest, SubPubNoLocking) {
    SimpleEvent<TestEventData> event;

    int publishedValue = 0;

    event.Subscribe([&](const TestEventData &data) {
        publishedValue = data.someValue;
    });

    ::TestEventData data;
    data.someValue = 123;

    event.Publish(data);

    EXPECT_EQ(publishedValue, data.someValue);
}

TEST(EventDelegateTest, SubPubSharedLocking) {
    ThreadedEvent<TestEventData> event;

    int publishedValue = 0;

    event.Subscribe([&](const TestEventData &data) {
        publishedValue = data.someValue;
    });

    ::TestEventData data;
    data.someValue = 123;

    event.Publish(data);

    EXPECT_EQ(publishedValue, data.someValue);
}
}