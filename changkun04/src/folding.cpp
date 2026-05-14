#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <memory>

class PowerMonitorNode : public rclcpp::Node {
    private:
template<typename... ComponentsWattage>
auto calculateWattage(ComponentsWattage... componentswattage) {
    return (... + componentswattage); //unary left fold
}

template<typename... States>
bool allokay(States... states) {
    return (... && states); //unary left fold
}
public:
PowerMonitorNode() : Node("PowerMonitorNode") {
    double cpu_wattage = 15.5;
    double gpu_wattage = 25.0;
    double memory_wattage = 5.0;

    double total_wattage = calculateWattage(cpu_wattage, gpu_wattage, memory_wattage);
    RCLCPP_INFO(this->get_logger(), "Total Power Consumption: %.2f Watts", total_wattage);

    bool cpu_okay = true;
    bool gpu_okay = true;
    bool memory_okay = false;

    if (allokay(cpu_okay, gpu_okay, memory_okay)) {
        RCLCPP_INFO(this->get_logger(), "All components are operating within normal parameters.");
    } else {
        RCLCPP_WARN(this->get_logger(), "One or more components are not operating within normal parameters!");
    }
}

};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PowerMonitorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
/*take home message 14.Mai 2026:
- folding used when variadic was used before Args... args (Args is a bag, args are all elements inside that bag)
- 4 principles of unpacking (folding):
    1. unary left fold: (... + args) => (((arg1 + arg2) + arg3) + ...)
    2. unary right fold: (args + ...) => (arg1 + (arg2 + (arg3 + ...)))
    3. binary left fold: (init + ... + args) => (((init + arg1) + arg2) + ...)
    4. binary right fold: (args + ... + init) => (arg1 + (arg2 + (arg3 + ... + init)))
*/