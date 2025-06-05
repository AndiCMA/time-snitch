#pragma once
#include <thread>
#include <atomic>
#include "DatabaseManager.h"
#include "WindowContextManager.h"
#include "InputMonitor.h"
#include "AppSession.h"
#include <chrono>


class AppTrackerService {
public:
    AppTrackerService(DatabaseManager* db);
    ~AppTrackerService();

    void Start();
    void Stop();

private:
    std::thread trackerThread;
    std::atomic<bool> running;
    DatabaseManager* dbManager;
    WindowContextManager windowCtx;
    InputMonitor inputMonitor;

    void TrackingLoop();
};
