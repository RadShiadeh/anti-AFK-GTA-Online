#include <windows.h>
#include <iostream>
#include <random>
#include <cmath>

int main() {
    bool wiggle = true;

    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 1500.0;
    double stddv = 250.0;

    std::normal_distribution<double> norm(mean, stddv);

    while (wiggle) {
        POINT originalPosition;
        GetCursorPos(&originalPosition);
        double rand = norm(gen);

        SetCursorPos(originalPosition.x + 100, originalPosition.y + 100);
        Sleep(rand);
        SetCursorPos(originalPosition.x, originalPosition.y);
        double rand2 = norm(gen);
        Sleep(rand + rand2);
    }

    return 0;
}
