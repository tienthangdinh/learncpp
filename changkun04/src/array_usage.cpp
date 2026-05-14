#include <iostream>
#include <vector>
#include <rclcpp/rclcpp.hpp>

// A "Legacy" C function (you cannot change this)
extern "C" bool calculate_checksum(const float* data, int length) { //input is a pointer to float, and the length of the array
    //imagine doing something
    return true; 
}

class IMUFilterNode : public rclcpp::Node {
public:
  IMUFilterNode() : Node("IMUFilterNode") {
    std::array<float, 3> imu_readings = {0.1f, 0.2f, 0.3f}; // live fixed on STACK, No 'new', no 'delete', no heap manager.
    RCLCPP_INFO(this->get_logger(), "IMU readings size %zu", imu_readings.size()); //it knows it own size
    std::sort(imu_readings.begin(), imu_readings.end()); //https://en.cppreference.com/cpp/algorithm/sort
    RCLCPP_INFO(this->get_logger(), "Sorted IMU readings: %f, %f, %f", imu_readings[0], imu_readings[1], imu_readings[2]);

    bool ok_1 = calculate_checksum(imu_readings.data(), imu_readings.size()); // .data() gives you the raw pointer, 
    RCLCPP_INFO(this->get_logger(), "Checksum valid: %s", ok_1 ? "true" : "false");
    bool ok_2 = calculate_checksum(&imu_readings[0], imu_readings.size()); // &imu_readings[0] also gives you the raw pointer to the first element
    RCLCPP_INFO(this->get_logger(), "Checksum valid: %s", ok_2 ? "true" : "false");
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<IMUFilterNode>();
  rclcpp::shutdown();
  return 0;
}

/*take home message 11. Mai 2026:
- Use std::array for fixed-size arrays on the stack
- Use .data() to get a raw pointer to the underlying array
- Also &array[0] can be used to get a raw pointer to the first element
- Use .size() to get the number of elements in the array
- std::sort sorts from small to large by default
- reading documentation: RandomIt is like std::vector<double>::iterator or anything
*/