#include "hardware_monitor.hpp"
#include <thread>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/mach_host.h>

HardwareMonitor::HardwareMonitor() {}

void HardwareMonitor::get_cpu_info() {
    std::cout << "================== CPU Information ==================" << std::endl;
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Available Hardware Threads: " << cores << std::endl;

    char cpuBrand[128]; //each char is 1 byte
    size_t size = sizeof(cpuBrand); //total size is 128 bytes
    sysctlbyname("machdep.cpu.brand_string", &cpuBrand, &size, nullptr, 0); //why do we pass these two values in here? -> kinda write back
    std::cout << "CPU Brand: " << cpuBrand << std::endl;
}

void HardwareMonitor::get_memory_info() {
    std::cout << "================== Memory Information ==================" << std::endl;
    int64_t total_physical_memory;
    size_t size = sizeof(total_physical_memory);
    sysctlbyname("hw.memsize", &total_physical_memory, &size, nullptr, 0);
    std::cout << "Total Physical Memory: " << total_physical_memory / (1024 * 1024) << " MB" << std::endl;

    mach_msg_type_number_t count = HOST_VM_INFO_COUNT; //where did this HOST_VM_INFO_COUNT come from? and what the heck does the type mean? who defined the type name?
    vm_statistics_data_t vm_stat;
    host_t host = mach_host_self(); //what the heck is this?
    if (host_statistics(host, HOST_VM_INFO, reinterpret_cast<host_info_t>(&vm_stat), &count) == KERN_SUCCESS) {
        vm_size_t page_size; //what does page size mean? -> virtual memory page size, which is the smallest unit of memory that can be managed by the operating system
        host_page_size(host, &page_size);
        int64_t free_memory = static_cast<int64_t>(vm_stat.free_count) * page_size; //why multiply with page_size? -> because the free_count is the number of free pages, and we need to multiply it by the page size to get the total free memory in bytes
        std::cout << "Free Memory: " << free_memory / (1024 * 1024) << " MB" << std::endl;
    } else {    
        std::cerr << "Failed to get free memory information." << std::endl;
    }
}