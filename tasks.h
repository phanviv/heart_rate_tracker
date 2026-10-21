#pragma once
#include "user.h"
#include "sensor.h"
#include "readinglog.h"

// Member A
void taskCreateProfile(UserProfile& user);
void taskRunWorkout(HeartRateSensor& sensor, ReadingLog& log);
void taskViewLatest(const ReadingLog& log);
void taskViewHistory(const ReadingLog& log);

// Member B
void taskSave(const UserProfile& user, const ReadingLog& log);
void taskLoad(UserProfile& user, ReadingLog& log);
void taskStatistics(const ReadingLog& log);
void taskZoneSummary(const UserProfile& user, const ReadingLog& log);
void taskAlerts(const ReadingLog& log);
