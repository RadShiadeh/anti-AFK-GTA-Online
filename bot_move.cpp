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

void randMove(USHORT keyCodeA, USHORT keyCodeS, USHORT keyCodeD, USHORT keyCodeW) {
    std::random_device rd;
    std::mt19937 gen(rd());

    double mean = 4.0;
    double std = 2.0;

    std::normal_distribution<double> norm(mean, std);
    double r = norm(gen);

    int randint = int(r) % 5;

    if (randint == 0) {
        PressKey(keyCodeA);
    } else if (randint == 1) {
        PressKey(keyCodeS);
    } else if (randint == 2) {
        PressKey(keyCodeD);
    } else {
        PressKey(keyCodeW);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    ReleaseKey(keyCodeA);
    ReleaseKey(keyCodeS);
    ReleaseKey(keyCodeD);
    ReleaseKey(keyCodeW);

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    while (true) {
        randMove(0x41, 0x53, 0x44, 0x11);
    }

    return 0;
}
