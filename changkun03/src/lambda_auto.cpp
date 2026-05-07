#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>

class RobotNode : public rclcpp::Node {
public:
  RobotNode() : Node("Lambda_Auto") {

    auto is_safe = [](auto value, auto min, auto max) {
      bool safe = min <= value && value <= max;
      if (safe) {
        std::cout << "normal" << std::endl;
      }
      return safe;
    };

    is_safe(this->encoder_ticks, 0, 5001);
    is_safe(this->battery_volt, 0.3, 12.4);
    is_safe(this->lidar_range, 0.002, 30.01);
  };

private:
  int encoder_ticks = 5000;
  double battery_volt = 7.43;
  float lidar_range = 4.22;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RobotNode>();
  // no need for spin
  rclcpp::shutdown();
  return 0;
}

/*take home message 04. Mai 2026:
- generic lambda like a very normal function haizz
- generic lambda like a template
- ROS spin means stay there and wait for the node's queue: if a message or sth
arrive, run the code,
- without ROS spin, it immediately being shut down (just exist for microseconds)
- Even if your main function gets busy or finishes its current block, the
shared_ptr ensures the node stays in memory as long as rclcpp::spin (or any
other part of the system) still needs it.
- What if just normal RosNode node?
- the Node will be on Stack, Lifetime only exists as long as the code is inside
the {} of main. But maybe it will pass the node to another program to do
something and main function ends first
*/