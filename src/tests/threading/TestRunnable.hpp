#pragma once

#include <thread>

#include <glove/threading/Thread.hpp>

namespace glove {
struct TestRunnable : public Runnable {
  public:
    TestRunnable(int valueToStore) : valueToStore(valueToStore) { flag.store(valueToStore - 1); }

    virtual void Run(const Thread& thread) {
        flag.store(valueToStore);

        while (!thread.InterruptRequested()) {
            std::this_thread::yield();
        }
    }

    int GetFlag() const { return flag.load(); }

  private:
    int valueToStore;
    std::atomic_int flag;
};
}