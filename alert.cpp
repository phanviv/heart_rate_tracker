#include <iostream>
#include "alert.h"
using namespace std;

AlertSystem::AlertSystem() {
    lowLimit = 0;
    highLimit = 0;
}

void AlertSystem::setLimits(int low, int high) {
    cout << "Not implemented yet" << endl;
}

bool AlertSystem::isAlert(Reading r) const {
    cout << "Not implemented yet" << endl;
    return false;
}

void AlertSystem::printAlerts(const ReadingLog& log) const {
    cout << "Not implemented yet" << endl;
}
