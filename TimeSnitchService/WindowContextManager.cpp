#include "WindowContextManager.h"
#include <windows.h>

std::string GetWindowTextFromHandle(HWND hwnd) {
    char title[256];
    GetWindowTextA(hwnd, title, sizeof(title));
    return std::string(title);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    std::vector<std::string>* titles = reinterpret_cast<std::vector<std::string>*>(lParam);
    if (IsWindowVisible(hwnd)) {
        std::string title = GetWindowTextFromHandle(hwnd);
        if (!title.empty()) titles->push_back(title);
    }
    return TRUE;
}

std::vector<std::string> WindowContextManager::GetOpenWindows() {
    std::vector<std::string> result;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&result));
    return result;
}

std::string WindowContextManager::GetForegroundWindowTitle() {
    HWND hwnd = GetForegroundWindow();
    return GetWindowTextFromHandle(hwnd);
}
