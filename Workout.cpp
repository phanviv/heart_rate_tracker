#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "Workout.h"
using namespace std;

Workout::Workout() : activity(""), startTime(0), endTime(0), activeSeconds(0)
{
}

// end time starts equal to start time
Workout::Workout(string activity, long startTime)
	: activity(activity), startTime(startTime), endTime(startTime), activeSeconds(0)
{
}

string Workout::getActivity() const
{
	return activity;
}

time_t Workout::getStartTime() const
{
	return startTime;
}

time_t Workout::getEndTime() const
{
	return endTime;
}

long Workout::getDurationSeconds() const // gets active seconds
{
	return activeSeconds;
}

vector<Reading> Workout::getReadings() const
{
	return readings.getReadings();
}

void Workout::setEndTime(time_t newEndTime)
{
	endTime = newEndTime;
}

void Workout::addReading(Reading reading)
{
	readings.addReading(reading);
}

void Workout::addActiveSeconds(long seconds)
{
	activeSeconds += seconds;
}

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
