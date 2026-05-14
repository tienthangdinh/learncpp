#include <iostream>
#include <set>
#include <map>
#include <rclcpp/rclcpp.hpp>

class SensorManagerNode : public rclcpp::Node {
public:
    SensorManagerNode() : Node("SensorManagerNode") {
        // Using std::set to store unique sensor names
        std::set<int> active_sensors;
        active_sensors.insert(1);
        active_sensors.insert(2);
        active_sensors.insert(2); // Duplicate, will not be added
        std::cout << "Active Sensors: ";
        for (const auto& sensor : active_sensors) {
            std::cout << sensor << " ";
        }
        std::cout << std::endl;

        std::multiset<float> distances;
        distances.insert(1.5f);
        distances.insert(2.0f);
        distances.insert(1.5f); // Duplicate, will be added

        std::cout << "Distances: ";
        for (const auto& dist : distances) {
            std::cout << dist << " ";
        }
        std::cout << std::endl;

        std::map<std::string, std::string> sensor_nicknames;
        sensor_nicknames["sensor1"] = "Sensor One";
        sensor_nicknames["sensor2"] = "Sensor Two";
        sensor_nicknames["sensor3"] = "Sensor Three";

        std::cout << "Sensor Nicknames: " << std::endl;
        for (const auto& [name, nickname] : sensor_nicknames) {
            std::cout << name << ": " << nickname << std::endl;
        }

        std::multimap<std::string, std::string> sensor_locations;
        sensor_locations.insert({"sensor1", "Room A"});
        sensor_locations.insert({"sensor1", "Room B"}); 
        sensor_locations.insert({"sensor2", "Room C"}); 
        sensor_locations.insert({"sensor2", "Room D"}); 
        std::cout << "Sensor Locations: " << std::endl;
        for (const auto& [name, location] : sensor_locations) {
            std::cout << name << ": " << location << std::endl;
        }

    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SensorManagerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

/*take home message 12.Mai 2026:
- std::set is ordered collection of unique elements => std::multiset allows duplicates
- std::map is ordered collection of key-value pairs => std::multimap allows duplicate keys
*/