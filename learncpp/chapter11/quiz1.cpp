#include <iostream>

void print(int x) {
    std::cout << "int" << x << "\n";
}

void print(double x) {
    std::cout << "double" << x << "\n";
}

int main() {
    short s {5};
    print(s);
    return 0;
}
