#include "MemoryProfile.h"

#include "core/pitamem/MemoryProfiler.h"
#include "utils/Demangle.h"

namespace glove {
MemoryProfile::~MemoryProfile() {
    MemoryProfiler::GetProfilerInstance()->UnregisterProfilable(this);
}

MemoryProfile::MemoryProfile(const std::type_info& typeinf, unsigned long sizeInBytes, void* root, MemoryGroup memGroup, bool autoregister)
        :
        sizeInBytes(sizeInBytes), rootMemory(root), memGroup(memGroup), sibling(nullptr) {
    typeName = Demangle(typeinf.name());

    if (autoregister) {
        MemoryProfiler::GetProfilerInstance()->RegisterProfilable(this);
    }
}

MemoryProfile::MemoryProfile(const std::type_info& typeinf, unsigned long sizeInBytes, void* root, MemoryGroup memGroup)
        :
        MemoryProfile(typeinf, sizeInBytes, root, memGroup, true) {
}

void MemoryProfile::SetSibling(MemoryProfile* sibling) {
    if (this->sibling == nullptr) {
        this->sibling = sibling;
    }
    else {
        this->sibling->SetSibling(sibling);
    }


}

MemoryProfile::SiblingIterator MemoryProfile::GetSiblings() {
    return SiblingIterator(sibling);
}

}