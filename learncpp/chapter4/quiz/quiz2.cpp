#include <iostream>

double getDouble() {
    std::cout << "first input:";
    double first {};
    std::cin >> first;
    return first;
}

char getOperator() {
    std::cout << "operation:";
    char operation {};
    std::cin >> operation;
    return operation;
}

void printResult(double first, double second, char operation) {
    double result {};
    if (operation == '+')
        result = first + second;
    else if (operation == '*')
        result = first * second;
    else
        return;
    std::cout << result << "\n";
}

int main() {

    double first { getDouble()};
    double second { getDouble()};
    char operation { getOperator()};
    printResult(first, second, operation);
    
}