#include <iostream>

int main() {
    std::cout <<"Please insert a character: ";
    char c{};
    std::cin >> c; //cout >> cin >> c
    std::cout << "ASCII code:" << static_cast<int>(c) << "\n";

}