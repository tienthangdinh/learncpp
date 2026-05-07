#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>

class LambdaRobotNode : public rclcpp::Node {
public:
  LambdaRobotNode() : Node("lambda_node") {

    int battery = this->battery;
    int alive_time = this->alive_time;

    auto val_time_callback = [battery, alive_time]() {
      std::cout << "[Value] Battery: " << battery
                << ", Alive Time: " << alive_time << std::endl;
    };
    auto ref_time_callback = [&battery, &alive_time]() {
      std::cout << "[Ref] Battery: " << battery
                << ", Alive Time: " << alive_time << std::endl;
    };
    battery = 75;
    val_time_callback();
    ref_time_callback();
    std::cout << "-------------------------------" << std::endl;

    timer = this->create_wall_timer(std::chrono::seconds(1), [this]() {
      this->battery -= 1;
      this->alive_time += 1;
      RCLCPP_INFO(this->get_logger(),
                  "Robot %s has battery %d and alive time %d", this->get_name(),
                  this->battery, this->alive_time);
    });
  }

private:
  rclcpp::TimerBase::SharedPtr timer;
  int battery = 100;
  int alive_time = 0;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<LambdaRobotNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

/*take home message 03. Mai 2026:
- lambda with val (treat as constant) and ref
- constructed a ROS node that : public rclcpp::Node
- scope of variable, please declare in private or public, not in just a function
- "this" is ALWAYS a POINTER!!!
*/
