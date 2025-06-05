#include "AppTrackerService.h"
#include <chrono>
#include <iostream>

AppTrackerService::AppTrackerService(DatabaseManager* db) : dbManager(db), running(false) {}

AppTrackerService::~AppTrackerService() {
    Stop();
}

void AppTrackerService::Start() {
    running = true;
    trackerThread = std::thread(&AppTrackerService::TrackingLoop, this);
}

void AppTrackerService::Stop() {
    running = false;
    if (trackerThread.joinable()) trackerThread.join();
}

void AppTrackerService::TrackingLoop() {
    inputMonitor.StartMonitoring();

    AppSession session;
    while (running) {
        bool changed = false;
        if (session.windowTitle != windowCtx.GetForegroundWindowTitle()) {
            if ( session.windowTitle != "") dbManager->LogAppSession(session);
            session.windowTitle = windowCtx.GetForegroundWindowTitle();
            std::cout << session.windowTitle << " ";
            session.startTime = std::chrono::system_clock::now();
            time(&session.startStamp);
            changed = true;
        }
        
        int startKeys = inputMonitor.GetKeyCount();
        int startClicks = inputMonitor.GetClickCount();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        int endKeys = inputMonitor.GetKeyCount();
        int endClicks = inputMonitor.GetClickCount();
        
        session.endTime = std::chrono::system_clock::now();
        session.relatedWindows = windowCtx.GetOpenWindows();
        time(&session.endStamp);

        if (changed) {
           session.keyCount = endKeys - startKeys;
           session.clickCount = endClicks - startClicks;
           std::cout << "Logged " << session.keyCount << " keys, " << session.clickCount << " clicks for " << session.windowTitle << "\n";

        }
        else {
            session.keyCount += endKeys - startKeys;
            session.clickCount += endClicks - startClicks;
            std::cout << "Updated logged " << session.keyCount << " keys, " << session.clickCount << " clicks for " << session.windowTitle << "\n";
        }
    }


    inputMonitor.StopMonitoring();
}

