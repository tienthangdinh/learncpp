#include <iomanip>
#include <iostream>
#include <climits>

int main() {
    std::cout << "A byte is" << CHAR_BIT << " bits\n\n";

    std::cout << std::left;

    std::cout << std::setw(16) << "long double" << sizeof(long double) << "bytes\n";
    std::cout << "double" << sizeof(double) << "bytes\n";
    std::cout << "float" << sizeof(float) << "bytes\n";
    std::cout << "void" << sizeof(void) << "bytes\n";
}
