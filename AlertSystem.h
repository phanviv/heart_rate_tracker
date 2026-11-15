#ifndef ALERT_SYSTEM_H
#define ALERT_SYSTEM_H
#include "user.h"
#include "reading.h"

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