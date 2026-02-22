#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstddef>

class MemoryPool {
private:
    size_t blockSize;
    size_t blockCount;
    void* memoryStart;
    void* freeList;

public:
    MemoryPool(size_t size, size_t count);
    ~MemoryPool();

    void* allocate();
    void deallocate(void* ptr);
};

#endif