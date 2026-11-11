#include "reading.h"
#include <iostream>
using namespace std;

// Constructor: saves the time and bpm when a Reading is created
Reading::Reading(long timestamp, int bpm) : timestamp(timestamp), bpm(bpm)
{
}

// Returns the time the reading was taken
time_t Reading::getTimestamp() const
{
    return timestamp;
}

// Returns the heart rate
int Reading::getBPM() const
{
    return bpm;
}

// Shows the reading on screen
void Reading::print() const
{
    cout << timestamp << " " << bpm << " bpm" << endl;
}