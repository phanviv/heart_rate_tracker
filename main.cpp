#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tasks.h"
using namespace std;

void printMenu() {
    cout << "\n=== Heart Rate Tracker ===\n"
         << "1. Create profile\n"
         << "2. Start workout\n"
         << "3. View latest readings\n"
         << "4. Save data\n"
         << "5. Load data\n"
         << "6. View full history\n"
         << "7. Statistics\n"
         << "8. Heart rate zones\n"
         << "9. Alerts\n"
         << "0. Exit\n"
         << "Choice: ";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    UserProfile user;
    HeartRateSensor sensor;
    ReadingLog log;
    int choice;

    do {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1: taskCreateProfile(user); break;
            case 2: taskRunWorkout(sensor, log); break;
            case 3: taskViewLatest(log); break;
            case 4: taskSave(user, log); break;
            case 5: taskLoad(user, log); break;
            case 6: taskViewHistory(log); break;
            case 7: taskStatistics(log); break;
            case 8: taskZoneSummary(user, log); break;
            case 9: taskAlerts(log); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    return 0;
}
