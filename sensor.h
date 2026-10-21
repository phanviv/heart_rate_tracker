#pragma once
#include "readinglog.h"
#include <string>

const int SECONDS_PER_READING = 5;

class HeartRateSensor
{
private:
    ReadingLog readings; // readings from the current workout
    bool running;
    std::string activity; // 1 = Rest, 2 = Walk, 3 = Run
    int timeSec;

public:
    HeartRateSensor();
    void start(std::string activity);
    void stop();
    bool isRunning() const;
    Reading takeReading(); // simulates one heartbeat reading
    const ReadingLog &getReadings() const;
    double getAverageBPM() const;
    double getRecentAverageBPMFrom(float seconds) const;
    double getLastAverageBPM(int numberOfRecentReadings) const;
};
