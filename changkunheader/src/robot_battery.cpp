#include "robot_battery.hpp"
#include <thread>

RobotBattery::RobotBattery(const std::string& type, int initialCharge)
    : batteryType(type), chargeLevel(initialCharge) {}

void RobotBattery::charge(int amount) {
    for (int i = 0; i < amount; ++i) {
        if (chargeLevel < 100) {
            ++chargeLevel;
            //sleep for 0.5 seconds to simulate charging time
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else {
            std::cout << "Battery is fully charged!" << std::endl;
            break;
        }
    }
}

void RobotBattery::discharge(int amount) {
    for (int i = 0; i < amount; ++i) {
        if (chargeLevel > 0) {
            --chargeLevel;
            //sleep for 0.5 seconds to simulate discharging time
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } else {
            std::cout << "Battery is empty!" << std::endl;
            break;
        }
    }
}

int RobotBattery::getChargeLevel() const {
    return chargeLevel;
}