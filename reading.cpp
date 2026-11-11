#include "reading.h"
#include <iostream>
using namespace std;

// Constructor: saves the time and bpm when a Reading is created
Reading::Reading(time_t t, int b)
{
    timestamp = t;
    bpm = b;
}

// Returns the time the reading was taken
time_t Reading::getTimestamp() const
{
    return timestamp;
}

// Returns the heart rate
int Reading::getBpm() const
{
    return bpm;
}

// Shows the reading on screen
void Reading::print() const
{
    cout << timestamp << " " << bpm << " bpm" << endl;
}