# Scalable-Thread-Local-Memory-Allocator

Scalable Thread-Local Memory Allocator (C++)
📌 Overview

This project implements a high-performance fixed-size memory allocator in C++ using a free-list architecture. The allocator is optimized for multi-core scalability by eliminating global lock contention through thread-local sharded memory pools.

The project includes multithreaded benchmarking and performance comparison against the standard new/delete allocator.

⚙️ Design Architecture
1️⃣ Fixed-Size Memory Pool

Pre-allocates a large contiguous memory block.

Divides memory into equal-sized blocks.

Maintains a free-list for O(1) allocation and deallocation.

2️⃣ Thread-Local Sharding

Each thread maintains its own memory pool.

Eliminates global mutex contention.

Enables near-linear scalability under high concurrency.

3️⃣ Benchmarking Framework

Uses std::thread for multithreading.

Uses std::chrono for precise timing.

Compares performance across 1–32 threads.

📊 Benchmark Results
Workload

100,000 allocations per thread

Threads tested: 1, 2, 4, 8, 16, 32

Threads	new/delete (sec)	Thread-Local Pool (sec)
1	0.0679	0.00355
2	0.0891	0.00697
4	0.2236	0.01194
8	0.6837	0.01990
16	1.3845	0.04721
32	2.8268	0.09666
Observations

Up to 20× faster allocation compared to new/delete.

Significant scalability improvement under high concurrency.

Eliminated global lock bottleneck by using thread-local pools.

🧠 Concepts Demonstrated

Custom memory management

Free-list data structures

Heap vs pool allocation trade-offs

Lock contention analysis

Thread-local sharding strategy

Multithreaded benchmarking

Performance engineering in C++

🏗️ Project Structure
memoryPoolAllocator/
│
├── src/
│   ├── main.cpp
│   ├── memory_pool.h
│   └── memory_pool.cpp
│
└── README.md
🛠️ Build & Run

Using MinGW (Windows):

g++ src/main.cpp src/memory_pool.cpp -std=c++17 -pthread -O2 -o main.exe
.\main.exe
🔍 Key Trade-offs
Design Choice	Benefit	Limitation
Fixed-size blocks	O(1) allocation	Only supports uniform size
Thread-local pools	Eliminates contention	Requires ownership assumptions
No metadata per block	Low memory overhead	Limited cross-thread free support
🎯 Future Improvements

Hybrid allocator with global fallback pool

Lock-free free-list using CAS

Size-class based slab allocator

Cross-thread deallocation handling

Performance visualization charts

📌 Motivation

This project was built to explore:

How general-purpose allocators behave under contention

How sharding improves scalability

The impact of synchronization on performance

It demonstrates practical understanding of concurrency, memory management, and performance optimization in C++.
