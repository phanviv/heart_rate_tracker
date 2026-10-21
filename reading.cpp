#include <iostream>
#include "reading.h"
using namespace std;

Reading::Reading(int t, int b, int a) {
    timeSec = t;
    bpm = b;
    activity = a;
}

int Reading::getTime() const { return timeSec; }
int Reading::getBpm() const { return bpm; }
int Reading::getActivity() const { return activity; }

void Reading::print() const {
    cout << "t=" << timeSec << "s  " << bpm << " BPM  ";
    if (activity == 1) cout << "Rest";
    else if (activity == 2) cout << "Walk";
    else cout << "Run";
    cout << "\n";
}
