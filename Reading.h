// Reading.h
// Author: Vivian Phan
// Declares Reading: one heart rate reading (the time it was taken and the
// BPM), kept private so nothing outside the class can change them directly.

#ifndef READING_H
#define READING_H

class Reading
{

private:
    long timestamp;
    int bpm;

public:
    Reading(long timestamp = 0, int bpm = 0);
    long getTimestamp() const;
    int getBPM() const;
    void print() const;
};

#endif