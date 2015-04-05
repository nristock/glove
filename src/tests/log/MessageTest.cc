#include <gmock/gmock.hpp>

#include <glove/log/Message.hpp>

#include <glove/log/MessageProcessors.hpp>
#include <glove/log/Logger.hpp>

namespace glove {
TEST(MessageTest, CanCreateFromLogLevelAndString) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";

    auto message = Message{expectedLogLevel, expectedMessage};

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_EQ(expectedMessage, message.GetMessage());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
}

TEST(MessageTest, CanCreateFromLogLevelAndException) {
    struct TestException : std::exception {
        TestException(const std::string& message) : message(message) {}

        const char* what() const noexcept {
            return message.c_str();
        }

        std::string message;
    };

    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::exception& expectedException = TestException("My Message");

    auto message = Message{expectedLogLevel, expectedException};

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_EQ(expectedException.what(), message.GetMessage());
    EXPECT_TRUE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
}

TEST(MessageTest, CanCreateFromLogLevelAndStreamMessage) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";

    auto message = Message{expectedLogLevel, StreamMessage() << expectedMessage};

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_EQ(expectedMessage, message.GetMessage());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
}

TEST(MessageTest, ReturnsMessageAsTextIfNoTextHasBeenSet) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";

    auto message = Message{expectedLogLevel,  expectedMessage};

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
    EXPECT_EQ(expectedMessage, message.GetText());
}

TEST(MessageTest, ReturnsTextIfTextHasBeenSet) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";
    const std::string expectedText = "My Text";

    auto message = Message{expectedLogLevel,  expectedMessage};
    message.SetText(expectedText);

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
    EXPECT_EQ(expectedMessage, message.GetMessage());
    EXPECT_EQ(expectedText, message.GetText());
}

TEST(MessageTest, CanSetAndGetCustomProperties) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";

    const std::string expectedCustomProperty = "My prop";

    auto message = Message{expectedLogLevel, expectedMessage};
    message.SetProperty("CustomProp", expectedCustomProperty);

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_EQ(expectedMessage, message.GetMessage());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
    EXPECT_EQ(expectedCustomProperty, message.GetProperty("CustomProp"));
}

TEST(MessageTest, CanSetAndGetSource) {
    const LogLevel expectedLogLevel = LogLevel::Info;
    const std::string expectedMessage = "My awesome message";
    const std::string expectedSource = "My source";

    auto message = Message{expectedLogLevel, expectedMessage};
    message.SetSource(expectedSource);

    EXPECT_EQ(expectedLogLevel, message.GetLogLevel());
    EXPECT_EQ(expectedMessage, message.GetMessage());
    EXPECT_FALSE(message.IsExceptionMessage());
    EXPECT_EQ(std::this_thread::get_id(), message.GetThreadId());
    EXPECT_EQ(expectedSource, message.GetSource());
}
}