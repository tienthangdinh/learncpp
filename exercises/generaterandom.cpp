// Source - https://stackoverflow.com/a/13445752
// Posted by Cornstalks, modified by community. See post 'Timeline' for change
// history Retrieved 2026-04-28, License - CC BY-SA 4.0

#include <iostream>
#include <random>

int main() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      1, 156); // distribution in range [1, 6]

  std::cout << dist6(rng) << std::endl;
}
