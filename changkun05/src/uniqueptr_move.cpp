#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <memory>

struct LidarPayload {
    std::vector<float> ranges;
    LidarPayload() : ranges(360, 5.5f) { //set 260deg of radius 5,5m
        std::cout << "LidarPayload initialized on Heap " << this << " and range at "<<  &ranges << std::endl; //this is already a pointer
    }
    ~LidarPayload() {
        std::cout << "LidarPayload deconstructed from Heap" << std::endl;
    }
};

class RobotNode : public rclcpp::Node {
    public:
    RobotNode() : Node("RobotNode") {
        std::unique_ptr<LidarPayload> pointer1 = std::make_unique<LidarPayload>();
        std::cout << "pointer1 on stack" << &pointer1 << " is pointing to heap " << pointer1.get() << std::endl;
        std::unique_ptr<LidarPayload> pointer2 = std::move(pointer1);
        std::cout << "transfered ownership to pointer 2" << std::endl;
        std::cout << "pointer1 on stack" << &pointer1 << " is pointing to heap " << pointer1.get() << std::endl;
        std::cout << "pointer2 on stack" << &pointer2 << " is pointing to heap " << pointer2.get()  << std::endl;
        pointer1 = std::move(pointer2);
        std::cout << "transfered ownership back to pointer 1" << std::endl;
        std::cout << "pointer1 on stack" << &pointer1 << " is pointing to heap " << pointer1.get() << std::endl;
        std::cout << "pointer2 on stack" << &pointer2 << " is pointing to heap " << pointer2.get() << std::endl;
    }
};

int main(int argc, char** kwargs) {
    rclcpp::init(argc, kwargs);
    auto node = std::make_shared<RobotNode>();
    rclcpp::shutdown();
    return 0;
}


/* take home message 29. Mai 2026
- this is already a pointer, use &,*,.get() like normal
- std::unique_ptr: Exclusive, single ownership of a heap asset. Zero reference counting overhead.
- std::move on unique_ptr: Steals the pointer address handle, automatically grounding the original tracking variable to nullptr.
- Best Practice: Use unique_ptr by default for internal node pipelines. Only upgrade to shared_ptr if the data must be concurrently shared by multiple independent ROS subscribers or distinct system threads.
*/