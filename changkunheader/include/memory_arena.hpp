#pragma once

#include <iostream>
#include <cstdint>
#include <cstddef>
#include <new>

struct IMUPacket {
    int64_t timestamp;
    float accel[3];
    float gyro[3];

    IMUPacket(int64_t t, float ax, float ay, float az, float gx, float gy, float gz);
    ~IMUPacket() {
        std::cout << "IMUPacket destroyed at address " << this << std::endl;
    }

    void print() const;
};

// Fixed-size memory arena managing a raw contiguous byte buffer
class MemoryArena {
    private:
    alignas(alignof(std::max_align_t)) std::byte buffer_[1024]; // 1KB buffer
    std::size_t offset_;

    public:
    MemoryArena();
    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t));
    void reset();
    std::size_t getUsedMemory() const;
    std::size_t getTotalMemory() const;
};
