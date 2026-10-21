#pragma once
#include "user.h"
#include "sensor.h"
#include "readinglog.h"

// tasks_data.cpp (Tasks 1 to 5)
void taskCreateProfile(UserProfile& user);
void taskRunWorkout(HeartRateSensor& sensor, ReadingLog& log);
void taskViewLatest(const ReadingLog& log);
void taskSave(const UserProfile& user, const ReadingLog& log);
void taskLoad(UserProfile& user, ReadingLog& log);

// tasks_analysis.cpp (Tasks 6 to 9)
void taskViewHistory(const ReadingLog& log);
void taskStatistics(const ReadingLog& log);
void taskZoneSummary(const UserProfile& user, const ReadingLog& log);
void taskAlerts(const UserProfile& user, const ReadingLog& log);
