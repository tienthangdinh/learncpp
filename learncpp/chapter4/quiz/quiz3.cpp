#include <iostream>

double getTowerHeight() {
    std::cout <<"Tower height:";
    double height {};
    std::cin >> height;
    return height;
}

void ballHeight(double height, int seconds) {
    double gravity { 9.8};
    double fallDistance { gravity * (seconds * seconds) / 2.0 };
	double ballHeight { height - fallDistance };

    if (ballHeight < 0.0) 
        std::cout << 0 << "\n";

    std::cout << ballHeight << "\n";
}

int main() {
    double towerHeight { getTowerHeight()};

    ballHeight(towerHeight, 0);
    ballHeight(towerHeight, 1);
    ballHeight(towerHeight, 2);
    ballHeight(towerHeight, 3);
    ballHeight(towerHeight, 4);
    ballHeight(towerHeight, 5);
}