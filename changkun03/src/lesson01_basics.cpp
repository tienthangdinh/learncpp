#include "geometry_msgs/msg/point.hpp" // For x, y, z coordinates
#include "rclcpp/rclcpp.hpp"

// Using enum class for high-level robot behavior
enum class RobotMode : uint8_t { STATIONARY = 0, PATROLLING = 1, ESTOP = 2 };

class HelloRobotNode : public rclcpp::Node {
public:
  // Constructor Delegation: Default name is "my_robot"
  HelloRobotNode() : HelloRobotNode("my_robot") {}

  HelloRobotNode(std::string node_name) : Node(node_name) {
    current_mode_ = RobotMode::STATIONARY;

    // Initialize a position using geometry_msgs
    pos_.x = 0.0;
    pos_.y = 0.0;
    pos_.z = 0.0;

    RCLCPP_INFO(this->get_logger(), "Robot Node Started.");
    print_status();
  }

  void print_status() {
    RCLCPP_INFO(this->get_logger(), "Mode: %d | Position: (%.2f, %.2f)",
                static_cast<uint8_t>(current_mode_), pos_.x, pos_.y);
  }

private:
  RobotMode current_mode_;
  geometry_msgs::msg::Point pos_; // The dependency we added
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<HelloRobotNode>("changkun_robot");

  rclcpp::spin_some(node); // Process node logic once
  rclcpp::shutdown();
  return 0;
}