#include <iostream>

int main() {
    std::cout << "enter 3 number: ";
    int x {};
    int y {};
    int z {};
    std::cin >> x >> y >>z; //each input prompt divided by an enter
    std::cout << "you entered " << x << y << z << "\n";
    return 0;
}