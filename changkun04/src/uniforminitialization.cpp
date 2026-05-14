#include <string>
#include <vector>
#include <rclcpp/rclcpp.hpp>

struct PIDConfig {
    double p;
    double i;
    double d;
};

struct SensorConfig {
    std::string name;
    int update_rate_hz;
    PIDConfig filters; //nested struct
}

class ConfigNode : public rclcpp::Node {
public:
    ConfigNode() : Node("ConfigNode") {
        SensorConfig sensor1{"Lidar_Front", 30, {1.0, 0.5, 0.1}}}; 
        
        std::vector<SensorConfig> sensors = allsensors{
            {"Lidar_Front", 30, {1.0, 0.5, 0.1}},
            {"Camera_Front", 60, {0.8, 0.3, 0.05}},
            {"Radar_Rear", 20, {1.2, 0.6, 0.2}}
        };
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ConfigNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


/*take home message 14.Mai 2026:
- {} is so easy
- {} just simply like (), no difference, a little more stricted
- but could be mistaked with std::initializer_list
*/