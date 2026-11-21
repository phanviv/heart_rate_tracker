// Workout.cpp
// Author: Kai Hong
// Implements Workout: stores one session's activity, times, active seconds
// and readings, and prints a summary of it.

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "Workout.h"
using namespace std;

// Task: T2 Start Workout
Workout::Workout() : activity(""), startTime(0), endTime(0), activeSeconds(0)
{
}

// Task: T2 Start Workout
// end time starts equal to start time
Workout::Workout(string activity, long startTime)
	: activity(activity), startTime(startTime), endTime(startTime), activeSeconds(0)
{
}

// Task: T3 View Latest Readings
string Workout::getActivity() const
{
	return activity;
}

// Task: T3 View Latest Readings
time_t Workout::getStartTime() const
{
	return startTime;
}

// Task: T2 Start Workout
time_t Workout::getEndTime() const
{
	return endTime;
}

// Task: T5 View Workout History
long Workout::getDurationSeconds() const // gets active seconds
{
	return activeSeconds;
}

// Task: T3 View Latest Readings
vector<Reading> Workout::getReadings() const
{
	return readings.getReadings();
}

// Task: T2 Start Workout
void Workout::setEndTime(time_t newEndTime)
{
	endTime = newEndTime;
}

// Task: T2 Start Workout
void Workout::addReading(Reading reading)
{
	readings.addReading(reading);
}

// Task: T2 Start Workout
void Workout::addActiveSeconds(long seconds)
{
	activeSeconds += seconds;
}

// Task: T2 Start Workout, T5 View Workout History
// Prints the date, activity, duration (active time), and average BPM
void Workout::printSummary() const
{
	char dateText[20];
	strftime(dateText, sizeof(dateText), "%Y-%m-%d %H:%M", localtime(&startTime));

	long hours = activeSeconds / 3600;
	long minutes = (activeSeconds % 3600) / 60;
	long seconds = activeSeconds % 60;

	cout << "Date:     " << dateText << endl;
	cout << "Activity: " << activity << endl;
	cout << "Duration: ";
	if (hours > 0)
		cout << hours << "h ";
	cout << minutes << "m " << seconds << "s" << endl;

	cout << "Avg BPM:  ";
	if (readings.size() == 0)
		cout << "no readings" << endl;
	else
		cout << readings.avgBpm() << " bpm (" << readings.size() << " readings)" << endl;
}
