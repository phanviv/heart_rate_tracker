// AlertSystem.h
// Author: Kai Hong
// Declares AlertSystem, which holds the low/high BPM limits for a profile and
// flags readings outside them (T2 Start Workout, T8 Alerts).

#ifndef ALERT_SYSTEM_H
#define ALERT_SYSTEM_H
#include "UserProfile.h"
#include "Reading.h"
#include "ReadingLog.h"

class AlertSystem
{
private:
	int lowLimit;
	int highLimit;

public:
	void setLimitsFor(const UserProfile &, int maxHR);

	bool isAlert(Reading reading) const;

	void printAlerts(const ReadingLog &) const;
};
#endif