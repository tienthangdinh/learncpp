#include "robot_battery.hpp"
#include <thread>
#include <hardware_monitor.hpp>
#include <memory_arena.hpp>
#include "virtual_mem_buffer.hpp"
#include <new>       // Placement new
#include <virtual_mem_inspector.hpp>
#include "thread_stack_inspector.hpp"


int main() {
    HardwareMonitor monitor;
    monitor.get_cpu_info();
    monitor.get_memory_info();

    RobotBattery battery("Li-ion", 50);
    std::cout << "Initial charge level: " << battery.getChargeLevel() << "%" << std::endl;
    battery.charge(30);
    std::cout << "Charge level after charging: " << battery.getChargeLevel() << "%" << std::endl;
    battery.discharge(60);
    std::cout << "Charge level after discharging: " << battery.getChargeLevel() << "%" << std::endl;

    std::cout << "Testing MemoryArena..." << std::endl;
    MemoryArena arena;
    void* slot1 = arena.allocate(sizeof(IMUPacket), alignof(IMUPacket));
    IMUPacket* imuPacket1 = new (slot1) IMUPacket(123456789, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f);
    imuPacket1->print();
    imuPacket1->~IMUPacket(); // Manually call destructor since we used placement new
    std::cout << "Used memory: " << arena.getUsedMemory() << " bytes" << std::endl;
    std::cout << "Total memory: " << arena.getTotalMemory() << " bytes" << std::endl;
    arena.reset();
    std::cout << "New allocation after reset..." << std::endl;
    void* slot2 = arena.allocate(sizeof(IMUPacket), alignof(IMUPacket));
    IMUPacket* imuPacket2 = new (slot2) IMUPacket(987654321, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f);
    imuPacket2->print();
    imuPacket2->~IMUPacket(); // Manually call destructor since we used placement new
    std::cout << "Used memory: " << arena.getUsedMemory() << " bytes" << std::endl;
    std::cout << "Total memory: " << arena.getTotalMemory() << " bytes" << std::endl;



    std::cout << "Testing VirtualMemoryBuffer..." << std::endl;
    //request 2 pages of virtual memory
    VirtualMemoryBuffer vmb(2);

    SensorFrame* frame = static_cast<SensorFrame*>(vmb.get_raw_address()); //directly access the mapped region and treat it as a SensorFrame

    frame->frame_id = 1;
    frame->timestamp = 1234567890;
    for (int i = 0; i < 1024; ++i) {
        frame->sensor_data[i] = static_cast<float>(i) * 0.1f; //fill with some dummy data
    }

    std::cout << "Wrote SensorFrame to virtual memory buffer at address: " << static_cast<void*>(frame) << std::endl;
    std::cout << "SensorFrame ID: " << frame->frame_id << ", Timestamp: " << frame->timestamp << std::endl;
    std::cout << "First 5 sensor data points: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << frame->sensor_data[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing MemoryInspectorNode..." << std::endl;
    MemoryInspectorNode inspector;
    inspector.inspect_all_segments(10); //inspect stack, heap, and data segments with a recursion depth of 10

    std::cout << "Testing Thread Stack Inspector..." << std::endl;
    print_system_stack_limits();
    inspect_current_thread_stack(0);
    run_thread_spawn_benchmark(100000000); // Adjust the number of threads as needed

    return 0;
}

/*
HIGH ADDRESS
       +-------------------------------------------------------+
       | [Stack Base] (e.g., 0x16b000000)                      |
       |                                                       |
       |  main() starts -> pushes Frame (takes ~64 bytes)      |
       |  +-------------------------------------------------+  |
       |  | Frame: main()                                   |  |
       |  +-------------------------------------------------+  |
       |                                                       |
       |  main() calls read_sensor() -> pushes Frame (~96 bytes|
       |  +-------------------------------------------------+  |
       |  | Frame: read_sensor()                            |  |
       |  +-------------------------------------------------+  |
       |                                                       |
       |  read_sensor() calls filter() -> pushes Frame (~48 B) |
       |  +-------------------------------------------------+  |
       |  | Frame: filter()                                 |  | <-- Stack Pointer (SP)
       |  +-------------------------------------------------+  |
       |                                                       |
       |  ▼ ▼ ▼  (UNTOUCHED FREE SPACE: ~7.99 MB REMAINING)    |
       |                                                       |
       |                                                       |
       |                                                       |
       +-------------------------------------------------------+
       | [GUARD PAGE] (Inaccessible boundary at ~8 MB mark)    |
       +-------------------------------------------------------+
       LOW ADDRESS

       void calculate() {
    // This DOES NOT create an 8 MB stack!
    // It takes ~48 BYTES from the existing stack.
}

int main() {
    // 1. Thread 'main' already has its stack (~8 MB).

    calculate(); // Uses ~48 bytes inside main's stack.

    // 2. THIS creates a brand new stack!
    // The OS allocates a fresh 512 KB / 8 MB region for worker_thread.
    std::thread worker_thread(calculate); 
    worker_thread.join();
}
process = the whole virtual memory space of the program
thread = stack = 8MB
function call = stack frame = 48 bytes



Game Virtual Address Space (~128 TB available)
+-------------------------------------------------------------+
| STACK (~512 KB to 8 MB)                                     | <-- Stays tiny! (Controls & game loops)
+-------------------------------------------------------------+
| HEAP & GPU BUFFERS (10 GB - 24 GB)                          |
|  - Textures (4K albedo, normal maps, roughness)             | <-- The biggest consumer (~60%)
|  - 3D Meshes & Geometry (vertex/index buffers)              |
|  - Audio Banks (decompressed sound clips, dialogue)         |
|  - World State & Entities (physics trees, enemy AIs)        |
+-------------------------------------------------------------+
| PAGE CACHE (mmap'd game archives, .pak / .bundle files)     | <-- Streaming assets from NVMe SSD
+-------------------------------------------------------------+
| TEXT & SHADERS (Compiled metal/vulkan shaders, game engine) |
+-------------------------------------------------------------+

*/