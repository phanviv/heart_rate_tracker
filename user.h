#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <iostream>
#include <string>
#include <vector>
// TODO #include "Settings.h"
#include "Workout.h"

using namespace std;

class UserProfile
{
private:
    string name;
    int age;
    int restingHR;
    // TODO Settings settings;
    vector<Workout> workouts; // list of all user's workouts

public:
    UserProfile();

    void setProfile(string newName, int newAge, int newRestingHR);
    void setName(string newName);

    string getName() const;
    int getAge() const;
    int getRestingHR() const;
    int getMaxHR() const;
    int getZoneNumber(int bpm) const;
    string getZoneName(int zone) const;

    // TODO Settings getSettings();
    // TODO void setSettings(Settings newSettings);

    void addWorkout(Workout w);
    vector<Workout> getWorkouts();
    Workout getLatestWorkout();

    bool hasWorkouts() const;
    void print() const;
};

#endif
