#include <iostream>

int main() {
    double zero { 0.0 };
    std::cout << -5.0 / zero << "\n";
    std::cout << -0.0f / zero << "\n";
    std::cout << -0.0 / 0.0 << "\n";
}