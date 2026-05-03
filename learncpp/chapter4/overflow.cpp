#include <iostream>

int main() {
    int x {2'147'483'647 }; //4 bytes = 32 bits
    std::cout << x << "\n";
    x+=1;
    std::cout << x << "\n";
}