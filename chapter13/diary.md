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


# scope enumeration
- won’t implicitly convert to integers
- enumerators are only placed into the scope region of the enumeration
```
enum class Color {
    red,
    blue
};
std::cout << Color::red << '\n'; 
```