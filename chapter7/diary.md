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

# inline expansion
avoid overhead but
- cause the stack for the mother function to grow too big on memory caches
```
inline int min(int x, int y) {
    return (x < y) ? x : y;
}
```
