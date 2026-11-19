#ifndef TASKS_H
#define TASKS_H

#include "ProfileManager.h"
#include "FileManager.h"
#include "HeartRateSensor.h"
#include "AlertSystem.h"

// Each task is called from one case of the switch in main().
// All objects are created in main() and passed in by reference.

// ---- Data tasks (task_data.cpp) ----
void taskManageProfiles(ProfileManager &profiles, FileManager &files, HeartRateSensor &sensor); // 1
void taskRunWorkout(ProfileManager &profiles, FileManager &files,
					HeartRateSensor &sensor, AlertSystem &alerts);					  // 2
void taskViewLatest(ProfileManager &profiles);										  // 3
void taskLoad(ProfileManager &profiles, FileManager &files, HeartRateSensor &sensor); // 4

// Called once from main() after the data is loaded at start-up. Does nothing
// when there is no backup file; otherwise offers to continue, save or discard.
void recoverWorkout(ProfileManager &profiles, FileManager &files,
					HeartRateSensor &sensor, AlertSystem &alerts);

// Asks until the user types a whole number from min to max (also used by main()).
int readInt(const std::string &prompt, int min, int max);

// Prints a message and returns false when nobody is signed in.
bool requireProfile(const ProfileManager &profiles);

// ---- Analysis tasks (task_analysis.cpp) ----
void taskViewHistory(ProfileManager &profiles);					// 5
void taskStatistics(ProfileManager &profiles);					// 6
void taskZoneSummary(ProfileManager &profiles);					// 7
void taskAlerts(ProfileManager &profiles, AlertSystem &alerts); // 8

#endif