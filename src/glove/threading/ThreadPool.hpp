#pragma once

#include <memory>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <list>

#include "glove/GloveApi.hpp"
#include "glove/CommonTypes.hpp"
#include "glove/threading/Thread.hpp"
#include "glove/threading/TaskQueue.hpp"

namespace glove {
using TaskHandle = std::shared_ptr<Task>;
using ThreadHandle = std::shared_ptr<Thread>;

/**
* A PoolTask wraps a generic Task and allows to wait for its completion.
*/
class GLOVE_API_EXPORT PoolTask : public Task {
  public:
    PoolTask(TaskHandle innerTask) : innerTask(std::move(innerTask)) {}
    void Execute() override;

    void AwaitCompletion() { taskStatus.AwaitDone(); }

  private:
    struct TaskStatus {
      public:
        TaskStatus() { doneFlag.store(false, std::memory_order_release); }
        void AwaitDone();
        void SignalDone();

      private:
        std::mutex doneMutex;
        std::condition_variable done;
        std::atomic_bool doneFlag;
    };

    TaskHandle innerTask;
    TaskStatus taskStatus;
};

/**
* A ThreadPool executes submitted work using a fixed number of pooled worker threads.
*/
class GLOVE_API_EXPORT ThreadPool {
  public:
    ThreadPool(uint32 workerCount);

    /**
    * Ensures a clean shutdown of all workers.
    *
    * The destructor requests all workers to interrupt and waits for them to join. It will also push empty tasks to the
    * queue to trigger condition wakeups.
    */
    ~ThreadPool();

    std::shared_ptr<PoolTask> SubmitWork(TaskHandle task);

    uint32 GetWorkerCount() const { return workerCount; }

  private:
    void SpawnWorker();

    uint32 workerCount;

    /// The queue to poll work items from.
    std::shared_ptr<TaskQueue> taskQueue;
    /// The list of active threads.
    std::list<ThreadHandle> pool;

    std::mutex poolMutex;
};
} // namespace glove
