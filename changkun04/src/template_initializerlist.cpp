#include <iostream>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <initializer_list>

class PIDGains {
    public:
    double p,i,d;
    PIDGains(double kp, double ki, double kg) : p(kp), i(ki), d(kg) {}

    PIDGains(std::initializer_list<double>experimental_values) {
        auto it = experimental_values.begin(); // Get an iterator to the first element
        if (it != experimental_values.end()) {
            p = *it; 
            ++it;
        } else {
            p = 0.0;
        }

        if (it != experimental_values.end()) {
            i = *it; 
            ++it;
        } else {
            i = 0.0;
        }

        if (it != experimental_values.end()) {
            d = *it; 
        } else {
            d = 0.0;
        }
    }
};

class PIDNode : public rclcpp::Node {
public:
PIDNode() : Node("PIDNode") {
    PIDGains gains1(1.0, 0.5, 0.1);
    PIDGains gains2{1.5, 0.7, 2};
    RCLCPP_INFO(this->get_logger(), "Gains1 - P: %.2f, I: %.2f, D: %.2f", gains1.p, gains1.i, gains1.d);
    RCLCPP_INFO(this->get_logger(), "Gains2 - P: %.2f, I: %.2f, D: %.2f", gains2.p, gains2.i, gains2.d);
}
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PIDNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
