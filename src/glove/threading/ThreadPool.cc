#include "glove/utils/DebugUtils.hpp"
#include "glove/GloveConfig.hpp"
#include "glove/threading/ThreadPool.hpp"
#include "glove/threading/Thread.hpp"
#include "glove/threading/TaskQueue.hpp"
#include "glove/utils/DebugUtils.hpp"

namespace {

using namespace glove;

/**
* A NullTask doesn't do any actual work. Its merely used to trigger queue pop condition wakeups.
*/
class NullTask : public Task {
    void Execute() override {}
};

class PoolWorker : public Runnable {
  public:
    PoolWorker(std::shared_ptr<TaskQueue> taskQueue) : taskQueue(taskQueue) {}

    /**
    * Run will try to poll tasks from the underlying queue using a timed blocking poll strategy.
    *
    * This way the worker can respond to interrupt requests.
    */
    void Run(const Thread& thread) override {
        while (!thread.InterruptRequested()) {
            TaskHandle task;

            do {
                task = taskQueue->PopBlocking(std::chrono::milliseconds(GLOVE_POOL_WORKER_WAIT_TIMEOUT));

                if (thread.InterruptRequested()) {
                    return;
                }
            } while (!task);

            // At this point we have a valid task object.
            try {
                task->Execute();
            } catch (std::exception& ex) {
                LOG(Error, fmt::format("Error executing pool task {0}", ex.what()));
            }
        }
    }

  private:
    std::shared_ptr<TaskQueue> taskQueue;
};
}

namespace glove {

ThreadPool::ThreadPool(uint32 workerCount) : workerCount(workerCount) {
    taskQueue = std::make_shared<TaskQueue>();

    for (uint32 i = 0; i < workerCount; ++i) {
        SpawnWorker();
    }
}

ThreadPool::~ThreadPool() {
    for (auto& worker : pool) {
        worker->Interrupt();

        auto nullTask = std::make_shared<NullTask>();
        SubmitWork(nullTask);
    }

    for (auto& worker : pool) {
        worker->Join();
    }
}

void ThreadPool::SpawnWorker() {
    // Create the worker Runnable + Thread and start the Thread
    auto workerRunnable = std::make_shared<PoolWorker>(taskQueue);
    auto workerThread = Thread::CreateThread(workerRunnable);

    workerThread->Start();

    // Insert the new worker into the pool
    std::unique_lock<std::mutex> poolLock(poolMutex);
    pool.emplace_back(std::move(workerThread));
}

std::shared_ptr<PoolTask> ThreadPool::SubmitWork(TaskHandle task) {
    auto poolTask = std::make_shared<PoolTask>(std::move(task));
    taskQueue->Push(poolTask);

    return poolTask;
}

void PoolTask::Execute() {
    innerTask->Execute();
    taskStatus.SignalDone();
}

void PoolTask::TaskStatus::AwaitDone() {
    if (doneFlag.load(std::memory_order_acquire)) {
        return;
    }

    std::unique_lock<std::mutex> doneLock(doneMutex);
    done.wait(doneLock);
}

void PoolTask::TaskStatus::SignalDone() {
    doneFlag.store(true, std::memory_order_release);
    done.notify_all();
}
}