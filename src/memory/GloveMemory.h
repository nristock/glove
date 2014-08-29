#ifndef GLOVEMEMORY_H_
#define GLOVEMEMORY_H_

#include <atomic>
#include <string>

// Macro for class-specific allocators
#define GLOVE_MEM_ALLOC_FUNCS(id_)							\
public:														\
void* operator new(size_t size){							\
	return glove::GloveMemAllocN(size, id_);				\
}															\
void* operator new[](size_t size) {							\
	return glove::GloveMemAllocN(size, id_ "[]");			\
}															\
void operator delete(void* ptr) {							\
	glove::GloveMemFree(ptr);								\
}															\
void operator delete[](void* ptr) {							\
	glove::GloveMemFree(ptr);								\
}

// NEW/DELETE macros; primarily for array allocation
// We cannot globally overwrite new/delete operators because it wouldn't replace allocators in DLL on Windows systems. 
#define GLOVE_NEW_A(name, type) new(name) type
#define GLOVE_NEW(name, type, args) GLOVE_NEW_A(name, type)(args);
#define GLOVE_NEW_ARRAY(name, type, size) new(name) type[size];
#define GLOVE_DELETE(ptr) if(ptr != NULL) { glove::GloveMemFree(ptr); }

// Named block allocators
void* operator new(size_t size, const char* name);
void* operator new[](size_t size, const char* name);

namespace glove {
/*
* Double-linked list of all memory blocks.
*/
struct GloveMemoryBlock {
	GloveMemoryBlock* next;
	GloveMemoryBlock* prev;
	size_t blockSize;
	const char* name;

	// Memory tagging to track block state and prevent double double frees
	int memTag1;
	int memTag2;
	int memTag3;
};

// Allocates a generic heap block (creates a named block: "C++/Generic)
void* GloveMemAlloc(size_t size);
// Allocates a named heap block
void* GloveMemAllocN(size_t size, const char* name);

// Frees a heap block
void GloveMemFree(void* ptr);

// Memory management internals
namespace memory_internal {
// Internal memort block list
extern GloveMemoryBlock* memoryHead;
extern GloveMemoryBlock* memoryTail;

// Memort statistics
extern std::atomic_size_t memoryUsed;
extern std::atomic_size_t memoryPeak;

// Appends a new block to the end of the internal memory block list
void InsertIntoMemoryList(GloveMemoryBlock* memBlock);
std::string DumpList(); // TODO

} // namespcae memory_internal

} // namespace glove

#endif