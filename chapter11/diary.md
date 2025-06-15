# 1 function overloading
to make sure that int+int=int, float+float=float. But then has to rewrite alot of functions

we can make many functions with the same name (aslongas they works on different types) => this is called overloaded function

# 2 function overload differentiation
differentiated by (number of param, type of param), but not return type

# 3 resolution
using chapter 10 (type conversion)

# 4 delete function
# 5 default parameter
# 6 function template
```
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}
```
# 8 different types in template
cannot find any conversion bc everything is T
solution: typename T, typename U let them be independent

# 9 non-typte template parameter
just like passing another function parameter (but passed at compile time) and it kinda fixed in runtime, its not a variable
, its a constexpr
 # 10 function template in multiple files