#include <cstdlib>
#include "sensor.h"
#include <string>
#include <iostream>
using namespace std;

HeartRateSensor::HeartRateSensor()
{
	running = false;
	activity = "";
	timeSec = 0;
}

void HeartRateSensor::start(string activity)
{
	cout << "Not implemented yet" << endl;
}

void HeartRateSensor::stop()
{
	cout << "Not implemented yet" << endl;
}

bool HeartRateSensor::isRunning() const
{
	cout << "Not implemented yet" << endl;
	return false;
}

// Makes a fake BPM value based on the activity
Reading HeartRateSensor::takeReading()
{
	cout << "Not implemented yet" << endl;
	return Reading();
}

const ReadingLog &HeartRateSensor::getReadings() const
{
	cout << "Not implemented yet" << endl;
	return readings;
}

double HeartRateSensor::getAverageBPM() const
{
	cout << "Not implemented yet" << endl;
	return 0;
}

// Average of readings taken in the last "seconds" seconds
double HeartRateSensor::getRecentAverageBPMFrom(float seconds) const
{
	cout << "Not implemented yet" << endl;
	return 0;
}

// Average of the last n readings
double HeartRateSensor::getLastAverageBPM(int numberOfRecentReadings) const
{
	cout << "Not implemented yet" << endl;
	return 0;
}
