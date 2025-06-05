#include "SQLiteDatabaseManager.h"
#include <sqlite3.h>
#include <iostream>

static sqlite3* db = nullptr;

SQLiteDatabaseManager::SQLiteDatabaseManager(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Failed to open DB\n";
    }
    else {
        InitDB();
    }
}

SQLiteDatabaseManager::~SQLiteDatabaseManager() {
    if (db) sqlite3_close(db);
}

void SQLiteDatabaseManager::InitDB() {
    const char* createTable = R"(
        CREATE TABLE IF NOT EXISTS AppSessions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            windowTitle TEXT,
            seconds INTEGER,
            startTime TEXT,
            endTime TEXT,
            startStamp TEXT,
            endStamp TEXT,
            keyCount INTEGER,
            clickCount INTEGER,
            kpm INTEGER,
            cpm INTEGER,
            relatedWindows TEXT
        );
    )";
    sqlite3_exec(db, createTable, nullptr, nullptr, nullptr);
}

void SQLiteDatabaseManager::LogAppSession(const AppSession& session) {
    std::string sql = "INSERT INTO AppSessions (windowTitle, seconds, startTime, endTime, startStamp, endStamp, keyCount, clickCount, kpm, cpm, relatedWindows) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    std::string windows = [&]() {
        std::string out;
        for (const auto& wnd : session.relatedWindows) out += wnd + "; ";
        return out;
        }();
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, session.windowTitle.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, session.getSeconds());
        sqlite3_bind_text(stmt, 3, std::to_string(session.startTime.time_since_epoch().count()).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, std::to_string(session.endTime.time_since_epoch().count()).c_str(), -1, SQLITE_TRANSIENT); 
        sqlite3_bind_text(stmt, 5, std::to_string(session.startStamp).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, std::to_string(session.endStamp).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 7, session.keyCount);
        sqlite3_bind_int(stmt, 8, session.clickCount);
        sqlite3_bind_int(stmt, 9, session.getKpm());
        sqlite3_bind_int(stmt, 10, session.getCpm());
        sqlite3_bind_text(stmt, 11, windows.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
}
