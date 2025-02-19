# 2.1 2.2 functions
## return by value
return value is copied and is returned back to to the caller

when a value is returned, a caller can decide to use (assign into variable, cout,...) it or to ignore (discard) it

## main()
C++ requires main to return an int, and no call to main is allowed (this 2 things different from C)

### status code in main
exit code return code status code all the same, 0 means OK

function will return 0 automatically

## void
do not put void in expression that needs return value e.g `std::cout << `, it wont compile

# 2.4 parameters, arguments
pass by value: parameter is copied and saved in newly created variables

can also use return values as argument `printDouble(getValueFromUser());`

# 2.5 local scope
block scope, it will die when function terminates

# 2.7 forward declaration
declare first, explain later, so that the compiler knows by order
```
#include <iostream>

int add(int x, int y); // forward declaration of add() (using a function declaration)

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
    return 0;
}

int add(int x, int y) // even though the body of add() isn't defined until here
{
    return x + y;
}
```

# 2.8 multiple file
include all of the relevant code files on the compile line. For example: 
`g++ main.cpp add.cpp -o main`
 where main.cpp and add.cpp are the names of your code files, and main is the name of the output file.

# 2.9 namespace
## global namespace
any name, even a namespace is a part of global namespace (global scope)

## std namespace
everything belongs to standard library in their own namespace to avoid collision with user-defined variable names
=> `std::cout`

not recommend using explicit 
```
using namespace std;
cout << "a;
```

# 2.10 preprocessor
a step before compilation
- process all directives `#include`

e.g. `#include` will replace the file with the content of the file

`#define`for substitution
```
#include <iostream>

#define MY_NAME "Thang"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```

# header files .h
propagate a bunch of forward declarations

source files should include their paired header

do not #include .cpp: it will raise collision

## double quotes vs angle breackets
- angled bracket <>: file we didnt write outselves, it will search everywhere
- double quotes "": preprocessors search in project directory

## why iostream not an .h?
.h global namespace

without .h: .std namespace 

## best practice
- The paired header file for this code file (e.g. add.cpp should #include "add.h")
- Other headers from the same project (e.g. #include "mymath.h")
- 3rd party library headers (e.g. #include <boost/tuple/tuple.hpp>)
- Standard library headers (e.g. #include <iostream>)

# 2.12 header guard
in case really want to define something in header files, for example some structs
```#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

#endif
```

or use 
`pragma once`

but `pragma` is not official, just something for compiler implementer to do whatever they want to do, so each compiler is different