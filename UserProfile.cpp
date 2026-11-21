// UserProfile.cpp
// Author: Vivian Phan
// Implements UserProfile: stores a user's name, age and resting HR, works out
// their max HR and heart rate zones, and keeps their list of workouts.

#include "UserProfile.h"
using namespace std;

// Task: T1 Manage Profiles
UserProfile::UserProfile() : name(""), age(0), restingHR(0)
{
}

// Task: T1 Manage Profiles
void UserProfile::setProfile(string newName, int newAge, int newRestingHR)
{
	name = newName;
	age = newAge;
	restingHR = newRestingHR;
}

// Task: T1 Manage Profiles
void UserProfile::setName(string newName)
{
	name = newName;
}

// Task: T1 Manage Profiles (used by every task)
string UserProfile::getName() const
{
	return name;
}

// Task: T1 Manage Profiles
int UserProfile::getAge() const
{
	return age;
}

// Task: T1 Manage Profiles, T2 Start Workout
int UserProfile::getRestingHR() const
{
	return restingHR;
}

// Task: T2 Start Workout, T7 Heart Rate Zones, T8 Alerts
// Standard estimate: 220 minus age
int UserProfile::getMaxHR() const
{
	return 220 - age;
}

// Task: T7 Heart Rate Zones
// Zone 0: under 50% of max HR
// Zone 1: 50-59%   Zone 2: 60-69%   Zone 3: 70-79%
// Zone 4: 80-89%   Zone 5: 90-100%
// Zone 6: above max HR
int UserProfile::getZoneNumber(int bpm) const
{
	int maxHR = getMaxHR();
	if (maxHR <= 0)
		return 0;

	if (bpm > maxHR)
		return 6;

	int percent = bpm * 100 / maxHR;
	if (percent < 50)
		return 0;
	if (percent >= 90)
		return 5;
	return percent / 10 - 4; // 50-59 -> 1, 60-69 -> 2, 70-79 -> 3, 80-89 -> 4
}

// Task: T7 Heart Rate Zones
string UserProfile::getZoneName(int zone) const
{
	switch (zone)
	{
	case 0: return "Resting";
	case 1: return "Very light";
	case 2: return "Light";
	case 3: return "Moderate";
	case 4: return "Hard";
	case 5: return "Maximum";
	case 6: return "Above max";
	default: return "Unknown";
	}
}

// Task: T2 Start Workout, T4 Load Data, T10 Startup Recovery
void UserProfile::addWorkout(Workout w)
{
	workouts.push_back(w);
}

// Task: T5 View Workout History, T6 Statistics, T7 Heart Rate Zones, T8 Alerts
vector<Workout> UserProfile::getWorkouts() const
{
	return workouts;
}

// Task: T3 View Latest Readings, T6 Statistics
// Only call when hasWorkouts() is true
Workout UserProfile::getLatestWorkout()
{
	if (workouts.empty())
		return Workout();
	return workouts.back();
}

// Task: T3 View Latest Readings, T6 Statistics, T8 Alerts
bool UserProfile::hasWorkouts() const
{
	return !workouts.empty();
}

// Task: T1 Manage Profiles
void UserProfile::print() const
{
	cout << name << " (age " << age << ", resting HR " << restingHR << ")" << endl;
}
