#include <iostream>
#include <vector>
#include <rclcpp/rclcpp.hpp>

class ArchitectureCheckNode : public rclcpp::Node {
    public:
    ArchitectureCheckNode() : Node("ArchitectureCheckNode") {
        std::vector<int>::size_type vector_size_type;
        size_t global_size_type;

        RCLCPP_INFO(this->get_logger(), "Size of size_t is %zu bytes", sizeof(size_t)); //64bit is 8 bytes
        RCLCPP_INFO(this->get_logger(), "Size of vector<int>::size_type is %zu bytes", sizeof(vector_size_type));
        RCLCPP_INFO(this->get_logger(), "Size of a standard int is %zu bytes", sizeof(int)); //32bit is 4 bytes
}
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ArchitectureCheckNode>();
    rclcpp::shutdown();
    return 0;
}

/*take home message 11.Mai 2026:
- sizeof() takes input either a type or a variable, output number of bytes of type (size_t)
- std::vector<T>::size_type is just to say what type will the returned value of size() be
- and eventually, size() returns how many elements are there
- and more eventually, size() * sizeof(T) will give you the total size of the memory segment
- https://en.cppreference.com/cpp/container/vector

*/