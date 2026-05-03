# 7.2 defining own namespace

```
namespace Foo {
    int doSomething(int x, int y)
    {
        return x + y;
    }
}

int main() {
    int result = Foo::doSOmething(4, 3);
}
```

# 7.3 7.4 local & global variables
global variables is created before main() function (a.k.a. static duration)

# 7.5 variable shadowing (name hiding)
when a nested black has variable with the same name with outer block variable => overwriting
but please avoid it
```
#include <iostream>
int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}

int main()
{
    int value { 7 }; // hides the global variable value (wherever local variable value is in scope)

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    return 0;
} // local value is destroyed
```

# 7.6 internal linkage
decide if this variable accessible from other files or not
- internal: add `const`or `static`
- otherwise all non-constant global are external linkage

# 7.7 external linkage
- functions always external
- global variables always external
- use `extern`

## inline expansion
avoid overhead but
- cause the stack for the mother function to grow too big on memory caches
```
inline int min(int x, int y) {
    return (x < y) ? x : y;
}
```
- inline means: multiple definitions allowed

# 7.8 global constants
## global constants as internal variables
- create a header file to hold all constants
- inside this header file, define a namespace
- add all constant inside namespace
- add this header file

=> thi sis standard way, but rechange one header file need recompile every files
## global constants as external variables
- so that only need to recompile one file when 1 variable changes
## now add inline into .h
- it works as the first option again, recompile everything

# 7.11 static local variables
- static global easy, but how about local?
- duration: created at the start of the program, destroyed at the end => still retain value even after out of scope
=> use case: when one function called many time
=> still keep the state from the last funciton call (remembering)
- it is less expensive than global variable

# 7.12 scopr, duration, linkage
## scope
- block
- global
## duration
- automatic (local variables, function parameters)
- static (every where, never changes)
- dynamic (when called by programmer)
## linkage
whether a declaration of that same identifier in the different scope refers to the same entity
- no linkage: unique entity
- internal linkage: only in the same object or function
- external linkage: entire program

## forward declaration
to access a function or variable in another file

# 7.13 "using"
```
int main()
{
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // using namespace Foo expires

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // using namespace Goo expires

    return 0;
}
```
