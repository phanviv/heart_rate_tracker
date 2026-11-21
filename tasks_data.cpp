//Vivian Phan - menu tasks that change/load data profiles



#include "tasks.h"
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// TODO: remove once Settings exists; use profile.getSettings().getBackupInterval()
static const int BACKUP_INTERVAL_SECONDS = 30;

// ---------- Input helpers ----------

// Reads a whole line. If the input is closed (Ctrl+D / Ctrl+Z), exits
// instead of looping forever.
static string readText(const string &prompt)
{
	string line;
	cout << prompt;
	if (!getline(cin, line))
	{
		cout << "\nInput closed. Exiting." << endl;
		exit(0);
	}
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1);
	return line;
}

static string trimText(const string &s)
{
	size_t start = 0;
	while (start < s.size() && isspace((unsigned char)s[start]))
		start++;
	size_t end = s.size();
	while (end > start && isspace((unsigned char)s[end - 1]))
		end--;
	return s.substr(start, end - start);
}

// Asks until the user types a whole number between min and max.
int readInt(const string &prompt, int min, int max)
{
	while (true)
	{
		string line = trimText(readText(prompt));
		char *end = NULL;
		long value = strtol(line.c_str(), &end, 10);
		if (!line.empty() && *end == '\0' && value >= min && value <= max)
			return (int)value;
		cout << "Please enter a whole number from " << min << " to " << max << "." << endl;
	}
}

static bool askYesNo(const string &prompt)
{
	while (true)
	{
		string answer = trimText(readText(prompt + " (y/n): "));
		if (answer == "y" || answer == "Y")
			return true;
		if (answer == "n" || answer == "N")
			return false;
		cout << "Please type y or n." << endl;
	}
}

static string formatTime(time_t t)
{
	char text[20];
	strftime(text, sizeof(text), "%Y-%m-%d %H:%M", localtime(&t));
	return text;
}

// ---------- Other helpers ----------

bool requireProfile(const ProfileManager &profiles)
{
	if (!profiles.hasCurrent())
	{
		cout << "Nobody is signed in. Use option 1 to create or select a profile." << endl;
		return false;
	}
	return true;
}

// Lists the profiles and asks for one. Returns its 0-based index, or -1 if
// there are no profiles or the user cancels.
static int chooseProfile(const ProfileManager &profiles, const string &action)
{
	if (profiles.count() == 0)
	{
		cout << "No profiles yet." << endl;
		return -1;
	}
	profiles.printList();
	int choice = readInt(action + " which profile? (0 to cancel): ", 0, profiles.count());
	return choice - 1;
}

static void saveOrWarn(const ProfileManager &profiles, const FileManager &files)
{
	if (!files.save(profiles))
		cout << "Warning: could not save the data file." << endl;
}

// Builds a Workout from a list of readings.
static Workout buildWorkout(const string &activity, time_t startTime, time_t endTime,
							long activeSeconds, const vector<Reading> &readings)
{
	Workout w(activity, (long)startTime);
	w.setEndTime(endTime);
	w.addActiveSeconds(activeSeconds);
	for (size_t i = 0; i < readings.size(); i++)
		w.addReading(readings[i]);
	return w;
}

// ---------- Workout loop ----------

