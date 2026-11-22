// Reading.cpp
// Author: Vivian Phan
// Implements Reading: stores one heart rate reading's time and BPM, and
// prints it.

#include "Reading.h"
#include <iostream>
using namespace std;

// Task: T2 Start Workout, T4 Load Data
// Constructor: saves the time and bpm when a Reading is created
Reading::Reading(long timestamp, int bpm) : timestamp(timestamp), bpm(bpm)
{
}

// Task: T2 Start Workout, T10 Startup Recovery
// Returns the time the reading was taken
long Reading::getTimestamp() const
{
    return timestamp;
}

// Task: T2 Start Workout, T6 Statistics, T7 Heart Rate Zones, T8 Alerts
// Returns the heart rate
int Reading::getBPM() const
{
    return bpm;
}

// Task: T2 Start Workout, T3 View Latest Readings
// Shows the reading on screen
void Reading::print() const
{
    cout << timestamp << " " << bpm << " bpm" << endl;
}