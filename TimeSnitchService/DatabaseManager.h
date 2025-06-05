#pragma once
#include "AppSession.h"

class DatabaseManager {
public:
    virtual ~DatabaseManager() = default;
    virtual void LogAppSession(const AppSession& session) = 0;
    // Add more virtuals like LogInputActivity, etc.
};
