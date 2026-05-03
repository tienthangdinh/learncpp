# 4.1 data types
## bit, bytes, memory addressing
there is no bit address, computer only works with byte for each address

a.k.a byte sized chunks of data

- float, double, long double
- short int, int, long int, long long int
- std::nullpter_t
- bool
- char, wchar_t, char8_t, char16_t, char32_t
- void

# 4.3 object sizes
C++ does not define exact size of any fundamental types, each assembler language defines it differently (CPU family aka ISA)
| bool     | 1 byte = 8 bit |
| :---        |    :----:   |  
| char      | 1 byte       | 
| wchar_t   | 2-4 bytes        | 
| char16_t      | 2 bytes | 
| short (int)        |    2 bytes   |  
| int      | 4 bytes       | 
| long (int)   | 4-8 bytes        | 
| long long      | 8 bytes | 
| float        |    4 bytes = 32 bits  |  
| double      | 8 bytes = 64 bits       | 
| long double   | 8, 12, 16 bytes        | 

## sizeof(float), sizeof(long double)
returns the size, and that value actually in type of `std::size_t`, which is an alias of unsigned integer, or typedef

# 4.5 Signed integers
actually all we knows are signed:
- short = signed short
- int = signed int
- long = signed long
(signed) is an optional syntax

signed = 1/2 unsigned we know

if no sign provided, positive is assumed

# Please avoid unsigned integers
`unsigned int i;` only for networking system and bit manipulation
unsigned works like modulo of a list length
- -1 is 65535
- 65536 + 1 = 0

# 4.6 fixed-width integers & size_t
what if same type but on each ISA different size?

but why isnt fixed?: compiler picks the one works best on the computer architecture => programmer no need to worry

## fixed width
```
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int32_t x { 32767 }; // x is always a 32-bit integer
    x = x + 1;                // so 32768 will always fit
    std::cout << x << '\n';

    return 0;
}
```
but will not always work on all ISA

# 4.7 scientific notation
- 1.2 x 10⁴ would be written as 1.2e4
- 5e-2 is equivalent to 5 * 10⁻²

# 4.8 floating point numbers
the decimal point can float => variable
- `float c { 5.0f};` this is float (with suffix f)
- `double c{ 5.0 };` this is double (without suffix f)

# 5.9 boolean is actually integer
if (x) means “if x is non-zero/non-empty”.

# 5.11 char
ASCII code
```
char ch { 5 };
char ch { "5" };
```
but when input then the input will taken from buffer std::cin one by one, because char is just 1 character

```
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
- Escape sequence `\` for `\n, \t`,...
- single quotes for char
- double quote for string

# 5.12 type conversion & static_cast
how to convert int to double?
type conversion will create totally new value (using direct initialization and point the variable to it)
`static_cast<new_type>(expression)`
everthing inside <> is usually a type