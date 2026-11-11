#ifndef READING_H
#define READING_H

class Reading
{

private:
    long timestamp;
    int bpm;

public:
    Reading(long timestamp, int bpm);
    long getTimestamp() const;
    int getBPM() const;
    void print() const;
};

#endif