#include <rclcpp/rclcpp.hpp>
#include <tuple>
#include <string>
#include <iostream>
#include <string>
#include <variant>

template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
    if (i == n) return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    if constexpr (n + 1 < sizeof...(T)) return _tuple_index<n + 1>(tpl, i);
    throw std::out_of_range("Index out of range");
}

template<typename... T>
std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
    return _tuple_index<0>(tpl, i);
}

// 2. Custom Printer for the Variant
template <typename T0, typename... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
    std::visit([&](auto && x){ s << x; }, v);
    return s;
}

template<typename T>
auto tuple_len(const T &) {
    return std::tuple_size<T>::value;
}

class AggregateNode : public rclcpp::Node {
public:
    AggregateNode() : Node("AggregateNode") {
        auto base_info = std::make_tuple("Robot_001", 1.5);
        auto sensor_data = std::make_tuple(45.5, true);
        auto full_report = std::tuple_cat(base_info, sensor_data);

        for (size_t i = 0; i < tuple_len(full_report); ++i) {
            auto value = tuple_index(full_report, i);
            std::visit([](auto && arg) { std::cout << arg << " "; }, value);
        }
        std::cout << std::endl;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AggregateNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

/*take home message 15.Mai 2026:
- just basic std::make_tuple, std::tuple_cat and std::get, std::tuple_size
- std::visit once again does a good job of taking a value and doing something with it, in this case printing it out
- the tuple_index function is a bit more complex, it uses recursion and template metaprogramming to access the tuple elements by index, and returns a std::variant that can hold any of the types in the tuple, which is a neat way to handle the fact that tuples can have heterogeneous types
*/