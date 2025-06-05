#pragma once
#include <vector>
#include <string>

class WindowContextManager {
public:
    std::vector<std::string> GetOpenWindows();
    std::string GetForegroundWindowTitle();
};
