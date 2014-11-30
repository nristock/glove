#include <functional>
#include <algorithm>
#include "MemoryProfiler.h"
#include "MemoryProfile.h"

namespace glove {
std::map<std::thread::id, MemoryProfiler*> MemoryProfiler::instances;
std::recursive_mutex MemoryProfiler::mutex;

void MemoryProfiler::RegisterProfilable(MemoryProfile* profilable) {
    LockGuard lock(mutex);

    auto iter = profilableObjects.find(profilable);
    if (iter != profilableObjects.end()) {
        (*iter)->SetSibling(profilable);
    }

    currentMemoryUsage += profilable->GetSizeInBytes();
    if (currentMemoryUsage > peakMemoryUsage)
        peakMemoryUsage = currentMemoryUsage;
    profilableObjects.insert(profilable);
}

void MemoryProfiler::UnregisterProfilable(MemoryProfile* profilable) {
    LockGuard lock(mutex);

    if (profilableObjects.find(profilable) == profilableObjects.end())
        return;

    currentMemoryUsage -= profilable->GetSizeInBytes();
    profilableObjects.erase(profilable);
}

void MemoryProfiler::IterateRegisteredObjects(std::function<void(MemoryProfile*)> callback) {
    LockGuard lock(mutex);

    for (MemoryProfile* profilable : profilableObjects) {
        callback(profilable);
    }
}
}
