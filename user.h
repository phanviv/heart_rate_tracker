#pragma once
#include <string>
using namespace std;

class UserProfile {
private:
    string name;
    int age;
    int restingHR;
public:
    UserProfile();
    void setProfile(string n, int a, int r);
    string getName() const;
    int getAge() const;
    int getRestingHR() const;
    int getMaxHR() const;               // 220 - age
    int getZoneNumber(int bpm) const;   // 0 to 5, using heart rate reserve (HRR)
    string getZoneName(int zone) const; // name of zone 0 to 5
    string getZone(int bpm) const;      // zone name for a BPM
    bool hasProfile() const;
    void print() const;
};
