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

void wiggleMouse(LONG dx, LONG dy) {
    Input_I ii;
    ii.mi = {dx, dy, 0, MOUSEEVENTF_MOVE, 0, 0};
    Input x = {INPUT_MOUSE, ii};

    LPINPUT lpInput = reinterpret_cast<LPINPUT>(&x);
    SendInput(1, lpInput, sizeof(INPUT));
}

int main() {
    while (true) {
        PressKey(0x11);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ReleaseKey(0x11);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        wiggleMouse(101, 110);
    }

    return 0;
}
