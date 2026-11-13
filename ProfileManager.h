#ifndef PROFILE_MANAGER_H
#define PROFILE_MANAGER_H
#include "user.h"
// TODO #include "Settings.h"

// Holds every profile and tracks which one is signed in.
// Profile indexes are 0-based (printList() shows them as 1, 2, 3, ...).
class ProfileManager
{
private:
	std::vector<UserProfile> profiles;
	int currentIndex; // -1 when nobody is signed in
	// TODO Settings defaults; // given to new profiles

	// Index of the profile with this name (ignoring case and outer spaces),
	// skipping skipIndex. Returns -1 if there is none.
	int findName(const std::string &name, int skipIndex = -1) const;
	bool validIndex(int index) const;

public:
	ProfileManager();

	// Adds a profile and signs in to it.
	// Returns false if the name is empty or already taken.
	bool createProfile(std::string name, int age, int restingHR);

	// Returns false if the index is invalid, or the new name is empty or
	// taken by another profile.
	bool renameProfile(int index, std::string newName);

	// Removes the profile with its workouts. If it was the signed-in
	// profile, nobody is signed in afterwards. Returns false if the index is invalid.
	bool deleteProfile(int index);

	// Compares names ignoring upper/lower case and spaces at either end,
	// so "Alex" and "alex " count as the same name.
	bool nameExists(std::string name) const;

	// Switches to an existing profile. Returns false if the index is invalid.
	bool selectProfile(int index);

	bool hasCurrent() const;
	// Only call when hasCurrent() is true.
	UserProfile &getCurrent();
	int getCurrentIndex() const;

	const std::vector<UserProfile> &getProfiles() const;
	int count() const;

	// Removes every profile and signs out (used by FileManager::load).
	void clear();

	// TODO Settings getDefaults() const;
	// TODO void setDefaults(Settings newDefaults);

	void printList() const;
};
#endif
