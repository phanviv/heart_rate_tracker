#include "ProfileManager.h"
#include <cctype>
#include <iostream>
using namespace std;

// Removes spaces, tabs and newlines from both ends.
static string trim(const string &s)
{
	size_t start = 0;
	while (start < s.size() && isspace((unsigned char)s[start]))
		start++;

	size_t end = s.size();
	while (end > start && isspace((unsigned char)s[end - 1]))
		end--;

	return s.substr(start, end - start);
}

// Trimmed, lower-case copy of a name, used to compare names.
static string normalize(const string &name)
{
	string result = trim(name);
	for (size_t i = 0; i < result.size(); i++)
		result[i] = tolower((unsigned char)result[i]);
	return result;
}

ProfileManager::ProfileManager() : currentIndex(-1)
{
}

int ProfileManager::findName(const string &name, int skipIndex) const
{
	string target = normalize(name);
	for (int i = 0; i < count(); i++)
	{
		if (i != skipIndex && normalize(profiles[i].getName()) == target)
			return i;
	}
	return -1;
}

bool ProfileManager::validIndex(int index) const
{
	return index >= 0 && index < count();
}

bool ProfileManager::createProfile(string name, int age, int restingHR)
{
	name = trim(name);
	if (name.empty() || nameExists(name))
		return false;

	UserProfile profile;
	profile.setProfile(name, age, restingHR);
	// TODO profile.setSettings(defaults);

	profiles.push_back(profile);
	currentIndex = count() - 1; // sign in to the new profile
	return true;
}

bool ProfileManager::renameProfile(int index, string newName)
{
	newName = trim(newName);
	if (!validIndex(index) || newName.empty())
		return false;

	// Skip this profile so it can change the case of its own name ("alex" -> "Alex")
	if (findName(newName, index) != -1)
		return false;

	profiles[index].setName(newName);
	return true;
}

bool ProfileManager::deleteProfile(int index)
{
	if (!validIndex(index))
		return false;

	profiles.erase(profiles.begin() + index);

	if (index == currentIndex)
		currentIndex = -1; // the signed-in profile was deleted
	else if (index < currentIndex)
		currentIndex--; // the signed-in profile moved down one place

	return true;
}

bool ProfileManager::nameExists(string name) const
{
	return findName(name) != -1;
}

bool ProfileManager::selectProfile(int index)
{
	if (!validIndex(index))
		return false;

	currentIndex = index;
	return true;
}

bool ProfileManager::hasCurrent() const
{
	return validIndex(currentIndex);
}

UserProfile &ProfileManager::getCurrent()
{
	return profiles[currentIndex];
}

int ProfileManager::getCurrentIndex() const
{
	return currentIndex;
}

const vector<UserProfile> &ProfileManager::getProfiles() const
{
	return profiles;
}

int ProfileManager::count() const
{
	return (int)profiles.size();
}

void ProfileManager::clear()
{
	profiles.clear();
	currentIndex = -1;
}

void ProfileManager::printList() const
{
	if (profiles.empty())
	{
		cout << "No profiles yet." << endl;
		return;
	}

	for (int i = 0; i < count(); i++)
	{
		cout << (i + 1) << ". " << profiles[i].getName()
			 << " (age " << profiles[i].getAge()
			 << ", resting HR " << profiles[i].getRestingHR() << ")";
		if (i == currentIndex)
			cout << "  <- signed in";
		cout << endl;
	}
}
