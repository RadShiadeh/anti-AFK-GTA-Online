#include <windows.h>
#include <iostream>
#include <random>
#include <cmath>

const char* targetWindowTitle = "Grand Theft Auto V";  // Replace with your actual target window title

void switchToTargetApplication() {
    HWND targetWindow = FindWindowA(NULL, targetWindowTitle);
    if (targetWindow != NULL) {
        ShowWindow(targetWindow, SW_RESTORE);
        SetForegroundWindow(targetWindow);
    }
    else {
        std::cout << "Target window not found." << std::endl;
    }
}

void pressKey(WORD KeyCode) {
    keybd_event(KeyCode, 0, KEYEVENTF_EXTENDEDKEY, 0);
}

void releaseKey(WORD KeyCode) {
    keybd_event(KeyCode, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void randMove() {
    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 4.0;
    double std = 2.0;

    std::normal_distribution<double> norm(mean, std);

    double randint = norm(gen);
    int r = int(randint) % 5;

    // Press key
    int i = 0;
    while (i < 1000) {
        if (r == 0) {
            pressKey('A');
        } else if (r == 1) {
            pressKey('S');
        } else if (r == 2) {
            pressKey('D');
        } else {
            pressKey('W');
        }
        i++;
    }

    // Release key
    i = 0;
    while (i < 1000) {
        if (r == 0) {
            releaseKey('A');
        } else if (r == 1) {
            releaseKey('S');
        } else if (r == 2) {
            releaseKey('D');
        } else {
            releaseKey('W');
        }
        i++;
    }
}


int main() {
    bool wiggle = true;

    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 1500.0;
    double stddv = 250.0;

    std::normal_distribution<double> norm(mean, stddv);

    while (wiggle) {
        switchToTargetApplication();
        POINT originalPosition;
        GetCursorPos(&originalPosition);
        double rand = norm(gen);

        SetCursorPos(originalPosition.x + 100, originalPosition.y + 100);
        Sleep(rand);
        SetCursorPos(originalPosition.x, originalPosition.y);
        double rand2 = norm(gen);
        Sleep(rand + rand2);
        randMove();
    }

    return 0;
}
