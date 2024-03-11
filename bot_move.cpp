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
    const double factor = 0.00001;

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

void callMutt() {
    int i = 0;
    while (i < 2) {
        PressKey(0x17); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        ReleaseKey(0x17);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        i++;
    }

    PressKey(0x26); // l
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ReleaseKey(0x26);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    PressKey(0x1C); //enter
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ReleaseKey(0x1C);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    int k = 0;
    while (k < 19) {
        PressKey(0x25); //k
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ReleaseKey(0x25);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        k++;
    }

    PressKey(0x1C); //enter
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ReleaseKey(0x1C);
    std::this_thread::sleep_for(std::chrono::seconds(10));

    PressKey(0x25); //k
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    ReleaseKey(0x25);
    std::this_thread::sleep_for(std::chrono::seconds(3));

    int e = 0;
    while (e < 2) {
        PressKey(0x1C); //enter
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ReleaseKey(0x1C);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    int b = 0;
    while (b < 5) {
        PressKey(0x0E); //backspace to close phone
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ReleaseKey(0x0E);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));        
    }

}

int main() {
    auto timer_start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    int muttCallCount = 0;

    while (true) {
        int sleep_timer = randGen(1, 0);
        int dx = randGen(0.0, 2.0);
        int dy = randGen(0.0, 0.01);

        PressKey(0x11); //http://www.gamespp.com/directx/directInputKeyboardScanCodes.html for codes
        std::this_thread::sleep_for(std::chrono::seconds(sleep_timer));

        ReleaseKey(0x11);
        std::this_thread::sleep_for(std::chrono::seconds(sleep_timer));

        wiggleMouse(dx, dy);


        auto timer_end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::seconds>(timer_end - timer_start);

        if (dur >= std::chrono::hours(1) && muttCallCount < 2) {
            callMutt();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            timer_start = std::chrono::high_resolution_clock::now();
            muttCallCount++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(sleep_timer));
    }

    return 0;
}
