# 1 std::array
- 3 types of array `std::vector` (dynamic, length can change but it is slow), `std::array` and C-style array are both fix-size array
- arrays are saved contguosly in stack, so be mindful how to use
- `constexpr` is `const`but value initialized in compile time.

## aggregate type initialization
- `std::array` is an aggregate, which means no constructor=> use aggregate initialization, which is list initializer
```
#include <array>
#include <iostream>
int main() {
    std::array<int, 6> fibonnaci {0, 1, 2, 3, 5, 8}; //list initialization
    std::array<int, 5> primes = {1, 2, 3, 5, 7}; //copy-list initialization is also ok
    std::cout << primes.size();
    return 0;
}
```

## default value initialization
```
#include <array>
#include <vector>
int main() {
    std::array<int, 5> a;
    std::array<int, 5> b{};
    std::vector<int> v(5); //vector for comparison
    return 0;
}
```

# 2 pass and return array
## pass with length information
```
#include <array>
#include <iostream>
template<typename T, std::size_t N>
void passbyref(std::array<T, N>$ arr) {
    std::cout << arr;
}
int main() {
    std::array<int, 5> firstarray {1, 2, 3, 4, 5}; //normal
    std::array secondarray {5, 4, 3, 2, 1} //CTAD initializer to infer std::array<int, 5>

    passbyref(firstarray);
    passbyref(secondarray);

    return 0;
}
```
## return
- ok we like pass by reference, but what if we really want to return `std::array`?
- well, `std::array`does not have Move capability, so yeah we can return by value
- or return by reference using `out parameter`
```
#include <array>
void modify(std::array& in, std::array& out) {
    for (std::size_t i; i < in.length(); i++) {
        out[i] = in[i]+1;
    }
}
int main() {
    std::array in {1,2, 3, 4, 5};
    std::array out;
    modify(in, out);
    return 0;
}
```

# 3 std::array of class type
```
#include <array>
struct House {
    int number{};
    int stories{};
}
int main() {
    std::array<House, 3> houses {
        {
            {2, 2}, {12, 3}, {23, 6}
        }
    };
    return 0;
}
```
3 types of data in C++:
- object/data value
- pointer `Student*` holds a memory address, so a memory address of a variable to passed in should be `&s`;
- reference is just about alias of an object `Student&`

```
#include <array>
struct Student {
    int id {};
}
constexpr std::array<Student, 3> students { Student{1}, Student{2}, Student{3}};
Student* findbyid(int id) {
    for (Student& s : students) {
        if (s.id == 1) return &s;
    }
}
int main() {
    const Student* one {findbyid(1)};
    return 0;
}
```

# 7 C-style array
- aggregate initialization, a.k.a using list initialization
```
int main() {
    int haha[3] {};
    int hoho[4] {1, 2, 3, 4}; //list init
    int hehe[3] = {1, 2, 3}; //copy list init
    auto size = sizeof(hoho);
    std::size_t sizelength = std::size(hehe);
    return 0;
}
```

# 8 C-style array is actually a pointer to address of the first element
```
#include <array>
#include <iostream>
int main() {
    int arr[5] {3, 5, 1, 2, 4};
    int* ptr {a};
    std::cout << std::boolalpha << (&array[0] == ptr);
    return 0;
}
```

# 9 pointer arithmetic
`ptr`, `ptr + 1`, and so on, where it is exactly depends on kidn of data, for example if `ptr` is an `int*`, it will be 4 bytes
```
#include <iostream>
int main() {
    int x {};
    const int* ptr {&x};
    std::cout << ++ptr <<--ptr;
    return 0;
}
```
```
#include <array>
#include <iostream>
int main() {
    int arr[] {3, 2, 4, 5};
    int* ptr {&arr[3]};
    std::cout << *ptr << ptr[0];
}
```

# 10 avoid C-style string+

# 11 multidimensional C-style array
```
#include <array>
int main() {
    int arr[3][4] {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}
    }
    for (std::size_t row {0}; row < std::size(arr);row++) {
        for (std::size_t col {0}; col < std::size(arr[0]); arr++) {
            std::cout << arr[row][col];
        }
    }
    return 0;
}
```
# 13 multidimensional std::array
originally it could be defined like this
```
#include <array>
#include <iostream>
int main() {
    std::array<std::array<int, 3>, 4> arr {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}
    }
    for (auto& row : arr) {
        for (auto& col : row) {
            std::cout << col;
        }
    }
    return 0;
}
```