#include "FileManager.h"
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// ---------- Helpers ----------

// Reads one line and removes a trailing '\r' (files edited on Windows).
static bool readLine(istream &in, string &line)
{
	if (!getline(in, line))
		return false;
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);
	return true;
}

// Splits a line into exactly `count` fields. The last field gets the rest
// of the line, commas included, so names and activities can contain commas.
// Returns false if the line has too few commas.
static bool splitFields(const string &line, int count, vector<string> &fields)
{
	fields.clear();
	size_t start = 0;
	for (int i = 0; i < count - 1; i++)
	{
		size_t comma = line.find(',', start);
		if (comma == string::npos)
			return false;
		fields.push_back(line.substr(start, comma - start));
		start = comma + 1;
	}
	fields.push_back(line.substr(start));
	return true;
}

static bool toLong(const string &text, long &value)
{
	if (text.empty())
		return false;
	char *end = NULL;
	errno = 0;
	long result = strtol(text.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE)
		return false;
	value = result;
	return true;
}

static bool toInt(const string &text, int &value)
{
	long result;
	if (!toLong(text, result) || result < INT_MIN || result > INT_MAX)
		return false;
	value = (int)result;
	return true;
}

// PROFILE,<age>,<restingHR>,<name>
// Adds the profile and signs in to it. Returns false for a bad line or a
// name that is already taken.
static bool parseProfile(const string &line, ProfileManager &profiles)
{
	vector<string> f;
	int age, restingHR;
	if (!splitFields(line, 4, f) || f[0] != "PROFILE" ||
		!toInt(f[1], age) || !toInt(f[2], restingHR))
		return false;
	return profiles.createProfile(f[3], age, restingHR);
}

// WORKOUT,<startTime>,<endTime>,<activeSeconds>,<activity>
static bool parseWorkout(const string &line, Workout &workout)
{
	vector<string> f;
	long start, end, active;
	if (!splitFields(line, 5, f) || f[0] != "WORKOUT" ||
		!toLong(f[1], start) || !toLong(f[2], end) ||
		!toLong(f[3], active) || active < 0)
		return false;

	workout = Workout(f[4], start);
	workout.setEndTime(end);
	workout.addActiveSeconds(active);
	return true;
}

// READING,<timestamp>,<bpm>
static bool parseReading(const string &line, Workout &workout)
{
	vector<string> f;
	long timestamp;
	int bpm;
	if (!splitFields(line, 3, f) || f[0] != "READING" ||
		!toLong(f[1], timestamp) || !toInt(f[2], bpm))
		return false;

	workout.addReading(Reading(timestamp, bpm));
	return true;
}

// Writes a WORKOUT line followed by its READING lines.
static void writeWorkout(ostream &out, const Workout &workout, long endTime)
{
	out << "WORKOUT," << workout.getStartTime() << ',' << endTime << ','
		<< workout.getDurationSeconds() << ',' << workout.getActivity() << '\n';

	vector<Reading> readings = workout.getReadings();
	for (size_t i = 0; i < readings.size(); i++)
		out << "READING," << readings[i].getTimestamp() << ','
			<< readings[i].getBPM() << '\n';
}

// Writes to a temporary file first, then swaps it in, so a crash while
// saving never leaves a half-written file behind.
static bool writeFileSafely(const string &path, const string &contents)
{
	string tempPath = path + ".tmp";
	{
		ofstream out(tempPath.c_str());
		if (!out)
			return false;
		out << contents;
		out.close();
		if (!out)
		{
			remove(tempPath.c_str());
			return false;
		}
	}

	if (rename(tempPath.c_str(), path.c_str()) != 0)
	{
		// Windows can't rename over an existing file, so remove it first
		remove(path.c_str());
		if (rename(tempPath.c_str(), path.c_str()) != 0)
			return false;
	}
	return true;
}

// ---------- FileManager ----------

FileManager::FileManager()
	: dataFile("heart_data.txt"),
	  settingsFile("settings.txt"),
	  backupFile("workout_backup.txt")
{
}

FileManager::FileManager(string dataFile, string settingsFile, string backupFile)
	: dataFile(dataFile), settingsFile(settingsFile), backupFile(backupFile)
{
}

