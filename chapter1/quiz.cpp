#include <iostream>

int main() {
    std::cout << "please add first number";
    int first {};
    std::cin >> first;
    std::cout << "please add second number";
    int second {};
    std::cin >> second;
    std::cout << first + second << "\n";
    return 0;
}