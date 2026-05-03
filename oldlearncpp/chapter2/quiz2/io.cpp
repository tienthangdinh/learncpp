#include <iostream>

int readNumber() {
    std::cout << "Please input number: ";
    int var {};
    std::cin >> var;
    return var;
}

void writeAnswer(int x, int y) {
    std::cout << "The answer is" << x + y << "\n";
}