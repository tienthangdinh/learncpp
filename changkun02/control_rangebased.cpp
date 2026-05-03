#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> status_codes = {0, 0, 0, 1, 0, 0};
  std::vector<int>::iterator itr =
      std::find(status_codes.begin(), status_codes.end(), 1);
  if (itr != status_codes.end()) {
    int index = std::distance(status_codes.begin(), itr);
    std::cout << "an error" << *itr << " found at index " << index << std::endl;
  }

  std::cout << "reading only-------" << std::endl;

  for (int el : status_codes) {
    std::cout << el;
  }
  std::cout << std::endl;

  std::cout << "reset bits--------" << std::endl;
  for (int &el : status_codes) {
    el = 0;
  }

  for (auto el : status_codes) {
    std::cout << el;
  }
  std::cout << std::endl;
  return 0;
}

/*take home message 01. Mai 2026
- reference using &
- now I know the type of iterator is std::vector<int>::iterator
*/