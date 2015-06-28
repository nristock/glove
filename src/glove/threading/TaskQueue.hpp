#pragma once

#include <queue>
#include <memory>
#include <atomic>
#include <chrono>
#include <mutex>
#include <condition_variable>

#include "glove/CommonTypes.hpp"
#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

/**
* A Task represents a single unit of work which can be completed in a finite amount of time.
*
* Tasks should not be used to implement event-loop sort of constructs because that would stall a thread pools worker
* thread.
*
*/
class BD_API_EXPORT Task {
  public:
    virtual ~Task() = default;

    virtual void Execute() = 0;
};

using TaskHandle = std::shared_ptr<Task>;

/**
* A WrappedTask combines a shared_ptr to a Task and the task ID assigned to it.
*
* This class allows us to use value semantics when working with tasks internally.
*/
struct BD_API_EXPORT WrappedTask {
    WrappedTask() : WrappedTask(0, nullptr) {}
    WrappedTask(int taskId, TaskHandle innerTask) : taskId(taskId), innerTask(innerTask) {}

    int GetTaskId() const { return taskId; }
    TaskHandle GetTask() const { return innerTask; }

  protected:
    int taskId;
    TaskHandle innerTask;
};

/**
* Generic concurrent queue interface.
*/
template <class TItem> class BD_API_EXPORT Queue {
  public:
    virtual ~Queue() = default;

    /**
    * Pops the first element off the queue and returns it. If the queue is empty an invalid (nullptr) shared pointer
    * will be returned instead.
    */
    virtual std::shared_ptr<TItem> TryPop() = 0;

    /**
    * Pops the first element off the queue and returns it. If the queue is empty the method will block until the next
    *item has been queued.
    *
    * Note: This method will *never* return if the queue is drained and no new items are pushed.
    */
    virtual std::shared_ptr<TItem> PopBlocking() = 0;

    /**
    * Pops the first element off the queue and returns it. If the queue is empty the method will block until the next
    *item has been queued or @p maxWaitTime time has expired.
    *
    * If the method returned because of a timeout, an invalid (nullptr) shared pointer will be returned.
    */
    virtual std::shared_ptr<TItem> PopBlocking(const std::chrono::milliseconds maxWaitTime) = 0;

    /// Adds a new item to the end of the queue.
    virtual void Push(std::shared_ptr<TItem> item) = 0;

  protected:
    Queue() = default;
};

/**
* A TaskQueue allows to queue ont-time tasks.
*
* This class will not dispatch any threads nor execute the queued tasks on its own. ThreadPools use this class as their
* backing queue.
*/
class BD_API_EXPORT TaskQueue : public Queue<Task> {
  public:
    TaskQueue() { taskIdCounter.store(1); }
    virtual ~TaskQueue() = default;

    virtual TaskHandle TryPop() override;
    virtual TaskHandle PopBlocking() override;
    virtual TaskHandle PopBlocking(const std::chrono::milliseconds maxWaitTime) override;
    virtual void Push(TaskHandle task) override;

  protected:
    int GetNextTaskId() { return ++taskIdCounter; }

    /// Used to create unique task IDs.
    std::atomic_int taskIdCounter;

    std::mutex tasksMutex;
    /// One-time fire and forget tasks.
    std::queue<WrappedTask> tasks;
    std::condition_variable hasItems;

  private:
    /// Returns the front of the queue or an empty WrappedTask if the queue was empty. No lock is acquired.
    WrappedTask GetFrontChecked() const;
};

} /* namespace BlueDwarf */