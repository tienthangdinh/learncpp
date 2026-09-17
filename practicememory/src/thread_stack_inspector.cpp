#include "thread_stack_inspector.hpp"
#include <iostream>
#include <sys/resource.h>

void print_system_stack_limits() {
    struct rlimit stack_limit;
    if (getrlimit(RLIMIT_STACK, &stack_limit) == 0) { //what is RLIMIT_STACK? It is a constant that represents the stack size limit for a process. The getrlimit function retrieves the current limits for the specified resource (in this case, the stack size) and stores them in the provided rlimit structure.
        std::cout << "System Stack Limit (rlimit): " << stack_limit.rlim_cur / (1024 * 1024) << " MB" << std::endl;
    } else {
        std::cerr << "Failed to get system stack limit" << std::endl;
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr); //is this creating a new thread? No, pthread_attr_init initializes a thread attributes object (attr) that can be used to specify attributes for threads that will be created later. It does not create a new thread itself.
    size_t stack_size;
    pthread_attr_getstacksize(&attr, &stack_size);
    std::cout << "Default pthread stack size: " << stack_size / (1024 * 1024) << " MB" << std::endl;
    pthread_attr_destroy(&attr);

}

void inspect_current_thread_stack(int thread_id) {
    pthread_t thread = pthread_self(); //what is pthread_t? pthread_t is a data type used to represent a thread in the POSIX threads (pthreads) library. It is typically an opaque type that uniquely identifies a thread within a process.
    //so what is it doing here? pthread_self() returns the thread ID of the calling thread. In this context, it is used to obtain the identifier of the current thread so that its stack boundaries and other attributes can be inspected.
    //you mean the thread calling this function or the thread_id passed to this function? It refers to the thread that is calling the inspect_current_thread_stack function, not the thread_id passed as an argument. The thread_id parameter is not used in this function; instead, pthread_self() retrieves the ID of the currently executing thread.
    size_t actual_stack_size = pthread_get_stacksize_np(thread); //what is pthread_get_stacksize_np? pthread_get_stacksize_np is a non-portable (NP) function specific to certain implementations of the POSIX threads library. It retrieves the size of the stack allocated for the specified thread (in this case, the current thread) and returns it as a size_t value.
    //what is difference between stacksize and stack limit? The stack size refers to the actual size of the stack allocated for a specific thread, while the stack limit (rlimit) is a system-level constraint that defines the maximum allowable stack size for a process. The stack size can be smaller than or equal to the stack limit, but it cannot exceed it.
    //like stacksize is slowly increasing in runtime? No, the stack size for a thread is typically fixed at the time of thread creation and does not change during runtime. However, the stack limit (rlimit) can be adjusted by the operating system or by the process itself, but it does not affect the already allocated stack size of existing threads.
    //if it does not change in runtime, then it is not different from stack limit, right? The stack size and stack limit are related but serve different purposes. The stack size is the actual allocated memory for a thread's stack, while the stack limit is a system-imposed maximum that restricts how large a thread's stack can be. The stack size is determined at thread creation and remains constant, while the stack limit can be queried or modified by the process or operating system. So, while they may not change during runtime for existing threads, they are conceptually different: one is an allocation (stack size), and the other is a constraint (stack limit).
    //so stack limit is hard limit by the OS, and stack size is the actual allocated size for a thread's stack? Yes, that's correct. The stack limit is a hard limit set by the operating system that defines the maximum allowable stack size for a process or thread. The stack size is the actual amount of memory allocated for a thread's stack when it is created, and it must be less than or equal to the stack limit.
    void* stack_base = pthread_get_stackaddr_np(thread); //highest address of the stack
    void* stack_top = static_cast<char*>(stack_base) - actual_stack_size; //the lowest address of the stack currently right? Yes, that's correct. The stack_base obtained from pthread_get_stackaddr_np represents the highest address of the stack (the base of the stack), and by subtracting the actual_stack_size from it, you get the lowest address of the stack (the top of the stack). This calculation gives you the range of addresses that make up the thread's stack.
    //wait, stack_top does not change in runtime, right? Correct. The stack_top (the lowest address of the stack) does not change during the lifetime of the thread. It is determined at the time of thread creation based on the allocated stack size and remains constant for that thread. The stack grows downward from stack_base to stack_top, but the addresses themselves do not change once allocated.
    std::cout << "Thread ID: " << thread_id << std::endl;
    std::cout << "Stack Base (Highest Address): " << stack_base << std::hex << stack_base << std::dec << std::endl;
    std::cout << "Stack Top (Lowest Address): " << stack_top << std::hex << stack_top << std::dec << std::endl;
    std::cout << "Actual Stack Size: " << actual_stack_size / (1024 * 1024) << " MB" << std::endl;
}

void idle_worker(int id, bool print_details) {
    if (print_details) {
        inspect_current_thread_stack(id);
    }
    // Simulate some work
    for (int i = 0; i < 1000000; ++i);
}

void run_thread_spawn_benchmark(std::size_t num_threads) {
    std::vector<pthread_t> threads(num_threads);
    for (std::size_t i = 0; i < num_threads; ++i) {
        try
        {
            pthread_create(&threads[i], nullptr, reinterpret_cast<void* (*)(void*)>(&idle_worker), reinterpret_cast<void*>(i));

        }
        catch(const std::exception& e)
        {
            std::cerr << "Failed to create thread " << i << ": " << e.what() << std::endl;
        }
        
        //pthread_create(&threads[i], nullptr, reinterpret_cast<void* (*)(void*)>(&idle_worker), reinterpret_cast<void*>(i));
    }
    std::cout << "Successfully spawned " << threads.size() << " threads." << std::endl;
    for (std::size_t i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], nullptr);
    }
}

/*
BE CAREFUL STACK OVERFLOW: each thread has its own stack with fixed size
1) if a threads has functions keep calling nested instead of sequentially
2) if a thread instantiate a very large local variable
=> SOLUTION:
   VIRTUAL ADDRESS SPACE OF THE PROCESS
┌────────────────────────────────────────────────────────┐
│  [Shared Global Heap] <--- Can grow to gigabytes       │
│   ▲               ▲                                    │
│   │ (allocates)   │ (allocates)                        │
│ ┌─┴──────────┐  ┌─┴──────────┐                         │
│ │ Thread 1   │  │ Thread 2   │                         │
│ │ Fixed Stack│  │ Fixed Stack│                         │
│ └────────────┘  └────────────┘                         │
└────────────────────────────────────────────────────────┘
When your heavy thread uses C++ containers like std::vector, std::string, or manually calls new / std::make_shared:
- The tiny management pointer lives on the thread's fixed stack.
- The actual raw, heavy payload data is allocated dynamically in the shared heap.
- The heap is flexible and can grow dynamically to fill your system's entire available RAM and virtual memory using mechanisms like mmap() or brk.
*/