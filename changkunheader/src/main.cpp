#include "robot_battery.hpp"
#include <thread>
#include <hardware_monitor.hpp>

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
    return 0;
}