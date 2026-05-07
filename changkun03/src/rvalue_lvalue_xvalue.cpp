#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <utility>
#include <vector>

std::vector<int> heavyreturnedvector(int length) {
  std::vector<int> big_map(length, 1);
  std::cout << "Big map created at address" << (void *)big_map.data()
            << std::endl;
  return big_map;
}

class MemoryRobotNode : public rclcpp::Node {
public:
  MemoryRobotNode() : Node("MemoryRobotNode") {
    std::vector<int> returned_big_map = heavyreturnedvector(1000000);
    this->stored_map_ = std::move(returned_big_map);

    // The address will be THE SAME as the original big_map! No pixels were
    // copied.
    RCLCPP_INFO(this->get_logger(),
                "Stored map is now at address %p", // for pointer
                (void *)stored_map_.data());
    RCLCPP_INFO(this->get_logger(),
                "Original big_map size is now: %zu", // for size
                returned_big_map.size());
  }

private:
  std::vector<int> stored_map_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MemoryRobotNode>();
  rclcpp::shutdown();
  return 0;
}

/*take home message 05. Mai 2026:
- .data() is a property of std::vector it returns the pointer to the beginning
of the vector
- (void*) is casting the pointer to int to the generic pointer (because we dont
care, printing just need to know its a pointer)
- lvalue is like variables or so, exist after expression, rvalue dies
immediately
- xvalue is originally lvalue that the value inside will be moved to another
lvalue then die. It is an "eXpiring" value. It has an identity like an lvalue,
but we treat it as an rvalue so we can move its contents safely.
*/