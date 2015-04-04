#include <gtest/gtest.hpp>

#include "TestRunnable.hpp"

#include <glove/threading/Async.hpp>

#include <iostream>

namespace glove {
class ThreadTest : public ::testing::Test {

  protected:
    virtual void SetUp() {
        valueToStore = 15;
        runnable = std::make_shared<TestRunnable>(valueToStore);
        thread = Thread::CreateThread(runnable);
    }

    void StartThread() {
        thread->Start();
    }

    void InterruptThread() {
        thread->Interrupt();
    }

    void JoinThread() {
        thread->Join();
    }

    void InterruptAndJoin() {
        InterruptThread();
        JoinThread();
    }

    int valueToStore;
    std::shared_ptr<TestRunnable> runnable;
    std::shared_ptr<Thread> thread;
};

TEST_F(ThreadTest, CanStartAndStopThread) {
    EXPECT_NE(valueToStore, runnable->GetFlag());

    StartThread();
    InterruptThread();
    JoinThread();

    EXPECT_EQ(valueToStore, runnable->GetFlag());
}

TEST_F(ThreadTest, ThreadIsInValidStateAfterConstruction) {
    EXPECT_FALSE(thread->InterruptRequested());
    EXPECT_FALSE(thread->HasFinishedExecution());
}

TEST_F(ThreadTest, ThreadIsInValidStateAfterStart) {
    StartThread();
    EXPECT_FALSE(thread->InterruptRequested());
    EXPECT_FALSE(thread->HasFinishedExecution());

    InterruptAndJoin();
}

TEST_F(ThreadTest, PropagatesInterruptRequest) {
    InterruptThread();
    EXPECT_TRUE(thread->InterruptRequested());
}

}