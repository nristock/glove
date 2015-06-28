#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/threading/ThreadPool.hpp"

namespace BlueDwarf {
namespace async {
/**
* A global thread pool used when executing generic async tasks.
*
* Generic async tasks are non-time-sensitive tasks like reading files or compiling resources.
*/
extern ThreadPool g_dwarfGlobalAsyncPool;

/**
* Queues a generic async task to be executed in the global async pool.
*/
template<typename TFunc> std::shared_ptr<PoolTask> ExecuteAsync(TFunc func) {
    class AsyncTask : public Task {
      public:
        AsyncTask(TFunc&& callable) : callable(callable) {}

        void Execute() {
            callable();
        }

      private:
        TFunc callable;
    };

    auto task = std::make_shared<AsyncTask>(std::move(func));
    return std::move(g_dwarfGlobalAsyncPool.SubmitWork(std::move(task)));
}
}
}