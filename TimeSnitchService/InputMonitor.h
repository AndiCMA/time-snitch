#pragma once

class InputMonitor {
public:
    void StartMonitoring();
    void StopMonitoring();
    int GetKeyCount(); 
    int GetClickCount();
};
