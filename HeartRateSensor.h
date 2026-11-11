#ifndef HEART_RATE_SENSOR_H
#define HEART_RATE_SENSOR_H
#include <ctime>
#include "ReadingLog.h"
#include "reading.h"
#include "user.h"

// Produces heart rate readings in real time. For now the BPM values are
// simulated; later they could come from a data file or a real sensor
// without changing the rest of the system.
class HeartRateSensor
{
private:
	ReadingLog readings; // the current workout's readings
	bool running;
	time_t lastReadingTime;
	int intervalSeconds;
	int abnormalPercent;
	int lowLimit;
	int highLimit;
	int currentBpm; // the simulator's last normal value

public:
	HeartRateSensor();

	// takes the interval, abnormal chance, and limits from the profile's
	// settings, and the starting BPM from its resting HR
	void configure(const UserProfile &userProfile);

	void start();							   // clears the log and starts the sensor
	void resume(const ReadingLog &readingLog); // starts with the readings of a recovered workout;
											   // the simulation continues from the last reading's BPM
	void stop();
	bool isRunning() const;

	bool isReadingDue() const; // true when the interval has passed since the last reading
	Reading takeReading();	   // creates a Reading with the current time and a BPM value,
							   // adds it to the log, and returns it

	void clear(); // empties the log (used when the signed-in profile changes)
	const ReadingLog &getReadings() const;

	int getAverageBPM() const;
	int getRecentAverageBPMFrom(float seconds) const;		 // average over the last seconds of real time
	int getLastAverageBPM(int numberOfRecentReadings) const; // average of the last n readings
};
#endif
