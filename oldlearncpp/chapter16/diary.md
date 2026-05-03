# 1 intro to container & array
## container
```
#include <iostream>
#include <string>
int main() {
    std::string name{ "Thang" }; //strings are containers for character
    std::cout << name.lengt();
    return 0;
}
```
- containers single element does not have a name, only the container itself

## array
- is a type of container
- `std::vector` C++ style, flexible
- `std::array` C-style, fixed and dangerous behavior

# 2 std::vector is the new array
```
#include <vector>
#include <iostream>
int main() {
    std::vector<int> primes {2, 3, 5, 7};
    std::vector vowels {'a', 'b', 'c'};
    std::cout << "Second element" << primes[1];
    std::cout << &(primes[0]);
    std::cout << &(primes[1]);
    return 0;
}
```
- Containers typically have a special constructor called a list constructor like above
- `explicit std::vector<T>(std::size_t)` for e.g. `std::vector<int> hehe(10);` in order to define legnth of vector
```
//copy init
std::vector<int> v1 = 10;
//direct init
std::vector<int> v2(10);
//list init
std::vector<int> v3{10};
//copy list init
std::vector<int> v4 = {10};
//default init
std::vector<int> v5 {};
```
# 4 pass by reference std::vector
```
#include <iostream>
#include <vector>

template <typename T>
void passbyreference(std::vector<T>& arr) {
    std::cout << arr[0];
}
int main() {
    std::vector<int> primes{1, 2, 3, 4};
    passbyreference(primes);
    return 0;
}
```

# 5 return by value std::vector??????? & copy constructor again
```
#include <iostream>
#include <vector>
int main() {
    std::vector<int> arr1 {1, 2, 3, 4};
    std::vector arr2 {arr1};
    return 0;
}
```
## move is auto used in return by value
- inexpensive move the ownership, what cannot be move will be copied
- now we have so many options to avoid pass by value (which making copies many times): pass by reference, pass by address, 
- we can pass by reference or address, but we should return by move (which will auto used by return by value)
- basically because the reference will die after the function ends, so yeah we should not return by reference/address.

# 8 range based array loop
```
#include <vector>
#include <iostream>
int main() {
    std::vector<int> arr = {0, 1, 2, 3, 4, 5};
    for (auto& num : arr)
        *auto += 1;
    for (std::size_t iter{0}; iter < arr.length(); iter++)
        std::cout << arr[iter];
    return 0;
}
```
- auto when you want to modify copies of the elements.
- auto& when you want to modify the original elements.

# resizing vector
- `arr.resize(5);`

# 11 std::vector on stack behavior
- stack is actually not good: last in first out
- push & pop
```
#include <vector>
int main() {
    std::vector<int> stack;
    stack.push_back(1);
    stack.push_back(2);
    stack.pop_back();
    return 0;
}
```
