#pragma once

#include <memory>
#include <mutex>

namespace glove {

template<typename T>
class Singleton {
public:
    typedef std::shared_ptr<T> SharedPtr;

    static const SharedPtr& GetInstance() {
        static SharedPtr instance;

        if (!instance) {
            LockGuard lock = GetWriteLock();

            if (!instance) {
                instance = std::make_shared<T>();
            }
        }

        return instance;
    }

private:
    typedef std::lock_guard<std::mutex> LockGuard;

    static LockGuard GetWriteLock() {
        static std::mutex writeMutex;

        return LockGuard(writeMutex);
    }
};

} /* namespace glove */