bool FileManager::save(const ProfileManager &profiles) const
{
	ostringstream out;
	const vector<UserProfile> &list = profiles.getProfiles();

	for (size_t i = 0; i < list.size(); i++)
	{
		const UserProfile &profile = list[i];
		out << "PROFILE," << profile.getAge() << ',' << profile.getRestingHR()
			<< ',' << profile.getName() << '\n';

		vector<Workout> workouts = profile.getWorkouts();
		for (size_t j = 0; j < workouts.size(); j++)
			writeWorkout(out, workouts[j], workouts[j].getEndTime());
	}

	// TODO write the [default] and per-profile sections of settingsFile
	//      once the Settings class exists.

	return writeFileSafely(dataFile, out.str());
}

bool FileManager::load(ProfileManager &profiles) const
{
	// Remember who was signed in, to sign them back in afterwards
	string signedIn = profiles.hasCurrent() ? profiles.getCurrent().getName() : "";

	profiles.clear();

	int skipped = 0;
	int firstSkipped = 0;

	ifstream in(dataFile.c_str());
	if (in) // a missing data file just means no profiles yet
	{
		string line;
		int lineNumber = 0;
		bool inProfile = false; // the last PROFILE line was added (it is the current profile)
		bool inWorkout = false; // `workout` holds a workout that still needs adding
		Workout workout;

		while (readLine(in, line))
		{
			lineNumber++;
			if (line.empty() || line[0] == '#')
				continue;

			string tag = line.substr(0, line.find(','));
			bool ok;

			if (tag == "PROFILE")
			{
				if (inWorkout)
					profiles.getCurrent().addWorkout(workout);
				inWorkout = false;
				inProfile = parseProfile(line, profiles);
				ok = inProfile;
			}
			else if (tag == "WORKOUT")
			{
				if (inWorkout)
					profiles.getCurrent().addWorkout(workout);
				inWorkout = inProfile && parseWorkout(line, workout);
				ok = inWorkout;
			}
			else if (tag == "READING")
			{
				ok = inWorkout && parseReading(line, workout);
			}
			else
			{
				ok = false;
			}

			if (!ok)
			{
				if (skipped == 0)
					firstSkipped = lineNumber;
				skipped++;
			}
		}

		if (inWorkout)
			profiles.getCurrent().addWorkout(workout);
	}

	// TODO read settingsFile once the Settings class exists. Profiles without
	//      a section, and missing keys, use the [default] values.

	// createProfile() signs in to each new profile, so sign out and then
	// sign back in to whoever was signed in before loading.
	profiles.signOut();
	const vector<UserProfile> &list = profiles.getProfiles();
	for (int i = 0; i < (int)list.size(); i++)
	{
		if (!signedIn.empty() && list[i].getName() == signedIn)
			profiles.selectProfile(i);
	}

	if (skipped > 0)
	{
		cerr << "Warning: skipped " << skipped << " line(s) of " << dataFile
			 << " that could not be read (first at line " << firstSkipped << ")." << endl;
		return false;
	}
	return true;
}

bool FileManager::saveBackup(const string &profileName, const Workout &workout) const
{
	ostringstream out;
	out << "BACKUP," << profileName << '\n';
	writeWorkout(out, workout, (long)time(NULL)); // end time = time of this backup
	return writeFileSafely(backupFile, out.str());
}

bool FileManager::hasBackup() const
{
	ifstream in(backupFile.c_str());
	return (bool)in;
}

bool FileManager::loadBackup(string &profileName, Workout &workout) const
{
	ifstream in(backupFile.c_str());
	if (!in)
		return false;

	// BACKUP,<profile name>
	string line;
	vector<string> f;
	if (!readLine(in, line) || !splitFields(line, 2, f) || f[0] != "BACKUP")
		return false;
	string name = f[1];

	// WORKOUT,... followed by READING,... lines
	Workout loaded;
	if (!readLine(in, line) || !parseWorkout(line, loaded))
		return false;

	while (readLine(in, line))
	{
		// Skip bad reading lines instead of losing the whole workout
		if (!line.empty())
			parseReading(line, loaded);
	}

	profileName = name;
	workout = loaded;
	return true;
}

bool FileManager::deleteBackup() const
{
	return remove(backupFile.c_str()) == 0 || !hasBackup();
}
