#include <string>
#include <unordered_map>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <vector>
#include <list>

struct HashEntry {
    std::string key;
    std::string value;
};
class SensorMapNode : public rclcpp::Node {
    private:
    std::vector<std::list<HashEntry>> hash_table;
    public:
    SensorMapNode() : Node("SensorMapNode"), hash_table(5) {}
    void insert(const std::string& key, const std::string& value) { //why const? reference does not allow rvalue, but in case you want to pass a rvalue, use const to trick the compiler that oh ok, i am not touching this, so please let this alive at least till the end of function
        size_t bucket = std::hash<std::string>{}(key) % 5;
        hash_table[bucket].push_back({key, value});
    }
    std::string get(std::string key) {
        size_t bucket = std::hash<std::string>{}(key) % 5;
        for (const auto& entry : hash_table[bucket]) { //use & because every step in the loop, please do not copy, use directly
            if (entry.key == key) {
                return entry.value;
            }
        }
        return "Not found";
    }
};
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SensorMapNode>();
    node->insert("temperature", "25C");
    node->insert("humidity", "60%");
    std::cout << "Temperature: " << node->get("temperature") << std::endl;
    std::cout << "Humidity: " << node->get("humidity") << std::endl;
    std::cout << "Pressure: " << node->get("pressure") << std::endl;
    rclcpp::shutdown();
    return 0;
}

/*take home message 12.Mai 2026
- this is an example of a simple hash table implementation using separate chaining for collision resolution
- size_t bucket = std::hash<std::string>{}(key) is a 2 steps: call the constructor then call the operator() function (Functor - function object)
- but why size_t and not an int? int can be negative, and std::hash<T>::operator() returns a size_t ---https://en.cppreference.com/cpp/utility/hash/operator()
- use auto& because every step in the loop, please do not copy, use directly
- but why const auto&? just a promise to compiler that we will not modify the entry, just read it
- why const std::string&? reference does not allow rvalue because it dies after the function call, but in case you want to pass a rvalue, use const to trick the compiler that oh ok, i am not touching this, so please let this alive at least till the end of function
*/

