#ifndef HEART_RATE_SENSOR_H
#define HEART_RATE_SENSOR_H
#include "ReadingLog.h"
#include "reading.h"

class HeartRateSensor
{
private:
	ReadingLog readings;
	bool running;
	long lastReadingTime;
	int intervalSeconds;
	int abnormalPercent;
	int lowLimit;
	int highLimit;
	int currentBpm;

public:
	configure(const UserProfile);
};
#endif