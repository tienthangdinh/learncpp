# 1 something new function pointer
```
int foo() {
    return 5;
}
int goo(int a) {
    return a;
}
int main() {
    int (*fncPtr)() {&foo}; //assign function pointer
    fncPtr = &goo;

    (*fncPtr)(5); //call function
}
```

## goal: passing callback function
```
void selectionSort(int* array, bool (*comparisonFnc)(int, int)) {...}

//or this is also correct

void selectionSort(int* array, int size, bool comparisonFcn(int, int)) {...}
```

## using std::function for function pointers
```
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> foo);
```

```
#include <functional>
int foo() { return 5; }
int main() {
    std::function<int()> fncPtr{ &foo };
}
```
