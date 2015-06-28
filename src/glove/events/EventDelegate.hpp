#pragma once

#include <list>
#include <functional>
#include <shared_mutex>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {

namespace events {
/// \brief Locking policy using shared_timed_mutex.
///
/// This sharing policy uses a shared mutex for locking and should be used for objects which are shared in a threaded
/// context.
class SharedMutexLockingPolicy {
  public:
    inline void LockShared() {
        mutex.lock_shared();
    }

    inline void LockExclusive() {
        mutex.lock();
    }

    inline void UnlockShared() {
        mutex.unlock_shared();
    }

    inline void UnlockExclusive() {
        mutex.unlock();
    }

  private:
    std::shared_timed_mutex mutex;
};

/// \brief No-lock locking policy (i.e. no-op implementation).
///
/// This sharing policy does not lock and should be used for objects which will not be shared in a threaded context.
class NoLockPolicy {
  public:
    inline void LockShared() {}
    inline void LockExclusive() {}
    inline void UnlockShared() {}
    inline void UnlockExclusive() {}
};
}

/// \brief Basic class for implementing a sync distributed event system.
///
/// Objects and interfaces can expose instances of this class to allow subscriber registrations.
/// Template parameter T is the event data type. Publish will accept a const T& event data object and pass it on to
/// individual event handlers. An event handler is a std::function with the signature void(const T& eventData).
///
/// Thread safety of this class/objects of this class is defined by the specified LockingPolicy.
/// A LockingPolicy needs to provide the following methods:
///   LockShared(void)
///   LockExclusive(void)
///   UnlockShared(void)
///   UnlockExclusive(void)
/// Two default policy implementations exist: @link NoLockPolicy and @link SharedMutexLockingPolicy.
/// Every time the internal list of subscribers is accessed for reading, the policies LockShared and UnlockShared
/// methods are called. Write access to the subscriber list is secured by calls to LockExclusive and UnlockExclusive.
template<class T, class LockingPolicy>
class BD_API_EXPORT EventDelegate {
  public:
    using EventType = T;
    using HandlerType = std::function<void(const T& eventData)>;

    void Publish(const T& eventData) const {
        lockingPolicy.LockShared();
        for (const auto &handler : subscribers) {
            handler(eventData);
        }
        lockingPolicy.UnlockShared();
    }

    void Subscribe(HandlerType handler) const {
        lockingPolicy.LockExclusive();
        subscribers.emplace_back(handler);
        lockingPolicy.UnlockExclusive();
    }

  private:
    mutable std::list<HandlerType> subscribers;
    mutable LockingPolicy lockingPolicy;
};

/// An event which is not thread-safe but optimized for single-threaded usage (i.e. no mutex locking).
template<class T> using SimpleEvent = EventDelegate<T, events::NoLockPolicy>;
/// An event which is thread-safe using shared (R/W) mutex locking.
template<class T> using ThreadedEvent = EventDelegate<T, events::SharedMutexLockingPolicy>;
}