integer value 3 might be stored as binary 0000 0000 0000 0000 0000 0000 0000 0011, whereas floating point value 3.0 might be stored as binary 0100 0000 0100 0000 0000 0000 0000 0000.

# implicit type conversion
- initialization, assignment
- return value
- operation cong tru nhan chia
```
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double

float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}

double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
```


Some 32-bit processors (such as 32-bit x86 CPUs) can manipulate 8-bit or 16-bit values directly. However, doing so is often slower than manipulating 32-bit values! Other 32-bit CPUs (like 32-bit PowerPC CPUs), can only operate on 32-bit values, and additional tricks must be employed to manipulate narrower values.

# numeric promotion
```
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

Assuming an 8 bit byte and an int size of 4 bytes or larger (which is typical these days), the above basically means that bool, char, signed char, unsigned char, signed short, and unsigned short all get promoted to int.

# numeric conversion
these are implicit conversions
```
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int

float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double

int i = 3.5; // convert double to int

double d = 3; // convert int to double

bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

## but one case impossible
```
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```