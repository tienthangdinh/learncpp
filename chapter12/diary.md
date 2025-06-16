# 1 compound data type
- function
- arrays
- pointers: to object, to function and its members
- reference: L-value, R-value
- enumarated: unscoped, scoped
- class: struct, class, unions

# 2 value category r and l
Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.

# 3 lvalue reference
```
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```
```
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```