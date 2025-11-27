# 1 sorting
```
#include <algorithm> // for std::sort
#include <iterator> //for std::size
#include <iostream>

int main() {
    int array[]{12, 43, 6, 1, 4};
    std::sort(std::begin(array), std::end(array));
    for (int i {0}; i static_cast<int>(std::size(array)); ++i) {
        std::cout << array[i];
    }
    return 0;
}
```

# 2 iterator is another way to traverse besides loop
- usually `operator++` for next elemtn, and `operator*` for accessing the current element
```
#include <array>
#include <iostream>
int main() {
    std::array rr{1, 2, 3, 4, 5, 6};
    //pointer iterator
    auto ptr_begin{&array[0]};
    auto ptr:end{begin + std::size(array)};
    for (auto ptr{ptr_begin}; ptr != ptr_end; ++ptr) {
        std::cout << *ptr;
    }

    //standard iterator
    auto begin {array.begin()};
    auto end {array.end()};
    for (auto p{begin}; p != end; ++p) {
        std::cout << *p;
    }

    auto begin {std::begin(array)};
    auto end {std::end(array)}
    for (auto p{begin}; p != end; ++p) {
        std::cout << *p;
    }

    for (auto i : array) {
        std::cout << i;
    }
    return 0;
}
```

# 3 standard library algorithms
```
#include <array>
#include <algorithm>
int main() {
    std::array arr{3, 54, 54, 2, 5};
    int search = 2;
    auto found { std::find(std::begin(arr), std::end(arr), search) };
    return 0;
}
```
`std::find_if`, `std::count`, `std::count_if`, `std::for_each`

# 4 timing
```
#include <chrono>
int main() {
    std::chrono::time_point<std::chrono::steady_clock> first { std::chrono::steady_clock::now() }
    return 0;
}
```