// Runs the workout loop for the current profile. For a recovered workout,
// pass the old readings in `previous` and the old active time in priorActive.
static void runWorkoutLoop(ProfileManager &profiles, FileManager &files,
						   HeartRateSensor &sensor, AlertSystem &alerts,
						   const string &activity, time_t workoutStart, int minutes,
						   long priorActive, const ReadingLog *previous)
{
	UserProfile &profile = profiles.getCurrent();

	sensor.configure(profile);
	alerts.setLimitsFor(profile, 0); // 0 = use the profile's max HR as the high limit
	if (previous != NULL)
		sensor.resume(*previous);
	else
		sensor.start();

	time_t loopStart = time(NULL);
	time_t endTime = loopStart + (time_t)minutes * 60;
	time_t lastBackup = loopStart;

	cout << "Workout started: " << activity << " for " << minutes << " minute(s)." << endl;
	cout << "Readings are taken automatically. Press Ctrl+C to stop early." << endl;

	while (time(NULL) < endTime)
	{
		if (sensor.isReadingDue())
		{
			Reading reading = sensor.takeReading();
			reading.print();
			if (alerts.isAlert(reading))
				cout << "  *** ALERT: " << reading.getBPM() << " bpm is outside the safe limits ***" << endl;
		}

		time_t now = time(NULL);
		if (difftime(now, lastBackup) >= BACKUP_INTERVAL_SECONDS)
		{
			Workout partial = buildWorkout(activity, workoutStart, now,
										   priorActive + (long)(now - loopStart),
										   sensor.getReadings().getReadings());
			files.saveBackup(profile.getName(), partial);
			lastBackup = now;
		}

		this_thread::sleep_for(chrono::milliseconds(50)); // don't use 100% CPU
	}
	sensor.stop();

	time_t finish = time(NULL);
	Workout finished = buildWorkout(activity, workoutStart, finish,
									priorActive + (long)(finish - loopStart),
									sensor.getReadings().getReadings());
	profile.addWorkout(finished);

	// Delete the backup only after the workout is safely in the data file
	if (files.save(profiles))
		files.deleteBackup();
	else
		cout << "Warning: could not save the data file. The backup was kept." << endl;

	cout << endl << "Workout finished." << endl;
	finished.printSummary();
	cout << "Average BPM:             " << sensor.getAverageBPM() << endl;
	cout << "Average, last 30 sec:    " << sensor.getRecentAverageBPMFrom(30) << endl;
	cout << "Average, last 5 readings: " << sensor.getLastAverageBPM(5) << endl;
}

// ---------- Task 1: manage profiles ----------

void taskManageProfiles(ProfileManager &profiles, FileManager &files, HeartRateSensor &sensor)
{
	while (true)
	{
		cout << endl << "--- Profiles ---" << endl;
		profiles.printList();
		cout << "1. Create profile" << endl
			 << "2. Switch profile" << endl
			 << "3. Rename profile" << endl
			 << "4. Delete profile" << endl
			 << "0. Back" << endl;

		int choice = readInt("Choice: ", 0, 4);

		if (choice == 0)
			return;

		if (choice == 1)
		{
			string name;
			while (true)
			{
				name = trimText(readText("Name (blank to cancel): "));
				if (name.empty())
					break;
				if (!profiles.nameExists(name))
					break;
				cout << "That name is already taken." << endl;
			}
			if (name.empty())
				continue;

			int age = readInt("Age: ", 1, 120);
			int restingHR = readInt("Resting HR: ", 20, 250);
			if (profiles.createProfile(name, age, restingHR))
			{
				sensor.clear();
				saveOrWarn(profiles, files);
				cout << "Created and signed in to " << name << "." << endl;
			}
			else
				cout << "Could not create the profile." << endl;
		}
		else if (choice == 2)
		{
			int index = chooseProfile(profiles, "Switch to");
			if (index >= 0 && profiles.selectProfile(index))
			{
				sensor.clear(); // no readings carry over between profiles
				cout << "Signed in to " << profiles.getCurrent().getName() << "." << endl;
			}
		}
		else if (choice == 3)
		{
			int index = chooseProfile(profiles, "Rename");
			if (index < 0)
				continue;
			string newName = trimText(readText("New name: "));
			if (profiles.renameProfile(index, newName))
			{
				saveOrWarn(profiles, files);
				cout << "Renamed." << endl;
			}
			else
				cout << "Could not rename: the name is empty or already taken." << endl;
		}
		else // choice == 4
		{
			int index = chooseProfile(profiles, "Delete");
			if (index < 0)
				continue;
			string name = profiles.getProfiles()[index].getName();
			if (!askYesNo("Delete " + name + " and all of their workouts? This cannot be undone"))
			{
				cout << "Cancelled." << endl;
				continue;
			}
			if (profiles.deleteProfile(index))
			{
				sensor.clear();
				saveOrWarn(profiles, files);
				cout << "Deleted " << name << "." << endl;
				if (!profiles.hasCurrent())
					cout << "Nobody is signed in now." << endl;
			}
		}
	}
}

// ---------- Task 2: start workout ----------

void taskRunWorkout(ProfileManager &profiles, FileManager &files,
					HeartRateSensor &sensor, AlertSystem &alerts)
{
	if (!requireProfile(profiles))
		return;

	string activity;
	while (activity.empty())
	{
		activity = trimText(readText("Activity (e.g. Run, Swim): "));
		if (activity.empty())
			cout << "Please type an activity." << endl;
	}
	int minutes = readInt("Length in minutes: ", 1, 1440);

	sensor.clear(); // start() clears too, but be explicit
	runWorkoutLoop(profiles, files, sensor, alerts, activity, time(NULL), minutes, 0, NULL);
}

