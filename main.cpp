#include <iostream>
#include "Tasks.h"
using namespace std;

int main()
{
    // the four shared objects (see tasks.h for what the names mean)
    ProfileManager pm;       // all profiles
    FileManager fm;          // saves/loads files
    HeartRateSensor sensor;  // simulated sensor
    AlertSystem alerts;      // checks for unsafe readings

    fm.load(pm);                              // load everything at start-up
    recoverWorkout(pm, fm, sensor, alerts);   // offer to recover an unfinished workout (if any)

    int choice = -1;
    while (choice != 0)   // keep showing the menu until the user picks 0
    {
        cout << endl << "=== Heart Rate Tracker ===" << endl;
        if (pm.hasCurrent()) cout << "Signed in as: " << pm.getCurrent().getName() << endl;
        else cout << "Not signed in" << endl;
        cout << "1. Manage profiles" << endl;
        cout << "2. Start workout" << endl;
        cout << "3. View latest readings" << endl;
        cout << "4. Load data" << endl;
        cout << "5. View workout history" << endl;
        cout << "6. Statistics" << endl;
        cout << "7. Heart rate zones" << endl;
        cout << "8. Alerts" << endl;
        cout << "0. Exit" << endl;
        choice = readInt("Choice: ", 0, 8);   // only accepts a number from 0 to 8

        // options 2, 3 and 5-8 need a signed-in profile
        bool needsProfile = (choice >= 2 && choice <= 3) || (choice >= 5 && choice <= 8);
        if (needsProfile && !pm.hasCurrent())
        {
            cout << "Please sign in first (option 1)." << endl;
            continue;   // go back to the top of the loop (show the menu again)
        }

        // one case per menu option, each calls one task function
        switch (choice)
        {
            case 1: taskManageProfiles(pm, fm, sensor); break;
            case 2: taskRunWorkout(pm, fm, sensor, alerts); break;
            case 3: taskViewLatest(pm); break;
            case 4: taskLoad(pm, fm, sensor); break;
            case 5: taskViewHistory(pm); break;
            case 6: taskStatistics(pm); break;
            case 7: taskZoneSummary(pm); break;
            case 8: taskAlerts(pm, alerts); break;
            case 0: cout << "Goodbye!" << endl; break;
        }
    }
    return 0;  
}