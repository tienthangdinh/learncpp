#include "robot_battery.hpp"
#include <thread>
#include <hardware_monitor.hpp>
#include <memory_arena.hpp>
#include "virtual_mem_buffer.hpp"
#include <new>       // Placement new

//create a main function to test the RobotBattery class
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
    return 0;
}