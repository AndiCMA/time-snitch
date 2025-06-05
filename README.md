-----------------------TimeSnitch-----------------------
TimeSnitch is a lightweight Windows application that tracks active window usage, input activity, and context changes in real time. It logs this information to a local SQLite database for analysis.

-----------------------Features-----------------------
Tracks the currently focused window

Detects changes in window focus and logs new sessions

Captures keystroke and mouse click counts per session

Collects window context (list of visible windows)

Stores session data in a local SQLite file

Measures session duration and input performance (KPM, CPM)

-----------------------Components-----------------------
AppTrackerService: Runs the tracking loop, monitors window changes, and gathers input data

InputMonitor: Hooks into the system to count real keyboard and mouse input

WindowContextManager: Gets the foreground window title and visible windows

SQLiteDatabaseManager: Manages session storage and schema creation

-----------------------Logged Fields-----------------------
Each session saved to the database includes:

windowTitle

seconds

startTime, endTime (raw timestamps)

startStamp, endStamp (epoch-based time_t)

keyCount, clickCount

kpm, cpm

relatedWindows (joined by ; )

-----------------------Requirements-----------------------
Windows OS

Visual Studio with C++17

SQLite3 (compiled from amalgamation or installed via vcpkg)

-----------------------Usage-----------------------
Build the project using Visual Studio

Run the executable

Console will show real-time session logs

Check AppSessions table in timesnitch_db.db for full logs

