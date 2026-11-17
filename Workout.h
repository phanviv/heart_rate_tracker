#ifndef WORKOUT_H
#define WORKOUT_H
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "ReadingLog.h"
#include "Reading.h"

using namespace std;

class Workout
{
private:
	string activity;
	time_t startTime;
	time_t endTime;
	long activeSeconds;
	ReadingLog readings;

public:
	Workout();
	Workout(string activity, long startTime); // end time starts equal to start time

	string getActivity() const;
	time_t getStartTime() const;
	time_t getEndTime() const;
	long getDurationSeconds() const; // gets active seconds
	vector<Reading> getReadings() const;

	void setEndTime(time_t newEndTime);
	void addReading(Reading reading);
	void addActiveSeconds(long seconds);
	void printSummary() const;
};

#endif