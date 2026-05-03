#include <iostream>
#include <vector>

// tell the compiler to not instantiate machine code for this in here, take the
// external one
extern template class std::vector<double>;

int main() {
  std::vector<double> joint_angles = {23.4, 54.3, 0.3, 160.3, 145.7, 100.2};
  std::cout << "Joint angles: ";
  for (double angle : joint_angles) {
    std::cout << angle << " ";
  }
  std::cout << std::endl;
  return 0;
}

/*take home message 01. Mai 2026:
- using extern template class to only define a type once
- .cpp compiled into object files, then linker links object files main.o and
robotmap.o code into 1 single executable .out
*/