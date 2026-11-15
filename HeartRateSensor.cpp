#include "HeartRateSensor.h"
#include <cstdlib>

// TODO: remove these once Settings exists and configure() reads from it
const int DEFAULT_INTERVAL_SECONDS = 5;
const int DEFAULT_ABNORMAL_PERCENT = 2;
const int DEFAULT_LOW_LIMIT = 40;

const int MAX_DRIFT = 3;		   // a normal reading moves at most this many BPM from the last one
const int MAX_ABNORMAL_OFFSET = 5; // an abnormal reading is 1 to this many BPM outside the limits

// Keeps a BPM value between the low and high limits
static int clampBpm(int bpm, int low, int high)
{
	if (bpm < low)
		return low;
	if (bpm > high)
		return high;
	return bpm;
}

// Returns a random whole number from min to max, including both
static int randomBetween(int min, int max)
{
	return min + rand() % (max - min + 1);
}

HeartRateSensor::HeartRateSensor()
	: running(false),
	  lastReadingTime(0),
	  intervalSeconds(DEFAULT_INTERVAL_SECONDS),
	  abnormalPercent(DEFAULT_ABNORMAL_PERCENT),
	  lowLimit(DEFAULT_LOW_LIMIT),
	  highLimit(190), // max HR of a 30-year-old until configure() is called
	  currentBpm(70)
{
	// seed the random numbers only once, even if several sensors are created
	static bool seeded = false;
	if (!seeded)
	{
		srand(static_cast<unsigned>(time(nullptr)));
		seeded = true;
	}
}

void HeartRateSensor::configure(const UserProfile &userProfile)
{
	// TODO: take these from userProfile.getSettings() once Settings exists:
	//   intervalSeconds = settings.getReadingInterval();
	//   abnormalPercent = settings.getAbnormalPercent();
	//   lowLimit = settings.getAlertLow();
	//   highLimit = settings.getAlertHigh(), or getMaxHR() when it is 0 ("max")
	intervalSeconds = DEFAULT_INTERVAL_SECONDS;
	abnormalPercent = DEFAULT_ABNORMAL_PERCENT;
	lowLimit = DEFAULT_LOW_LIMIT;
	highLimit = userProfile.getMaxHR();

	currentBpm = clampBpm(userProfile.getRestingHR(), lowLimit, highLimit);
}

void HeartRateSensor::start()
{
	readings.clear();
	lastReadingTime = 0; // so the first reading is due right away
	running = true;
}

void HeartRateSensor::resume(const ReadingLog &readingLog)
{
	readings = readingLog;
	lastReadingTime = 0;

	if (readings.size() > 0)
	{
		Reading last = readings.get(readings.size() - 1);
		// the last reading may have been abnormal, so bring it back between the limits
		currentBpm = clampBpm(last.getBPM(), lowLimit, highLimit);
		lastReadingTime = last.getTimestamp();
	}

	running = true;
}

void HeartRateSensor::stop()
{
	running = false;
}

bool HeartRateSensor::isRunning() const
{
	return running;
}

bool HeartRateSensor::isReadingDue() const
{
	if (!running)
		return false;
	return difftime(time(nullptr), lastReadingTime) >= intervalSeconds;
}

Reading HeartRateSensor::takeReading()
{
	time_t now = time(nullptr);
	int bpm;

	if (rand() % 100 < abnormalPercent)
	{
		// abnormal spike just outside the limits; currentBpm is left unchanged
		// so the next reading goes back to the normal drift
		int offset = randomBetween(1, MAX_ABNORMAL_OFFSET);
		if (rand() % 2 == 0)
			bpm = lowLimit - offset;
		else
			bpm = highLimit + offset;
	}
	else
	{
		// normal reading: drift a few BPM up or down, staying between the limits
		currentBpm = clampBpm(currentBpm + randomBetween(-MAX_DRIFT, MAX_DRIFT), lowLimit, highLimit);
		bpm = currentBpm;
	}

	Reading reading(now, bpm);
	readings.addReading(reading);
	lastReadingTime = now; // the next automatic reading comes a full interval later
	return reading;
}

void HeartRateSensor::clear()
{
	readings.clear();
	lastReadingTime = 0;
}

const ReadingLog &HeartRateSensor::getReadings() const
{
	return readings;
}

int HeartRateSensor::getAverageBPM() const
{
	return readings.avgBpm();
}

int HeartRateSensor::getRecentAverageBPMFrom(float seconds) const
{
	return readings.avgSince(static_cast<long>(seconds));
}

int HeartRateSensor::getLastAverageBPM(int numberOfRecentReadings) const
{
	return readings.avgLast(numberOfRecentReadings);
}
