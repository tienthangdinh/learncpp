#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <rclcpp/rclcpp.hpp>

class MemoryBenchmarkNode : public rclcpp::Node {
public:
    MemoryBenchmarkNode() : Node("MemoryBenchmarkNode") {
        const int count = 100000;
        std::vector<std::string> keys(count);
        for (int i = 0; i < count; ++i) {
            keys[i] = "landmark_id_" + std::to_string(i);
        }

        std::map<std::string, int> ordered_map;
        for (const auto& key : keys) {
            ordered_map[key] = 1;
        }

        std::unordered_map<std::string, int> unordered_map;
        for (const auto& key : keys) {
            unordered_map[key] = 1;
        }

        std::string test_key = "landmark_id_99999";

        auto start = std::chrono::high_resolution_clock::now();
        auto it = ordered_map.find(test_key);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> ordered_duration = end - start;
        std::cout << "Ordered map search duration: " << ordered_duration.count() << " seconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        auto it_unordered = unordered_map.find(test_key);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> unordered_duration = end - start;
        std::cout << "Unordered map search duration: " << unordered_duration.count() << " seconds" << std::endl;

        size_t bucket_count = unordered_map.bucket_count();
        std::cout << "Unordered map bucket count: " << bucket_count << std::endl;
        float load_factor = unordered_map.load_factor();
        std::cout << "Unordered map load factor: " << load_factor << std::endl;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MemoryBenchmarkNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
/*take home message 12.Mai 2026:
- std::unordered_set and std::unordered_map are hash-based containers, they do not maintain any order of elements
- but they provide average O(1) time complexity for search, insert, and delete operations, but worst-case O(n) if there are many hash collisions
- std::set and std::map garantee O(log n) time complexity for search, insert, and delete operations because implemented as balanced binary search trees ($O(\log n)$)
- but ordered eventhough ($O(\log n)$) a little slower but it is predictable
- but std::unordered_set and std::unordered_map use more memory than std::set and std::map because it has to reserve extra buckets even if they are not used
- map tries to keep its Load Factor (Items ÷ Buckets) around 0.5 to 0.7, and will automatically resize (rehash) when the load factor exceeds a certain threshold, which can lead to O(n) time complexity for that operation, but it happens infrequently
- AND also it needs to save overhead Hash value.
*/