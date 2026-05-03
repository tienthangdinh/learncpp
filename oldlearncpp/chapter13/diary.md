# 1 program-defined types
- enumerate
- class
```
struct Fraction {
    int numerator {};
    inz denominator {};
};
```

# 2 enumeration
compound data type that contaisn a set of symbolic constants
```
enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}
```
# 3 unscoped enumeration integral
each enumerator has an integer value (automatically associated with an integer value based on its position in the enumerator list.)

# 4,5 conversion enumeration <=> string
Overloading operator<< to print an enumerator 


# 6 scope enumeration
- won’t implicitly convert to integers
- enumerators are only placed into the scope region of the enumeration
```
enum class Color {
    red,
    blue
};
std::cout << Color::red << '\n'; 
```

# 7 struct
```
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

# 10 passing & returning structs
- mostly passed by reference
```
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };
    printEmployee(joe);
    std::cout << '\n';
    printEmployee(frank);
    return 0;
}
```
- passing a temporary variable
```
 printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter)
```
- returning a struct
```
#include <iostream>

struct Point3d
{
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3d getZeroPoint()
{
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}

int main()
{
    Point3d zero{ getZeroPoint() };
    return 0;
}
```

# 12 pointer & selection
`ptr->id` is equivalent to `(*ptr).id`
```
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers
    std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection
    std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    return 0;
}
```
## Chaining
```
    Triangle tr { &a, &b, &c };
    Triangle* ptr {&tr};

    // ptr is a pointer to a Triangle, which contains members that are pointers to a Point
    // To access member y of Point c of the Triangle pointed to by ptr, the following are equivalent:

    // access via operator.
    std::cout << (*(*ptr).c).y << '\n'; // ugly!

    // access via operator->
    std::cout << ptr -> c -> y << '\n'; // much nicer
```

# 13 class template
```
#include <iostream>

// a single function template for max
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(5, 6);  
    std::cout << max(1.2, 3.4); 
    return 0;
}
```
- aggregate types like struct
```
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };  
    std::cout << max<int>(p1) << " is larger\n"; 
    Pair<double> p2{ 1.2, 3.4 }; 
    Pair<double> p3{ 7.8, 9.0 }; 
    return 0;
}
```

# 15 alias template
```
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
void print(const Pair<T>& p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    using Point = Pair<int>; // create normal type alias
    Point p { 1, 2 };        // compiler replaces this with Pair<int>
    return 0;
}
```