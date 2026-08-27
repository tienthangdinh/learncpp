#pragma once

#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <memory>

class MemoryInspectorNode {
private:
    int lidar_device_fd_ = -1; // File Descriptor (lives in Kernel PCB table)

public:
    MemoryInspectorNode();
    ~MemoryInspectorNode();

    void inspect_all_segments(int recursion_depth);
};