#pragma once
#include <cstddef>

// Query and print OS-level process stack limit (rlimit) and default pthread stack size
void print_system_stack_limits();

// Inspect stack boundaries and current frame position for a specific thread
void inspect_current_thread_stack(int thread_id);

// Worker payload function executed by each spawned thread
void idle_worker(int id, bool print_details);

// Demonstrates spawning large batches of threads and catching OS-level thread exhaustion
void run_thread_spawn_benchmark(std::size_t num_threads);