#pragma once
#include "DatabaseManager.h"

class SQLiteDatabaseManager : public DatabaseManager {
public:
    SQLiteDatabaseManager(const std::string& dbPath);
    ~SQLiteDatabaseManager();

    void LogAppSession(const AppSession& session) override;

private:
    void InitDB();
    // Add sqlite3* and helpers
};