// ---------- Task 3: view latest readings ----------

void taskViewLatest(ProfileManager &profiles)
{
	if (!requireProfile(profiles))
		return;

	UserProfile &profile = profiles.getCurrent();
	if (!profile.hasWorkouts())
	{
		cout << "No workouts yet for " << profile.getName() << "." << endl;
		return;
	}

	Workout latest = profile.getLatestWorkout();
	cout << "Latest workout: " << latest.getActivity() << " on "
		 << formatTime(latest.getStartTime()) << endl;

	ReadingLog log;
	vector<Reading> readings = latest.getReadings();
	for (size_t i = 0; i < readings.size(); i++)
		log.addReading(readings[i]);
	log.printLast(10);
}

// ---------- Task 4: load data ----------

void taskLoad(ProfileManager &profiles, FileManager &files, HeartRateSensor &sensor)
{
	bool ok = files.load(profiles);
	sensor.clear();
	cout << "Loaded " << profiles.count() << " profile(s)";
	if (!ok)
		cout << " (some lines were skipped, see the warning above)";
	cout << "." << endl;
}

// ---------- Recovering an unfinished workout ----------

void recoverWorkout(ProfileManager &profiles, FileManager &files,
					HeartRateSensor &sensor, AlertSystem &alerts)
{
	if (!files.hasBackup())
		return;

	string name;
	Workout saved;
	if (!files.loadBackup(name, saved))
	{
		cout << "A workout backup file exists but could not be read." << endl;
		if (askYesNo("Delete it?"))
			files.deleteBackup();
		return;
	}

	// Find the profile the workout belongs to
	int index = -1;
	for (int i = 0; i < profiles.count(); i++)
	{
		if (profiles.getProfiles()[i].getName() == name)
			index = i;
	}

	// Already saved before the program stopped: the backup is out of date
	if (index >= 0)
	{
		vector<Workout> history = profiles.getProfiles()[index].getWorkouts();
		for (size_t i = 0; i < history.size(); i++)
		{
			if (history[i].getStartTime() == saved.getStartTime())
			{
				files.deleteBackup();
				return;
			}
		}
	}

	vector<Reading> readings = saved.getReadings();
	cout << endl << "An unfinished workout was found:" << endl;
	cout << "  Profile: " << name << "   Activity: " << saved.getActivity() << endl;
	cout << "  Started: " << formatTime(saved.getStartTime())
		 << "   Readings: " << readings.size();
		if (!readings.empty())
	{
		time_t last = readings.back().getTimestamp();
		char timeText[10];
		strftime(timeText, sizeof(timeText), "%H:%M", localtime(&last));
		cout << " (last at " << timeText << ")";
	}
	cout << endl;

	// Without its profile the workout can't be continued or saved
	if (index < 0)
	{
		cout << "The profile \"" << name << "\" no longer exists, so this workout cannot be recovered." << endl;
		if (askYesNo("Delete the backup?"))
			files.deleteBackup();
		return;
	}

	cout << "1. Continue the workout" << endl
		 << "2. Save it as it is" << endl
		 << "3. Discard it" << endl
		 << "0. Decide later" << endl;
	int choice = readInt("Choice: ", 0, 3);

	if (choice == 0)
		return; // the backup stays for the next start-up

	if (choice == 3)
	{
		if (askYesNo("Discard this workout? This cannot be undone"))
			files.deleteBackup();
		return;
	}

	profiles.selectProfile(index);
	sensor.clear();

	if (choice == 2)
	{
		profiles.getCurrent().addWorkout(saved);
		if (files.save(profiles))
		{
			files.deleteBackup();
			cout << "Workout saved." << endl;
		}
		else
			cout << "Warning: could not save the data file. The backup was kept." << endl;
		return;
	}

	// choice == 1: continue with the old readings and active time
	ReadingLog previous;
	for (size_t i = 0; i < readings.size(); i++)
		previous.addReading(readings[i]);

	int minutes = readInt("How many more minutes? ", 1, 1440);
	runWorkoutLoop(profiles, files, sensor, alerts, saved.getActivity(),
				   saved.getStartTime(), minutes, saved.getDurationSeconds(), &previous);
}