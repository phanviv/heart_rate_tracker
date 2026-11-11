#ifndef WORKOUT_H
#define WORKOUT_H
#include <iostream>
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
	string getActivity();
	long getStartTime();
	long getEndTime();
	long getDurationSeconds(); // gets active seconds
	vector<Reading> getReadings();

	void addActiveSeconds(long seconds);
	void printSummary();
};

#endif