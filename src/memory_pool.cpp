#include "memory_pool.h"
#include <cstdlib>
#include <new>

MemoryPool::MemoryPool(size_t size, size_t count)
    : blockSize(size < sizeof(void*) ? sizeof(void*) : size),
      blockCount(count),
      memoryStart(nullptr),
      freeList(nullptr)
{
    memoryStart = std::malloc(blockSize * blockCount);
    if (!memoryStart)
        throw std::bad_alloc();

    char* current = static_cast<char*>(memoryStart);

    for (size_t i = 0; i < blockCount - 1; ++i) {
        *(void**)current = current + blockSize;
        current += blockSize;
    }

    *(void**)current = nullptr;
    freeList = memoryStart;
}

MemoryPool::~MemoryPool() {
    std::free(memoryStart);
}

void* MemoryPool::allocate() {
    if (!freeList)
        return nullptr;

    void* block = freeList;
    freeList = *(void**)freeList;
    return block;
}

void MemoryPool::deallocate(void* ptr) {
    *(void**)ptr = freeList;
    freeList = ptr;
}