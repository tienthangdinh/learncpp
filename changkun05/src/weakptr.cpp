#include <memory>
#include <iostream>
#include <rclcpp/rclcpp.hpp>

class SafetyMonitor; //forward declaration

class RobotStateTelemetry {
    public:
    std::shared_ptr<SafetyMonitor> safety_monitor_;
};

class SafetyMonitor {
    public:
    std::weak_ptr<RobotStateTelemetry> telemetry_observer_;
};

class WeakPtrNode : rclcpp::Node {
    public:
    WeakPtrNode() : Node("WeakPtrNode") {
        auto telemetry = std::make_shared<RobotStateTelemetry>();
        auto monitor = std::make_shared<SafetyMonitor>();

        telemetry->safety_monitor_ = monitor;
        monitor->telemetry_observer_ = telemetry;
    }
};

int main(int argc, char** kwargs) {
    rclcpp::init(argc, kwargs);
    auto node = std::make_shared<WeakPtrNode>();
    rclcpp::shutdown();
    return 0;
}

/*take home message 29.Mai 2026
- in some special cases, 2 objects holding a std::shared_ptr pointing to each other, these pointers will keep them alive forever. BTW is it because these pointers are located in heap? and when a program finishs, it only clean the stack?
- weak_ptr only observe, not increase reference_count
*/