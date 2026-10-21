#include <iostream>
#include "tasks.h"
#include "alert.h"
using namespace std;

void taskViewHistory(const ReadingLog& log) {
    cout << "Full history (" << log.size() << " readings):\n";
    log.print();
}

void taskStatistics(const ReadingLog& log) {
    if (log.size() == 0) {
        cout << "No readings yet.\n";
        return;
    }
    cout << "Readings: " << log.size() << "\n";
    cout << "Min BPM: " << log.minBpm() << "\n";
    cout << "Max BPM: " << log.maxBpm() << "\n";
    cout << "Average BPM: " << log.avgBpm() << "\n";
}

void taskZoneSummary(const UserProfile& user, const ReadingLog& log) {
    if (!user.hasProfile()) {
        cout << "Create a profile first (option 1).\n";
        return;
    }
    if (log.size() == 0) {
        cout << "No readings yet.\n";
        return;
    }

    // Count how many readings fall in each zone (0 to 5)
    int counts[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < log.size(); i++) {
        int zone = user.getZoneNumber(log.get(i).getBpm());
        counts[zone]++;
    }

    cout << "Max HR: " << user.getMaxHR() << "  Resting HR: " << user.getRestingHR() << "\n";
    for (int zone = 0; zone < 6; zone++) {
        cout << user.getZoneName(zone) << ": " << counts[zone] << " reading(s)\n";
    }
}

void taskAlerts(const UserProfile& user, const ReadingLog& log) {
    if (!user.hasProfile()) {
        cout << "Create a profile first (option 1).\n";
        return;
    }
    AlertSystem alerts;
    alerts.setLimits(40, 200 - user.getAge());
    alerts.printAlerts(log);
}
