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
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```
lreference must be initialized
`int& ref {x};` (reference binding)

# 5 pass by lvalue reference
pass by value will just copy,
but pass by reference will keep the reference there

and also pass the reference can also modify the object value
```
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
```
# 7 pointers
- When following a type name, & denotes an lvalue reference: int& ref.
- When used in a unary context in an expression, & is the address-of variable: std::cout << &x.

## deference
`x; &x; *(&x)`

## pointers
hold memory address
```
int;  // a normal int
int&; // an lvalue reference to an int value

int*; // a pointer to an int value (holds the address of an integer value)
```

- initialize a pointer using an address of a variable
`int* ptr = &x;`

since pointer holds address => the value of the pointer should be a reference => use &

- after that of course we can dereference 
`x = *(&x) = *ptr;`

- change address => `ptr`
- change value => `*ptr`

reference operation returns a pointer
`typeid(&x).name() `=> int *

# 10 pass by address (besides pass by value, reference)
prefer pass by reference!!!

# 12 return by reference & by address
prefer return by reference!!!

ALso because pointer can be null and danngling => undefined behavior

# 13 in and out parameter
out parameter is to modify the value in function, mostly no need to return back

the initiaal value of out parameter does not maetter

should pass out reference parameter instead of address


Question #3

Name two reasons why we prefer to pass arguments by const reference instead of by non-const reference whenever possible.

ide Solution

A non-const reference parameter can be used to modify the value of the argument. If we do not need this ability, it’s better to pass by const reference so that we don’t accidentally modify the argument.
A non-const reference parameter can only accept a modifiable lvalue as an argument. A const reference-parameter can accept a modifiable lvalue, a non-modifiable lvalue, or an rvalue as an argument.

