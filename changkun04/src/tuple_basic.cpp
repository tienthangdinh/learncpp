#include <iostream>
#include <tuple>
#include <string>
#include <rclcpp/rclcpp.hpp>

class NavigationNode : public rclcpp::Node {
public:
    NavigationNode() : Node("NavigationNode") {
        //2 ways to create a tuple
        std::tuple<std::string, double, double> navigationtarget = std::make_tuple("Door", 1.0, 2.0);
        std::tuple<std::string, double, double> navigationstart("Toilet", 3.0, 4.0);

        //Accessing tuple elements
        std::string targetname = std::get<0>(navigationtarget);
        std::cout << "Target name: " << targetname << std::endl;

        //tie
        std::string startname;
        double startx, starty;
        std::tie(startname, startx, starty) = navigationstart;
        std::cout << "Start name: " << startname << ", x: " << startx << ", y: " << starty << std::endl;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NavigationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
/*take home message 12.Mai 2026:
- std::tuple quite easy
- also have a look at std::tie, std::get, std::make_tuple,...
*/




