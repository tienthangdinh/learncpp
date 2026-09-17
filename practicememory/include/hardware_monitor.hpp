#pragma once

#include <iostream>
#include <string>

class HardwareMonitor {
public:
    HardwareMonitor();
    void get_cpu_info();
    void get_memory_info();
};