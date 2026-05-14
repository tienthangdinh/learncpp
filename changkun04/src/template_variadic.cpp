#include <vector>
#include <iostream>
#include <numeric>
#include <rclcpp/rclcpp.hpp>
#include <initializer_list>

class SensorStatus {
    public:
    int id;
    int health_score;

    SensorStatus(int sensor_id, int score) : id(sensor_id), health_score(score) {}

    //list of scores for 1 sensor
    SensorStatus(std::initializer_list<int> scores) {
        id = 0; //defualt id
        health_score = std::accumulate(scores.begin(), scores.end(), 0);
    }
};

class SensorNode : public rclcpp::Node {
public:
    SensorNode() : Node("SensorNode") {
        SensorStatus sensor1(1, 85);
        SensorStatus sensor2{90, 80, 95}; //using initializer list to calculate health score

private:
template<typename... T> //variadic template accepts any number of SensorStatus objects
int calculate_total_health(T... sensors) {
    return (sensors.health_score + ...); // This expands to: (s1.health_score + s2.health_score + s3.health_score)
}
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SensorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

/*take home message 14.Mai 2026
- ok but can std::initializer_list be used for different types? no, it is for same type only, but variadic template can be used for different types
- but the uniform initialization with {} could be mistaken it is like normal cosntructor
- the unpacking (sensors.health_score + ...) is really interesting, it is called fold expression, it is a C++17 feature, it can be used to apply an operator to all arguments in a parameter pack
- 4 principles of unpacking (folding):
    1. unary left fold: (... + args) => (((arg1 + arg2) + arg3) + ...)
    2. unary right fold: (args + ...) => (arg1 + (arg2 + (arg3 + ...)))
    3. binary left fold: (init + ... + args) => (((init + arg1) + arg2) + ...)
    4. binary right fold: (args + ... + init) => (arg1 + (arg2 + (arg3 + ... + init)))
*/
