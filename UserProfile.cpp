//Vivian Phan - Creating the useprofile using their name, age and resting HR

#include "UserProfile.h"
using namespace std;

UserProfile::UserProfile() : name(""), age(0), restingHR(0)
{
}

void UserProfile::setProfile(string newName, int newAge, int newRestingHR)
{
	name = newName;
	age = newAge;
	restingHR = newRestingHR;
}

void UserProfile::setName(string newName)
{
	name = newName;
}

string UserProfile::getName() const
{
	return name;
}

int UserProfile::getAge() const
{
	return age;
}

int UserProfile::getRestingHR() const
{
	return restingHR;
}

// Standard estimate: 220 minus age
int UserProfile::getMaxHR() const
{
	return 220 - age;
}

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

void UserProfile::addWorkout(Workout w)
{
	workouts.push_back(w);
}

vector<Workout> UserProfile::getWorkouts() const
{
	return workouts;
}

// Only call when hasWorkouts() is true
Workout UserProfile::getLatestWorkout()
{
	if (workouts.empty())
		return Workout();
	return workouts.back();
}

bool UserProfile::hasWorkouts() const
{
	return !workouts.empty();
}

void UserProfile::print() const
{
	cout << name << " (age " << age << ", resting HR " << restingHR << ")" << endl;
}