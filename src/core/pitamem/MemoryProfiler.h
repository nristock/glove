#pragma once

#include <list>
#include <memory>
#include <functional>
#include <map>
#include <unordered_set>
#include <thread>
#include <mutex>

#include <core/pitamem/MemoryProfile.h>

#ifdef _MSC_VER
#define thread_local __declspec(thread)
#endif

namespace glove {

class MemoryProfile;

class MemoryProfiler;

typedef std::shared_ptr<MemoryProfiler> MemoryProfilerPtr;

class MemoryProfiler {
public:
    static MemoryProfiler* GetProfilerInstance() {
        return GetThreadProfilerInstance(std::this_thread::get_id());
    }

    static MemoryProfiler* GetThreadProfilerInstance(std::thread::id threadId) {
        LockGuard lock(mutex);

        if (instances.find(threadId) == instances.end()) {
            SetThreadProfilerInstance(threadId, new MemoryProfiler());
        }

        return instances.find(std::this_thread::get_id())->second;
    }

    static void SetProfilerInstance(MemoryProfiler* profiler) {
        SetThreadProfilerInstance(std::this_thread::get_id(), profiler);
    }

    static void SetThreadProfilerInstance(std::thread::id threadId, MemoryProfiler* profiler) {
        LockGuard lock(mutex);

        if (instances.find(threadId) != instances.end()) {
            MemoryProfiler* oldProfiler = instances[threadId];
            instances.erase(threadId);
            delete oldProfiler;
        }

        instances.insert(InstanceEntry(threadId, profiler));
    }

    MemoryProfiler() :
            currentMemoryUsage(0),
            peakMemoryUsage(0),
            profilableObjects(64,
                    [](MemoryProfile* profile) {
                        return (std::size_t) (profile->GetMemoryRoot());
                    },
                    [](MemoryProfile* lhs, MemoryProfile* rhs) {
                        return lhs->GetMemoryRoot() == rhs->GetMemoryRoot();
                    }) {
    }

    virtual ~MemoryProfiler() {

    }

    unsigned long GetCurrentMemoryUsage() const {
        return currentMemoryUsage;
    }

    unsigned long GetPeakMemoryUsage() const {
        return peakMemoryUsage;
    }

    unsigned long GetRegisteredObjectCount() const {
        return profilableObjects.size();
    }

    void RegisterProfilable(MemoryProfile* profilable);

    void UnregisterProfilable(MemoryProfile* profilable);

    void IterateRegisteredObjects(std::function<void(MemoryProfile*)> callback);

private:
    typedef std::lock_guard<std::recursive_mutex> LockGuard;
    typedef std::pair<std::thread::id, MemoryProfiler*> InstanceEntry;
    typedef std::unordered_set<MemoryProfile*, std::function<size_t(MemoryProfile*)>, std::function<bool(MemoryProfile*, MemoryProfile*)>> ProfilableObjectList;

    static std::map<std::thread::id, MemoryProfiler*> instances;
    static std::recursive_mutex mutex;

    unsigned long currentMemoryUsage;
    unsigned long peakMemoryUsage;

    ProfilableObjectList profilableObjects;
};

} /* namespace glove */