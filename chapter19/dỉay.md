# 1 dynamic memory allocation with new and delete
again, 3 types of memory allocation:
- static global var for the whole program
- automatic, for local var on memory stack
- now dynamic mem allocation

- both static and automatic has 2 similarities: size fixed, and allocated and deleted automatically
- AND sometimes we do not know these in compile time
- Solution: use HEAP!! much larger than STACK
```
new int; //this way to allocate
new *ptr {new int} //or allocate a pointer like this
*ptr = 7; //dereference to assign value
delete prt;
ptr = nullptr; //this is safer
```
- to get the dynamically allocated memory, it takes longer, because it has t use the pointer to get address first, then go to that address to get the actual object

## how does dynamic allocation work?
- stack var we do not need to care about memory
- but dynamic var we need to define mem address
- therefore use `new *ptr {new int (5)}`

## null pointer is pretty safe
```
new *ptr;
delete ptr;
```

# memory leak
when we forget to delete pointer => less freespace => slower computer

# 2 dynamically allocate array
- the length can be defined in runtime
```
#include <array>
#include <iostream>
int main() {
    std::size_t length {}
    std::cout << "Please define array length";
    std::cin >> length;
    int* array {new int[length] };
    array[0] = 5;
    delete[] array;
    return 0;
}
```
- `new[]` and `delete[]`for arrays

# 3 destructor
- when go out of scope, delete => `delete` constructor will do the cleanup
```
#include <iostream>
#include <array>
class InArray {
    private:
        int* m_array {}
    public:
        InArray(int length) {
            m_array = new int[static_cast<std::size_t>length]{};
        }    
        ~InArray {
            delete[] m_array;
        }
}
int main() {
    int length
    std::cout << "Give a length please";
    std::cin >> length;
    InArray arr(length);
    return 0;
}
```

# 5 void pointer
- aka a generic pointer - can point to any type
```
int main() {
    int nValue {};
    float fValue {};

    void* ptr {};
    ptr = &nValue; //legal

    //now dereference we need to convert
    int* inptr {static_cast<int*>(ptr)};
    *inptr = 5;
}
```
