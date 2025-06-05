#include "AppTrackerService.h"
#include "SQLiteDatabaseManager.h"
#include <iostream>

int main() {
    SQLiteDatabaseManager db("timesnitch_db.db");
    AppTrackerService service(&db);

    std::cout << "[TimeSnitch] Starting tracking...\n";
    service.Start();

    std::cout << "[TimeSnitch] Press Enter to stop.\n";
    std::cin.get();

    service.Stop();
    std::cout << "[TimeSnitch] Stopped.\n";
    return 0;
}
