#include <iostream>
#include "user.h"
using namespace std;

UserProfile::UserProfile() {
    name = "";
    age = 0;
    restingHR = 0;
}

void UserProfile::setProfile(string n, int a, int r) {
    cout << "Not implemented yet" << endl;
}

string UserProfile::getName() const {
    cout << "Not implemented yet" << endl;
    return "";
}

int UserProfile::getAge() const {
    cout << "Not implemented yet" << endl;
    return 0;
}

int UserProfile::getRestingHR() const {
    cout << "Not implemented yet" << endl;
    return 0;
}

int UserProfile::getMaxHR() const {
    cout << "Not implemented yet" << endl;
    return 0;
}

bool UserProfile::hasProfile() const {
    cout << "Not implemented yet" << endl;
    return false;
}

int UserProfile::getZoneNumber(int bpm) const {
    cout << "Not implemented yet" << endl;
    return 0;
}

string UserProfile::getZone(int bpm) const {
    cout << "Not implemented yet" << endl;
    return "";
}

string UserProfile::getZoneName(int zone) const {
    cout << "Not implemented yet" << endl;
    return "";
}

void UserProfile::print() const {
    cout << "Not implemented yet" << endl;
}
