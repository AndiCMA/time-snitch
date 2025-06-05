#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <ctime>

struct AppSession {
    std::string windowTitle = "";
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point endTime;
    time_t startStamp = time(nullptr);
    time_t endStamp;
    std::vector<std::string> relatedWindows;
    int keyCount = 0;
    int clickCount = 0;

    int getSeconds() const {
        return std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    }

    int getKpm() const {
        int s = getSeconds();
        return s ? (keyCount * 60 / s) : 0;
    }

    int getCpm() const {
        int s = getSeconds();
        return s ? (clickCount * 60 / s) : 0;
    }
};
