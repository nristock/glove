#pragma once

#include <string>
#include <typeinfo>
#include <memory>

#include "pitamem/MemoryGroup.h"

#define EnableProfilable() __memProfilerInterface(this, MG_GENERIC)
#define Profilable() private: ::glove::memory::ProfilableBase __memProfilerInterface;

namespace glove {

/**
* This class is used by the memory profiling subsystem to track engine objects.
*  It holds information about the object's location in memory, its size and type as well as its memory group.
*  If more than one MemoryProfile is constructed for the same object a linked list of corresponding MemoryProfiles is created.
*/
class MemoryProfile : public std::enable_shared_from_this<MemoryProfile> {
public:

    /** An iterator to walk through all related MemoryProfiles */
    struct SiblingIterator {
        /** The current sibling */
        MemoryProfile* sibling;

        SiblingIterator(MemoryProfile* sibling) : sibling(sibling) {
        }

        /** Returns true if the current sibling has a sibling != nullptr */
        bool HasNext() {
            return !(sibling->sibling == nullptr);
        }

        /** Returns true if the current sibling is null */
        bool IsEnd() {
            return sibling == nullptr;
        }

        /** The increment operator sets the current sibling to the current sibling's sibling */
        SiblingIterator& operator++() {
            sibling = sibling->sibling;

            return *this;
        }

        /** "Dereferences" the iterator to the current memory profile */
        MemoryProfile* operator*() {
            return sibling;
        }
    };

    /**
     * Creates a self-registereing memory profile using the provided type information, size, root and memory group.
     * See MemoryProfile(const std::type_info& typeinf, unsigned long sizeInBytes, void* root, MemoryGroup memGroup, bool autoregister) for more information.
    */
    MemoryProfile(const std::type_info& typeinf, unsigned long sizeInBytes, void* root, MemoryGroup memGroup);

    /**
     * Creates a memory profile.
     * @param [in] typeinf The std::type_info (typeid(...)) of the object to register with the profiler.
     * @param [in] sizeInBytes The object's size in bytes (sizeof(...))
     * @param [in] root The object's location in memory. This parameter is used to determine whether a MemoryProfile for this object has already been created.
     * @param [in] memGroup The object's memory group. This parameter is used to provide grouped diagnostics output from the profiler.
     * @param [in] autoregister Specifies whether the MemoryProfile should announce itself to the profiler.
     */
    MemoryProfile(const std::type_info& typeinf, unsigned long sizeInBytes, void* root, MemoryGroup memGroup, bool autoregister);

    /** Automatically unregisters this MemoryProfile from the profiler. */
    virtual ~MemoryProfile();

    /** Returns the size of the tracked object in bytes. (sizeof(...)) */
    unsigned long GetSizeInBytes() const {
        return sizeInBytes;
    }

    /** Returns the demangled type name of the tracked object. */
    const std::string& GetTypeName() const {
        return typeName;
    }

    /** Returns the tracked object's location in memory. */
    void* GetMemoryRoot() const {
        return rootMemory;
    }

    /** Returns the assigned memory group. */
    MemoryGroup GetMemoryGroup() const {
        return memGroup;
    }

    /** Recursively adds a sibling to the linked list of siblings. */
    void SetSibling(MemoryProfile* sibling);

    /** Gets an iterator to the next sibling. */
    SiblingIterator GetSiblings();

    /** Returns a pointer to the immediate sibling. */
    MemoryProfile* GetImmediateSibling() const {
        return sibling;
    }

private:
    /** The immediate sibling */
    MemoryProfile* sibling;

    /** The tracked object's size in bytes */
    unsigned long sizeInBytes;
    /** Tracked object's demangled type name */
    std::string typeName;
    /** Tracked object's location in memory */
    void* rootMemory;
    /** Tracked object's memory group */
    MemoryGroup memGroup;
};

namespace memory {

class ProfilableBase {
private:
    std::shared_ptr<MemoryProfile> __profilable;
public:
    template<typename T>
    ProfilableBase(T* self, MemoryGroup memGroup)
            : __profilable(new MemoryProfile(typeid(T), sizeof(T), (void*) self, memGroup)) {
    }

    virtual ~ProfilableBase() {
        //if (__profilable) delete __profilable;
    }
};

}

} /* namespace glove */