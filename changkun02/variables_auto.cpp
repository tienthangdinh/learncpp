#include <algorithm>
#include <iostream>
#include <iterator> // Required for std::distance
#include <vector>

int main() {
  std::vector<int> vecc = {1, 2, 3, 4};
  std::vector<int>::iterator itr = std::find(vecc.begin(), vecc.end(), 2);
  if (itr != vecc.end())
    std::cout << *itr << "at position" << std::distance(vecc.begin(), itr)
              << std::endl;

  // now use auto, can also use for (std::vector<int>::iterator el =
  // vecc.begin(); el != vecc.end(); ++el)
  for (auto el = vecc.begin(); el != vecc.end(); ++el)
    std::cout << *el << std::endl;
}

/*take home message 29.04.2026:
- auto type in for, if
- first use with vector
=> iterating over list of lidar sensor data
*/