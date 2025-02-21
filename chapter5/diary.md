# 5.1 constant variable
## declaring
```
int double gravity { 9.8 };
const int a { 2 };
```
reduce moving part, reduce risk, and compile also faster

# 5.2 Literal
## suffix
- integer: u, l ul ,ll,
- float: f, l
````
    std::cout << 5L << '\n'; // 5L is type long
    std::cout << 5.0 << '\n';  // 5.0 (no suffix) is type double (by default)
    std::cout << 5.0f << '\n'; // 5.0f is type float

````
# 5.4 optimization
profiler software (in compiler) will have a look deeper into each block of the program to find optimization.

It runs the program multiple times at the first compilation, then it will adapt and actual compile.

- constant folding `int a { 3 + 4};`
- constant propagation `std::cout << a;`
- dead code elimination (when a line never used) => less variable initialization

# 5.6 compile-time constant evaluation
````
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression
````
- const: value known at runtime
- constexpr: value known at compile time

# std::string in C++
avoid C-string, let's use C++ strings:
Because its dynamically memory allocation => can be flexible in runtime (length changes)
`std::string name { "Thang "};`

read input, using getline:
````
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);
````
std::getline() does not ignore leading whitespace. If you want it to ignore leading whitespace, pass std::cin >> std::ws as the first argument. It stops extracting when encountering a newline.

member function: `name.length()`instead of `length(name)`




