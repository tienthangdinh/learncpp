#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <utility>

class TelemetryNode : public rclcpp::Node {
public:
  TelemetryNode() : Node("TelemetryNode") {}
  template <typename T> void middleware_process_incomingmess(T &&mess) {
    process_message(std::forward<T>(mess));
  }

private:
  void process_message(std::string &msg) {
    RCLCPP_INFO(this->get_logger(), "Processing LVALUE (copying): %s",
                msg.c_str());
  }
  void process_message(std::string &&msg) {
    RCLCPP_INFO(this->get_logger(),
                "Processing RVALUE (moving): %s", // s for string
                msg.c_str()); // string is a complex object, can have size(),
                              // append(),...
    permanent_storage = std::move(msg); // efficient steal
  }
  std::string permanent_storage;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TelemetryNode>();
  std::string new_mess = "Battery 80%";
  // test lvalue
  node->middleware_process_incomingmess(new_mess);
  // test rvalue
  node->middleware_process_incomingmess(std::string("Battery died"));
  rclcpp::shutdown();
  return 0;
}

/*take home message 07. Mai 2026:
- as you can see here, node is a pointer
- std::move converts lvalue->rvalue
- std::forward keeps the same, but this is only needed when we use template
*/