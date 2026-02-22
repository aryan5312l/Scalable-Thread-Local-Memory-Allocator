#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

#include "memory_pool.h"

void benchmark_new_delete(size_t threadCount, size_t iterations)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    for (size_t i = 0; i < threadCount; ++i)
    {
        threads.emplace_back([iterations]() {
            for (size_t j = 0; j < iterations; ++j) {
                int* ptr = new int;
                *ptr = 42;
                delete ptr;
            }
        });
    }

    for (auto& th : threads)
        th.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "New/Delete Time: "
              << std::chrono::duration<double>(end - start).count()
              << " seconds\n";
}

int main()
{
    const size_t threadCount = 32;
    const size_t iterations = 100000;

    std::cout << "=== Benchmarking new/delete ===\n";
    benchmark_new_delete(threadCount, iterations);

    std::cout << "\n=== Benchmarking Thread-Local MemoryPool ===\n";

    // Create one pool per thread
    std::vector<std::unique_ptr<MemoryPool>> pools;
    for (size_t i = 0; i < threadCount; ++i) {
        pools.push_back(std::make_unique<MemoryPool>(sizeof(int), iterations));
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    for (size_t t = 0; t < threadCount; ++t)
    {
        threads.emplace_back([&, t]() {

            MemoryPool* pool = pools[t].get();

            for (size_t i = 0; i < iterations; ++i) {
                int* ptr = static_cast<int*>(pool->allocate());
                if (ptr) {
                    *ptr = 42;
                    pool->deallocate(ptr);
                }
            }
        });
    }

    for (auto& th : threads)
        th.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "MemoryPool Time: "
              << std::chrono::duration<double>(end - start).count()
              << " seconds\n";

    return 0;
}