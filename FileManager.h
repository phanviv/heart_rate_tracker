#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include <string>
#include "ProfileManager.h"
#include "Workout.h"

// Saves and loads all data. It is the only class that reads or writes files.
// File formats are described in docs/iteration02-system-design/README.md (section 5).
class FileManager
{
private:
	std::string dataFile;	  // profiles, workouts, readings
	std::string settingsFile; // default and per-profile settings
	std::string backupFile;	  // the workout in progress

public:
	// Uses heart_data.txt, settings.txt and workout_backup.txt
	FileManager();
	FileManager(std::string dataFile, std::string settingsFile, std::string backupFile);

	// Rewrites the data file with every profile, workout and reading.
	// Returns false if the file could not be written (the old file is kept).
	bool save(const ProfileManager &profiles) const;

	// Replaces everything in `profiles` with the contents of the data file.
	// A missing file means no profiles yet. Whoever was signed in stays signed
	// in if their profile still exists. Lines that can't be read are skipped
	// with a warning, and the function then returns false.
	bool load(ProfileManager &profiles) const;

	// Overwrites the backup file with the workout so far. The end time
	// written is the time of this backup.
	bool saveBackup(const std::string &profileName, const Workout &workout) const;

	bool hasBackup() const;

	// Reads the backup file into profileName and workout. Returns false
	// (and leaves both unchanged) if the file is missing or unreadable.
	bool loadBackup(std::string &profileName, Workout &workout) const;

	// Returns true if the backup file is gone afterwards.
	bool deleteBackup() const;
};
#endif
