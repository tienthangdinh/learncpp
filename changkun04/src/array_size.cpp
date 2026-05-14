#include <array>
#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <vector>

class RobotHardwareNode : public rclcpp::Node {
public:
  RobotHardwareNode() : Node("RobotHardwareNode") {

    std::array<float, 4> wheel_speeds = {1.1f, 1.12f, 1.02f,
                                         1.05f}; // fixed on stack
    RCLCPP_INFO(this->get_logger(), "Wheel speed list size %zu",
                wheel_speeds.size());
    std::vector<float> lidar_scans; // dynamic on heap
    lidar_scans.reserve(200); // PRO-TIP: pre-book memory to AVOID RELLOCATION
    for (int i = 0; i < 200; i++) { //it has to be 200, not lidar_scans.size() because it is 0 at the beginning, and it will be increased by push_back
      lidar_scans.push_back(4.54f);
    }

    RCLCPP_INFO(this->get_logger(), "Scan size %zu, Capacity %zu",
                lidar_scans.size(), lidar_scans.capacity());
    lidar_scans.clear();
    RCLCPP_INFO(this->get_logger(), "After clear: Scan size %zu, Capacity %zu",
                lidar_scans.size(), lidar_scans.capacity());
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RobotHardwareNode>();
  rclcpp::shutdown();
  return 0;
}
/*take home message 11. Mai 2026
-std::array<int, 5> in Stack while std::vector<int> (Manger in Stack) (Data in
Heap),
-so std::vector<int> can sometimes expensive because it may relocate and
copy the whole memory segment
-at clearance it also does nto free memory
immediately
- size() return size_t (64bit unsigned) => use %zu, size_t is returned type of
size(), capacity(), sizeof(), max_size(),...
- integer is (32bit signed) => use %d
- but can still cast: int my_size = static_cast<int>(my_vector.size());
*/