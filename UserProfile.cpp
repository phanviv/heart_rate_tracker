#include "UserProfile.h"

UserProfile::UserProfile() : name("Unnamed"), age(0), restingHR(0)
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

int UserProfile::getMaxHR() const
{
	return 220 - age;
}

int UserProfile::getZoneNumber(int bpm) const
{
	// Reliable comparison for integers
	// per <= 50, bpm/maxHr*100 <= 50, bpm*100<=50*maxHR
	int maxHR = getMaxHR();
	if (bpm * 100 <= maxHR * 50)
		return 0;
	else if (bpm * 100 <= maxHR * 60)
		return 1;
	else if (bpm * 100 <= maxHR * 70)
		return 2;
	else if (bpm * 100 <= maxHR * 80)
		return 3;
	else if (bpm * 100 <= maxHR * 90)
		return 4;
	else if (bpm * 100 <= maxHR * 100)
		return 5;
	else
		return 6;
}

string UserProfile::getZoneName(int zone) const
{
	switch (zone)
	{
	case 0:
		return "Below Zone 1";
	case 1:
		return "Warm-up / Recovery (low to moderate)";
	case 2:
		return "Aerobic / Endurance (moderate)";
	case 3:
		return "Tempo / Threshold (moderate to high)";
	case 4:
		return "Lactate threshold (high)";
	case 5:
		return "Anaerobic / Max effort (very high)";
	case 6:
		return "Above max";
	}

	return "NO ZONE FOUND - ERROR";
}

void UserProfile::addWorkout(Workout workout)
{
	workouts.push_back(workout);
}

const vector<Workout> &UserProfile::getWorkouts() const
{
	return workouts;
}

Workout UserProfile::getLatestWorkout() const
{
	if (hasWorkouts())
		return workouts.back();
	else
		return Workout();
}

bool UserProfile::hasWorkouts() const
{
	return workouts.size() > 0;
}

void UserProfile::print() const
{
	cout << "Name:       " << name << endl;
	cout << "Age:        " << age << endl;
	cout << "Resting HR: " << restingHR << " bpm" << endl;
	cout << "Max HR:     " << getMaxHR() << " bpm" << endl;
	cout << "Workouts:   " << workouts.size() << endl;

	if (hasWorkouts())
	{
		cout << endl
			 << "Latest workout:" << endl;
		getLatestWorkout().printSummary();
	}
}