#include <windows.h>
#include <iostream>
#include <random>
#include <cmath>
#include <thread>

typedef struct tagKeyBdInput {
    USHORT wVk;
    USHORT wScan;
    ULONG dwFlags;
    ULONG time;
    ULONG_PTR dwExtraInfo;
} KeyBdInput, *PKeyBdInput, *LPKeyBdInput;

typedef struct tagHardwareInput {
    ULONG uMsg;
    SHORT wParamL;
    USHORT wParamH;
} HardwareInput, *PHardwareInput, *LPHardwareInput;

typedef struct tagMouseInput {
    LONG dx;
    LONG dy;
    ULONG mouseData;
    ULONG dwFlags;
    ULONG time;
    ULONG_PTR dwExtraInfo;
} MouseInput, *PMouseInput, *LPMouseInput;

typedef union tagInput_I {
    KeyBdInput ki;
    MouseInput mi;
    HardwareInput hi;
} Input_I, *PInput_I, *LPInput_I;

typedef struct tagInput {
    ULONG type;
    Input_I ii;
} Input, *PInput, *LPInput;

void PressKey(USHORT hexKeyCode) {
    ULONG_PTR extra = 0;
    Input_I ii;
    ii.ki = {0, hexKeyCode, 0x0008, 0, extra};
    Input x = {INPUT_KEYBOARD, ii};
    
    LPINPUT lpInput = reinterpret_cast<LPINPUT>(&x);
    SendInput(1, lpInput, sizeof(INPUT));
}

void ReleaseKey(USHORT hexKeyCode) {
    ULONG_PTR extra = 0;
    Input_I ii;
    ii.ki = {0, hexKeyCode, 0x0008 | 0x0002, 0, extra};
    Input x = {INPUT_KEYBOARD, ii};
    
    LPINPUT lpInput = reinterpret_cast<LPINPUT>(&x);
    SendInput(1, lpInput, sizeof(INPUT));
}

int randGen(double mean, double std) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<double> norm(mean, std);

    double randint = norm(gen);

    return int(randint);
}

void wiggleMouse(LONG dx, LONG dy) {
    const int steps = 1000;
    const double factor = 0.005;

    for (int i = 1; i <= steps; i++) {
        double t = static_cast<double>(i) / steps;
        double ease = pow(t, factor);

        LONG easedDx = static_cast<LONG>(dx * ease);
        LONG easedDy = static_cast<LONG>(dy * ease);

        Input_I ii;
        ii.mi = {easedDx, easedDy, 0, MOUSEEVENTF_MOVE, 0, 0};
        Input x = {INPUT_MOUSE, ii};
        LPINPUT lpInput = reinterpret_cast<LPINPUT>(&x);
        SendInput(1, lpInput, sizeof(INPUT));
    }
}

int main() {
    while (true) {
        int sleep_timer = randGen(1, 0);
        int dx = randGen(0.0, 5.0);
        int dy = randGen(0.0, 1);
        PressKey(0x11);
        std::this_thread::sleep_for(std::chrono::seconds(sleep_timer));
        ReleaseKey(0x11);
        std::this_thread::sleep_for(std::chrono::seconds(sleep_timer));
        wiggleMouse(dx, dy);
    }

    return 0;
}
