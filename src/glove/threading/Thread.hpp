#pragma once

#include <thread>
#include <atomic>
#include <memory>

#include "glove/GloveApi.hpp"
#include "glove/utils/DebugUtils.hpp"

namespace glove {
class Thread;

struct GLOVE_API_EXPORT Runnable {
  public:
    virtual ~Runnable() = default;

    virtual void Run(const Thread& thread) = 0;
};

using RunnableHandle = std::shared_ptr<Runnable>;

/**
* A Thread executes a Runnable implementation on a different system thread.
*
* Threads can be interrupted. While the time between an interrupt and the termination of the underlying system thread is
* finite, the time span can be arbitrarily long.
* Thread objects should not be created on the stack, hence the constructor is protected and a factory method is
* provided.
*/
class GLOVE_API_EXPORT Thread {
  public:
    ~Thread();

    /// Thread is not copyable
    Thread(const Thread&) = delete;
    /// Thread is not copyable
    Thread& operator=(const Thread&) = delete;

    /// Creates a new system thread and the call the Run function in this newly created thread.
    void Start();

    /**
    * Sets the interrupt flag.
    *
    * The runnable must ensure that a call to Join returns in a finite amount of time after Interrupt has been called.
    */
    void Interrupt();

    /// Blocks until the thread has finished execution. (std::thread::join)
    void Join();

    /**
    * Returns true if the executionFinished flag has been set.
    *
    * The executionFinished flag is set when the thread has left the scope of Thread::Run. The system thread may or may
    * not have terminated yet.
    * A true return value guarantees that a call to Join would return in a finite amount of time.
    */
    bool HasFinishedExecution() const;

    /// Returns the state of the interrupt flag.
    bool InterruptRequested() const;

    static std::shared_ptr<Thread> CreateThread(RunnableHandle runnable);

  protected:
    Thread(RunnableHandle runnable);

    /// Run invokes runnable's Runnable::Run method and sets the executionFinished flag once Runnable::Run returns.
    void Run();

    std::thread nativeThread;

    std::atomic_bool interruptFlag;
    std::atomic_bool executionFinished;

    RunnableHandle runnable;
};

} // namespace glove
