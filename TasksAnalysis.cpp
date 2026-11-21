// TaskAnalysis.cpp
// Author: Vivian Phan
// Implements the menu tasks that only read and report on the saved data:
// T5 View Workout History, T6 Statistics, T7 Heart Rate Zones, T8 Alerts.

#include "tasks.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// ---------- Helpers ----------

// Task: T6 Statistics, T7 Heart Rate Zones, T8 Alerts
// Adds every reading of a workout to a log.
static void appendReadings(ReadingLog &log, const Workout &workout)
{
	vector<Reading> readings = workout.getReadings();
	for (size_t i = 0; i < readings.size(); i++)
		log.addReading(readings[i]);
}

// Task: T6 Statistics, T7 Heart Rate Zones, T8 Alerts
// Every reading from every workout of a profile, in order.
static ReadingLog allReadings(const UserProfile &profile)
{
	ReadingLog log;
	vector<Workout> workouts = profile.getWorkouts();
	for (size_t i = 0; i < workouts.size(); i++)
		appendReadings(log, workouts[i]);
	return log;
}

// Task: T6 Statistics
static void printStats(const string &title, const ReadingLog &log)
{
	cout << title << endl;
	if (log.size() == 0)
	{
		cout << "  No readings." << endl;
		return;
	}
	cout << "  Readings: " << log.size() << endl;
	cout << "  Minimum:  " << log.minBpm() << " bpm" << endl;
	cout << "  Maximum:  " << log.maxBpm() << " bpm" << endl;
	cout << "  Average:  " << log.avgBpm() << " bpm" << endl;
}

// ---------- Task 5: workout history ----------

// Task: T5 View Workout History
void taskViewHistory(ProfileManager &profiles)
{
	if (!requireProfile(profiles))
		return;

	UserProfile &profile = profiles.getCurrent();
	vector<Workout> workouts = profile.getWorkouts();
	if (workouts.empty())
	{
		cout << "No workouts yet for " << profile.getName() << "." << endl;
		return;
	}

	cout << "Workout history for " << profile.getName() << " ("
		 << workouts.size() << " workout(s)):" << endl;
	for (size_t i = 0; i < workouts.size(); i++)
	{
		cout << endl
			 << "Workout " << (i + 1) << endl;
		workouts[i].printSummary();
	}
}

// ---------- Task 6: statistics ----------

// Task: T6 Statistics
void taskStatistics(ProfileManager &profiles)
{
	if (!requireProfile(profiles))
		return;

	UserProfile &profile = profiles.getCurrent();
	if (!profile.hasWorkouts())
	{
		cout << "No workouts yet for " << profile.getName() << "." << endl;
		return;
	}

	ReadingLog latestLog;
	appendReadings(latestLog, profile.getLatestWorkout());

	printStats("Latest workout:", latestLog);
	cout << endl;
	printStats("All workouts:", allReadings(profile));
}

// ---------- Task 7: heart rate zones ----------

// Task: T7 Heart Rate Zones
void taskZoneSummary(ProfileManager &profiles)
{
	if (!requireProfile(profiles))
		return;

	UserProfile &profile = profiles.getCurrent();
	vector<Reading> readings = allReadings(profile).getReadings();
	if (readings.empty())
	{
		cout << "No readings yet for " << profile.getName() << "." << endl;
		return;
	}

	const int ZONES = 7; // zones 0 to 6
	int counts[ZONES] = {0, 0, 0, 0, 0, 0, 0};
	for (size_t i = 0; i < readings.size(); i++)
	{
		int zone = profile.getZoneNumber(readings[i].getBPM());
		if (zone >= 0 && zone < ZONES)
			counts[zone]++;
	}

	cout << "Time in each heart rate zone for " << profile.getName()
		 << " (max HR " << profile.getMaxHR() << " bpm):" << endl;
	cout << fixed << setprecision(1);
	for (int zone = 0; zone < ZONES; zone++)
	{
		double percent = 100.0 * counts[zone] / readings.size();
		cout << "  Zone " << zone << " " << profile.getZoneName(zone) << ": "
			 << counts[zone] << " reading(s), " << percent << "%" << endl;
	}
	cout << "Total: " << readings.size() << " readings." << endl;
	cout.unsetf(ios::floatfield);
}

// ---------- Task 8: alerts ----------

// Task: T8 Alerts
void taskAlerts(ProfileManager &profiles, AlertSystem &alerts)
{
	if (!requireProfile(profiles))
		return;

	UserProfile &profile = profiles.getCurrent();
	if (!profile.hasWorkouts())
	{
		cout << "No workouts yet for " << profile.getName() << "." << endl;
		return;
	}

	alerts.setLimitsFor(profile, 0); // 0 = use the profile's max HR as the high limit
	alerts.printAlerts(allReadings(profile));
}