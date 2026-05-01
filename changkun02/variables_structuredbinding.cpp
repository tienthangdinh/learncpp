#import <iostream>
#import <tuple>

std::tuple<bool, double, std::string> checkPath() {
  return {true, 5.3, "Path found"};
}

struct Point {
  int x, y;
};

int main() {
  Point startingpoint = {0, 0};
  auto [posX, posY] = startingpoint;
  std::cout << "starting point: " << posX << ";" << posY << std::endl;

  auto [status, distance, message] = checkPath();
  if (status) {
    std::cout << message << " " << distance << "m" << std::endl;
  }
  return 0;
}

/*take home message 01. Mai 2026
- using structure for complex return structure
- std is a namespace
- every C++ compiler already contain Standard Template Library (STL) with
std::vector, std::iostream,... and you load each of them
*/