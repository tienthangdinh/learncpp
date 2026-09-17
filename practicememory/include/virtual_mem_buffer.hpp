#pragma once

#include <iostream> //for std::cout, std::endl
#include <cstddef> //for std::byte
#include <cstdint> //for fixed-width integer types (int32_t, int64_t, etc.)
#include <sys/mman.h> //POSIX memory management functions (mmap, munmap, mprotect)
#include <unistd.h> //POSIX standard symbolic constants and types (sysconf)

struct SensorFrame {
    uint32_t frame_id; 
    uint64_t timestamp;
    float sensor_data[1024]; //1024 coordinates of sensor data
};

class VirtualMemoryBuffer {
    private:
        void* mapped_region_; // Pointer to the mapped memory region
        std::size_t total_size_ = 0; // Total size of the mapped region
        std::size_t page_size_ = 0; // System page size

    public:
        VirtualMemoryBuffer(std::size_t num_pages);
        ~VirtualMemoryBuffer();
        
        VirtualMemoryBuffer(const VirtualMemoryBuffer&) = delete; // Disable copy constructor
        VirtualMemoryBuffer& operator=(const VirtualMemoryBuffer&) = delete; // Disable copy assignment

        void* get_raw_address() const { //direct pointer to the mapped region
            return mapped_region_;
        }
        std::size_t get_total_size() const {
            return total_size_;
        }
        std::size_t get_page_size() const {
            return page_size_;
        }

        bool set_read_only(); // Set the memory region to read-only
        bool set_read_write(); // Set the memory region to read-write
};