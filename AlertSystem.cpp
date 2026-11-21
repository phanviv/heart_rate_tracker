// AlertSystem.cpp
// Author: Kai Hong
// Implements AlertSystem: sets BPM alert limits for a profile, checks single
// readings during a workout, and lists every alert in a reading log.

#include "AlertSystem.h"
#include <ctime>
#include <iostream>
using namespace std;

// TODO: remove this once Settings exists and setLimitsFor() reads from it
const int DEFAULT_LOW_LIMIT = 40;

// Task: T2 Start Workout, T8 Alerts
// Sets the alert limits for this profile. A maxHR of 0 (the "max" setting)
// means the high limit is the user's own max HR (220 - age).
void AlertSystem::setLimitsFor(const UserProfile &userProfile, int maxHR)
{
	// TODO: take the low limit from userProfile.getSettings().getAlertLow()
	lowLimit = DEFAULT_LOW_LIMIT;

	if (maxHR > 0)
		highLimit = maxHR;
	else
		highLimit = userProfile.getMaxHR();
}

// Task: T2 Start Workout, T8 Alerts
// True when the reading is below the low limit or above the high limit
bool AlertSystem::isAlert(Reading reading) const
{
	int bpm = reading.getBPM();
	return bpm < lowLimit || bpm > highLimit;
}

// Task: T8 Alerts
// Lists every reading in the log that is outside the limits
void AlertSystem::printAlerts(const ReadingLog &readingLog) const
{
	cout << "Alert limits: " << lowLimit << " - " << highLimit << " bpm" << endl;

	int alertCount = 0;
	for (int i = 0; i < readingLog.size(); i++)
	{
		Reading reading = readingLog.get(i);
		if (!isAlert(reading))
			continue;

		time_t timestamp = reading.getTimestamp();
		char timeText[20];
		strftime(timeText, sizeof(timeText), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));

		int bpm = reading.getBPM();
		cout << timeText << "  " << bpm << " bpm  ";
		if (bpm < lowLimit)
			cout << "LOW (below " << lowLimit << ")" << endl;
		else
			cout << "HIGH (above " << highLimit << ")" << endl;

		alertCount++;
	}

	if (alertCount == 0)
		cout << "No alerts." << endl;
	else
		cout << alertCount << " alert(s) out of " << readingLog.size() << " readings." << endl;
}
