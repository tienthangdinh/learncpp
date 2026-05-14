#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <iterator>
#include <rclcpp/rclcpp.hpp>

class TestNode : public rclcpp::Node {
public:
    TestNode() : Node("TestNode") {
        const int count = 100000000;
    std::vector<int> v(count, 10);
    std::list<int> l(count, 10);

    auto start = std::chrono::high_resolution_clock::now();
    v.insert(v.begin() + 350000, 20); // Random Access Iterator knows the size of each element, v.begin() is the pointer to the first element
    v.erase(v.begin() + 99990); // Erase 
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> vector_duration = end - start;

    start = std::chrono::high_resolution_clock::now();
    auto it = l.begin();
    std::advance(it, 350000); // Move iterator to the middle of the list
    l.insert(it, 20); // Insert in the middle of the list
    it = l.begin();
    std::advance(it, 99990); // Move iterator to the position to erase
    l.erase(it); // Erase
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> list_duration = end - start;

    std::cout << "Vector insert and erase duration: " << vector_duration.count() << " seconds" << std::endl;
    std::cout << "List insert and erase duration: " << list_duration.count() << " seconds" << std::endl;
    }
};
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TestNode>();
    rclcpp::shutdown();

    return 0;
}


/*take home message 11.Mai 2026
- Iterator is basically just a pointer and it knows the type of the container, springing by sizeof(T)
- vector: contiguous----------fast access O(1)----slow insert/delete O(n)------Random Access Interator RamdomIt (can go anywhere)
- list: scattered linked list--- slow access O(n)--fast insert/delete O(1) -- Bidirectional Iterator BidirIt (can only go +-1) 
- std::sort wont work on linkedlist because not RandomAccessIterator it has its own list.sort()*/
