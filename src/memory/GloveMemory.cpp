#include "GloveMemory.h"

#include <sstream>

#define GLOVE_MEM_TAG_1 75
#define GLOVE_MEM_TAG_2 127
#define GLOVE_MEM_TAG_3 15
#define GLOVE_MEM_TAG_FREE 111

void* operator new(size_t size, const char* name){
	return glove::GloveMemAllocN(size, name);
}
void* operator new[](size_t size, const char* name) {
	return glove::GloveMemAllocN(size, name);
}

namespace glove {

void* GloveMemAlloc(size_t size) {
	return GloveMemAllocN(size, "C++/Generic");
}

void* GloveMemAllocN(size_t size, const char* name) {
	GloveMemoryBlock* memBlock = reinterpret_cast<GloveMemoryBlock*>(malloc(sizeof(GloveMemoryBlock) + size));
	memBlock->blockSize = size;
	memBlock->name = name;

	memBlock->memTag1 = GLOVE_MEM_TAG_1;
	memBlock->memTag2 = GLOVE_MEM_TAG_2;
	memBlock->memTag3 = GLOVE_MEM_TAG_3;

	memory_internal::InsertIntoMemoryList(memBlock);

	return ++memBlock;
}

void GloveMemFree(void* ptr) {
	if (ptr == NULL || ptr == nullptr) {
		// TODO: error
	}

	GloveMemoryBlock* memBlock = reinterpret_cast<GloveMemoryBlock*>(ptr) - 1;

	if (memBlock->memTag1 == GLOVE_MEM_TAG_FREE && memBlock->memTag2 == GLOVE_MEM_TAG_2 && memBlock->memTag3 == GLOVE_MEM_TAG_FREE) {
		// TODO: double-free
		return;
	}
	if (memBlock->memTag1 != GLOVE_MEM_TAG_1 || memBlock->memTag2 != GLOVE_MEM_TAG_2 || memBlock->memTag3 != GLOVE_MEM_TAG_3) {
		// TODO: invalid pointer (either complete rubbish or not allocated using glove memory subsystem)
		return;
	}
	
	// Remove block from linked list
	if (memBlock->prev != NULL) memBlock->prev->next = memBlock->next;
	else memory_internal::memoryHead = memBlock->next;
	if (memBlock->next != NULL) memBlock->next->prev = memBlock->prev;
	else memory_internal::memoryTail = memBlock->prev;

	memBlock->memTag1 = GLOVE_MEM_TAG_FREE;
	memBlock->memTag3 = GLOVE_MEM_TAG_FREE;

	free(memBlock);
}


namespace memory_internal {
// Memory block list
GloveMemoryBlock* memoryHead = NULL;
GloveMemoryBlock* memoryTail = NULL;

// Memory statistics
std::atomic_size_t memoryUsed = 0;
std::atomic_size_t memoryPeak = 0;

void InsertIntoMemoryList(GloveMemoryBlock* memBlock) {
	memBlock->next = NULL;

	// List is empty
	if (memoryHead == NULL && memoryTail == NULL) {
		memoryHead = memoryTail = memBlock;
		memBlock->prev = NULL;
		return;
	}

	memoryTail->next = memBlock;
	memBlock->prev = memoryTail;
	memoryTail = memBlock;

	memoryUsed.fetch_add(memBlock->blockSize);
	memoryPeak = memoryUsed.load() > memoryPeak.load() ? memoryUsed.load() : memoryPeak.load();
}

std::string DumpList() {
	std::stringstream outStream;
	outStream << "[GLOVE HEAP (P: " << memoryPeak << "B, U: " << memoryUsed << "B)]" << std::endl << std::endl;

	GloveMemoryBlock* currentBlock = memoryHead;
	while (currentBlock != NULL) {
		outStream << "[" << currentBlock->name << "@" << currentBlock << "] " << currentBlock->blockSize << std::endl;
		currentBlock = currentBlock->next;
	}

	return outStream.str();
}

} // namespace memory_internal
} // namespace glove