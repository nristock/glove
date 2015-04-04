#include <gtest/gtest.hpp>

#include <glove/threading/ThreadPool.hpp>
#include <glove/threading/TaskQueue.hpp>

namespace glove {
class ThreadPoolTest : public ::testing::Test {

  protected:
    virtual void SetUp() {
        valueToSet = 15;
        expectedWorkerCount = 3;
    }

    uint32 valueToSet;
    uint32 expectedWorkerCount;
};

TEST_F(ThreadPoolTest, CanCreateThreadPoolOfDesiredSize) {
    ThreadPool pool(expectedWorkerCount);

    EXPECT_EQ(expectedWorkerCount, pool.GetWorkerCount());
}

TEST_F(ThreadPoolTest, ExecutesSubmittedWork) {
    ThreadPool pool(1);

    struct TestTask : public Task {
        TestTask(int valueToStore) : valueToStore(valueToStore) {storedValue.store(valueToStore - 1);}
        virtual void Execute() { storedValue.store(valueToStore); }
        int GetStoredValue() const { return storedValue.load(); }
      private:
        const int valueToStore;
        std::atomic_int storedValue;
    };

    auto task = std::make_shared<TestTask>(valueToSet);

    EXPECT_NE(valueToSet, task->GetStoredValue());

    auto taskStatus = pool.SubmitWork(task);
    taskStatus->AwaitCompletion();

    EXPECT_EQ(valueToSet, task->GetStoredValue());
}
}