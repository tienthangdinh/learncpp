# 1.1 Statement
## Statement
usually ends with a semicolon
# Functions and main functions
every C++ program must have a function named main

name of a function, object, type, template is called an identifier

# 1.2 Comments
// and /* */

# 1.3 Data and Values
program is loaded to RAM (by the OS)
## Object & Variables
C++ discourage access direct memory. C++ access memory indirectly through an object in RAM or CPU register "go get the value stored by this object"

Object is an annamed object in meemory (variable or function). Variable is an object with a name

At runtime, a variable is allocated a storage location

data type must be known at compile-time, can only hold that type

# 1.4 Variable assignment & initialization
## Default initialization
`int a;`when no need a specific value, it will create some random value, but this case should consider the zero initialization
## Copy assignment
`int a = 5;` copy a value of 5 to the variable on left hand side. old

## Direct initialization
`int width ( 5 );`. also old

## List initialization (moderm way)
`int width {5};`(preferred) or `int width = {6};` used we we actually use the value

## Value initilization (or zero initialization)
`int width {};`a value near zero initialized, used when we will change it soon

## Instantiation
variable created (allocated) & initialized a.k.a. object => instance

## The [[maybe_unused]] attribute
so that C++ does not give a warning, we add 
`[[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused`

### iosteam: cout, cin, endl
`#include <iostram>`library contains a few predefined variables to use:
- `std::cout`...

`<<`is an insertion operator

# 1.8 Whitespace
C++ is whitespace independent, unlike Python

# 1.9 Literal & Operator
## Literal
is already a value in code cannot change, unlike variable
## Operator (not yet a statement)
- unary: e.g. `-5`
- binary: e.g. `3+4`
- tenary only 1
- nullary only 1

## Chaining operators
3+4+6

# Expressions
all of these are expressions
```
2               // 2 is a literal that evaluates to value 2
"Hello world!"  // "Hello world!" is a literal that evaluates to text "Hello world!"
x               // x is a variable that evaluates to the value held by variable x
2 + 3           // operator+ uses operands 2 and 3 to evaluate to value 5
five()          // evaluates to the return value of function five()
```