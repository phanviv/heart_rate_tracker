#ifndef WORKOUT_H
#define WORKOUT_H
#include <iostream>
#include <vector>

int add(int a, int b);

int main()
{
	int result = add(2, 3);
	return 0;
}

using namespace std;

class Workout
{
private:
	string activity;
	long startTime;
	long endTime;
	long activeSeconds;
	// TODO ReadingLog readings;

public:
	string getActivity();
	long getStartTime();
	long getEndTime();
	long getDurationSeconds(); // gets active seconds
	// TODO vector<Reading> getReadings();

	void addActiveSeconds(long seconds);
	void printSummary();
};

#endif