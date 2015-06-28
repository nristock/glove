#include <gtest/gtest.hpp>

#include <chrono>

#include <glove/threading/TaskQueue.hpp>

namespace {
struct TestTask : public BlueDwarf::Task {
    TestTask() {
        hasExecutedFlag.store(false);
    }

    void Execute() override {
        hasExecutedFlag.store(true);
    }

    bool HasExecuted() {
        return hasExecutedFlag.load();
    }

  private:
    std::atomic_bool hasExecutedFlag;
};
}

namespace BlueDwarf {
TEST(TaskQueueTest, CanPushElements) {
    TaskQueue taskQueue;

    auto testTask = std::make_shared<TestTask>();

    taskQueue.Push(testTask);
}

TEST(TaskQueueTest, TryPopReturnsFirstElementInQueue) {
    TaskQueue taskQueue;

    auto firstTask = std::make_shared<TestTask>();
    auto secondTask = std::make_shared<TestTask>();

    taskQueue.Push(firstTask);
    taskQueue.Push(secondTask);

    auto poppedTask = taskQueue.TryPop();
    EXPECT_EQ(firstTask, poppedTask);

    poppedTask = taskQueue.TryPop();
    EXPECT_EQ(secondTask, poppedTask);
}

TEST(TaskQueueTest, TryPopReturnsEmptyPointerIfQueueIsEmpty) {
    TaskQueue taskQueue;

    auto poppedTask = taskQueue.TryPop();
    EXPECT_FALSE((bool)poppedTask);
}

TEST(TaskQueueTest, PopBlockingTimesOutAfterMaxWaitTimeIfQueueIsEmpty) {
    TaskQueue taskQueue;

    auto poppedTask = taskQueue.PopBlocking(std::chrono::milliseconds(10));
    EXPECT_FALSE((bool)poppedTask);
}

TEST(TaskQueueTest, PopBlockingDoesNotBlockIfQueueIsNotEmpty) {
    TaskQueue taskQueue;

    auto testTask = std::make_shared<TestTask>();
    taskQueue.Push(testTask);

    auto poppedTask = taskQueue.PopBlocking();
    EXPECT_EQ(testTask, poppedTask);
}
}