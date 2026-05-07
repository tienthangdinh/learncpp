#include <functional>
#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <vector>

void check_hardware() { std::cout << "Hardware checked!" << std::endl; }

class FunctionWrapperRobotNode : public rclcpp::Node {
public:
  FunctionWrapperRobotNode() : Node("FunctionWrapperRobotNode") {
    int battery = 90;
    safety_routines_.push_back(check_hardware);
    safety_routines_.push_back([this, battery]() {
      RCLCPP_INFO(this->get_logger(), "Battery %d %%", battery);
    });

    for (auto &routine : safety_routines_) {
      routine();
    }
  }

private:
  std::vector<std::function<void()>> safety_routines_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<FunctionWrapperRobotNode>();
  rclcpp::shutdown();
  return 0;
}

/*take home message 04. Mai 2026:
- put both lambda function and normal function into the same list, basically
making them to be of the same type, this is good when we need to list functiosn
together, as long as they both have same input, output datatype
- char = char
- char* = pointer to a first char = a string
- char** = pointer to a pointer to the first char of the first string?
- basically we use this instead of std::vector<std::string> because its legacy
- but how does it know when does a string stops? because always add \0 at the
end of the string*/