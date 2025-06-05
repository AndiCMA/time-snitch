#include "InputMonitor.h"
#include <windows.h>
#include <atomic>
#include <thread>

static std::atomic<int> keyCount = 0;
static std::atomic<int> clickCount = 0;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
        ++keyCount;
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN))
        ++clickCount;
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void InputMonitor::StartMonitoring() {
    std::thread([]() {
        HHOOK kHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
        HHOOK mHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, nullptr, 0);
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        UnhookWindowsHookEx(kHook);
        UnhookWindowsHookEx(mHook);
        }).detach();
}

void InputMonitor::StopMonitoring() {
    PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
}

int InputMonitor::GetKeyCount() { return keyCount; }
int InputMonitor::GetClickCount() { return clickCount; }
