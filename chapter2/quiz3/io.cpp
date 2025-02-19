#include "io.h" //actually this line is totally no need, but its a good practice for us developer to know they are related and to force us to implement their declarations, so that if anything changes, compile error for us to know
// it forces us to fix any change before linking, compile will error immediately
#include <iostream>

int readNumber()
{
    std::cout << "Enter a number to add: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x, int y)
{
    std::cout << "The answer is " << x+y << '\n';
}