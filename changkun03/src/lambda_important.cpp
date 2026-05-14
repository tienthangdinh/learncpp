#include <iostream>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <variant>
#include <type_traits>

//either a reading from a sensor or a status message, dont know yet
using SensorData = std::variant<double, std::string>;

class DiagnosticNode : public rclcpp::Node {
public:
    DiagnosticNode() : Node("DiagnosticNode") {
        double threshold = 50.0;
        int error_count = 0;
        std::string robot_id = "Robot_001";

        std::vector<SensorData> sensor_readings = {45.5, "OK", 60.2, "Warning", 30.0};

        auto process_report = [this, threshold, &error_count, robot_id](auto && data) {
            std::visit([this, threshold, &error_count, robot_id](auto && value) {
                using T = std::decay_t<decltype(value)>;
                if constexpr (std::is_same_v<T, double>) {
                    if (value > threshold) {
                        RCLCPP_WARN(this->get_logger(), "Sensor reading %.2f exceeds threshold!", value);
                        error_count++;
                    } else {
                        RCLCPP_INFO(this->get_logger(), "Sensor reading %.2f is within normal range.", value);
                    }
                } else if constexpr (std::is_same_v<T, std::string>) {
                    RCLCPP_INFO(this->get_logger(), "Status message: %s", value.c_str());
                    if (value == "Warning") {
                        error_count++;
                        RCLCPP_WARN(this->get_logger(), "Warning status received for robot: %s", robot_id.c_str());
                    }
                }
            }, data);
        };

        for (const auto &reading : sensor_readings) {
            process_report(reading);
        }

        auto log_all_by_value = [=]() {};
        auto log_all_by_reference = [&]() {};
        auto log_all_mixed = [=, &error_count]() {};
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DiagnosticNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

/*take home message 14.Mai 2026:
- [] nothing, [=] copies everything, [&] reference everything (means we are also changing it), the rest is personalized like [this], [a, &b], [=, &b],...
- int& means reference to lvalue
- int&& means reference to both rvalue and lvalue, but usually used for rvalue reference
- intersting right?
- => [auto && x] means maximum of flexibility
- "using" means creating an alias for shortcut
- std::visit takes data value, put it in val, then do the lambda function
*/