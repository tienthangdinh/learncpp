#include "memory_arena.hpp"

IMUPacket::IMUPacket(int64_t t, float ax, float ay, float az, float gx, float gy, float gz)
    : timestamp(t) {
    accel[0] = ax;
    accel[1] = ay;
    accel[2] = az;
    gyro[0] = gx;
    gyro[1] = gy;
    gyro[2] = gz;

    std::cout << "IMUPacket created at address " << this << std::endl;
}

void IMUPacket::print() const {
    std::cout << "Timestamp: " << timestamp << ", Accel: [" 
              << accel[0] << ", " << accel[1] << ", " << accel[2] 
              << "], Gyro: [" 
              << gyro[0] << ", " << gyro[1] << ", " << gyro[2] 
              << "]" << std::endl;
}

MemoryArena::MemoryArena() : offset_(0) {
    std::cout << "MemoryArena created with buffer size: " << sizeof(buffer_) << " bytes" << " Base address: " << static_cast<void*>(buffer_) << std::endl;
}

void MemoryArena::reset() {
    offset_ = 0;
    std::cout << "MemoryArena reset. Offset set to 0." << std::endl;
}

void* MemoryArena::allocate(std::size_t size, std::size_t alignment) {
    std::size_t currentAddress = reinterpret_cast<std::size_t>(buffer_) + offset_;
    std::size_t alignedAddress = (currentAddress + alignment - 1) & ~(alignment - 1);
    std::size_t newOffset = alignedAddress - reinterpret_cast<std::size_t>(buffer_) + size;

    if (newOffset > sizeof(buffer_)) {
        throw std::bad_alloc();
    }

    void* ptr = reinterpret_cast<void*>(alignedAddress);
    offset_ = newOffset;

    std::cout << "Allocated " << size << " bytes at address " << ptr 
              << " with alignment " << alignment 
              << ". New offset: " << offset_ << std::endl;

    return ptr;
}

std::size_t MemoryArena::getUsedMemory() const {
    return offset_;
}

std::size_t MemoryArena::getTotalMemory() const {
    return sizeof(buffer_);
}


/*TAKE HOME MESSAGE
- alignas, alignof for aligning the pointer
- new (ptr) Type(args) for placement new
- reinterpret_cast for casting pointer types to anything
*/