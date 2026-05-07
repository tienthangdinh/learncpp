#include <iostream>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <utility>
#include <vector>

class ScanProcessorNode : public rclcpp::Node {
public:
  ScanProcessorNode() : Node("ScanProcessorNode") {
    std::vector<float> raw_lidar_data = {324.03, 425.32, 4252.35, 765.42};
    RCLCPP_INFO(this->get_logger(), "Lidar data created at %p",
                (void *)raw_lidar_data.data());

    process_scan(
        std::move(raw_lidar_data)); // we are forced to convert into xvalue
                                    // because the function expect xvalue param

    RCLCPP_INFO(this->get_logger(),
                "After move, the original raw lidar data has size %zu",
                raw_lidar_data.size());
  }

private:
  std::vector<float> stored_data_;
  void process_scan(std::vector<float> &&heavy_data) {
    this->stored_data_ =
        std::move(heavy_data); // why std::move again? because C++ still does
                               // not accept it to be an xvalue yet
    RCLCPP_INFO(
        this->get_logger(), "Scan stolen by another pointer at %p",
        (void *)stored_data_.data()); // actually it should still be the same
                                      // address since data is not moving
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ScanProcessorNode>();
  rclcpp::shutdown();
  return 0;
}

/*take home message 06. Mai 2026:
- std::move is like a converter from lvalue to xvalue
- && is the declaration type of xvalue
- &stored_data_ is the address of the pointer manager: Lives on the Stack. It's
the small 24-byte manager (Size, Capacity, Pointer)
- stored_data_.data() is the address of the data it is pointing to. Lives on the
Heap. It's the large chunk of memory where your floats are actually sitting.
*/