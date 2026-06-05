#include <thread>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <iostream>
#include <string>

class SensorBootNode : public rclcpp::Node {
    private:
    void boot_lidar() {
        std::cout << "booting lidar" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "finished booting lidar" << std::endl;
    }
    void boot_camera() {
        std::cout << "booting camera" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "finished booting camera" << std::endl;
    }

    public:
    SensorBootNode() : Node("SensorBootNode") {
        auto start_time = std::chrono::high_resolution_clock::now();

        std::thread lidar_thread(&SensorBootNode::boot_lidar, this);
        std::thread camera_thread(&SensorBootNode::boot_camera, this);

        lidar_thread.join();
        std::cout << "Joined lidar thread" << std::endl;
        camera_thread.join();
        std::cout << "Joined camera thread" << std::endl;
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end_time - start_time;
        std::cout << "Total booting time: " << elapsed.count() << "sec" << std::endl;
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    std::shared_ptr<SensorBootNode> node = std::make_shared<SensorBootNode>();
    rclcpp::shutdown();
    return 0;
}
