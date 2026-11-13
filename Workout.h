#ifndef WORKOUT_H
#define WORKOUT_H
#include <iostream>
#include <string>
#include <vector>
#include "ReadingLog.h"
#include "reading.h"

using namespace std;

class Workout
{
private:
	string activity;
	long startTime;
	long endTime;
	long activeSeconds;
	ReadingLog readings;

public:
	Workout();
	Workout(string activity, long startTime); // end time starts equal to start time

	string getActivity() const;
	long getStartTime() const;
	long getEndTime() const;
	long getDurationSeconds() const; // gets active seconds
	vector<Reading> getReadings() const;

	void setEndTime(long newEndTime);
	void addReading(Reading reading);
	void addActiveSeconds(long seconds);
	void printSummary();
};

#endif