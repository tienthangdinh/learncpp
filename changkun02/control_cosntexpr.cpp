#include <iostream>
#include <type_traits>

template <typename CoordsT> auto robot_hit_wall(const CoordsT &distance) {
  if constexpr (std::is_integral<CoordsT>::value) {
    std::cout << "Warning: Robot hit wall in " << distance << "m" << std::endl;
    return 0.0;
  } else {
    return distance;
  }
};

int main() {
  auto distance = robot_hit_wall(0.01);
  return 0;
}

/*take home message 01. Mai 2026
- use constexpr again for compilation
- referencing & instead of passing an argument, remind me of 1 semester
*/