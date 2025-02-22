#include <iostream>

std::string_view getQuantityPhrase(int num) {
    if (num < 0) {
        return "negative";
    }
    if (num == 0) {
        return "no";
    }
    if (num == 1) {
        return "a single";
    } else {
        return "many";
    }
}

std::string_view getApplesPluralized(int num) {
    return (num == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}