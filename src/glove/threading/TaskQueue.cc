#include "glove/threading/TaskQueue.hpp"
#include "glove/threading/ThreadPool.hpp"

namespace {
using Milliseconds = std::chrono::duration<BlueDwarf::uint32, std::milli>;
}

namespace BlueDwarf {

void TaskQueue::Push(TaskHandle task) {
    int taskId = GetNextTaskId();

    // Actually insert the new task
    {
        std::unique_lock<std::mutex> lock(tasksMutex);
        tasks.emplace(taskId, task);
    }

    hasItems.notify_one();
}

TaskHandle TaskQueue::TryPop() {
    WrappedTask task;
    {
        std::unique_lock<std::mutex> lock(tasksMutex);
        if(!tasks.empty()) {
            task = tasks.front();
            tasks.pop();
        }
    }

    return task.GetTask();
}

TaskHandle TaskQueue::PopBlocking() {
    WrappedTask task;
    {
        std::unique_lock<std::mutex> lock(tasksMutex);
        task = GetFrontChecked();

        while (!task.GetTask()) {
            hasItems.wait(lock);
            task = GetFrontChecked();
        }

        tasks.pop();
    }

    return task.GetTask();
}

TaskHandle TaskQueue::PopBlocking(const std::chrono::milliseconds maxWaitTime) {
    WrappedTask task;
    {
        std::unique_lock<std::mutex> lock(tasksMutex);
        task = GetFrontChecked();

        while (!task.GetTask()) {
            auto wakeupReason = hasItems.wait_for(lock, maxWaitTime);
            if(wakeupReason == std::cv_status::timeout) {
                return task.GetTask();
            }

            task = GetFrontChecked();
        }

        tasks.pop();
    }

    return task.GetTask();
}

WrappedTask TaskQueue::GetFrontChecked() const {
    if(!tasks.empty()) {
        return tasks.front();
    }

    return WrappedTask{};
}
}