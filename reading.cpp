#include <iostream>
#include "reading.h"
using namespace std;

Reading::Reading(int t, int b, int a)
{
    timeSec = t;
    bpm = b;
    activity = a;
}

int Reading::getTime() const { return timeSec; }
int Reading::getBpm() const { return bpm; }
int Reading::getActivity() const { return activity; }

void Reading::print() const
{
    cout << "Not implemented yet" << endl;
}
