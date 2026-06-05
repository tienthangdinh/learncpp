#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <chrono>

class ThreadNode : public rclcpp::Node {
    private:
    std::mutex counter_mutex_; //don't see any explicit relationship of this mutex to the shared_heap_counter_ yet, yeah because not yet
    long long shared_heap_counter_ = 0; //shared asset on the heap

    void heavy_math_worker(int thread_id, int operations) {
        long long local_stack_counter_ = 0; //private on each thread's stack

        for (int i = 0; i < operations; ++i) {
            local_stack_counter_ += (i % 3) * 2; //just simulating some random calculation
        }

        { //CRITICAL AREA: we write back the the shared heap counter
            std::lock_guard<std::mutex> lock(counter_mutex_); //this lockk hold this mutex (turn) for the whole scope {...}, so dont forget to close bracket :))
            shared_heap_counter_ += local_stack_counter_;
            std::cout << "Thread " << thread_id << " finished" << std::endl;
        }// mutex auto unlock after leaving this scope
    }

    public:
    ThreadNode() : Node("ThreadNode") {
        unsigned int max_threads = std::thread::hardware_concurrency();
        std::cout << "Detected " << max_threads << " threads maximum on this computer" << std::endl;

        std::vector<std::thread> thread_pool;
        int operations_per_threads = 5000000;

        auto start_time = std::chrono::high_resolution_clock::now();

        for (unsigned int i = 0; i < max_threads; ++i) {
            std::cout << "Launching thread " << i << "on private stack segment" << std::endl;
            thread_pool.push_back(std::thread(&ThreadNode::heavy_math_worker, this, i, operations_per_threads)); //is this really launching? it is just simply adding a thread object to the vector? -> doch, it also construct the std::thread directly and start executing right away
        } //btw we are passing Class:function, and C++ has a rule that passing a Class::function can only use pointer, like look at the blueprint of this class and find that function
        std::cout << "all threads running --------------------" << std::endl;

        for (std::thread &t : thread_pool) {
            if (t.joinable()) {
                t.join();
            }
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;

        std::cout << "Total time: " << elapsed.count() << " seconds" << std::endl;
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    std::shared_ptr<ThreadNode> threadnode = std::make_shared<ThreadNode>();
    rclcpp::shutdown();
    return 0;
}

/* take home message 30.Mai 2026
- each thread gets separately 8MB stacks but still share the same heap
- if 2 threads try to access same heap address => race condition
- but normally, does C++ program automatically divides into threads? or everything sequentially on the same thread?
    -> no, C++ always 1 single thread & will never try to parallelize, unles using std::thread, std::async
- how to know how many thread a processor can run? is it the same as the number of CPU core?
    -> we dont know, can only get from std::thread::hardware_concurrency(), because some CPU are SMT
- so if 1 thread, the whole virtual memory for a program is only 8MB, but if now we use n threads, then we get extra n*8MB for each thread stack?
    -> yes!
*/