#include <initializer_list>
#include <iostream>
#include <vector>

class Robot {
public:
  int value_x;
  int value_y;
  int value_z;
  int value_a;
  int value_b;
  int value_c;
  Robot(int x, int y, int z, int a, int b, int c)
      : value_x(x), value_y(y), value_z(z), value_a(a), value_b(b), value_c(c) {
  }
};

class ListRobot {
public:
  std::vector<int> coordinates;
  ListRobot(std::initializer_list<int> list) {
    for (std::initializer_list<int>::iterator itr = list.begin();
         itr != list.end(); ++itr)
      coordinates.push_back(*itr);
  }
};

int main() {
  // traditional way to declare objects, as we can see, each has different way
  int arr[3] = {1, 2, 3};
  Robot robot(1, 2, 3, 4, 5, 6);
  std::vector<int> vec = {1, 2, 3, 4, 5};

  // new way to declare everything with this same style, so we have a unified
  // way to declare objects
  ListRobot robotcoords = {1, 2, 3, 4, 5, 6};
  std::vector<int> coords = {1, 2, 3, 4, 5, 6};

  std::cout << robotcoords.coordinates.size() << " " << coords.size()
            << std::endl;
  return 0;
}

/*take home message 29. April 2026
- unified way to declare and initialize different objects
- but in order to do that, you need to use std::initializer_list
*/