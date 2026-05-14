#include <iostream>
#include <tuple>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <variant>
#include <stdexcept>

template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if (i == n) {
        return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    }
    
    // FIXED: Only recurse if there are more types left. 
    // This stops the compiler from generating code infinitely.
    if constexpr (n + 1 < sizeof...(T)) {
        return _tuple_index<n + 1>(tpl, i);
    } else {
        throw std::out_of_range("Index out of range in tuple");
    }
}

template <typename... T>
std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t  i) {
    return _tuple_index<0>(tpl, i);
}

// Custom printer for the variant
// 3. FIXED PRINTER: Added T0 to prevent matching empty variants
template <typename T0, typename... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
    std::visit([&](auto && x){ s << x; }, v);
    return s;
}


class NavigationNode : public rclcpp::Node {
public:
    NavigationNode() : Node("NavigationNode") {
        // (Timestamp, Sensor_Name, Reading, Is_Critical)
        auto diagnostic = std::make_tuple(16839000.5, "Lidar_Front", 42.7, true);
        // Imagine this index comes from a ROS 2 Parameter or a Subscriber
        // It is NOT known at compile time.
        int requested_index = 1;
        RCLCPP_INFO(this->get_logger(), "Inspecting field at index %d...", requested_index);
        auto value = tuple_index(diagnostic, requested_index); //let see how the returend value as std::variant loos like
        std::cout << "Value at index " << requested_index << ": " << value << std::endl;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NavigationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
/*take home message 14.Mai 2026:
- <typename...T> maybe will have func(intvar, doublevar, stringvar, floatvar) later
- std::variant<T...> means can be any type in T, std::variant<int, double> used normal as a class or a datatype
- remember template<typename T, int N> could be used as std::array<float, 3>?
- if constexpr means this condition will be fixed => please evaluate in compile time and reduce the code => much faster
- sizeof...(T) means how many types in T, sizeof...(args) means how many arguments in args https://en.cppreference.com/cpp/language/sizeof...
- std::variant<T...>{ ... } modern way to constructor, uniform initialization, like array or so, array {}, object (), 
- remember lambda? [&](auto && x){ s << x; }, auto && x means can be any type, and we capture all variables by reference, so we can use s in the lambda body
*/