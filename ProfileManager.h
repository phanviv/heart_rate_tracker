#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H
#include <string>
using namespace std;

class ProfileManager
{
private:
	// TODO vector<UserProfile> profiles;
	int currentIndex = -1;
	// TODO Settings defaults;

public:
	bool createProfile(string name, int age, int restingHR);
	bool renameProfile(int index, string newName);
	bool deleteProfile(int index);
	bool nameExists(string name);
	bool selectProfile(int index);

	bool hasCurrent();
	bool getCurrent();
	bool getProfiles();
	int count();
};

#endif