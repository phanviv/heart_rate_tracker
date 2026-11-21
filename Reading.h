//Vivian Phan: declares the class, with the two valyes private so nothing outside can change them directly

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